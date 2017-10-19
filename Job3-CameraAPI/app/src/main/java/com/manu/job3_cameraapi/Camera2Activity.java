package com.manu.job3_cameraapi;

import android.content.Context;
import android.graphics.ImageFormat;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CaptureRequest;
import android.media.Image;
import android.media.ImageReader;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.SurfaceView;
import android.widget.Toast;

import com.manu.job3_cameraapi.util.ImageUtil;

import java.util.Arrays;

/**
 * Created by intel on 2017/10/19.
 */

@RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
public class Camera2Activity extends AppCompatActivity {

    private CameraManager cameraManager;
    private String cameraId;
    private CameraDevice cameraDevice;
    private CameraCaptureSession mCameraCaptureSession;
    private ImageReader previewReader;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera2);
        cameraManager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
        cameraId = Integer.toString(CameraCharacteristics.LENS_FACING_FRONT);
        previewReader = ImageReader.newInstance(1080, 1920, ImageFormat.YUV_420_888, 2);
//        previewReader.setOnImageAvailableListener(new ImageReader.OnImageAvailableListener() {
//            @Override
//            public void onImageAvailable(ImageReader imageReader) {
//                Image image = null;
//                try {
//                    image = imageReader.acquireLatestImage();
//                    Log.d("PreviewListener", "GetPreviewImage");
//                    if (image == null) {
//                        return;
//                    }
//                    byte[] bytes = ImageUtil.imageToByteArray(image);
//                    if (pushFlag == false)
//                        uploadImg(bytes);
//                } finally {
//                    if (image != null) {
//                        image.close();
//                    }
//                }
//
//            }
//        }, mainHandler);
//        cameraManager.openCamera(cameraId, cameraCallback, mainHandler);
    }

    private CameraDevice.StateCallback cameraCallback = new CameraDevice.StateCallback() {
        @Override
        public void onOpened(CameraDevice camera) {
            Log.d("CameraCallback", "Camera Opened");
            cameraDevice = camera;
//            takePreview();
        }

        @Override
        public void onDisconnected(CameraDevice cameraDevice) {
            Log.d("CameraCallback", "Camera Disconnected");
            closeCameraDevice();
        }

        @Override
        public void onError(CameraDevice cameraDevice, int i) {
            Log.d("CameraCallback", "Camera Error");
            Toast.makeText(Camera2Activity.this, "摄像头开启失败", Toast.LENGTH_SHORT).show();
        }
    };

    private void closeCameraDevice() {
        cameraDevice.close();
    }

//    private void takePreview() {
//        try {
//            final CaptureRequest.Builder previewRequestBuilder
//                    = cameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
//            previewRequestBuilder.addTarget(surfaceHolder.getSurface());
//            previewRequestBuilder.addTarget(previewReader.getSurface());
//            cameraDevice.createCaptureSession(Arrays.asList(surfaceHolder.getSurface(),
//                    previewReader.getSurface(),
//                    imageReader.getSurface()), new CameraCaptureSession.StateCallback() {
//                @Override
//                public void onConfigured(CameraCaptureSession cameraCaptureSession) {
//                    if (cameraDevice == null) return;
//                    mCameraCaptureSession = cameraCaptureSession;
//
//                    try {
//                        previewRequestBuilder.set(CaptureRequest.CONTROL_AF_MODE,
//                                CaptureRequest.CONTROL_AF_MODE_CONTINUOUS_PICTURE);
//                        previewRequestBuilder.set(CaptureRequest.CONTROL_AE_MODE,
//                                CaptureRequest.CONTROL_AE_MODE_OFF);
//
//                        CaptureRequest previewRequest = previewRequestBuilder.build();
//                        mCameraCaptureSession.setRepeatingRequest(previewRequest, null, childHandler);
//                    } catch (CameraAccessException e) {
//                        e.printStackTrace();
//                    }
//                }
//
//                @Override
//                public void onConfigureFailed(CameraCaptureSession cameraCaptureSession) {
//                    Toast.makeText(Camera2Activity.this, "配置失败", Toast.LENGTH_SHORT).show();
//                }
//            }, childHandler);
//        } catch (CameraAccessException e) {
//            e.printStackTrace();
//        }
//    }




}
