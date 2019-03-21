call setenv.bat

adb wait-for-device
adb reboot bootloader 

fastboot flash splash  Z:\Qualcomm\R6_ORG\device\qcom\msm8937_64\splash.img
fastboot reboot
pause
