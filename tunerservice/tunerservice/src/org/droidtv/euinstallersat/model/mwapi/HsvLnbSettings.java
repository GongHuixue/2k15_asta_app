package org.droidtv.euinstallersat.model.mwapi;

public class HsvLnbSettings {
	class HsvLnbConnectionType {
		public static final int LnbConnectionSingle = 0;
		public static final int LnbConnectionDiSeqcMini = 1;
		public static final int LnbConnectionDiSeqc1_0 = 2;
		public static final int LnbConnectionUnicableLnb = 3;
		public static final int LnbConnectionUnicableSwitch = 4;
	}
	class HsvLnbType 
	{
		public static final int LnbUniversal = 0;
		public static final int LnbUnicable = 1;
		public static final int LnbCustom = 2;
		public static final int LnbCircular = 3;
		public static final int LnbMdutype1 = 4;
		public static final int LnbMdutype2 = 5;
		public static final int LnbMdutype3 = 6;
		public static final int LnbMdutype4 = 7;
		public static final int LnbMdutype5 = 8;
		public static final int LnbMdutype6 = 9;
		public static final int LnbInvalid = 10;
	} 
	int ConnectionType;
	LnbSettingsEntry		LnbSettings[];
	
}
