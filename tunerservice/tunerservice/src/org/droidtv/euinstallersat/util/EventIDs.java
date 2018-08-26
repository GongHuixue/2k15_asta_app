package org.droidtv.euinstallersat.util;

public class EventIDs
{
	// Install prescan
	public static final int EVENT_INSTALL_PRESCANLNB1 = 0;
	public static final int EVENT_INSTALL_PRESCANLNB2 = 1;
	public static final int EVENT_INSTALL_PRESCANLNB3 = 2;
	public static final int EVENT_INSTALL_PRESCANLNB4 = 3;
	public static final int EVENT_INSTALL_PRESCANLNB1COMPLETED = 4;
	public static final int EVENT_INSTALL_PRESCANLNB2COMPLETED = 5;
	public static final int EVENT_INSTALL_PRESCANLNB3COMPLETED = 6;
	public static final int EVENT_INSTALL_PRESCANLNB4COMPLETED = 7;

	// Install
	public static final int EVENT_PACKAGENAME = 8;
	public static final int EVENT_SATELLITE_LNB1 = 9;
	public static final int EVENT_SATELLITE_LNB2 = 10;
	public static final int EVENT_SATELLITE_LNB3 = 11;
	public static final int EVENT_SATELLITE_LNB4 = 12;
	public static final int EVENT_SATELLITE_LNB1COMPLETED = 13;
	public static final int EVENT_SATELLITE_LNB2COMPLETED = 14;
	public static final int EVENT_SATELLITE_LNB3COMPLETED = 15;
	public static final int EVENT_SATELLITE_LNB4COMPLETED = 16;
	public static final int EVENT_SATELLITE_LNB1TVLIST = 17;
	public static final int EVENT_SATELLITE_LNB1RADIOLIST = 18;
	public static final int EVENT_SATELLITE_LNB2TVLIST = 19;
	public static final int EVENT_SATELLITE_LNB2RADIOLIST = 20;
	public static final int EVENT_SATELLITE_LNB3TVLIST = 21;
	public static final int EVENT_SATELLITE_LNB3RADIOLIST = 22;
	public static final int EVENT_SATELLITE_LNB4TVLIST = 23;
	public static final int EVENT_SATELLITE_LNB4RADIOLIST = 24;
	public static final int EVENT_PACKAGENAME_COMPLETED = 25;
	public static final int EVENT_PACKAGE_TVLIST = 26;
	public static final int EVENT_PACKAGE_RADIOLIST = 27;

	// UPDATE SCAN
	public static final int EVENT_UPDATE_LNB1 = 28;
	public static final int EVENT_UPDATE_LNB1COMPLETED = 29;
	public static final int EVENT_UPDATE_LNB1_TVCHADDED = 30;
	public static final int EVENT_UPDATE_LNB1_TVCHREMOVED = 31;
	public static final int EVENT_UPDATE_LNB1_RADIOCHADDED = 32;
	public static final int EVENT_UPDATE_LNB1_RADIOCHREMOVED = 33;
	public static final int EVENT_UPDATE_LNB2 = 34;
	public static final int EVENT_UPDATE_LNB2COMPLETED = 35;
	public static final int EVENT_UPDATE_LNB2_TVCHADDED = 36;
	public static final int EVENT_UPDATE_LNB2_TVCHREMOVED = 37;
	public static final int EVENT_UPDATE_LNB2_RADIOCHADDED = 38;
	public static final int EVENT_UPDATE_LNB2_RADIOCHREMOVED = 39;
	public static final int EVENT_UPDATE_LNB3 = 40;
	public static final int EVENT_UPDATE_LNB3COMPLETED = 41;
	public static final int EVENT_UPDATE_LNB3_TVCHADDED = 42;
	public static final int EVENT_UPDATE_LNB3_TVCHREMOVED = 43;
	public static final int EVENT_UPDATE_LNB3_RADIOCHADDED = 44;
	public static final int EVENT_UPDATE_LNB3_RADIOCHREMOVED = 45;
	public static final int EVENT_UPDATE_LNB4 = 46;
	public static final int EVENT_UPDATE_LNB4COMPLETED = 47;
	public static final int EVENT_UPDATE_LNB4_TVCHADDED = 48;
	public static final int EVENT_UPDATE_LNB4_TVCHREMOVED = 49;
	public static final int EVENT_UPDATE_LNB4_RADIOCHADDED = 50;
	public static final int EVENT_UPDATE_LNB4_RADIOCHREMOVED = 51;

	// Add Sat PreScan
	public static final int EVENT_ADDSAT_PRESCANLNB1 = 52;
	public static final int EVENT_ADDSAT_PRESCANLNB2 = 53;
	public static final int EVENT_ADDSAT_PRESCANLNB3 = 54;
	public static final int EVENT_ADDSAT_PRESCANLNB4 = 55;
	public static final int EVENT_ADDSAT_PRESCANLNB1COMPLETED = 56;
	public static final int EVENT_ADDSAT_PRESCANLNB2COMPLETED = 57;
	public static final int EVENT_ADDSAT_PRESCANLNB3COMPLETED = 58;
	public static final int EVENT_ADDSAT_PRESCANLNB4COMPLETED = 59;

