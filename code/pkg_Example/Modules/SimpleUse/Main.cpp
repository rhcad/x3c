#include <PluginInc.h>

#define USE_ONE_PLUGIN
#include <XComCreator.h>

extern HMODULE g_hPluginDll;    // 见 XComCreator.h

bool LoadPlugin(const wchar_t* filename);
void Test();

#if defined(_MSC_VER) && defined(UNICODE)
#define main wmain
#endif

int main()
{
    if (LoadPlugin( L"../Plugins/Win32DllTempl.plugin.dll") )
    {
        Test();

        FreeLibrary(g_hPluginDll);
        g_hPluginDll = NULL;
    }
    if (LoadPlugin( L"../Plugins/MFCExtTempl.plugin.dll") )
    {
        Test();

        FreeLibrary(g_hPluginDll);
        g_hPluginDll = NULL;
    }

    return 0;
}

bool LoadPlugin(const wchar_t* filename)
{
    g_hPluginDll = LoadLibraryW(filename);

    return g_hPluginDll != NULL;
}


#include <Ix_Example.h>

void MyFunc2(const Cx_Ptr& obj)
{
    // Cx_Interface与Cx_Ptr互转，转为特定接口
    Cx_Interface<Ix_Example> pIFExample(obj);
    if (pIFExample)
    {
        pIFExample->Foo();
    }
}

void Test()
{
    // 使用类ID和接口创建对象
    Cx_Interface<Ix_Example> pIFExample(CLSID_Example);
    if (pIFExample)
    {
        pIFExample->Foo();    // 调用接口函数
    }

    // 转换为其他接口
    Cx_Interface<Ix_Example2> pIFExample2(pIFExample);
    if (pIFExample2.IsNotNull())
    {
        pIFExample2->Foo2();
    }

    // 转为无接口类型的Cx_Ptr，可避免函数定义时必须包含其他接口文件
    MyFunc2(Cx_Ptr(pIFExample2));
}
