import x3core as C

assert(C.LoadPluginFiles("ChangeManager"))
files = C.GetPluginFiles()
print(files)

C.UnloadPlugins()