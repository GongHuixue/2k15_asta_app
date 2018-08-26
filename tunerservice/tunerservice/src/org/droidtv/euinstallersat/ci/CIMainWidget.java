package org.droidtv.euinstallersat.ci;


import android.util.Log;


public class CIMainWidget extends CIInitializeInterface{

	private static final String TAG = CIMainWidget.class.getName();
	private static CIMainWidget ciWidget;
	private static final String action = "org.droidtv.action.ACTION_MAIN_AMMI";
	
	private CIMainWidget(){
	}
	public static CIMainWidget getInstance() {
		if (ciWidget == null) {
			ciWidget = new CIMainWidget();
		}
		Log.i(TAG, "CIMainWidget called:"+ciWidget);
		return ciWidget;
	}
	
	

}
