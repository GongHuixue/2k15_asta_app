package org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard;

import java.util.Observer;

import org.droidtv.euinstallersat.wizard.settings.connectionTypeWizard.ConnTypeWizard.ConnTypeScreenReq;

public interface ConnTypeScreen extends Observer
{
	public abstract void setInstance(ConnTypeWizard p_wizard); 
	public abstract ConnTypeScreenReq getScreenName(); 
	public abstract void screenIntialization(); 
}
