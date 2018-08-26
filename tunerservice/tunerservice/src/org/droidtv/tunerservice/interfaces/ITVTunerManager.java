package org.droidtv.tunerservice.interfaces;

import java.lang.String;
import android.os.Bundle;
import android.view.View;
import android.view.Surface;
import org.droidtv.tunerservice.TunerService;
import org.droidtv.tv.tvinput.ITVTunerSession;
import android.media.tv.TvInputService.Session;
import org.droidtv.tv.media.TvMediaPlayerContext;
import org.droidtv.tunerservice.tvmanager.AuxTVManager;
import org.droidtv.tunerservice.tvmanager.MainTVManager;

public interface ITVTunerManager extends ITVTunerSession,ITVInputSession{

	public void registerListener(TunerService.TunerSession pListener);
	public void unRegisterListener(TunerService.TunerSession pListener);
	public void notifyEvent(final String pEvent, Bundle pData);
	public TvMediaPlayerContext getTvMediaPlayerContext();
	public View getOverlayView();
	public void setMainTvManager(MainTVManager maintvManager);
	public void setAuxTvManager(AuxTVManager auxtvManager);
	public void setSession(Session session, Surface surface);
	public Session getCurrentActiveSession();
}
