call setenv.bat

adb wait-for-device
adb reboot bootloader 

fastboot flash recovery %WORK_PATH%\recovery.img
fastboot reboot
pause
