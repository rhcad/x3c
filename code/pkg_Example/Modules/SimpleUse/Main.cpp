#include <UtilFunc/PluginInc.h>

#define USE_ONE_PLUGIN
#include <PluginManager/XComCreator.h>
#include <UtilFunc/LoadDllHelper.h>

extern HMODULE g_hPluginDll;    // see XComCreator.h

static void Test();

#if defined(_MSC_VER) && defined(UNICODE)
#define main wmain
#endif

int main()
{
    LoadDllHelper dll (NULL, &g_hPluginDll);

    if (dll.Load(L"../Plugins/Win32DllTempl.plugin" PLNEXT))
    {
        Test();
    }
    if (dll.Load( L"../Plugins/MFCExtTempl.plugin" PLNEXT))
    {
        Test();
    }

    return 0;
}

#include <Ix_Example.h>

void MyFunc2(const Cx_Ptr& obj)
{
    long value = 0;

    // Cx_Interface与Cx_Ptr互转，转为特定接口
    Cx_Interface<Ix_Example> pIFExample(obj);
    if (pIFExample)
    {
        pIFExample->Foo(value);
        printf("value: %ld\n", value);
    }
}

static void Test()
{
    long value = 0;

    // 使用类ID和接口创建对象
    Cx_Interface<Ix_Example> pIFExample(CLSID_Example);
    if (pIFExample)
    {
        pIFExample->Foo(value);    // 调用接口函数
        printf("value: %ld\n", value);
    }

    // 转换为其他接口
    Cx_Interface<Ix_Example2> pIFExample2(pIFExample);
    if (pIFExample2.IsNotNull())
    {
        pIFExample2->Foo2(value);
    }

    // 转为无接口类型的Cx_Ptr，可避免函数定义时必须包含其他接口文件
    MyFunc2(Cx_Ptr(pIFExample2));
}
