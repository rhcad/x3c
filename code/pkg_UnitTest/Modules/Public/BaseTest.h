// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

#ifndef X3_UNITTEST_BASETEST_H_
#define X3_UNITTEST_BASETEST_H_

class BaseTest : public CppUnit::TestFixture
{
protected:
    BaseTest();

    long LoadPlugins(const wchar_t* plugins, bool loadCore = true);
    void UnloadPlugins();
    std::wstring MakeDataPath(const wchar_t* folder, const wchar_t* file);

private:
    void MakeRootPath(wchar_t* path, const wchar_t* name);
};

#endif // X3_UNITTEST_BASETEST_H_
