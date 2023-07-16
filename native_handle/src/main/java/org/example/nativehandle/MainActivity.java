package org.example.nativehandle;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.util.Log;

public class MainActivity extends Activity {

    private static final String TAG = "MainActivity";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("handle");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (checkSelfPermission(Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.READ_PHONE_STATE}, 1);
        } else {
            leakImei();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch (requestCode) {
            case 1: {
                leakImei();
                return;
            }
        }
    }

    private void leakImei() {
        Log.d(TAG, "onCreate: permission granted.");
        String imei = getImei(getApplicationContext());
        long handle = allocateInNative(50);
        setStringInNative(handle, imei, 50);
//        String read = readStringFromNative(handle);
//        Log.d(TAG, read);
        leakInNative(handle);
    }

    public static String getImei(Context applicationContext) {
        TelephonyManager tel = (TelephonyManager) applicationContext.getSystemService(TELEPHONY_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            return tel.getImei();
        } else {
            return tel.getDeviceId();
        }
    }

    private static native void setStringInNative(long handle, String imei, long size);
    private static native long allocateInNative(long size);
    private static native void releaseInNative(long handle);
    private static native long leakInNative(long size);
    private static native String readStringFromNative(long handle);
}