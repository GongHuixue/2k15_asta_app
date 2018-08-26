package org.droidtv.tunerservice.iapp.interfaces;

public interface IAppListener{

	public void onAppStarted();
	
	public void onAppExited();
	
	public void invokeInteractiveApp(String Appreference);

}