#!/usr/bin/perl
####################################################################################
# Description: a Perl script for auto-generation of X3C Plugin 
# Usage:          
# Creator:     thinkhy
# Date:        2010.10.13 
#
# ChangeList:  1. Implemented the fuction: Modify interface file,replace GUID. Finished basic function of the script. [thinkhy 10/10/19]
#              2. Added configuration file(config.h). [thinkhy 10/10/21]
#              3. Implemented the function to change the version information. [thinkhy 10/11/15]
#              4. Translated comments to English. [thinkhy 10/11/15]

#
#  TODO:       1. Remove all the SVN information in the directory of the generated plugin¡£ [thinkhy 11/01/06]
####################################################################################
use strict;
use warnings;

# Copy directory: dircopy
# CPAN  http://search.cpan.org/~dmuey/File-Copy-Recursive-0.38/Recursive.pm
use File::Copy::Recursive qw(fcopy rcopy dircopy fmove rmove dirmove);

# Copy file
use File::Copy;

# Locate work directory
use Cwd;

# Generate GUID: Data::GUID->new
# http://search.cpan.org/~rjbs/Data-GUID-0.045/lib/Data/GUID.pm
use Data::GUID;


######################################################
# Read configuration file (makePlugin.xml)
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

# Step1: Copy directory from template 
######################################################
my $orig = $cfg->val('exampleplugin','plugindir');
my $interfaceDir = $cfg->val('exampleplugin','interfacedir');
chomp($orig);

dircopy($orig,$pluginName) or die "Failed to copy files from $orig to $pluginName";

# Step2: Change filename and contents
######################################################
my $curdir = getcwd;
chdir($pluginName); # Locate work directory

# Process moduel directory 
foreach my $file (glob "*")  { #  Find all the files of current directory 
    print "$file\n";

    # get extenstion name 
    my $extName = ($file =~ m/([^.]+)$/)[0];

    # process source code and project files 
    if ($extName =~ /vcproj|dsp|c|cxx|cpp|h|hpp|rc/i) { 
        open(FILE, $file)
            or warn "Failed to open $file!\n";

        my @lines = <FILE>;
        close FILE;

        open(OUT, "> $file")
            or warn "Failed to open $file!\n";

        foreach my $line (@lines) {
            # replace plugin name and project name
            $line =~ s/$tmpPrjName/$prjName/g;
            $line =~ s/$tmpPluginName/$pluginName/g;
            print OUT $line; # Written back to the original file
        }


        close OUT;
    }

    my $newFile = $file;
    if ($file =~ /$tmpPrjName/g) # replace project name
    {
        $newFile =~ s/$tmpPrjName/$prjName/g; 
        rename $file, $newFile 
    }
    else {
        if ($file =~ /$tmpPluginName/g) # replace plugin name
        {
            $newFile =~ s/$tmpPluginName/$pluginName/g; 
            rename $file, $newFile 
        }
    }
}

######################################################


# STEP3 Process Interface
######################################################
my $data = Data::GUID->new;
my $guid = $data->as_string;

# locate the original directory
chdir($curdir);

# Reloacte to the interface directory  
chdir($interfaceDir)
    or die "Failed to locate to directory of $interfaceDir!";  


my $IDFile= "ClsID_".$tmpPluginName.".h";
my $newIDFile= "ClsID_".$pluginName.".h";

my $IxFile= "Ix_".$tmpPluginName.".h";
my $newIxFile= "Ix_".$pluginName.".h";

copy $IDFile, $newIDFile
    or warn "Failed to copy from $newIDFile to $IDFile\n";

copy $IxFile, $newIxFile
    or warn "Failed to Copy from $newIxFile to $IxFile\n";

# Replace the contents fo interface files and generate GUID
my @files = ($newIDFile, $newIxFile);
foreach my $file  (@files)  { # Find all the files 
    print "$file\n";

    open(FILE, $file)
        or warn "Failed to open $file!\n";
    my @lines = <FILE>;
    close FILE;

    open(OUT, "> $file")
        or warn "Failed to open $file!\n";

    foreach my $line (@lines) {
        # replace plugin name
        $line =~ s/$tmpPluginName/$pluginName/g;

        # replace GUID
        $line =~ s/(CLSID_.*\(\")(.*)(\"\);)/$1$guid$3/g;
        print OUT $line; # write back to the original file
    }
    close OUT;
}

# STEP4 replace version information
######################################################

# Firstly,locate to plugin 
chdir($curdir."\/".$pluginName);

my $rcfile = $pluginName . ".rc";

open(FILE, $rcfile)
    or die "Failed to open $rcfile!\n";

# Read template file  
my $content = do { local $/; <FILE>; };
close FILE;

$content =~ s/(VALUE\s*\"FileDescription\",\s*)\".*?\"/$1\"$FileDescription\"/g;
$content =~ s/(VALUE\s*\"InternalName\",\s*)\".*?\"/$1\"$InternalName\"/g;
$content =~ s/(VALUE\s*\"OriginalFilename\",\s*)\".*?\"/$1\"$OriginalFilename\"/g;
$content =~ s/(VALUE\s*\"ProductName\",\s*)\".*?\"/$1 \"$ProductName\"/g;


open(OUT, "> $rcfile")
    or die "Failed to open $rcfile!\n";
print OUT $content; # Write back
close OUT;


 
