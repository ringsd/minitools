
:rb
adb wait-for-device

@echo off
echo µÈ´ý5Ãë¡­
echo.wscript.sleep(5000)>sleep.vbs
cscript //nologo sleep.vbs
del sleep.vbs
echo ¼ÌÐøÖ´ÐÐ¡­

adb reboot 
goto rb

