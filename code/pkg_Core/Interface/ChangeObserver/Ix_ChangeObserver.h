/*! \file Ix_ChangeObserver.h
 *  \brief Define change observer interface: Ix_ChangeObserver
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_OBSERVER_ICHANGEOBSERVER_H_
#define X3_OBSERVER_ICHANGEOBSERVER_H_

class ChangeNotifyData;

//! Change observer interface
/*!
    \interface Ix_ChangeObserver
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class Ix_ChangeObserver
{
public:
    virtual ~Ix_ChangeObserver() {}

    //! Notification of a event.
    /*!
        \param data the event data, it is usually a local variable's address.
    */
    virtual void Update(ChangeNotifyData* data) = 0;
};

#endif // X3_OBSERVER_ICHANGEOBSERVER_H_
