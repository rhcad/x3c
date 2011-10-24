// x3c - C++ PluginFramework
#ifndef _X3_UTILITY_FILETRANSACTION_H
#define _X3_UTILITY_FILETRANSACTION_H

#include <Utility/Ix_FileTransaction.h>

class Cx_FileTransaction : public Ix_FileTransaction
{
    X3BEGIN_CLASS_DECLARE(Cx_FileTransaction)
        X3DEFINE_INTERFACE_ENTRY(Ix_FileTransaction)
    X3END_CLASS_DECLARE()
protected:
    Cx_FileTransaction();
    virtual ~Cx_FileTransaction();

private:
    // From Ix_FileTransaction
    virtual void Rollback();
    virtual long GetLevel() const;
    virtual bool IsRollbacking() const;
    virtual bool DeletePathFile(const wchar_t* pszFileName, bool bRecycle = false);

private:
    long        m_lLevel;
};

#endif // _X3_UTILITY_FILETRANSACTION_H
