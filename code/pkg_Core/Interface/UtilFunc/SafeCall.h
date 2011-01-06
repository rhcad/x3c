//! \file SafeCall.h
//! \brief 定义普通指针和智能指针的安全调用的宏和函数

#ifndef __APPCORE_SAFECALL_H
#define __APPCORE_SAFECALL_H

// Validate before call function of pointer, "v" is default return value
#ifndef SafeCall
#define SafeCall(p, f)							if (p) p->f
#define SafeCallIf(p, f, v)						((p) ? (p->f) : (v))
#define SafeCallWithReturn(p, f, v)				if (p) return p->f; else return (v);
#define WndSafeCall(p, f)						if (p && ::IsWindow(p->GetSafeHwnd())) p->f
#define WndSafeCallWithReturn(p, f, v)			if (p && ::IsWindow(p->GetSafeHwnd())) return p->f; else return (v);
#define InterfaceSafeCall(p, f)					if (p.IsNotNull()) p->f
#define InterfaceSafeCallIf(p, f, v)			(p.IsNotNull() ? (p->f) : (v))
#define InterfaceSafeCallWithReturn(p, f, v)	if (p.IsNotNull()) return p->f; else return (v);
#endif // SafeCall

#ifndef DeletePtrInContainer
#undef SafeDelete
#undef SafeDeleteArray

//! 删除指针对象
/*!
	\ingroup _GROUP_UTILFUNC
	\param p 指针对象，采用 new 申请的
*/
template<class T>
void SafeDelete(T*& p)
{
	if (p != NULL)
		delete p;
	p = NULL;
	*(&p) = NULL;
}

//! 删除指针数组对象
/*!
	\ingroup _GROUP_UTILFUNC
	\param p 指针数组对象，采用 new[] 申请的
*/
template<class T>
void SafeDeleteArray(T*& p)
{
	if (p != NULL)
		delete []p;
	p = NULL;
}

//! 删除容器内的所有指针元素
/*!
	\ingroup _GROUP_UTILFUNC
	\param container STL数组变量，例如" vector<int*> arr; "
*/
template<class CONTAINER>
void DeletePtrInContainer(CONTAINER& container)
{
	CONTAINER::iterator it = container.begin();
	for(; it != container.end(); ++it)
		SafeDelete(*it);
	container.resize(0);
}

#endif // DeletePtrInContainer

#endif // __APPCORE_SAFECALL_H
