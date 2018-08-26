package org.droidtv.euinstallersat.wizard.util;

import java.util.Observer;

import org.droidtv.euinstallersat.wizard.SatelliteWizard;
import org.droidtv.euinstallersat.wizard.SatelliteWizard.ScreenRequest;

public interface SatelliteScreen extends Observer {

	public abstract void setInstance(SatelliteWizard wizard); // individual screen can always get the context of main application
	public abstract ScreenRequest getScreenName(); // individual screen should always return unique name, used for navigation
	public abstract void screenIntialization(); // whenever screen is launched this function is called, all the init shouls
	public abstract void screenExit(); // called when dialog invoked by back key forces launch of first screen
}
