
adb wait-for-device
adb root
adb wait-for-device
adb remount

set WORK_PATH=Z:\Qualcomm\P6\out\target\product\msm8937_64

adb push %WORK_PATH%/system/lib64/libwilhelm.so /system/lib64/libwilhelm.so
adb push %WORK_PATH%/system/lib/libwilhelm.so /system/lib/libwilhelm.so
adb push %WORK_PATH%/system/lib64/libOpenSLES.so /system/lib64/libOpenSLES.so
adb push %WORK_PATH%/system/lib/libOpenSLES.so /system/lib/libOpenSLES.so
adb push %WORK_PATH%/system/lib64/libOpenMAXAL.so /system/lib64/libOpenMAXAL.so
adb push %WORK_PATH%/system/lib/libOpenMAXAL.so /system/lib/libOpenMAXAL.so

REM adb reboot
pause
