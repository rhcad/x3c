/*! \file Ix_ChangeManager.h
 *  \brief Define interface of change observer manager: Ix_ChangeManager
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \version
 *      2010.10.22: First release.
 *      2011.02.08: Add parameter 'fromdll' in RegisterObserver.
 *      2011.06.30: Remove RTTI.
 */
#ifndef X3_OBSERVER_ICHANGEMANAGER_H_
#define X3_OBSERVER_ICHANGEMANAGER_H_

#include "Ix_ChangeObserver.h"

X3CLSID_DEFINE(CLSID_ChangeManager, "34c6e7c0-fe4a-45a1-b227-3da06e08499f");

//! interface of change observer manager.
/*!
    \interface Ix_ChangeManager
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see x3::CLSID_ChangeManager
*/
class Ix_ChangeManager : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_ChangeManager)

    //! Add a change observer.
    /*!
        \param type observer type interpreted by specific system.
        \param observer a observer to add.
        \param fromdll dll handle of the observer.
    */
    virtual void RegisterObserver(const char* type, 
        Ix_ChangeObserver* observer, HMODULE fromdll = NULL) = 0;

    //! Remove a change observer.
    /*!
        \param type observer type interpreted by specific system.
        \param observer a observer to remove.
    */
    virtual void UnRegisterObserver(const char* type, Ix_ChangeObserver* observer) = 0;

    //! Broadcast change event.
    /*!
        \param type observer type interpreted by specific system.
        \param data the event data, it is usually a local variable's address.
    */
    virtual void ChangeNotify(const char* type, ChangeNotifyData* data) = 0;
};

#endif // X3_OBSERVER_ICHANGEMANAGER_H_
