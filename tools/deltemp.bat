cd ..\projects
attrib -R -H *.suo /S
del /F/S/Q *.ncb,*.opt,*.suo,*.user,*.aps,*.depend,*.layout,*.cbtemp
del /F/S/Q ..\code\bin\*.ilk,..\code\bin\*.a,..\code\bin\*.def
cd ..\tools
