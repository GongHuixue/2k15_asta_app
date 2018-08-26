package org.droidtv.tunerservice.interfaces;

import android.view.Surface;
import android.net.Uri;
import android.graphics.Rect;
import android.media.tv.TvTrackInfo;
import android.os.Bundle;
import android.os.IBinder;
import java.lang.String;
import org.droidtv.tunerservice.TunerService.TunerSession;

public interface ITVInputSession{

	void release(TunerSession pSession);
	
    void setMainSession(boolean pIsMainSession);	
	
    void setSurface(Surface pSurface);	
	
    void dispatchSurfaceChanged(int pFormat, int pWidth, int pHeight, Surface pSurface);

	void setVolume(float pVolume);
	
    void tune(Uri pChannelUri);	

	void tune(Uri pChannelUri,Bundle params);		
	
    void setCaptionEnabled(boolean pEnabled);
	
    void selectTrack(TvTrackInfo pTrack);
	
    void unselectTrack(TvTrackInfo pTrack);

    void appPrivateCommand(String pAction, Bundle pData);

    void createOverlayView(IBinder pWindowToken, Rect pFrame);
	
    void relayoutOverlayView(Rect pFrame);
	
    void removeOverlayView();

    void requestUnblockContent(String pUnblockedRating);
	
	void SetMain(boolean isMainSession);
	
	void setSessionType(String sessionType);

}