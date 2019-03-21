call setenv.bat
adb wait-for-device
adb reboot bootloader 
fastboot flash boot %WORK_PATH%\boot.img
fastboot reboot
pause
