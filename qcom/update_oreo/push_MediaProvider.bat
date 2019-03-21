call setenv.bat
@echo off
adb wait-for-device
adb root
adb wait-for-device
adb remount

set pushpath=/system/priv-app/MediaProvider/MediaProvider.apk ^
/system/priv-app/MediaProvider/oat/arm64/MediaProvider.odex

call :adbpush
pause
adb reboot
exit /b 0

:adbpush

for %%f in (%pushpath%) do (
	echo %%f
    adb push %WORK_PATH%\%%f %%f
)
exit /b 0
