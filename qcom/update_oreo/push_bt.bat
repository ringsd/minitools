call setenv.bat
adb wait-for-device
adb root
adb wait-for-device
adb remount

set pushpath=/system/lib/hw/bluetooth.default.so ^
/system/lib64/hw/bluetooth.default.so ^
/system/lib/hw/audio.a2dp.default.so ^
/system/lib64/hw/audio.a2dp.default.so ^
/system/app/Bluetooth/oat/arm64/Bluetooth.vdex  ^
/system/app/Bluetooth/oat/arm64/Bluetooth.odex ^
/vendor/bin/hci_qcomm_init ^
/system/app/Bluetooth/Bluetooth.apk ^


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

adb push %HOME_PATH%\frameworks\av\services\audiopolicy\config\a2dp_audio_policy_configuration.xml /vendor/etc/a2dp_audio_policy_configuration.xml

exit /b 0
