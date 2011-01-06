pkg_Core: 插件框架内核部分

PluginManager: 插件管理器, DLL
ChangeManager: 改变通知管理器插件，实现事件驱动机制，管理改变通知观察者
ConfigXml: XML读写封装插件，内部采用MSXML4DOM解析器实现
LogManager: 日志输出管理器插件，管理日志输出观察者
StringTable: 本地化字符串表插件，使用了ConfigXml的接口
