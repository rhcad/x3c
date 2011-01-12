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

#pragma once
#include "BaseTest.h"

#include "Ix_ObjectFactory.h"
#include "Ix_PluginLoader.h"

class TestPluginManager : public BaseTest
{
    CPPUNIT_TEST_SUITE( TestPluginManager );
    CPPUNIT_TEST( testLoadUnloadPlugin );
    CPPUNIT_TEST( testLoadUnloadPlugins );
    CPPUNIT_TEST( testLoadPluginFiles );
    CPPUNIT_TEST( testInitializePlugins );
    CPPUNIT_TEST( testRegisterPlugin );

    CPPUNIT_TEST( testCreateObject );
    CPPUNIT_TEST( testIsCreatorRegister );
    CPPUNIT_TEST( testCreateSpecialInterfaceObjects );
    CPPUNIT_TEST( testQuerySpecialInterfaceObject );
    CPPUNIT_TEST( testHasCreatorReplaced );
    CPPUNIT_TEST_SUITE_END();

public:
    TestPluginManager(void);
    ~TestPluginManager(void);

    virtual void setUp();
    virtual void tearDown();

public:
    void testLoadUnloadPlugin();
    void testLoadUnloadPlugins();
    void testLoadPluginFiles();
    void testInitializePlugins();
    void testRegisterPlugin();

    void testCreateObject();
    void testIsCreatorRegister();
    void testCreateSpecialInterfaceObjects();
    void testQuerySpecialInterfaceObject();
    void testHasCreatorReplaced();

private:
    Ix_PluginLoader* GetManagerLoader(void);
    Ix_ObjectFactory* GetManagerObjectFactory(void);

    long GetPluginsNum(const wchar_t* path, const wchar_t* ext = L".plugin.dll", bool recursive = true);
};
