
:rb
adb wait-for-device

@echo off
echo �ȴ�5�롭
echo.wscript.sleep(5000)>sleep.vbs
cscript //nologo sleep.vbs
del sleep.vbs
echo ����ִ�С�

adb reboot 
goto rb

