#include "stdafx.h"

// 有该函数时，在插件加载时由插件管理器调用，可做关键初始化操作
OUTAPI bool InitializePlugin()
{
    return true;
}

// 有该函数时，在插件卸载前由插件管理器调用，可做释放资源操作
OUTAPI void UninitializePlugin()
{
}
