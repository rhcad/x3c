import x3core as C

C.LoadPluginFiles("ChangeManager")
assert(C.LoadAllPlugins() > 0)
for f in C.GetPluginFiles(): print(f)

C.UnloadPlugins()
