/*! \file Cx_SimpleObject.h
 *  \brief 定义可直接实例化的简单模板类 Cx_SimpleObject
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_SIMPLEOBJECT_H_
#define X3_PLUGINIMPL_SIMPLEOBJECT_H_

#include "Cx_Object.h"
#include "XComPtr.h"

//! 可直接实例化的简单模板类
/*! 使用示例: \code
    Cx_Ptr MyFunc()
    {
        Cx_Ptr objRet;
        Cx_SimpleObject<Cx_MyInternal>* p = Cx_SimpleObject<Cx_MyInternal>::Create(objRet);

        p->Init();

        return objRet;
    }
    \endcode
    最好在 XBEGIN_DEFINE_MODULE 组件类列表中把该实现类登记上，
    这样就可以外部模块是否引用其对象，例如： \code
    XBEGIN_DEFINE_MODULE()
        XDEFINE_CLASSMAP_ENTRY(XCLSID(), Cx_MyInternal)
    XEND_DEFINE_MODULE()
    \endcode
    \ingroup _GROUP_PLUGIN_CORE2_
*/
template <class ClsType>
class Cx_SimpleObject : public Cx_Object<ClsType>
{
public:
    //! 创建一个对象，并由Cx_Ptr接管
    static Cx_SimpleObject<ClsType>* Create(Cx_Ptr& objOwner)
    {
        Cx_SimpleObject<ClsType>* p = new Cx_SimpleObject<ClsType>();
        objOwner.AttachInterface(p);
        return p;
    }
    
    //! 创建一个对象，并由Cx_Interface接管
    template <class IF_Type>
    static Cx_SimpleObject<ClsType>* Create(Cx_Interface<IF_Type>& pIFOwner)
    {
        Cx_SimpleObject<ClsType>* p = new Cx_SimpleObject<ClsType>();
        return pIFOwner.AttachInterface(static_cast<Ix_Object*>(p)) ? p : NULL;
    }

private:
    Cx_SimpleObject() {}
    Cx_SimpleObject(const Cx_SimpleObject&);
};

#endif // X3_PLUGINIMPL_SIMPLEOBJECT_H_
