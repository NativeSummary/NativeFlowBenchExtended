package org.example.nativeglobalid;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.NonNull;

public class MainActivity extends Activity {

    private static final String TAG = "native_global_id";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("globalId");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (checkSelfPermission(Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.READ_PHONE_STATE}, 1);
        } else {
            Log.d(TAG, "onCreate: permission granted.");
            leakimei();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch (requestCode) {
            case 1:
                leakimei();
                return;
            default:
        }
    }

    private void leakimei() {
        String imei = getImei(getApplicationContext()); // source
        Log.i("imei", imei); // sink
    }

    public static native String getImei(Context applicationContext);


}