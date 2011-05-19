cd ..\projects
attrib -R -H *.suo /S
del /F/S/Q *.ncb,*.opt,*.suo,*.user,*.aps,*.depend,*.layout
del /F/S/Q ..\code\bin\*.ilk
rd /S/Q ..\doc\html
rd /S/Q ..\doc\x3full
cd ..\tools
