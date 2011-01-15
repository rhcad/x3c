// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef _X3_UTILITY_FILETRANSACTION_H
#define _X3_UTILITY_FILETRANSACTION_H

#include "Ix_FileTransaction.h"

class Cx_FileTransaction : public Ix_FileTransaction
{
public:
    Cx_FileTransaction();
    virtual ~Cx_FileTransaction();

public:
    // From Ix_FileTransaction
    virtual void Rollback();
    virtual long GetLevel() const;
    virtual bool IsRollbacking() const;
    virtual bool DeletePathFile(const wchar_t* pszFileName, bool bRecycle = false);

private:
    long        m_lLevel;
};

#endif // _X3_UTILITY_FILETRANSACTION_H
