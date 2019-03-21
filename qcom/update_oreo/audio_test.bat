adb wait-for-devices
adb root
adb wait-for-devices

rem set AUDIO_TEST=/mnt/sdcard/Music
set AUDIO_TEST=/mnt/media_rw/3238-6330/0_small

adb shell "tinymix 'MI2S_RX Format' 'S16_LE'"
adb shell "tinymix 'Output Select' 'None'"

adb shell "tinymix 'QUIN_MI2S_RX Audio Mixer MultiMedia1' 1"
REM adb shell "tinymix 'Output Select' 'Balance'"
adb shell "tinymix 'Output Select' 'Balance'"
adb shell "tinymix 'Right Playback Volume' 80"
adb shell "tinymix 'Left Playback Volume' 80"
REM adb shell "tinypcminfo -D 0 -d 0"
:loop

REM mute test
REM adb shell "tinyplay /mnt/media_rw/3238-6330/test/n-384k.wav"
REM adb shell "tinyplay /mnt/media_rw/3238-6330/test/q-11.2MHZ.dff"
REM adb shell "tinyplay %AUDIO_TEST%/g1-44.1K.wav"
REM adb shell "tinyplay /mnt/media_rw/3238-6330/test/m-192k.wav"
REM adb shell "tinyplay /mnt/media_rw/3238-6330/test/o1-2.8MHz.dff"
REM goto quit

REM adb shell "tinyplay %AUDIO_TEST%/g1-44.1K.wav"
REM adb shell "tinyplay %AUDIO_TEST%/g1-44.1K.wav"
rem adb shell "tinyplay %AUDIO_TEST%/m-192k.wav"
REM adb shell "tinyplay %AUDIO_TEST%/24B-192K.wav"
REM adb shell "tinyplay %AUDIO_TEST%/24B-44K.wav"
REM adb shell "tinyplay %AUDIO_TEST%/24B-176K.wav"
REM adb shell "tinyplay %AUDIO_TEST%/16B-48K.wav"
REM adb shell "tinyplay %AUDIO_TEST%/16B-192K.wav"
adb shell "tinyplay %AUDIO_TEST%/24B-96K.wav"
REM adb shell "tinyplay %AUDIO_TEST%/j-88.2k.wav"
REM adb shell "tinyplay %AUDIO_TEST%/m-192k.wav"

REM adb shell "tinyplay /mnt/media_rw/3238-6330/test/l2-176.4k.wav"
goto loop

:quit

adb shell "tinymix 'Output Select' 'None'"

pause
