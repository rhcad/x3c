/*! \file Ix_ChangeObserver.h
 *  \brief 定义改变通知观察者的接口 Ix_ChangeObserver
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_OBSERVER_ICHANGEOBSERVER_H_
#define X3_OBSERVER_ICHANGEOBSERVER_H_

class ChangeNotifyData;

//! 改变通知观察者的接口
/*!
    \interface Ix_ChangeObserver
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
interface Ix_ChangeObserver
{
    //! 改变的通知
    /*!
        \param data 通知参数，一般为一个局部变量的地址
    */
    virtual void Update(ChangeNotifyData* data) = 0;
};

#endif // X3_OBSERVER_ICHANGEOBSERVER_H_
