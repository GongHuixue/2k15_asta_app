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

import android.net.Uri;
import android.os.IBinder;
import android.graphics.Rect;

/**
 * This listener interface is registered on Interactive applications for Interactive services 
 * to make requests to carry on the activities decided by the Interactive Engine.
 */

/** @hide */
interface InteractiveServiceCallBack {

	/**
	 * To Set the video position for making the video position fitting in a PIP.
	 * @param left co-ordinate
	 * @param top co-ordinate
	 * @param width of the view 
	 * @param height of the view
	 */
	void setVideoPosition(int left, int top, int width, int height);
	
	/**
	*	To request TextureView for rendering background graphics of Interactive applications	
	*/
	void requestVideoBackgroundSurface();
	
	/**
	*	To release the requested TextureView for rendering background graphics of Interactive applications	
	*/
	void releaseVideoBackgroundSurface();
	
	/**
	*	To request SurfaceView Surface for Media Playback over http and 
	*	TextureView for rendering subtitles for the Media Playback by Interactive Applications
	*	surfaceindex 0 -> video Surface 
	*	surfaceindex 1 -> subtitle Surface
	*/
	void requestMediaPlaybackSurfaces(int video_manager_cacheid);
	
	/**
	*	To release the requested SurfaceView Surface for Media Playback over http and 
	*	TextureView for rendering subtitles for the Media Playback by Interactive Applications
	*/
	void releaseMediaPlaybackSurfaces();
	
	/**
	* To resize the View provided for subtitles or Video playback
	*	surfaceindex 0 -> video Surface 
	*	surfaceindex 1 -> subtitle Surface
	*/
	void relayoutMediaPlaybackSurface(int surfaceindex, int width, int height);
	
	/**
	* To resize the TextureView provided for rendering graphics of Interactive applications
	*/
	void relayoutSurface(int width, int height);
	
	/**
	* To resize the TextureView provided for rendering background graphics of Interactive applications
	*/
	void relayoutVideoBackgroundSurface(int width, int height);
	
	/**
	* Interactive applications indicate that the Application has started 
	**/
	void onAppStarted ();

	/**
	* Interactive applications indicate that the Application has exited
	**/
	void onAppExited ();
	
	/**
	 * Interactive applications are notified to start the engine and look for application based on the reference passed
	 */	
	 void invokeInteractiveApp(String url);

    /**
     * Interactive applications can resize the graphics to the match the rectange specified in the Rect r  
     * provided in this api. 
     */ 
     void relayoutToDestinationRectangle(in Rect r);

}

