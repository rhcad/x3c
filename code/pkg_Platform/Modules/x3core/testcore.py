import x3core as C

assert(C.LoadPluginFiles("ChangeManager"))
for f in C.GetPluginFiles(): print(f)

C.UnloadPlugins()