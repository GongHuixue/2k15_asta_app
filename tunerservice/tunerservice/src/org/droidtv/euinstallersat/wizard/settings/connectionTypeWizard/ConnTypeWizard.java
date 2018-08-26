package org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Stack;

import org.droidtv.tunerservice.R;
import org.droidtv.ui.tvwidget2k15.NPanelBrowser;
import org.droidtv.ui.tvwidget2k15.VerticalText;
import org.droidtv.ui.tvwidget2k15.wizardframework.Wizard;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;

public class ConnTypeWizard extends Wizard
{

	private final String TAG = ConnTypeWizard.class.getName();
	
	private int m_progress;
	
	private Context m_context;
	
	private ArrayList<View> m_satelliteInstallation;
	private Stack<ConnTypeScreenReq> m_screenRequestStack;
	
	private ConnTypeScreenReq m_launchItem = ConnTypeScreenReq.SETTINGS;
	private ConnTypeScreen m_selectedSatelliteScreen = null;
	
	private NPanelBrowser m_nPanelBrowser;
	
	

	public enum ConnTypeScreenReq
	{
		SETTINGS, UNICABLEUBN, UNICABLEUBF, UNICABLEUBN2, UNICABLEUBF2, LNBSELECTION
	}

	public ConnTypeWizard(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		m_context = context;
		m_screenRequestStack = new Stack<ConnTypeWizard.ConnTypeScreenReq>();
		m_launchItem = ((ConnTypeActivity)m_context).firstScreen();
		m_screenRequestStack.push(m_launchItem);
		m_satelliteInstallation = new ArrayList<View>();
		loadLayout(context);
	}

	public ConnTypeWizard(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public ConnTypeWizard(Context context)
	{
		this(context, null, 0);
	}

	
	private void loadLayout(Context p_context)
	{
		ViewGroup l_viewGroup = (ViewGroup) View.inflate(m_context, R.layout.conntype_wizard_steps, null);
		m_nPanelBrowser = (NPanelBrowser) ((Activity) m_context).findViewById(org.droidtv.ui.tvwidget2k15.R.id.nPanelBrowser1);
		while (l_viewGroup.getChildCount() != 0)
		{
			View step = l_viewGroup.getChildAt(0);
			((ConnTypeScreen) step).setInstance(this);
			((WizardStep) step).setWizardListener(this);
			m_satelliteInstallation.add(step);
			l_viewGroup.removeViewAt(0);
		}
	}

	public void initWizardScreen()
	{
		if(m_selectedSatelliteScreen !=null)
		{
			m_selectedSatelliteScreen.screenIntialization();
		}
	}
	

	public void launchPreviousScren()
	{
		m_launchItem = m_screenRequestStack.pop();
		Log.d(TAG, "launchPreviousScreen currentscreen:" + m_launchItem);
		m_nPanelBrowser.scrollPrevPage();
		if(m_selectedSatelliteScreen !=null)
		{
			m_selectedSatelliteScreen.screenIntialization();
		}
	}

	public void launchScreen(ConnTypeScreenReq launchItem, ConnTypeScreenReq currentItem)
	{

		m_screenRequestStack.push(m_launchItem);
		m_launchItem = launchItem;
		m_nPanelBrowser.scrollNextPage(); // trigger callback by framework to getPanelView(index) function
		if(m_selectedSatelliteScreen !=null)
		{
			m_selectedSatelliteScreen.screenIntialization();
		}

	}

	@Override
	public void gotoNextStep()
	{
		super.gotoNextStep();
	}

	public ConnTypeScreenReq getCurrentScreen()
	{
		Log.d(TAG, "getCurrentScreen() " + m_launchItem);
		return m_launchItem;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.droidtv.ui.comps.wizardframework.Wizard#getBacktraceView(int,
	 * android.view.View)
	 */
	@Override
	public View getBacktraceView(int p_depth, View p_view)
	{
		Log.i(TAG, "getBackTrace View called");
		Iterator<View> l_iterator = m_satelliteInstallation.iterator();
		while (l_iterator.hasNext())
		{
			View l_retView = l_iterator.next();
			VerticalText l_verticalText;
			if((p_view != null) && (p_view instanceof VerticalText))
			{
				l_verticalText = (VerticalText)p_view;
			}
			else
			{
				l_verticalText = new VerticalText(m_context);
			}
			if (p_depth == -1)
			{
				
				l_verticalText.setText(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_CONNECTION_TYPE));
				return l_verticalText;
			}
			else
			{
				if (m_launchItem == (((ConnTypeScreen) l_retView).getScreenName()))
				{
					Log.i(TAG, "m_launchItem:" + m_launchItem);

					if (l_retView.getTag() != null)
					{
						l_verticalText.setText(l_retView.getTag().toString());
						Log.i(TAG, "vertical Text:" + l_verticalText.getText().toString());
						Log.i(TAG, "retView Text:" + l_retView.getTag().toString() + "RetView:" + l_retView);
					}
					else
					{
						l_verticalText.setText("Install Modes");
					}
					return l_verticalText;
				}
			}
		}
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.droidtv.ui.comps.wizardframework.Wizard#getPanelView(int)
	 */
	@Override
	public View getPanelView(int p_index)
	{
		View l_retView = null;
		setWizardLabel(m_context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_SETTINGS));
		m_progress = p_index;
		if (m_progress >= 0 && m_progress < m_satelliteInstallation.size() - 1)
		{
			setWizardProgress(m_progress + 1, m_satelliteInstallation.size() - 1);
		}

		Iterator<View> l_iterator = m_satelliteInstallation.iterator();
		while (l_iterator.hasNext())
		{
			l_retView = l_iterator.next();

			if (m_launchItem == ((ConnTypeScreen) l_retView).getScreenName())
			{
				Log.v(TAG, "getPanel View reView:" + l_retView);
				m_selectedSatelliteScreen = ((ConnTypeScreen) l_retView);
				
				return l_retView;
			}
		}
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.droidtv.ui.comps.wizardframework.Wizard#isFocussable(int)
	 */
	@Override
	public boolean isFocussable(int p_index)
	{
		if (p_index < m_satelliteInstallation.size())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}
