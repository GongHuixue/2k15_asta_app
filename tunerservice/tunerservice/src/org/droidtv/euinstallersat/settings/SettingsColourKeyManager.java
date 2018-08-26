package org.droidtv.euinstallersat.settings;

import org.droidtv.ui.tvwidget2k15.ColorKeys;
import org.droidtv.ui.tvwidget2k15.ColorKeys.IColorKeyCallback;

import android.content.Context;
public class SettingsColourKeyManager implements IColorKeyCallback
{
	ColorKeys m_colourKeys;
	Context m_context;

	public SettingsColourKeyManager(ColorKeys p_colorKeys, Context p_context)
	{
		m_colourKeys = p_colorKeys;
		m_colourKeys.registerCallback(this);
		m_context = p_context;
		m_colourKeys.setBlueLabel(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_COLOUR_HELP));
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
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean onGreenKeyPressed()
	{
		// TODO Auto-generated method stub
		return false;
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
	
	public void enableBlueKey()
	{
		m_colourKeys.setBlueLabel(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_COLOUR_HELP));
	}
	public void disableBlueKey()
	{
		m_colourKeys.setBlueLabel(null);
	}
	public void setHighlightedNodeId(int p_nodeId)
	{
		
	}

}
