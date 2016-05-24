set path=c:\bcc582\bin
bcc32 -W -I..\include %1 ..\lib\fivecpp.lib
if errorlevel 0 %1