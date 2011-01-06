MakePluginPerl: 自动生成插件工具

makePlugin_v0.3.pl: 生成插件的Perl脚本文件
config.ini:  配置文件
MFCExtTempl: 插件工程模板
Interface: 新生成接口文件的存放目录



**插件使用方法**

	1. 更改config.ini的配置选项，其中newplugin节的name选项表示生成插件的名称，project表示生成插件的VC++工程名。配置文件格式如下：
		 ;新建插件配置数据
	 	 [newplugin]
	  	 ; 插件名称
	  	 name=Test
	   
	  	 ; VC++工程名称
	  	 project=Test

	2. 执行脚本 makePlugin_v0.3.pl ，会在当前目录生成以新插件名称命名的目录，在Interface目录会生成相应的接口定义头文件。

	3. 将新生成的插件目录和接口文件分别拷贝到相应目录，即可编译和开发。



**Perl相关**

	Perl运行环境（Active Perl）: http://www.activestate.com/activeperl 
	Perl脚本转EXE文件（ActiveState PDK）: http://www.activestate.com/perl-dev-kit	
	依赖包（均来自CPAN）： File::Copy，Data::GUID，Config::IniFiles  
