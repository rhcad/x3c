// x3c - C++ PluginFramework
#ifndef _X3_FILEUTILITY_TRANSSTEP_H
#define _X3_FILEUTILITY_TRANSSTEP_H

#include <Utility/Ix_FileUtility.h>

class CTransStep
{
public:
    CTransStep() {}
    virtual ~CTransStep() {}

    virtual bool DoStep() = 0;
};

class CTransDeleteFile : public CTransStep
{
public:
    CTransDeleteFile(const wchar_t* pszFileName, bool bRecycle)
        : m_wstrFileName(pszFileName), m_bRecycle(bRecycle)
    {
    }

    virtual bool DoStep()
    {
        return x3::FileUtility()->DeletePathFile(m_wstrFileName.c_str(), m_bRecycle);
    }

private:
    std::wstring    m_wstrFileName;
    bool            m_bRecycle;
};

class CTransRenameFile : public CTransStep
{
public:
    CTransRenameFile(const wchar_t* pszOldFile, const wchar_t* pszNewFile)
        : m_wstrOldFile(pszOldFile), m_wstrNewFile(pszNewFile)
    {
    }

    virtual bool DoStep()
    {
        return x3::FileUtility()->RenamePathFile(m_wstrOldFile.c_str(), m_wstrNewFile.c_str());
    }

private:
    std::wstring    m_wstrOldFile;
    std::wstring    m_wstrNewFile;
};

class CFileTransactions
{
public:
    static CFileTransactions& Instance()
    {
        static CFileTransactions obj;
        return obj;
    }

    ~CFileTransactions()
    {
        Clear();
    }

    bool IsRollbacking() const
    {
        return m_bRollbacking;
    }

    void AddStep(CTransStep* pCommitStep, CTransStep* pRollbackStep)
    {
        ASSERT(!m_bRollbacking);
        m_steps.push_back(StepPair(pCommitStep, pRollbackStep));
    }

    void EndTransaction(bool bCommit)
    {
        m_bRollbacking = (m_bRollbacking || !bCommit);

        if (!m_bRollbacking)
        {
            while (!m_steps.empty())
            {
                if (m_steps.back().first->DoStep())
                    m_steps.pop_back();
                else
                {
                    m_bRollbacking = true;
                    break;
                }
            }
        }

        if (m_bRollbacking)
        {
            std::vector<StepPair>::reverse_iterator it;
            for (it = m_steps.rbegin(); it != m_steps.rend(); it++)
            {
                if (!it->second->DoStep())
                {
                }
            }
        }

        Clear();
    }

    void Reset()
    {
        ASSERT(m_steps.empty());
        m_bRollbacking = false;
    }

protected:
    CFileTransactions() : m_bRollbacking(false)
    {
    }

    void Clear()
    {
        while (!m_steps.empty())
        {
            StepPair item = m_steps.back();
            m_steps.pop_back();
            delete item.first;
            delete item.second;
        }
    }

private:
    typedef std::pair<CTransStep*, CTransStep*> StepPair;
    std::vector<StepPair>   m_steps;
    bool                    m_bRollbacking;
};

#endif // _X3_FILEUTILITY_TRANSSTEP_H
