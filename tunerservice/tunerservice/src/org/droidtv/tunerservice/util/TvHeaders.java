package org.droidtv.tunerservice.util;

public class TvHeaders {
	
	public static final String FREQUENCY					= "freq";
	public static final String SYMBOL_RATE					= "symrate";
	public static final String BANDWIDTH					= "bw";
	public static final String MODE							= "mode";
	public static final String PRESET_ID					= "Presetid";
	public static final String VIDEO_PID					= "vpid";
	public static final String AUDIO_PID					= "apid";
	public static final String PCR_PID						= "pcrpid";
	public static final String VIDEO_STREAM_TYPE			= "vstreamtype";
	public static final String AUDIO_STREAM_TYPE			= "astreamtype";
	public static final String CACHE_ID						= "cacheid";
	public static final String POLARIZATION					= "polarization";
	public static final String LNB_NUMBER					= "lnbno";
	public static final String LNB_TYPE						= "lnbtype";
	public static final String MODULATION					= "constellation";
	public static final String PLP_ID						= "plpid";
	public static final String STREAM_PRIORITY				= "streamprio";
	public static final String SERVICE_ID					= "sid";
	public static final String LOCK							= "lock";
	public static final String SELECTION_TYPE				= "seltype";
	public static final String USER_TYPE					= "usertype";
	public static final String CI_CAM						= "cicam";
	public static final String COMPLETE_URI					= "completeUri";
	public static final String LO_LOW_FREQUENCY				= "lolow";
	public static final String LO_HIGH_FREQUENCY			= "lohigh";
	public static final String TONE 						= "tone";
	public static final String LNB_POWER					= "custompow";
	public static final String CONNECTION_TYPE				= "connectiontype";
	public static final String USER_BAND_TUNER 				= "ubn";
	public static final String USER_BAND_FREQUENCY_TUNER	= "ubf";
	public static final String TV_SYSTEM					= "tvsys";
	public static final String MEDIUM						= "medium";
	public static final String SATIP_MODSYS					= "modsys";
	public static final String SATIP_FECINNER				= "fecinner";
	public static final String SATIP_ROLLOFF				= "rolloff";
	public static final String SATIP_PILOTS					= "pilots";
	public static final String FILE_LOCATION				= "location";
	public static final String RESOURCE_PQ_TYPE				= "PqResType";
	public static final String PREFERRED_STEREO				= "preferredStereo";
	public static final String SAP							= "sap";
	public static final String UNIQUE_ID					= "uniqueid";
	public static final String RECORDING_ID					= "recid";
	public static final String REQUEST_TYPE					= "reqType";
	public static final String SERVICE_TYPE         		= "serviceType";
	public static final String REQUEST_SUB_TYPE				= "reqSubType";
	public static final String WAKEUP_SELECTION				= "wakeup_selection";
	public static final String DISABLE_AUTO_MUTE			= "disable_auto_mute";
	public static final String PRIV_DATA_COOKIE				= "private_data_cookie";
	public static final String OUTPUT_TYPE					= "OutputType";
	public static final String OLYMPIC_USECASE				= "olympicUsecase";
	public static final String CAM_UPGRADE					= "camupgrade";
	public static final String NEW_PRESET	         		= "new_preset";
	public static final String RESTORE_CHANNEL_STATE		= "restore_channel_state";
	public static final String FILE_URI					= "file://";
	public static final String FORCE_CHANNEL_TUNING = "FRTUNE";
	public static final String HTV_DI_CHANNEL_CHECK_FLAG = "HTVDICHK";
	public static final String CHANNEL_ID 					= "channelid";
	
	public static final int MODE_ANALOG = 0x01;
	public static final int MODE_DVBT 	= 0x02;
	public static final int MODE_DVBT2	= 0x04;
	public static final int MODE_DVBC 	= 0x08;
	public static final int MODE_DVBS 	= 0x10;
	public static final int MODE_SATIP 	= 0x40;
	public static final int MODE_LOCAL_FILE = 0x80;
	
	public static final int	PQ_TYPE_SUB	= 0x02;
	
	public static final int PATH_AV 	= 0 ; // Both AUDIO & VIDEO outputs are required (default).
	public static final int PATH_AUDIO 	= 1 ; // Only Audio Output required, NO VIDEO
	public static final int PATH_VIDEO 	= 2 ; // Only Video Output required, NO AUDIO
	
	public static final String PRIV_DATA_CATCHUP_TUNE = "catch_up_tune";
}
