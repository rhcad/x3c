#!/usr/bin/perl
####################################################################################
# Description: X3框架插件创建脚本
# Usage:          
# Creator:     Huangye
# Date:        2010.10.13 
#
# ChangeList:  1. 更改接口文件，替换GUID, 完成脚本的基本功能。  [Huangye 10/10/19]
#              2. 增加了对配置文件(config.h)的支持。            [Huangye 10/10/21]
#              3. 更改资源文件版本信息                          [Huangye 10/11/15]
####################################################################################
use strict;
use warnings;

# 用于拷贝目录: dircopy
# CPAN  http://search.cpan.org/~dmuey/File-Copy-Recursive-0.38/Recursive.pm
use File::Copy::Recursive qw(fcopy rcopy dircopy fmove rmove dirmove);

# 用于拷贝文件
use File::Copy;

# 用于定位目录
use Cwd;

# 用于生成GUID: Data::GUID->new
# http://search.cpan.org/~rjbs/Data-GUID-0.045/lib/Data/GUID.pm
use Data::GUID;


######################################################
# 读入配置文件(makePlugin.xml)
# http://search.cpan.org/~wadg/Config-IniFiles-2.38/IniFiles.pm
use Config::IniFiles;


my $cfg = new Config::IniFiles( -file => "config.ini",  
                                -allowcontinue => 1,        
                                -reloadwarn => 1,           
                                -nocase  => 1,);           

my $tmpPrjName = $cfg->val('exampleplugin','project'); 
my $tmpPluginName = $cfg->val('exampleplugin','name');

my $prjName = $cfg->val('newplugin','project');
my $pluginName = $cfg->val('newplugin','name'); 

my $FileDescription = $cfg->val('newplugin','FileDescription');
my $InternalName = $cfg->val('newplugin','InternalName');
my $OriginalFilename = $cfg->val('newplugin','OriginalFilename');
my $ProductName = $cfg->val('newplugin','ProductName');

chomp($prjName);
chomp($pluginName);
chomp($FileDescription);
chomp($InternalName);
chomp($OriginalFilename);
chomp($ProductName);

# Step1: 拷贝插件目录
######################################################
my $orig = $cfg->val('exampleplugin','plugindir');
my $interfaceDir = $cfg->val('exampleplugin','interfacedir');
chomp($orig);

dircopy($orig,$pluginName) or die "拷贝目录从$orig到$pluginName失败";

# Step2: 更改文件名与文件内容
######################################################
my $curdir = getcwd;
chdir($pluginName); # 定位到插件目录
# 处理Module
foreach my $file (glob "*")  { # 查找当前目录下所有文件
    print "$file\n";

    # 获取扩展名 
    my $extName = ($file =~ m/([^.]+)$/)[0];

    # 处理源代码与工程文件
    if ($extName =~ /vcproj|dsp|c|cxx|cpp|h|hpp|rc/i) { 
        open(FILE, $file)
            or warn "打开文件$file失败!\n";

        my @lines = <FILE>;
        close FILE;

        open(OUT, "> $file")
            or warn "打开文件$file失败!\n";

        foreach my $line (@lines) {
            # 替换插件名与工程名
            $line =~ s/$tmpPrjName/$prjName/g;
            $line =~ s/$tmpPluginName/$pluginName/g;
            print OUT $line; # 写回到原文件
        }


        close OUT;
    }

    my $newFile = $file;
    if ($file =~ /$tmpPrjName/g) # 替换工程名
    {
        $newFile =~ s/$tmpPrjName/$prjName/g; 
        rename $file, $newFile 
    }
    else {
        if ($file =~ /$tmpPluginName/g) # 替换插件名
        {
            $newFile =~ s/$tmpPluginName/$pluginName/g; 
            rename $file, $newFile 
        }
    }

}
######################################################


# STEP3 处理Interface
######################################################
my $data = Data::GUID->new;
my $guid = $data->as_string;

# 先定位到原始目录
chdir($curdir);

# 再定位到接口目录
chdir($interfaceDir)
    or die "定位目录$interfaceDir出错!"; # 定位到插件目录

my $IDFile= "ClsID_".$tmpPluginName.".h";
my $newIDFile= "ClsID_".$pluginName.".h";

my $IxFile= "Ix_".$tmpPluginName.".h";
my $newIxFile= "Ix_".$pluginName.".h";

copy $IDFile, $newIDFile
    or warn "从$IDFile拷贝到$newIDFile出错\n";

copy $IxFile, $newIxFile
    or warn "从$IxFile拷贝到$newIxFile出错\n";

# 替换接口文件内容(生成GUID)
my @files = ($newIDFile, $newIxFile);
foreach my $file  (@files)  { # 查找当前目录下所有文件
    print "$file\n";

    open(FILE, $file)
        or warn "打开文件$file失败!\n";
    my @lines = <FILE>;
    close FILE;

    open(OUT, "> $file")
        or warn "打开文件$file失败!\n";

    foreach my $line (@lines) {
        # 替换插件名
        $line =~ s/$tmpPluginName/$pluginName/g;

        # 替换GUID
        $line =~ s/(CLSID_.*\(\")(.*)(\"\);)/$1$guid$3/g;
        print OUT $line; # 写回到原文件
    }
    close OUT;
}

# STEP4 替换版本信息
######################################################

# 先定位到原始目录
chdir($curdir."\/".$pluginName);

my $rcfile = $pluginName . ".rc";

open(FILE, $rcfile)
    or die "打开文件$rcfile失败!\n";

# 读取模板文件  
my $content = do { local $/; <FILE>; };
close FILE;

$content =~ s/(VALUE\s*\"FileDescription\",\s*)\".*?\"/$1\"$FileDescription\"/g;
$content =~ s/(VALUE\s*\"InternalName\",\s*)\".*?\"/$1\"$InternalName\"/g;
$content =~ s/(VALUE\s*\"OriginalFilename\",\s*)\".*?\"/$1\"$OriginalFilename\"/g;
$content =~ s/(VALUE\s*\"ProductName\",\s*)\".*?\"/$1 \"$ProductName\"/g;


open(OUT, "> $rcfile")
    or die "打开文件$rcfile失败!\n";
print OUT $content; # 写回到原文件
close OUT;


 
