MakePluginPerl: a tool for automatic generation of X3C plugin 

makePlugin_v0.3.pl: Perl script
config.ini:  configuration file
MFCExtTempl: template of MFC VC++ project
Interface: directory for storing interface files(*.h)


**Usage
    1. Open the configuration file config.ini. Change some options in the section of newplugin. the "name" option is the name  of the plugin that will be generated, and "project" is the name of the new VC++ project. Configuration file format is as follows:
	 	 [newplugin]
	  	 ; Plugin name
	  	 name=Test
	   
	  	 ; VC++ project name
	  	 project=Test

	2. Run the script makePlugin_v0.3.pl or makePlugin_v0.3.exe. The exe file could be run independently without Perl runtime Environment. The new plugin will be generated in the current directory,the head files of interface will generated in the directory of Interface.

	3. Copy the new plugin directory and interface files to your module directory, you 'll be happy to use it. Thanks to CPAN.


**Things related to Perl

	Perl Win32 Runtime Enviroment(Active Perl): http://www.activestate.com/activeperl 
	Perl2EXE convertor(ActiveState PDK): http://www.activestate.com/perl-dev-kit	
    Dependent packages(All packages come from CPAN): File::Copy,Data::GUID,Config::IniFiles  



Bug reports are welcome.  Please use the SourceForge bug tracking
system at http://sourceforge.net/projects/x3c/develop.

Email to the current maintainers of MakePluginPerl may be sent to <think.hy@gmail.com>.

