package org.example.nativecopy;

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

    static {
        System.loadLibrary("leak");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (checkSelfPermission(Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.READ_PHONE_STATE}, 1);
        } else {
            Log.d(TAG, "onCreate: permission granted.");
            doleak(getImei(getApplicationContext()));
        }
    }

    public static String getImei(Context applicationContext) {
        TelephonyManager tel = (TelephonyManager) applicationContext.getSystemService(TELEPHONY_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            return tel.getImei();
        } else {
            return tel.getDeviceId();
        }
    }

    public static native void doleak(String imei);
}