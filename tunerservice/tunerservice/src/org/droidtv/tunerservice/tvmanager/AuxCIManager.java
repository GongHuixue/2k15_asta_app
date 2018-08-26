package org.droidtv.tunerservice.tvmanager;

import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.tvmplfactory.PlayTVFacMediaPlayer;
import android.util.Log;
import android.net.Uri;
import android.os.Bundle;
import android.content.Context;
import org.droidtv.tv.media.TvMediaPlayerContext;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tunerservice.TunerService;
import org.droidtv.tv.tvinput.TVCIControlCallback;
import org.droidtv.tunerservice.tvmanager.AuxTVManager;
import org.droidtv.tunerservice.tvmpl.PlayTvCIPlusHandler;
import org.droidtv.tunerservice.interfaces.ICINotifyEvents;
import org.droidtv.tunerservice.overlay.OverlayManager;
import org.droidtv.tunerservice.util.PlayTvUtils;

public class AuxCIManager extends AbstractManager implements ICINotifyEvents{
	private static final String LOG_TAG  = "AuxCIManager";
	private Context mContext 						= null;
	private PlayTVFacMediaPlayer cplaytvmediaplayer = null;
	private PlayTVMediaPlayerFactory factory 		= null;
	private AuxTVManager mAuxTvManager				= null;
	private PlayTvCIPlusHandler mCiPlusHandler		= null;
	private static AuxCIManager mAuxCIManager;
		
	public AuxCIManager(Context pContext){
		mContext			= pContext;
		setAuxCIManager(this);
		factory				= PlayTVMediaPlayerFactory.getInstance();
		cplaytvmediaplayer 	= factory.getDirectMPLInstance(mContext,PlayTVMediaPlayerFactory.REQUEST_TYPE_AUX_CI);
		mCiPlusHandler		= new PlayTvCIPlusHandler(mContext,PlayTvUtils.AUX_ACTION,cplaytvmediaplayer);
		cplaytvmediaplayer.setCiPlusHandlerInstance(mCiPlusHandler);
	}
	
	private static void setAuxCIManager(AuxCIManager auxCIManager) {
		// TODO Auto-generated method stub
		mAuxCIManager=auxCIManager;
	}

	public static AuxCIManager getAuxCIManagerInstance(){
		return mAuxCIManager;
	}
	
	@Override
	public void setAuxTvManager(AuxTVManager auxtvManager) {
		Log.i(LOG_TAG,"setAuxTvManager called");
		mAuxTvManager = auxtvManager;
	}
	
	@Override
	public void setOverlayManager(OverlayManager overlayManager){
		if(mCiPlusHandler != null){
			mCiPlusHandler.setOverlayManager(overlayManager);
		}
	}
	
	@Override	
	public Uri getSelectedURI(){
		Log.i(LOG_TAG,"getSelectedURI called");
		if(mAuxTvManager != null) {
			return mAuxTvManager.getSelectedURI();
		}	
		return null;
	}
	
	@Override	
	public Uri getNextURI(Uri uri){
		Log.i(LOG_TAG,"getNextURI called .... current uri passed = "+uri);
		if(mAuxTvManager != null) {
			return mAuxTvManager.getNextURI(uri);
		}
		return null;
	}

	@Override	
	public Uri getPreviousURI(Uri uri){
		Log.i(LOG_TAG,"getPreviousURI called .... current uri passed = "+uri);
		if(mAuxTvManager != null) {
			return mAuxTvManager.getPreviousURI(uri);
		}
		return null;
	}
	
	@Override
    public void tune(Uri pChannelUri){
		Log.i(LOG_TAG,"tune called : " +pChannelUri);
		if(pChannelUri != null) {
			if(mAuxTvManager != null) {
				mAuxTvManager.tuneCamUpgradeChannel(pChannelUri);
			}
		}else {
			Log.i(LOG_TAG,"Not possible to tune as URI is NULL !!!");
		}
	}
	
	@Override
	public void tune(Uri pChannelUri,Bundle params) {
		Log.i(LOG_TAG,"tune called : " +pChannelUri);
		if(params == null) {
			if(mAuxTvManager != null) {
				mAuxTvManager.tuneCamUpgradeChannel(pChannelUri);
			}
		}else {
			Log.i(LOG_TAG,"tune with Bundle as of now not supported for AuxCIManager!!!");
		}
	}
	
	@Override
	public TvMediaPlayerContext getTvMediaPlayerContext(){
		TvMediaPlayerContext itmpc = null;
		if(cplaytvmediaplayer!=null) {
			itmpc = (TvMediaPlayerContext)cplaytvmediaplayer.getMediaPlayerInstance().getTvMediaPlayerContext();
		}
		return (TvMediaPlayerContext)itmpc;
	}
	
	@Override
	public void release(TunerService.TunerSession pSession){
		Log.i(LOG_TAG,"release called");
		cplaytvmediaplayer.setCiPlusHandlerInstance(null);
		cplaytvmediaplayer = null;
		mCiPlusHandler	   = null;
	}
	
	public void enableMMI(boolean enable) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.enableMMI(enable);
		}
	}
	
	public void updateMMIStatus(boolean status) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.updateMMIStatus(status);
		}
	}
	
	public void selectMMIItem(int menuType,int selectedItem) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.selectMMIItem(menuType,selectedItem);
		}
	}
	
	public String[] getMMIItems(int menuType) {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getMMIItems(menuType);
		}
		return null;
	}
	
	public int getLastSelectedMenuIndex() {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getLastSelectedMenuIndex();
		}
		return 0;
	}
	
	public void setEnquiryMMIResponse(String answer) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.setEnquiryMMIResponse(answer);
		}
	}
	
	public CIMmiEnq getEnquiryMMIInfo() {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getEnquiryMMIInfo();
		}
		return null;
	}
	
	public void cancelMMI(int menutype){
		if(mCiPlusHandler != null) {
			mCiPlusHandler.cancelMMI(menutype);
		}
	}

	public void enableCamUpgrade(boolean enable){
		if(mCiPlusHandler != null) {
			mCiPlusHandler.enableCamUpgrade(enable);
		}
	}
	
	public int getCAMUpgradeStatus() {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getCAMUpgradeStatus();
		}
		return 0;
	}
	
	public void updateCamInfo(CamInfo caminfo) {
		if(mCiPlusHandler != null) {
			mCiPlusHandler.updateCamInfo(caminfo);
		}
	}
	
	public void enableCAMUI(boolean enable) {
		//dummy
	}
	
	public CamInfo getCamInfo(int slotId) {
		if(mCiPlusHandler != null) {
			return mCiPlusHandler.getCamInfo(slotId);
		}
		return null;
	}
	
	public void registerCIControlListener(TVCIControlCallback callback){
		if(mCiPlusHandler != null) {
			mCiPlusHandler.registerCIControlListener(callback);
		}	
	}

	public void unRegisterCIControlListener(TVCIControlCallback callback){
		if(mCiPlusHandler != null) {
			mCiPlusHandler.unRegisterCIControlListener(callback);
		}
	}
	@Override
	public void notifyChannelInstallStatus(boolean status,Medium medium){
		Log.i(LOG_TAG,"Channel Installtion Completed notifyChannelInstallComplete called");
		
		if(mCiPlusHandler != null){
			mCiPlusHandler.notifyChannelInstallStatus(status,medium);
		}else {
			Log.d(LOG_TAG,"not shown camwizard as PlayTvCIPlusHandler object is null");
		}
			
	}
}