	public static final int EVENT_UPDATE_LNB1SATNAME = 60;
	public static final int EVENT_UPDATE_LNB2SATNAME = 61;
	public static final int EVENT_UPDATE_LNB3SATNAME = 62;
	public static final int EVENT_UPDATE_LNB4SATNAME = 63;

	// Add Sat Install
	public static final int EVENT_ADDSAT_INSTALLLNB1 = 64;
	public static final int EVENT_ADDSAT_INSTALLLNB2 = 65;
	public static final int EVENT_ADDSAT_INSTALLLNB3 = 66;
	public static final int EVENT_ADDSAT_INSTALLLNB4 = 67;
	public static final int EVENT_ADDSAT_INSTALLLNB1COMPLETED = 68;
	public static final int EVENT_ADDSAT_INSTALLLNB2COMPLETED = 69;
	public static final int EVENT_ADDSAT_INSTALLLNB3COMPLETED = 70;
	public static final int EVENT_ADDSAT_INSTALLLNB4COMPLETED = 71;
	public static final int EVENT_ADDSAT_INSTALLLNB1TVLIST = 72;
	public static final int EVENT_ADDSAT_INSTALLLNB2TVLIST = 73;
	public static final int EVENT_ADDSAT_INSTALLLNB3TVLIST = 74;
	public static final int EVENT_ADDSAT_INSTALLLNB4TVLIST = 75;
	public static final int EVENT_ADDSAT_INSTALLLNB1RADIOLIST = 76;
	public static final int EVENT_ADDSAT_INSTALLLNB2RADIOLIST = 77;
	public static final int EVENT_ADDSAT_INSTALLLNB3RADIOLIST = 78;
	public static final int EVENT_ADDSAT_INSTALLLNB4RADIOLIST = 79;
	public static final int EVENT_ADDSAT_INSTALLLNB1SATNAME = 80;
	public static final int EVENT_ADDSAT_INSTALLLNB2SATNAME = 81;
	public static final int EVENT_ADDSAT_INSTALLLNB3SATNAME = 82;
	public static final int EVENT_ADDSAT_INSTALLLNB4SATNAME = 83;
	
	public static final int PRESCAN_SUCCESS = 84;
	public static final int PRESCAN_FAIL = 85;
	public static final int PRESCAN_COMPLETE = 86;
	public static final int PRESCAN_UPDATE = 87;
	
	public static final int LNB_INSTALL_STARTED = 88;
	public static final int LNB_INSTALL_FINISHED = 89;
	public static final int PACKAGE_INSTALL_STARTED = 90;
	public static final int PACKAGE_INSTALL_FINISHED = 91;
	public static final int SERVICE_SCAN_UPDATE = 92;
	public static final int SERVICE_SCAN_COMPLETE = 93;
	public static final int SORTING_STARTED = 94;
	public static final int INSTALLATION_FAILED = 95;
	
	public static final int MANUAL_INSTALL_FAILED = 96;
	
	public static final int NATIVELAYER_INIT_DONE = 97;
	
	public static final int USB_UPDATE_FAIL_CHECK_USB = 98;
	public static final int USB_UPDATE_FAIL_OLD_VERSION = 99;
	public static final int USB_UPDATE_SUCCESS = 100;
	
	public static final int PACKAGE_LIST_CREATED = 101;
	
	public static final int WIZARD_SETTINGS_EXIT = 102;
	public static final int EVENT_INST_COMPLETED = 103;
	public static final int EVENT_INST_STARTED = 104;

	public static final int TRIGGER_BACKGROUND_UPDATE_INSTALL = 105;

	public static final int FOUND_DIFFERENT_SATELLITE = 106;
	public static final int SATELLITE_REMOVED = 107;

	public static final int AUDIO_FOCUS_LOST = 108;
	
	public static final int NATIVELAYER_INIT_DONE_TUNER2 = 109;
	
	// CI
	public static final int CI_OPENENQUIRY_WIDGET = 110;
	public static final int CI_OPENLIST_WIDGET = 111;
	public static final int CI_OPENMENU_WIDGET = 112;
	public static final int CI_OPENMMI_WIDGET = 113; 
	public static final int CI_CLOSEMMI_WIDGET = 114;
	public static final int CI_OPENTEXT_WIDGET = 115;
	public static final int CI_RELEASE = 116;
	public static final int CI_INACTIVE_STATE = 117;
	public static final int OP_PROFILE_INSTALL_REQUEST_IMMEDIATE = 118;
	
	public static final int SATIP_NETWK_CONN_CHANGE = 119;
	public static final int SATIP_SERV_SEARCH_COMPLETE = 120;
	public static final int MAJORVERSION_UPDATE = 121;
	public static final int COMMIT_TVPROVIDER_FINISHED = 122;
	
	public static final int OP_PROFILE_INSTALL_REQUEST_URGENT = 123;
	public static final int OP_PROFILE_INSTALL_REQUEST_NORMAL = 124;
	/* TRICOLOR region list created */
	public static final int REGION_SCAN_END = 125;
	public static final int EVENT_INS_STOPPED = 126;
	public static final int CAM_NIT_INSTALLATION = 127;
	public static final int CHECK_START_NEW_CAM_OP = 128;
	public static final int STORE_OP_CICAMID = 129;
	public static final int CHECK_START_OP_NIT_REQUEST = 130;
	public static final int STORE_OP_INFO_VERSION = 131;
	public static final int TRIGGER_OP_INSTALL_COMPLETE = 132;
}
