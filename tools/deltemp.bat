cd ..\projects
attrib -R -H *.suo /S
del /F/S/Q *.ncb,*.opt,*.suo,*.user,*.plg,*.aps,*.ilk,*.depend,*.layout,*.cbtemp,*.a,*.o
del /F/S/Q ..\code\bin\*.def
cd ..\tools
