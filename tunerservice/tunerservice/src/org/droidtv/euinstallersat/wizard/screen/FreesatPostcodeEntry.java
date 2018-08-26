package org.droidtv.euinstallersat.wizard.screen;

import java.util.Observable;

import org.droidtv.tunerservice.R;
import org.droidtv.euinstallersat.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;
import org.droidtv.euinstallersat.wizard.util.InvalidPostCodeDialog;
import org.droidtv.euinstallersat.wizard.util.SatelliteScreen;
import org.droidtv.ui.tvwidget2k15.wizardframework.WizardStep;


import android.content.Context;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextWatcher;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;

public class FreesatPostcodeEntry extends WizardStep implements SatelliteScreen, TextWatcher,OnEditorActionListener
{
	NativeAPIWrapper m_wrapper;
	Context m_Context;
	private static final String TAG = FreesatPostcodeEntry.class.getName();
	private final int MAX_LENGTH = 9;
	EditText m_postCodeText;
	Button m_buttonCancel;
	Button m_buttonPrevious;
	Button m_buttonNext;
	private SatelliteWizard mSatelliteWizard;
	
	public FreesatPostcodeEntry(Context context, AttributeSet attrSet, int defStyle)
	{
		super(context, attrSet, defStyle);
		m_Context = context;
		m_wrapper = NativeAPIWrapper.getInstance();
		loadLayout(context, attrSet, defStyle);
	}
	
	public FreesatPostcodeEntry(Context context, AttributeSet attrSet)
	{
		this(context, attrSet, 0);
	}

	public FreesatPostcodeEntry(Context context)
	{
		this(context, null, 0);
	}

	@Override
	public void update(Observable observable, Object data)
	{
		// TODO Auto-generated method stub

	}

	@Override
	public void setInstance(SatelliteWizard wizard)
	{
		mSatelliteWizard = wizard;

	}

	@Override
	public ScreenRequest getScreenName()
	{
		return ScreenRequest.FREESAT_POSTCODE_ENTRY;
	}

	@Override
	public void screenIntialization()
	{
		Log.d(TAG, "screenIntialization");
		m_postCodeText.requestFocus();
		m_postCodeText.requestFocusFromTouch();
		setButton3Enabled(false);

	}
	
