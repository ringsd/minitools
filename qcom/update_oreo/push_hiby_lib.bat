adb wait-for-device
adb root
adb wait-for-device
adb remount

adb push libhibyservice.so /data/data/com.hiby.music/lib/libhibyservice.so
adb push libhibyusbhost.so /data/data/com.hiby.music/lib/libhibyusbhost.so
