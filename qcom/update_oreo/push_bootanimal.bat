call setenv.bat
adb wait-for-device
adb root
adb wait-for-device
adb remount

set pushpath=/system/media/bootanimation.zip ^
/system/media/shutdownanimation.zip


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

