call setenv.bat
adb wait-for-device
adb root
adb wait-for-device
adb remount

set pushpath=/system/priv-app/SystemUI/oat/arm64/SystemUI.odex ^
/system/priv-app/SystemUI/SystemUI.apk


/system/lib64/hw/audio.primary.msm8937.so ^
/system/lib/hw/audio.primary.msm8937.so ^
/system/framework/services.jar ^
/system/framework/oat/arm64/services.odex ^
/system/framework/framework-res.apk

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
