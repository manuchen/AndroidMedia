package com.manu.job1pic;

import android.app.Activity;
import android.os.Bundle;


/**
 * Created by intel on 2017/10/23.
 */

public class CustomViewActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_customview);
        CustomView customView = (CustomView)findViewById(R.id.custom);
    }

}

