call setenv.bat
adb wait-for-device
adb reboot bootloader 

fastboot flash userdata %WORK_PATH%\userdata.img
fastboot reboot
pause
