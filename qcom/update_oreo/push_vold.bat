call setenv.bat
@echo off
adb wait-for-device
adb root
adb wait-for-device
adb remount

set pushpath=/system/bin/blkid ^
/system/bin/vold ^
/system/bin/vdc ^
/system/bin/secdiscard ^
/system/lib64/libext2_blkid.so ^
/system/lib64/libext2fs.so ^
/system/lib64/libext2_quota.so ^
/system/bin/e2fsck ^
/system/lib/libext2_blkid.so ^
/system/lib/libext2fs.so ^
/system/lib/libext2_quota.so ^
/system/bin/mke2fs ^
/system/bin/tune2fs ^
/system/bin/tune2fs_static ^
/system/bin/badblocks ^
/system/bin/resize2fs ^
/system/bin/sgdisk ^
/system/lib64/libntfs-3g.so ^
/system/lib/libntfs-3g.so ^
/system/bin/ntfs-3g

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
