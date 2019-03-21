call setenv.bat

adb reboot bootloader 

fastboot flash vendor %WORK_PATH%\vendor.img
fastboot reboot
pause
