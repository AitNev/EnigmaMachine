package aitor_nevzorov.glbook;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private GLSurfaceView glSurfaceView;
    private boolean rendererSet = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        glSurfaceView = new GLSurfaceView(this);

        final ActivityManager activityManager = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
        final ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
        final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000 ||
                (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1 &&
                        (Build.FINGERPRINT.startsWith("generic") || Build.FINGERPRINT.startsWith("unknown") ||
                                Build.MODEL.contains("google_sdk") || Build.MODEL.contains("Emulator") ||
                                Build.MODEL.contains("Android SDK built for x86")));
        final MainRenderer renderer = new MainRenderer(this);
        if(supportsEs2){
            glSurfaceView.setEGLContextClientVersion(2);
            glSurfaceView.setRenderer(renderer);
            rendererSet = true;
        }else{
            Toast.makeText(this, "This device doesn't support OpenGL ES 2.0", Toast.LENGTH_LONG).show();
            return;
        }
        glSurfaceView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent != null){
                    // Convert touch coordinates in to normalized device
                    // coordinates, keeping in mind that Android's Y
                    // coordinates are invented
                    final float normalizedX = (motionEvent.getX() / (float) view.getWidth())*2-1;
                    final float normalizedY = -((motionEvent.getY() / (float) view.getHeight())*2-1);

                    if (motionEvent.getAction() == MotionEvent.ACTION_DOWN){
                        glSurfaceView.queueEvent(new Runnable() {
                            @Override
                            public void run() {
                                renderer.handleTouchPress(normalizedX, normalizedY);
                            }
                        });
                    }else if (motionEvent.getAction() == MotionEvent.ACTION_MOVE){
                        glSurfaceView.queueEvent(new Runnable() {
                            @Override
                            public void run() {
                                renderer.handleTouchDrag(normalizedX, normalizedY);
                            }
                        });
                    }return true;
                }else {return false;}
            }
        });
        setContentView(glSurfaceView);

    }

    @Override
    protected void onPause() {
        super.onPause();

        if(rendererSet){
            glSurfaceView.onPause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        if (rendererSet){
            glSurfaceView.onResume();
        }
    }
}
