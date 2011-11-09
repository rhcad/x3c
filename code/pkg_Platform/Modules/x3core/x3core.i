%module x3core

%{
#include <UtilFunc/vecfunc.h>
using namespace std;
typedef vector<wstring> WStrVector;

bool LoadCorePlugins();
bool LoadAllPlugins();
bool LoadPluginFiles(const char* files);
void UnloadPlugins();
std::vector<std::wstring> GetPluginFiles();
%}

%include stl.i
using namespace std;

%template(WStrVector)    vector<wstring>;

bool LoadCorePlugins();
bool LoadAllPlugins();
bool LoadPluginFiles(const char* files);
void UnloadPlugins();
WStrVector GetPluginFiles();
