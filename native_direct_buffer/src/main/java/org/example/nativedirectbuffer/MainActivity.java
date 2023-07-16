package org.example.nativedirectbuffer;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.util.Log;

import java.nio.ByteBuffer;

public class MainActivity extends Activity {

    private static final String TAG = "MainActivity";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("nio");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (checkSelfPermission(Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.READ_PHONE_STATE}, 1);
        } else {
            Log.d(TAG, "onCreate: permission granted.");
            String imei = getImei(getApplicationContext());
            ByteBuffer buffer = ByteBuffer.allocateDirect(20);
            byte[] arr = imei.getBytes();

            for (int i=0;i<Math.min(arr.length, 20);i++) {
                buffer.put(i, arr[i]);
            }
            buffer.put(19, (byte) 0);
            doLeak(buffer);
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

    public static native void doLeak(ByteBuffer buf);
}