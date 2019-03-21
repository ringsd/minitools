call setenv.bat
@echo off
adb wait-for-device
adb root
adb wait-for-device
adb remount

set pushpath=/system/bin/healthd

call :adbpush
pause
adb reboot
exit /b 0

:adbpush

for %%f in (%pushpath%) do (
	echo %%f
    adb push %WORK_PATH%\%%f %%f
    adb shell chmod 777 %%f
)
exit /b 0
