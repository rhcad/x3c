#include "stdafx.h"
#include "DocObserverTest.h"

static CDocObserverTestOnRun* s_observer = NULL;

// 如果有本函数，则在插件加载时由插件管理器调用，可做注册等关键初始化操作
extern "C" __declspec(dllexport) bool InitializePlugin()
{
    s_observer = new CDocObserverTestOnRun;
    return true;
}

// 如果有本函数，则在插件卸载前由插件管理器调用，可做释放资源或注销操作
extern "C" __declspec(dllexport) void UninitializePlugin()
{
    delete s_observer;
}
