/*
 *  Copyright(C) 2012 TP Vision Holding B.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of TP Vision Holding B.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of TP Vision Holding B.V.
 *
 */
package org.droidtv.euinstallertc.wizard;

import java.util.Observer;

import org.droidtv.euinstallertc.wizard.InstallationWizard.ScreenRequest;

public interface IInstallationScreen extends Observer {
	public abstract void setInstance(InstallationWizard wizard); // individual screen can always get the context of main application
	public abstract ScreenRequest getScreenName(); // individual screen should always return unique name, used for navigation
	public abstract void screenIntialization(); // whenever screen is launched this function is called, all the init should be done here
}
