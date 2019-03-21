call setenv.bat

adb wait-for-device
adb root
adb wait-for-device
adb remount

adb push %WORK_PATH%\system/framework/services.jar /system/framework/services.jar
adb push %WORK_PATH%\system/framework/oat/arm64/services.odex /system/framework/oat/arm64/services.odex

adb reboot
pause