	private void loadLayout(final Context context, AttributeSet attrs, int defStyle)
	{
		LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View view = inflater.inflate(R.layout.freesat_postcode_entry, null);
		addView(view);
		
		String l_hintText = m_Context.getString(org.droidtv.ui.strings.R.string.MAIN_WI_SAT_POSTCODE);
		setHintText(l_hintText);
		m_postCodeText = (EditText) view.findViewById(R.id.postCode_edittext);
		m_postCodeText.addTextChangedListener(this);
		// m_postCodeText.setFocusable(true);
		m_postCodeText.setOnKeyListener(this);
		m_postCodeText.setOnEditorActionListener(this);
		m_postCodeText.setFilters(new InputFilter[]{new InputFilter.AllCaps(),new InputFilter.LengthFilter(MAX_LENGTH)});
		 
		
		OnClickListener buttonCancel_Listener = new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				Log.d(TAG,"cancel on PostCode Entry screen: Should Lauch StartScreen");
				m_wrapper.SetScanStops();
				m_wrapper.resetInstallation();
				mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.STARTSCREEN, getScreenName());	

			}
		};
		
	
		OnClickListener buttonNext_Listener = new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				if(m_wrapper.isPostCodeValid(m_postCodeText.getText().toString()))
               	{
                	Log.d(TAG,"Next on PostCode Entry screen: Should Lauch INSTALLSCREEN.");
					m_wrapper.setPostCode(m_postCodeText.getText().toString());
					m_wrapper.SetSelectedPackage(true);
					mSatelliteWizard.launchScreen(SatelliteWizard.ScreenRequest.INSTALLSCREEN, getScreenName());
               	}
               	else
               	{
                		  Log.d(TAG,"InValid PostCode Entered !!");
                		  showInvalidPostCodeDialog();
               	}
				
			}
		};

		String l_btnNext_txt = m_Context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_NEXT);
		String l_btnPrev_txt = m_Context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_PREVIOUS);
		String l_btnCancel_txt = m_Context.getString(org.droidtv.ui.strings.R.string.MAIN_BUTTON_CANCEL);
		
		setButton3(l_btnNext_txt, buttonNext_Listener, View.VISIBLE);
		setButton2(l_btnPrev_txt, buttonCancel_Listener, View.VISIBLE);
		setButton1(l_btnCancel_txt, buttonCancel_Listener, View.VISIBLE);
		
		
		
	}
	
    @Override
    public boolean onKey(View view, int keyCode, KeyEvent event)
    {

           Log.d(TAG,"OnKey");
           boolean l_isKeyHandled = false;
       if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT && event.getAction() == KeyEvent.ACTION_DOWN)
       {
                  Log.d(TAG,"KEYCODE_DPAD_RIGHT");
                  if(m_postCodeText == view)
                  {
                	  if(m_wrapper.isPostCodeValid(m_postCodeText.getText().toString()))
                	  {
                	  	  Log.d(TAG,"Valid PostCode Entered !!");
						  setButton3Enabled(true);
                          setButton3focussed(); 
                	  }
                	  else
                	  {
                		  Log.d(TAG,"InValid PostCode Entered !!");
                		  showInvalidPostCodeDialog();
                	  }
                	 
                  }
				  else
				  {
					super.onKey(view, keyCode, event);
				  }
                  l_isKeyHandled = true;
       }
       else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && event.getAction() == KeyEvent.ACTION_DOWN)
       {
              Log.d(TAG,"KEYCODE_DPAD_LEFT");
              if(m_postCodeText == view)
              {
                    setButton1focussed();
              }
			  else
			  {
				super.onKey(view, keyCode, event);
			  }
              l_isKeyHandled = true;
       }
       Log.d(TAG,"OnKey returning " + l_isKeyHandled);
       return l_isKeyHandled;

}


    @Override
    public boolean onEditorAction(TextView v, int actionId, KeyEvent event) 
    {
        boolean handled = false;
        if ((event != null && (event.getKeyCode() == KeyEvent.KEYCODE_ENTER))
                    || (actionId == EditorInfo.IME_ACTION_DONE))
		{
		            	 
			InputMethodManager imm = (InputMethodManager)m_Context.getSystemService(Context.INPUT_METHOD_SERVICE);
			imm.hideSoftInputFromWindow(m_postCodeText.getWindowToken(), 0);
			setButton3Enabled(true);
            setButton3focussed();
        }
        return handled;
    }

	private void showInvalidPostCodeDialog()
	{
			Log.d(TAG,"show InvalidPostCode Dialog");
			InvalidPostCodeDialog l_dialog = new InvalidPostCodeDialog(m_Context,mSatelliteWizard);
			l_dialog.setNextScreen(ScreenRequest.FREESAT_POSTCODE_ENTRY, ScreenRequest.INSTALLSCREEN);
			l_dialog.showDialog();
			m_postCodeText.requestFocus();
			//Clearing the Previous Text
			m_postCodeText.setText("");
	}
	
	
	@Override
	public void screenExit()
	{
		// TODO Auto-generated method stub
		
	}

    	@Override
	public void afterTextChanged(Editable p_editable)
	{
		if (p_editable != null)
		{
			String l_postCode = p_editable.toString();
			Log.d(TAG, "l_postCode = " + l_postCode);
		}

	}

	@Override
	public void beforeTextChanged(CharSequence s, int start, int count, int after)
	{
		// TODO Auto-generated method stub

	}

	@Override
	public void onTextChanged(CharSequence s, int start, int before, int count)
	{
		// TODO Auto-generated method stub

	}
	
	

}
