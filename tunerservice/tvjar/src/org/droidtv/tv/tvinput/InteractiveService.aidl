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
package org.droidtv.tv.tvinput;

import android.view.Surface;
import android.os.IBinder;
import android.view.KeyEvent;
import java.util.List;

/** @hide */
interface InteractiveService {

	/*
	* Once the TextureView is added to the MediaOverlay to support rendering graphics 
	* of the Interactive applications the Surface is parcelled to the Interactive Applications
	* with this method.
	*/
	void setSurface(in Surface surface);
	
	/**
	 * The TextureView is in the MediaOverlay and key events from the Activity are parcelled to the Service. 
	 * These keys have to be sent to the interactive engine to decide if the key event and take necessary action
	 * or pass it back if no action is required.
	 * @return TRUE/FALSE based on whether the key is consumed by interactive engine.
	 */
	boolean onKeyEvent ( in KeyEvent event );
	
	/**
	* The List of Surfaces contains two Surfaces
	*	1) VideoPlayback for http playback
	*	2) Subtitles support for http playback
	*   surfaceindex 0 -> video Surface 
	*   surfaceindex 1 -> subtitle Surface
	*/
	void setMediaPlaybackSurfaces(in List<Surface> surface);
	
	/**
	* To draw a background to the video surface view passed.
	* The View is actually placed on top of the video Surface but 
	* the cutting/punching hole has to be taken care by the interactive application
	**/
	void setVideoBackgroundSurface(in Surface surface);
		
    /**
	 * Register listener for interactive services. This call is made by PlayTV on 
	 * interactive services so that interactive * services need not explicitly bind 
	 * to any of the PlayTV services
	 * @param listener
	 */
	void setInteractiveServiceCallbackListener(IBinder listener);

	/**
	* Indicates InteractiveApp to start 
	**/
    void start();

	/**
	* Indicates InteractiveApp to stop 
	**/
	void stop();
	
	/**
	 * Method to launch an interactive application from another InteractiveApp
	 */	
	void startApp(String url);
	
}
