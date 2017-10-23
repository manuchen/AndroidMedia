package com.manu.job1pic;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.widget.Button;
import android.widget.ImageView;

import java.io.File;

/**
 * Created by intel on 2017/10/23.
 */

public class ImageViewActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image);
        ImageView imageView = (ImageView)findViewById(R.id.image);
        imageView.setImageResource(R.mipmap.ic_launcher);
    }
}
