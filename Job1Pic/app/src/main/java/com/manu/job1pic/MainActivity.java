package com.manu.job1pic;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
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
                    Toast.makeText(this, "Start Testing !", Toast.LENGTH_SHORT).show();
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
                    Toast.makeText(this, "Start Testing !", Toast.LENGTH_SHORT).show();
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
        Button imageBt = (Button)findViewById(R.id.image_bt);
        imageBt.setOnClickListener(this);
        Button surfaceViewBt = (Button)findViewById(R.id.surfaceView_bt);
        surfaceViewBt.setOnClickListener(this);
        Button customBt = (Button)findViewById(R.id.custom_bt);
        customBt.setOnClickListener(this);
        verifyStoragePermissions(MainActivity.this);
    }

    @Override
    public void onClick(View view) {
        Intent intent = new Intent();
        if(view.getId() == R.id.image_bt){
            intent.setClass(MainActivity.this,ImageViewActivity.class);
            startActivity(intent);
        }else if(view.getId() == R.id.surfaceView_bt){
            intent.setClass(MainActivity.this,SurfaceViewActivity.class);
            startActivity(intent);
        }else if(view.getId() == R.id.custom_bt){
            intent.setClass(MainActivity.this,CustomViewActivity.class);
            startActivity(intent);
        }
    }
}
