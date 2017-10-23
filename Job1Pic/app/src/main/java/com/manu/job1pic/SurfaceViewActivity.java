package com.manu.job1pic;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.io.File;


/**
 * Created by intel on 2017/10/23.
 */

public class SurfaceViewActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_surfaceview);
        SurfaceView surfaceView = (SurfaceView)findViewById(R.id.surfaceview);
        surfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder surfaceHolder) {

                if (surfaceHolder == null) {
                    return;
                }

                Paint paint = new Paint();
                paint.setAntiAlias(true);
                paint.setStyle(Paint.Style.STROKE);
                String path = Environment.getExternalStorageDirectory().getPath() + File.separator + "android.jpg";
                Log.d("TAG","path:"+path);
                Bitmap bitmap = BitmapFactory.decodeFile(path);  // 获取bitmap


                Canvas canvas = surfaceHolder.lockCanvas();  // 先锁定当前surfaceView的画布
                canvas.drawBitmap(bitmap, 0, 0, paint); //执行绘制操作
                surfaceHolder.unlockCanvasAndPost(canvas); // 解除锁定并显示在界面上
            }

            @Override
            public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {

            }

            @Override
            public void surfaceDestroyed(SurfaceHolder surfaceHolder) {

            }
        });
    }

}

