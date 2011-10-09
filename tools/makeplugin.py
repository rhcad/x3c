#!/usr/bin/env python
"""
Function:   Create a plugin project based on Win32DllTempl or MFCExtTempl.
            This script has been tested with ActivePython 2.7.

Usage:      makeplugin.py projname pkgname basetype
            projname: name of the new project.
            pkgname: package name of the new project, the default value
                is 'pkg_Example'.
            basetype: 'mfc', 'win32', 'view' or project name in pkg_Example,
                the default value is 'win32'.

Creator:    ooyg <rhcad@hotmail.com>
Date:       2011.10.9
ChangeList:
    1. Implemented the function: multireplace, copyfiles, makeproj
    2. Add 'view' for the param of 'basetype'.
       Skip project files while copying files in pkg_Example. [2011/10/10]
"""

import os, sys, re

def multireplace(text, adict):
    rx = re.compile('|'.join(map(re.escape, adict)))
    def xlat(match):
        return adict[match.group(0)]
    return rx.sub(xlat, text)

def copyfiles(srcdir, destdir, pairs, callback=None):
    if srcdir.find(".svn") > 0:
        return
    if not os.path.exists(destdir):
        os.makedirs(destdir)
    
    for fn in os.listdir(srcdir):
        srcfile = os.path.join(srcdir, fn)
        destfile = os.path.join(destdir, multireplace(fn, pairs))
        
        if os.path.isdir(srcfile):
            copyfiles(srcfile, destfile, pairs)
        if os.path.isfile(srcfile) and not os.path.exists(destfile) \
                and (not callback or callback(fn, pairs)):
            open(destfile, "wb").write(open(srcfile, "rb").read())
            text = open(destfile).read()
            newtext = multireplace(text, pairs)
            if newtext != text:
                open(destfile, 'w').write(newtext)
                print('%s [replaced]' % destfile)
            else:
                print(destfile)

def makeproj(projname, pkgname, baseproj):
    codepath = os.path.abspath('../code')
    basepath = os.path.join(codepath, 'pkg_Example', 'Modules', baseproj)
    
    if not os.path.exists(basepath):
        raise OSError, basepath
    if not os.path.exists(os.path.join(codepath, pkgname)):
        raise OSError, os.path.join(codepath, pkgname)
    if projname == '':
        raise AttributeError, projname

    destdir = os.path.join(codepath, pkgname, 'Modules', projname)
    pairs = {baseproj:projname, 'pkg_Example':pkgname}
    
    def matchfile(filename, pairs):
        if filename.find(".dsp") > 0 or filename.find(".vc") > 0:
            return False
        return True
    copyfiles(basepath, destdir, pairs, matchfile)

    def matchproj(filename, pairs):
        for key in pairs.keys():
            if filename.startswith(key):
                return True
        return False
    projects = os.path.abspath('../projects/msvc/vcproj')
    copyfiles(projects, projects, pairs, matchproj)

if __name__=="__main__":
    def inputparam(index, prompt, default=''):
        if len(sys.argv) > index:
            ret = sys.argv[index]
        else:
            ret = raw_input(prompt)
        if ret == '': ret = default
        return ret
    
    projname = inputparam(1, 'Project name: ')
    pkgname  = inputparam(2, 'Package name (pkg_Example): ', 'pkg_Example')
    baseproj = inputparam(3, 'Template project (win32, mfc, view, '   \
                             'or project name in pkg_Example): ', 'win32')
                
    if baseproj == 'win32': baseproj = 'Win32DllTempl'
    if baseproj == 'mfc':   baseproj = 'MFCExtTempl'
    if baseproj == 'view':  baseproj = 'HelloView'
    
    makeproj(projname, pkgname, baseproj)
