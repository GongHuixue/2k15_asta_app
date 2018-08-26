package org.droidtv.euinstallertc.wizard.screen;

import java.util.Observable;
import java.util.Observer;

import org.droidtv.euinstallertc.common.InstallerActivityManager;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIEnums.ACINavigate;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.notification.NotificationHandler;
import org.droidtv.euinstallertc.model.notification.NotificationInfoObject;
import org.droidtv.euinstallertc.util.EventIDs;

import android.app.Activity;
import android.content.Context;
import android.graphics.SurfaceTexture;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Surface;
import android.view.TextureView;
import android.view.TextureView.SurfaceTextureListener;
import android.view.Window;
import android.widget.FrameLayout;

public class ACIPageActivity extends Activity implements Observer,
        SurfaceTextureListener {

    private static final String TAG = ACIPageActivity.class.getName();

    private NativeAPIWrapper nwrap = NativeAPIWrapper.getInstance();
    private NotificationHandler ntf = NotificationHandler.getInstance();
    private FrameLayout frameLayout = null;
    private TextureView mTextureView = null;
    public Surface mSurface = null;
    private Context mContext = null;
    private InstallerActivityManager instActManager = InstallerActivityManager.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mContext = this;

        Log.d(TAG, "onCreate");
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        ntf.registerForNotification(this);
        
        instActManager.addActivityToStack(this);

        Log.d(TAG, "creating new texture view");
        mTextureView = new TextureView(mContext);
        mTextureView.setSurfaceTextureListener(this);

        Log.d(TAG, "creating new frame layout");
        frameLayout = new FrameLayout(mContext);
        frameLayout.addView(mTextureView);

        setContentView(frameLayout);

        Log.d(TAG, "ACI Page Setup Done");
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.d(TAG, "onStart");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "onResume");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d(TAG, "onPause");
        
        if(isFinishing()){
	        Log.d(TAG, "onPause & the reason is activity is finishing");
        }
    }

    @Override
    protected void onStop() {
    	Log.d(TAG, "onStop");
        super.onStop();
    }

    @Override
    protected void onDestroy() {
    	Log.d(TAG, "onDestroy");
        ntf.unregisterForNotification(this);
        instActManager.removeActivityFromStack(this);
        super.onDestroy();
    }

    @Override
    protected void onRestart() {
    	Log.d(TAG, "onRestart");
        super.onRestart();
    }

    @Override
    public void update(Observable observable, Object data) {
        final int eventID = ((NotificationInfoObject) data).actionID;
        switch (eventID) {
            case EventIDs.EVENT_CLOSE_ACI_PAGE:
                Log.d(TAG, "EventIDs.EVENT_CLOSE_ACI_PAGE");
                finish();
                break;
        }
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        int keyCode = event.getKeyCode();
        int keyAcion = event.getAction();
        Boolean handleKey = false;
        Log.d(TAG, "dispatchKeyEvent " + keyCode + ":" + keyAcion);

        switch (keyCode) {
            case KeyEvent.KEYCODE_DPAD_UP:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.UP);
                }
                handleKey = true;
                break;
            case KeyEvent.KEYCODE_DPAD_DOWN:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.DOWN);
                }
                handleKey = true;
                break;
            case KeyEvent.KEYCODE_DPAD_LEFT:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.LEFT);
                }
                handleKey = true;
                break;
            case KeyEvent.KEYCODE_DPAD_RIGHT:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.RIGHT);
                }
                handleKey = true;
                break;
            case KeyEvent.KEYCODE_BACK:
            case KeyEvent.KEYCODE_ESCAPE:
                // consume back key
                handleKey = true;
                break;
			case KeyEvent.KEYCODE_DPAD_CENTER:
            case KeyEvent.KEYCODE_ENTER:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.ENTER);
                }
                handleKey = true;
                break;
            case KeyEvent.KEYCODE_PROG_BLUE:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.BLUE);
                }
                handleKey = true;
                break;
            case KeyEvent.KEYCODE_PROG_GREEN:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.GREEN);
                }
                handleKey = true;
                break;
            case KeyEvent.KEYCODE_PROG_RED:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.RED);
                }
                handleKey = true;
                break;
            case KeyEvent.KEYCODE_PROG_WHITE:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.WHITE);
                }
                handleKey = true;
                break;
            case KeyEvent.KEYCODE_PROG_YELLOW:
                if (keyAcion == KeyEvent.ACTION_DOWN) {
                    nwrap.aciNavigate(ACINavigate.YELLOW);
                }
                handleKey = true;
                break;
                default:
                	// for other keys let it call super to retain default bheaviour from wizard framework
                	// but return true to avoid android from handling by default for activity switching
                	super.dispatchKeyEvent(event);
                	handleKey = true;
                	break;
        }

        return handleKey ;
    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surfacetxt, int width, int height) {
        Log.d(TAG, "onSurfaceTextureAvailable");
        mSurface = new Surface(surfacetxt);
        nwrap.aciSetSurface(mSurface);
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture arg0) {
        Log.d(TAG, "onSurfaceTextureDestroyed");
        return false;
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture arg0, int arg1, int arg2) {
        Log.d(TAG, "onSurfaceTextureSizeChanged");

    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture arg0) {
        Log.d(TAG, "onSurfaceTextureUpdated");

    }
}
