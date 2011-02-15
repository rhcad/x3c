// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/
// Changes:
// 2011.2.14, ooyg: Support MFC dialog application and console application.
//

#include "stdafx.h"
#ifdef _AFXDLL
#include <cppunit/ui/mfc/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

class CUnitTestsApp : public CWinApp
{
public:
    CUnitTestsApp()
    {
    }

    virtual BOOL InitInstance()
    {
        AfxOleInit();
        SetRegistryKey(_T("Founder\\UnitTests"));

        CppUnit::MfcUi::TestRunner runner;
        runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
        runner.run();

        return FALSE;
    }
};

CUnitTestsApp theApp;

#else   // Console application

int main(int argc, char** argv)
{
    // Get the top level suite from the registry
    CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);

    if ((argc > 1) && (strcmp(argv[1], "-x") == 0))
    {
        char filename[MAX_PATH];

        GetModuleFileNameA(NULL, filename, MAX_PATH);
        lstrcpyA(filename, PathFindFileNameA(filename));
        lstrcpyA(strrchr(filename, '.'), ".cppunit-result.xml");

        // Specify XML output and inform the test runner of this format
        std::ofstream outputFile(filename);
        runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), outputFile));
    }
    else
    {
        // Change the default outputter to a compiler error format outputter
        runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), CppUnit::stdCOut()));
    }

    // Run the test and return error code 1 if the one of test failed
	return runner.run() ? 0 : 1;
}

#endif  // _AFXDLL
