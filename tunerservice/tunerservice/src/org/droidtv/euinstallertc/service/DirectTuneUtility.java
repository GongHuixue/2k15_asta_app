package org.droidtv.euinstallertc.service;

import java.io.IOException;

import org.droidtv.euinstallertc.model.mwapi.IntKeyValueablesPrivate;
import org.droidtv.euinstallertc.model.mwapi.NativeAPIWrapper;
import org.droidtv.euinstallertc.model.mwapi.TvContractPrivate;
import org.droidtv.tv.tvinput.ITvContractExtras;
import org.droidtv.tv.util.IIntKeyValueables;

import android.content.Context;
import android.content.Intent;
import android.media.tv.TvContract.Channels;
import android.util.Log;

class DirectTuneUtility {
	
	public static final int INDEX_TUNETYPE_DVB_T = 0;
	public static final int INDEX_TUNETYPE_DVB_C = 1;
	public static final int INDEX_TUNETYPE_DVB_T2 = 2;
	public static final int INDEX_TUNETYPE_ANALOG = 3;
	
	public interface DirectTuneResultInterface {
		public void sendDTResultIntent(int aiErrCode);
		public void switchToSpecificChannel(int aiChId);
	}
	
	public static class CommonDTResultHandler implements DirectTuneResultInterface {
		
		private String TAG = CommonDTResultHandler.class.getSimpleName();
		private Context mContext;
		private NativeAPIWrapper mWrapper = NativeAPIWrapper.getInstance();
		
		public CommonDTResultHandler(Context aContext) {
			mContext = aContext;
		}

		@Override
		public void sendDTResultIntent(int aiErrCode) {
			final String fsActionName = EuInstallerService.ACTNAME_DIRECT_TUNE_RESULT;
			Log.d(TAG, "sendDTResultIntent " + fsActionName);
			Intent l_intent = new Intent(fsActionName);
			l_intent.putExtra(EuInstallerService.KEYNAME_DTR_RESULT, aiErrCode);
			
			mContext.sendBroadcast(l_intent);
		}

		@Override
		public void switchToSpecificChannel(int aiChId) {
			mWrapper.switchToSpecificChannel(aiChId);			
		}
		
	}
	
	public static class WIXPDTResultHandler implements DirectTuneResultInterface {

		private String TAG = WIXPDTResultHandler.class.getSimpleName();
		private Context mContext;
		
		public WIXPDTResultHandler(Context aContext) {
			mContext = aContext;
		}
		
		@Override
		public void sendDTResultIntent(int aiErrCode) {
			/*
			final String fsActionName = EuInstallerService.ACTNAME_DIRECT_TUNE_WIXP;
			
			if(aiErrCode != 0) {
				Log.d(TAG, "sendDTResultIntent " + fsActionName);
				Intent l_intent = new Intent(fsActionName);
			
				l_intent.putExtra(EuInstallerService.KEYNAME_DTR_RESULT, aiErrCode);
			
				mContext.sendBroadcast(l_intent);
			}*/
		}

		@Override
		public void switchToSpecificChannel(int aiChId) {
			final String fsActionName = EuInstallerService.ACTNAME_DIRECT_TUNE_WIXP;
			Log.d(TAG, "sendDTResultIntent " + fsActionName);
			Log.d(TAG, "Intent extras: (" + EuInstallerService.KEYNAME_DTR_CHID + " , " + aiChId + ")");
			Intent l_intent = new Intent(fsActionName);
			
			l_intent.putExtra(EuInstallerService.KEYNAME_DTR_CHID, aiChId);
			
			mContext.sendBroadcast(l_intent);			
		}
		
	}
	
	public static DirectTuneResultInterface getDirectTuneResultHandler(boolean abIsWIXP, Context aContext) {
		if(abIsWIXP)
			return new WIXPDTResultHandler(aContext);
		
		return new CommonDTResultHandler(aContext);
	}
	
	public static class ChannelData {
		
		public int miTuneType;
		public int miChNo;
		public int miFreq;
		public Integer miONID = null;
		public Integer miTSID = null;
		public Integer miServID = null;
		public Integer miSymRt = null;
		public Integer miMod = null;
		public Integer miTvSys = null;
		public Integer miBlank = null;
		public Integer miSkip = null;
		public String msChName = null;
		public Integer miBW = null;
		public Integer miPLPID = null;
		public int miPresetNum= 1;
		
		public ChannelData() {
		}
		
		public ChannelData(int aiTuneType,int aiFreq, Integer aiONID, Integer aiTSID, Integer aiServID, Integer aiSymRt) {
			miTuneType = aiTuneType;
			miFreq = aiFreq;
			miONID = aiONID;
			miTSID = aiTSID;
			miServID = aiServID;
			miSymRt = aiSymRt;
		}
	}
	
