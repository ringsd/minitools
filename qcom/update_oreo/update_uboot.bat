call setenv.bat
REM adb wait-for-device
adb reboot bootloader 

fastboot flash aboot  %WORK_PATH%\emmc_appsboot.mbn
fastboot reboot
pause
