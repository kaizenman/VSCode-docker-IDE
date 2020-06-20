echo "pushing file"
C:\platform-tools\adb.exe -s 192.168.1.6:5555 push C:\Users\niels\Projects\VSCode-docker-IDE\bin\app-release.apk /sdcard/app-release.apk
echo "uninstalling apk"
C:\platform-tools\adb.exe -s 192.168.1.6:5555 uninstall com.android.gl2jni
echo "installing apk"
C:\platform-tools\adb.exe -s 192.168.1.6:5555 shell pm install /sdcard/downloads/app-release.apk
echo "running apk"
C:\platform-tools\adb.exe -s 192.168.1.6:5555 shell am start -n com.android.gl2jni/com.android.gl2jni.GL2JNIActivity
echo "running shell"
C:\platform-tools\adb.exe -s 192.168.1.6:5555 shell