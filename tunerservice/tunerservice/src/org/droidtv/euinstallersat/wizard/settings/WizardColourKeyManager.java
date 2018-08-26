package org.droidtv.euinstallersat.wizard.settings;

import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.model.notification.NotificationHandler;
import org.droidtv.euinstallersat.util.EventIDs;
import org.droidtv.ui.tvwidget2k15.ColorKeys;
import org.droidtv.ui.tvwidget2k15.ColorKeys.IColorKeyCallback;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
public class WizardColourKeyManager implements IColorKeyCallback
{
	ColorKeys m_colourKeys;
	Context m_context;
	NativeAPIWrapper m_wrapper;
	NotificationHandler m_ntfHandler;
	private static final String TAG = WizardColourKeyManager.class.getName();

	public WizardColourKeyManager(ColorKeys p_colorKeys, Context p_context)
	{
		m_colourKeys = p_colorKeys;
		m_colourKeys.registerCallback(this);
		m_context = p_context;
		m_wrapper = NativeAPIWrapper.getInstance();
		m_ntfHandler = NotificationHandler.getInstance();
		m_colourKeys.setGreenLabel(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_COLOUR_DONE));
		m_colourKeys.setRedLabel(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_COLOUR_RESET));
	}

	@Override
	public boolean onInfoKeyPressed()
	{
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean onRedKeyPressed()
	{
		Log.d(TAG,"onRedKeyPressed");
		m_wrapper.resetLnbSettings();
		((Activity)m_context).finish();
		m_ntfHandler.notifyAllObservers(EventIDs.WIZARD_SETTINGS_EXIT,"");
		return false;
	}

	@Override
	public boolean onGreenKeyPressed()
	{
		Log.d(TAG,"onGreenKeyPressed");
		((Activity)m_context).finish();
		m_ntfHandler.notifyAllObservers(EventIDs.WIZARD_SETTINGS_EXIT,"");
		return true;
	}

	@Override
	public boolean onYellowKeyPressed()
	{
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean onBlueKeyPressed()
	{
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean onOptionKeyPressed()
	{
		// TODO Auto-generated method stub
		return false;
	}
	
	public void setHighlightedNodeId(int p_nodeId)
	{
		
	}

}
