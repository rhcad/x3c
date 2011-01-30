/*! \file Ix_ChangeManager.h
 *  \brief Define interface of change observer manager: Ix_ChangeManager
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_OBSERVER_ICHANGEMANAGER_H_
#define X3_OBSERVER_ICHANGEMANAGER_H_

#include "Ix_ChangeObserver.h"

const XCLSID CLSID_ChangeManager("34c6e7c0-fe4a-45a1-b227-3da06e08499f");

//! interface of change observer manager.
/*!
    \interface Ix_ChangeManager
    \ingroup _GROUP_CHANGE_OBSERVER_
    \see CLSID_ChangeManager
*/
interface Ix_ChangeManager
{
    //! Add a change observer.
    /*!
        \param type observer type interpreted by specific system.
        \param observer a observer to add.
    */
    virtual void RegisterObserver(const char* type, Ix_ChangeObserver* observer) = 0;

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
