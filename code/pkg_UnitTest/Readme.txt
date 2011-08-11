pkg_UnitTest: unittest projects, using cppunit 1.12.1.

Download cppunit files from one of these sites:
    http://sourceforge.net/projects/cppunit/files/cppunit/1.12.1/
    http://files.cnblogs.com/rhcad/cppunit-1.12.1-vc689&gcc.zip (fix for vc6 and gcc)
    \\dampub\Tools\CodeCheck\C++\CppUnit\cppunit-1.12.1  (Founder server)

Then copy 'include\cppunit' folder to 'pkg_UnitTest\Interface\cppunit\'.

Copy cppunit's LIBs and DLLs to folder 'code\bin\vcxx\xxx\tests'.

Running unittest application will create the config file 'UnitTests.ini'.
You can change TestData path in UnitTests.ini.
