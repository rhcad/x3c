pkg_Core: X3 core plugins.

PluginManager: plugin manager dll
ChangeManager: change observer manager plugin that implement event-driven model.
LogManager: Logging observer manager plugin.

StringTable: localization string table manager plugin.
ConfigXml: XML I/O wrapper plugin using MSXML6/4 DOM Parser.

FileUtility: file and folder operation plugin.
TextUtility: text content and file operation plugin.
LogWriter: logging writer plugin using log4cplus.

LogWriter plugin need log4cplus (eg: log4cplus-1.0.4-rc11):
Download from http://sourceforge.net/projects/log4cplus/ .
Copy it's folders (only need 'include' and 'src') to LogWriter\log4cplus\.

log4cplus-1.0.4 has some compiler errors for VC++ 6.0, you can find compatible patch about it or
download at http://files.cnblogs.com/rhcad/log4cplus-1.0.4-fix4vc6.zip .
