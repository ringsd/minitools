call setenv.bat

adb wait-for-device
adb root
adb wait-for-device
adb remount

adb push %WORK_PATH%\/system/vendor/lib64/libqti-perfd-client.so /system/vendor/lib64/libqti-perfd-client.so
adb push %WORK_PATH%\/system/vendor/lib/libqti-perfd-client.so /system/vendor/lib/libqti-perfd-client.so
adb push %WORK_PATH%\/system/vendor/bin/perfd /system/vendor/bin/perfd
adb push %WORK_PATH%\/system/etc/permissions/com.qualcomm.qti.Performance.xml /system/etc/permissions/com.qualcomm.qti.Performance.xml

adb reboot
pause
