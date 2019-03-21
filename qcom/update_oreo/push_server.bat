call setenv.bat
adb wait-for-device
adb root
adb wait-for-device
adb remount

REM set pushpath=/system/framework/framework.jar ^
REM /system/framework/framework-res.apk ^
REM /system/framework/oat/arm64/services.odex ^
REM /system/framework/services.jar


set pushpath=/system/framework/oat/arm64/services.odex ^
/system/framework/services.jar

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
