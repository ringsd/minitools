call setenv.bat
adb wait-for-device
adb reboot bootloader 

fastboot flash splash  %WORK_PATH%\splash.img
fastboot reboot
pause
