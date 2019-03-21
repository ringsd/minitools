call setenv.bat

adb wait-for-device
adb root
adb wait-for-device
adb remount

adb push %WORK_PATH%\system/lib/libtinyalsa.so /system/lib/libtinyalsa.so
adb push %WORK_PATH%\system/lib64/libtinyalsa.so /system/lib64/libtinyalsa.so 
adb push %WORK_PATH%\system\bin\tinyplay /system/bin/tinyplay
adb shell chmod 777 /system/bin/tinyplay
adb push %WORK_PATH%\system\bin\tinypcminfo /system/bin/tinypcminfo
adb shell chmod 777 /system/bin/tinypcminfo

REM adb reboot
pause
