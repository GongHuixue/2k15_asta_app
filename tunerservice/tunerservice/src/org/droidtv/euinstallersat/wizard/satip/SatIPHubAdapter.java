package org.droidtv.euinstallersat.wizard.satip;

import java.util.ArrayList;

import org.droidtv.tunerservice.R;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class SatIPHubAdapter extends BaseAdapter {

	private static final String TAG = SatIPHubAdapter.class.getName();
	private Context context;
	private ArrayList<SatIPHubItemInfo> itemList;

	public SatIPHubAdapter(Context context) {
		super();
		this.context = context;
	}

	public void setItemList(ArrayList<SatIPHubItemInfo> argItemList) {
		itemList = argItemList;
	}

	public ArrayList<SatIPHubItemInfo> getItemList() {
		return itemList;
	}

	@Override
	public int getCount() {
		return getItemList().size();
	}

	@Override
	public Object getItem(int itemPos) {
		return getItemList().get(itemPos).displayText;
	}

	@Override
	public long getItemId(int arg0) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public View getView(int position, View currentView, ViewGroup parent) {
		RelativeLayout rl = (RelativeLayout) View.inflate(context, R.layout.hub_listview, null);

		TextView dspTxt = (TextView) rl.findViewById(R.id.displayText);
		TextView dspSubTxt = (TextView) rl.findViewById(R.id.displaySubText);
		RelativeLayout tickMark = (RelativeLayout) rl.findViewById(R.id.tickMark);

		if (getItemList().get(position).isCompleted) {
			tickMark.setVisibility(View.VISIBLE);
		} else {
			tickMark.setVisibility(View.INVISIBLE);
		}
		
		dspTxt.setText(getItemList().get(position).displayText);
		dspTxt.setHeight(context.getResources().getDimensionPixelSize(org.droidtv.ui.tvwidget2k15.R.dimen.list_row_height));
		dspTxt.setWidth(context.getResources().getDimensionPixelSize(org.droidtv.ui.tvwidget2k15.R.dimen.list_row_width));

		dspSubTxt.setText(getItemList().get(position).displaySubText);
		dspSubTxt.setHeight(context.getResources().getDimensionPixelSize(org.droidtv.ui.tvwidget2k15.R.dimen.list_row_height));
		dspSubTxt.setWidth(context.getResources().getDimensionPixelSize(org.droidtv.ui.tvwidget2k15.R.dimen.list_row_width));

		return rl;
	}

}
