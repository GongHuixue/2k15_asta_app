package org.droidtv.euinstallertc.util;


import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.RelativeLayout;

public class RalativeLayoutView extends RelativeLayout {

    private static final String TAG = RalativeLayoutView.class.getName();
    public IViewListener        mKeyListener;

    public RalativeLayoutView(Context context) {
        this(context, null, 0);
    }

    public RalativeLayoutView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);

    }

    public RalativeLayoutView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }

    public void addListener(IViewListener argKeyListener) {
        mKeyListener = argKeyListener;
    }

    public void removeListener() {
        mKeyListener = null;
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        Log.d(TAG, "dispatchKeyEvent for RalativeLayoutView");
        Log.d(TAG, String.valueOf(event.getAction()));
        Boolean l_ret = false;

        if (mKeyListener != null) {
            l_ret = super.dispatchKeyEvent(event);
            if (l_ret == false) {
                l_ret = mKeyListener.handleKeyEvent(event);
            }
            return l_ret;
        } else {
            return super.dispatchKeyEvent(event);
        }
    }
}
