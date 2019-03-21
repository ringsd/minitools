call setenv.bat

adb reboot bootloader 

fastboot flash system %WORK_PATH%\system.img
fastboot reboot
pause
