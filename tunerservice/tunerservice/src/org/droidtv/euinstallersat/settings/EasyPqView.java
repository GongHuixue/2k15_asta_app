package org.droidtv.euinstallersat.settings;

import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.MenuItem;
import org.droidtv.ui.tvwidget2k15.setupmenuframework.interfaces.ICompanionWidgetControl;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class EasyPqView extends RelativeLayout implements ICompanionWidgetControl {

	private final String TAG = EasyPqView.class.getName();

	private View view;
	private TextView mDescView;
	private Context mContext;
	private int mCurrentState = -1;
	private String[] stringArray;

	public EasyPqView(Context context) {
		this(context, null, 0);
	}

	public EasyPqView(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public EasyPqView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		mContext = context;
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		view = inflater.inflate(R.layout.easy_pq_view, this, true);
		mDescView = (TextView) view.findViewById(R.id.textView);

	}

	@Override
	public void setData(MenuItem node, int value) {

		String[] desctiptionTextArray = node.getHintText();

		if (desctiptionTextArray != null) {
			String descText = desctiptionTextArray[0];
			Log.d(TAG, "descText " + descText);
			if(descText != null) {
				if ((descText.trim() == "") || (descText.equalsIgnoreCase(mContext.getString(org.droidtv.ui.strings.R.string.MAIN_NONE)))) {
					view.setVisibility(GONE);
				} else {
					view.setVisibility(VISIBLE);
					mDescView.setVisibility(VISIBLE);
					mDescView.setText(descText);
				}
			}
		}
	}

	@Override
	public void onNodeFocusGained() {
		// TODO Auto-generated method stub

	}

	@Override
	public void onNodeFocusLost() {
		// TODO Auto-generated method stub

	}
}
