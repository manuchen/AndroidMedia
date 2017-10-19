package com.jhuster.audiodemo.activity;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;

import com.jhuster.audiodemo.R;
import com.jhuster.audiodemo.tester.AudioCaptureTester;
import com.jhuster.audiodemo.tester.NativeAudioTester;
import com.jhuster.audiodemo.tester.AudioCodecTester;
import com.jhuster.audiodemo.tester.AudioPlayerTester;
import com.jhuster.audiodemo.tester.Tester;

public class MainActivity extends AppCompatActivity {

    private Spinner mTestSpinner;
    private Tester mTester;

    public static final String[] TEST_PROGRAM_ARRAY = {
            "录制 wav 文件",
            "播放 wav 文件",
            "OpenSL ES 录制",
            "OpenSL ES 播放",
            "音频编解码"
    };
    private static final int REQUEST_EXTERNAL_STORAGE = 1;
    private static String[] PERMISSIONS_STORAGE = {
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.WRITE_EXTERNAL_STORAGE",
            "android.permission.RECORD_AUDIO"};


    public  void verifyStoragePermissions(Activity activity) {

        try {
            //检测是否有写的权限
            int permission = ActivityCompat.checkSelfPermission(activity,
                    "android.permission.WRITE_EXTERNAL_STORAGE");
            int permission2 = ActivityCompat.checkSelfPermission(activity,
                    "android.permission.RECORD_AUDIO");
            if (permission != PackageManager.PERMISSION_GRANTED || permission2 != PackageManager.PERMISSION_GRANTED) {
                // 没有写的权限，去申请写的权限，会弹出对话框
                ActivityCompat.requestPermissions(activity, PERMISSIONS_STORAGE,REQUEST_EXTERNAL_STORAGE);
            }else{
                if (mTester != null) {
                    mTester.startTesting();
                    Toast.makeText(this, "Start Testing !", Toast.LENGTH_SHORT).show();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
    {

        if (requestCode == REQUEST_EXTERNAL_STORAGE)
        {
            if (grantResults[0] == PackageManager.PERMISSION_GRANTED)
            {
                if (mTester != null) {
                    mTester.startTesting();
                    Toast.makeText(this, "Start Testing !", Toast.LENGTH_SHORT).show();
                }
            } else
            {
                // Permission Denied
                Toast.makeText(MainActivity.this, "Permission Denied", Toast.LENGTH_SHORT).show();
            }
            return;
        }
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTestSpinner = (Spinner) findViewById(R.id.TestSpinner);
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, TEST_PROGRAM_ARRAY);
        mTestSpinner.setAdapter(adapter);
    }

    public void onClickStartTest(View v) {
        switch (mTestSpinner.getSelectedItemPosition()) {
            case 0:
                mTester = new AudioCaptureTester();
                break;
            case 1:
                mTester = new AudioPlayerTester();
                break;
            case 2:
                mTester = new NativeAudioTester(true);
                break;
            case 3:
                mTester = new NativeAudioTester(false);
                break;
            case 4:
                mTester = new AudioCodecTester();
                break;
            default:
                break;
        }
        verifyStoragePermissions(MainActivity.this);
//        if (mTester != null) {
//            mTester.startTesting();
//            Toast.makeText(this, "Start Testing !", Toast.LENGTH_SHORT).show();
//        }
    }

    public void onClickStopTest(View v) {
        if (mTester != null) {
            mTester.stopTesting();
            Toast.makeText(this, "Stop Testing !", Toast.LENGTH_SHORT).show();
        }
    }
}
