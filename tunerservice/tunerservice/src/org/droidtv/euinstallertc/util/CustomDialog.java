package org.droidtv.euinstallertc.util;

import android.app.Dialog;
import android.content.Context;
import android.util.Log;
import android.view.KeyEvent;

public class CustomDialog extends Dialog {

    private static final String TAG = CustomDialog.class.getName();

    public CustomDialog(Context context) {
        super(context);
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        boolean keyHandled = false;
        int keyCode = event.getKeyCode();
        if ((keyCode == KeyEvent.KEYCODE_DPAD_LEFT)
                || (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT)
                || (keyCode == KeyEvent.KEYCODE_DPAD_UP)
                || (keyCode == KeyEvent.KEYCODE_DPAD_DOWN)
                || (keyCode == KeyEvent.KEYCODE_DPAD_CENTER)
                || (keyCode == KeyEvent.KEYCODE_BACK)
                || ((keyCode >= KeyEvent.KEYCODE_0) &&  
                        (keyCode <= KeyEvent.KEYCODE_9))
                ) {
            keyHandled = false;
        } else {
            Log.d(TAG,"dispatchKeyEvent consumed for key " + event.getKeyCode());
            keyHandled = true;
        }

        return keyHandled || super.dispatchKeyEvent(event);
    }
}
