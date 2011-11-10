%module x3core

%{
#include <vector>
#include <string>

bool LoadCorePlugins();
bool LoadAllPlugins();
bool LoadPluginFiles(const char* files);
void UnloadPlugins();
std::vector<std::string> GetPluginFiles();
%}

%include stl.i
%include std_vector.i
%include std_string.i

bool LoadCorePlugins();
bool LoadAllPlugins();
bool LoadPluginFiles(const char* files);
void UnloadPlugins();
std::vector<std::string> GetPluginFiles();