	public static String mapTuneTypeString(int aiTuneType) {
		
		String fsResult = null;
		
		switch(aiTuneType) {
		case INDEX_TUNETYPE_DVB_T:
			fsResult = Channels.TYPE_DVB_T;
			break;
		case INDEX_TUNETYPE_DVB_C:
			fsResult = Channels.TYPE_DVB_C;
			break;
		case INDEX_TUNETYPE_DVB_T2:
			fsResult = Channels.TYPE_DVB_T2;
			break;
		case INDEX_TUNETYPE_ANALOG:
			fsResult = Channels.TYPE_PAL;			
		}
		
		return fsResult;
	}
	
	public static int mapVersion(int aiTuneType) {
		
		int fiResult = 0;
		
		switch(aiTuneType) {
		case INDEX_TUNETYPE_DVB_T:		
		case INDEX_TUNETYPE_DVB_T2:
		case INDEX_TUNETYPE_ANALOG:
			fiResult = 0;
			break;
		case INDEX_TUNETYPE_DVB_C:
			fiResult = 1;			
		}
		
		return fiResult;
	}
	
	private static int convertModulation(ChannelData aChData) {
		
		int fiResult = 0;
		
		if(aChData.miTuneType == 0) {
			switch(aChData.miMod) {
			case 1:
				fiResult = 2;
				break;
			case 3:
				fiResult = 3;
				break;
			case 5:
				fiResult = 4;
			}
		} else if(aChData.miTuneType == 1) {
			fiResult = aChData.miMod;
		}
		
		return fiResult;
	}
	
	private static int convertTvSystem(ChannelData aChData) {
		
		int fiTvSys;
		
		switch(aChData.miTvSys) {		
		case 1:
			fiTvSys = 0x4;//AnalogSystemCountry.EAST_EUROPE;
			break;
		case 2:
			fiTvSys = 0x2;//AnalogSystemCountry.UK;
			break;
		case 3:
			fiTvSys = 0x8;//AnalogSystemCountry.FRANCE;
			break;
		case 0:
		default:
			fiTvSys = 0x1;//AnalogSystemCountry.WEST_EUROPE;		
		}
		
		return fiTvSys;
	}
	
	public static byte[] formBlobData(ChannelData aChData) throws IOException {
		
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		
		keyvalues.put(ITvContractExtras.C_FREQUENCY, aChData.miFreq);
		
		if(aChData.miBW != null)
			keyvalues.put(ITvContractExtras.C_BANDWIDTH, aChData.miBW);
		
		if(aChData.miSymRt != null)
			keyvalues.put(ITvContractExtras.C_SYMBOLRATE, aChData.miSymRt);
		
		if(aChData.miMod != null)
			keyvalues.put(ITvContractExtras.C_MODULATION, convertModulation(aChData));
		else if(aChData.miTvSys != null)
			keyvalues.put(ITvContractExtras.C_MODULATION, convertTvSystem(aChData));
		
		keyvalues.put(ITvContractExtras.C_NUMERICSELECT, 1);
		
		keyvalues.put(ITvContractExtras.C_HBBTVON, 1);
		
		keyvalues.put(ITvContractExtras.C_AUDIOPID, 8191);
		keyvalues.put(ITvContractExtras.C_VIDEOPID, 8191);
		keyvalues.put(ITvContractExtras.C_PCRPID, 8191);
		keyvalues.put(ITvContractExtras.C_TXTPAGES, 2047);
		
		if(aChData.miServID != null)
			keyvalues.put(ITvContractExtras.C_SERVICEIDENTIFIER, aChData.miServID);
		
		if(aChData.miTuneType == INDEX_TUNETYPE_DVB_T2) {
			if(aChData.miPLPID != null)
				keyvalues.put(ITvContractExtras.C_PLPID, aChData.miPLPID);
			else
				keyvalues.put(ITvContractExtras.C_PLPID, -1);
		}
		
		keyvalues.put(ITvContractExtras.C_PreferredStereo, 1);
		keyvalues.put(ITvContractExtras.C_PMTPID, 8191);
		keyvalues.put(ITvContractExtras.C_SECONDARY_AUDIOPID, 8191);
		
		IntKeyValueablesPrivate privatekeyvalues = new IntKeyValueablesPrivate();
		
		privatekeyvalues.put (TvContractPrivate.C_TS_VERSION, -1);
		
		//if(aChData.miTuneType == INDEX_TUNETYPE_DVB_T
		//		|| aChData.miTuneType == INDEX_TUNETYPE_DVB_T2
		//		|| aChData.miTuneType == INDEX_TUNETYPE_DVB_C)
		//	privatekeyvalues.put (TvContractPrivate.C_TYPE, 3); //Must set to onepart channel
		privatekeyvalues.put(TvContractPrivate.C_ANALOG_TABLE_PRESET, aChData.miPresetNum);
		
		keyvalues.put(ITvContractExtras.C_INSTALLER_BLOB, privatekeyvalues.getBlob());
		

		return keyvalues.getBlob();
	}

}
