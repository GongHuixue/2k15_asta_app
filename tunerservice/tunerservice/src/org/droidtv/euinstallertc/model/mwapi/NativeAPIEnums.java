package org.droidtv.euinstallertc.model.mwapi;

public class NativeAPIEnums {
	public enum InstallationMode{
		AUTOSTORE_INSTALLATION,
		UPDATE_INSTALLATION,
		BACKGROUND_INSTALLATION,
		BACKGROUND_UPDATE,
		AUTOSTORE_PRESCAN,
		UPDATE_PRESCAN,
		DTR_INSTALLATION,
		CAM_INSTALLATION,
		NETWORK_UPDATE,
		MANUAL_INSTALLATION,
		INCOMPLETE_INSTALLATION,
		HTV_DTR_INSTALLATION
	}
	
	public enum TVMenuLanguage {
		ENGLISH,
		GERMAN
	}
	
	public enum DVBTOrDVBC {
		DVBT,
		DVBC
	}
	
	public enum DVBTMacro{
		DVBT_Full,
		DVBT_Light,
		DVBT_NotSupported
	}
	
	public enum DVBCMacro{
		DVBC_Full,
		DVBC_Light,
		DVBC_NotSupported
	}
	
	public enum DVBTOrDVBCMacro{
		DVBT_Full,
		DVBT_Light,
		DVBC_Full,
		DVBC_Light,
		DVBC_NotSupported,
		DVBT_NotSupported
	}
	public enum AnalogueOrDigital {
		DIGITAL_AND_ANALOGUE,
		ANALOGUE,
		DIGITAL,
	}
	
	public enum Operators{
		UPC,
		Ziggo,
		Unitymedia,
		KDG_SD,
		Other,
		Telenet,
		RCSRDS,
		CamOperator,
		Blizoo,
		CanalDigital,
		YouSee,
		Telemach,
		ComHem,
        KDG_HD
	}
	
	public enum ChannelType{
		ANALOG,
		DIGITAL,
		RADIO
	}
	
	public enum Regions{
		PRIMARY,
		SECONDARY,
		TERTIARY
	}
	
	public enum ACINavigate{
	    UP,
	    DOWN,
	    LEFT,
	    RIGHT,
	    ENTER,
	    BLUE,
	    GREEN,
	    YELLOW,
	    RED,
	    WHITE
	}
	
	public enum ApplicationState{
		INST_SETTINGS,
		INST_WIZARD,
		INST_SERVICE,
		INST_SETTINGS_WIZARD,
		INST_NETWORK_UPDATE,
		IDLE
	}
	
	public enum DTRScreenMode{
		LOAD_CHANNEL_FREQ,
		LOAD_CHANNEL_NUMBER,
	}
	
	public enum AnalogSystemCountry{
		WEST_EUROPE,
		EAST_EUROPE,
		UK,
		FRANCE
	}
}
