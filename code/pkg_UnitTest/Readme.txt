pkg_UnitTest: 单元测试工程，使用 cppunit_1_12_1

需要把cppunit对应的LIB和DLL放到 code\bin\vcxx\xxx\unittests 目录下。
方正内网中有各个版本的LIB和DLL: \\dampub\Tools\CodeCheck\C++\CppUnit\cppunit-1.12.1\lib\

单元测试数据的配置: 运行单元测试程序后会创建UnitTests.ini文件，
修改该配置文件的TestData键值为实际的单元测试数据文件路径。

TestCore: 插件框架内核部分的单元测试工程
