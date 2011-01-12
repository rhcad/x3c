// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef X3_UNITTEST_BASETEST_H_
#define X3_UNITTEST_BASETEST_H_

const LPCWSTR PLUGINS_DIR = L"../Plugins";
interface Ix_PluginLoader;

//! 测试用例基类
class BaseTest : public CppUnit::TestFixture
{
protected:
    BaseTest();

    //! 加载插件
    /*!
        \param plugins 由插件的相对文件名组成，
            用逗号或空白字符分隔，例如“1.dll, 2.dll”；可为空
        \param loadCore 是否加载插件框架内核的插件(LogManager.plugin.dll等)
        \return 在plugins所指定的插件中，加载成功的插件个数
    */
    long LoadPlugins(const wchar_t* plugins, bool loadCore = true);

    //! 卸载所有插件
    void UnloadPlugins();

    //! 得到插件加载管理对象，可用于加载更多插件
    Ix_PluginLoader* GetPluginLoader();

    //! 形成测试数据的文件全名
    /*! 测试数据的根目录在 UnitTests.ini 中[Path]下的 TestData 键来指定。
        \param folder 子目录名，例如“Pdf”，为空则取为临时输出目录，
            该临时目录在 UnitTests.ini 中[Path]下的 Temp 键来指定。
        \param file 相对文件名，为空则返回目录全名
        \return 文件或目录的全名
    */
    std::wstring MakeDataPath(const wchar_t* folder, const wchar_t* file);

private:
    void MakeRootPath(wchar_t* path, const wchar_t* name);
};

#endif // X3_UNITTEST_BASETEST_H_
