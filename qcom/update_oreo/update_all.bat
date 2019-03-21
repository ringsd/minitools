call setenv.bat

adb wait-for-devices
adb reboot bootloader 

fastboot flash boot %WORK_PATH%\boot.img
fastboot flash system %WORK_PATH%\system.img
fastboot flash vendor %WORK_PATH%\vendor.img
fastboot flash recovery %WORK_PATH%\recovery.img
fastboot flash splash  %WORK_PATH%\splash.img
fastboot flash modem %HOME_PATH%\QRD8937_HIBY\8917_Bin_Org\msm8917\NON-HLOS.bin
fastboot reboot
pause
