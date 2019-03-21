call setenv.bat
adb wait-for-device
adb root
adb wait-for-device
adb remount

set pushpath=/vendor/lib/hw/audio.primary.msm8937.so ^
/vendor/lib64/hw/audio.primary.msm8937.so
goto :start

/system/lib/libaudiopolicymanager.so ^
/system/lib64/libaudiopolicymanager.so ^
/system/lib/libaudiopolicymanagerdefault.so ^
/system/lib64/libaudiopolicymanagerdefault.so ^
/system/lib/libmedia.so ^
/system/lib64/libmedia.so ^
/system/lib/libaudioflinger.so ^
/system/lib/libaudioclient.so ^
/system/lib64/libaudioclient.so ^
/system/lib/libsmartaudioservice.so ^
/system/lib64/libsmartaudioservice.so ^
/system/lib/libaudiopolicyenginedefault.so ^
/system/lib64/libaudiopolicyenginedefault.so ^

:start
call :adbpush
::call :adbpushconf
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


:adbpushconf

adb push %HOME_PATH%\hardware\qcom\audio\configs\msm8937\audio_output_policy.conf /vendor/etc/audio_output_policy.conf
adb push %HOME_PATH%\hardware\qcom\audio\configs\msm8937\audio_policy.conf /vendor/etc/audio_policy.conf
adb push %HOME_PATH%\hardware\qcom\audio\configs\msm8937\mixer_paths_mtp.xml /vendor/etc/mixer_paths_mtp.xml
adb push %HOME_PATH%\hardware\qcom\audio\configs\msm8937\audio_policy_configuration.xml /vendor/etc/audio_policy_configuration.xml
adb push %HOME_PATH%\hardware\qcom\audio\configs\msm8937\audio_policy_configuration.xml /vendor/etc/audio/audio_policy_configuration.xml

exit /b 0
