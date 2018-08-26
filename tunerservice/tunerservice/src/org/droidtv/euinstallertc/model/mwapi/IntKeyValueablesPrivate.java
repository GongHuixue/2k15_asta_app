package org.droidtv.euinstallertc.model.mwapi;

import java.util.Arrays;



public class IntKeyValueablesPrivate{

		public static final String TAG = "IntKeyValueablesPrivate";

		
		/*OFFSETS*/

		public static final int C_BLOB_VERSION_OFFSET 			= 0;			
		public static final int C_SIGNAL_STRENGTH_OFFSET 		= 4;	
		public static final int C_SIGNAL_QUALITY_OFFSET 		= 8;	
		public static final int C_SDT_VERSION_OFFSET 			= 12;	
		public static final int C_NIT_VERSION_OFFSET 			= 16;	
		public static final int C_DELTAVOLUME_OFFSET 			= 20;	
		public static final int C_LOWPRIO_LCN_OFFSET 			= 24;	
		public static final int C_LOWPRIO_VISIBLESERVICE_OFFSET = 28;	
		public static final int C_VIDEODESCPRESENT_OFFSET 		= 32; 
		public static final int C_VISIBLESERVICE_OFFSET 		= 36;	
		public static final int C_USER_OVERRULED_LOGOURI_OFFSET = 40;	
		public static final int C_OUI_OFFSET 					= 44;
		public static final int C_SERVICELIST_VERSION_OFFSET 	= 48;
		public static final int C_USER_INSTALLED_OFFSET 		= 52;
		public static final int C_USERMODIFIEDNAME_OFFSET 		= 56;	
		public static final int C_PREFERRED_NICAM_OFFSET 		= 60; 
		public static final int C_NUM_BRAND_IDS_OFFSET 			= 64;
		public static final int C_SCRAMBLED_STATUS_OFFSET 		= 68;	
		public static final int C_REGION_DEPTH_OFFSET 			= 72;
		public static final int C_PRIMARY_REGION_OFFSET 		= 76;
		public static final int C_SECONDARY_REGION_OFFSET 		= 80;
		public static final int C_TERTIARY_REGION_OFFSET 		= 84;
		public static final int C_COUNTRY_CODE_OFFSET 			= 88;
		public static final int C_HDSIMULCASTREP_ONID_OFFSET 	= 92;
		public static final int C_HDSIMULCASTREP_TSID_OFFSET  	= 96;
		public static final int C_HDSIMULCASTREP_SVCID_OFFSET	= 100;
		public static final int C_FAVOURITENUMBER_OFFSET  		= 104;
		
		public static final int C_MULTIPLE_LCN_OFFSET			= 108; //32 bytes - int array of 8 elements
		public static final int  C_MULTIPLE_PRESET_OFFSET		= 140; //32 bytes - int array of 8 elements
		public static final int  C_MULTIPLE_FAVOURITE_ID_OFFSET = 172; //32 bytes - int array of 8 elements
		
		/*Analog Table Items*/
	
		public static final int  C_FUNETUNE_FREQUENCY_OFFSET 	= 204;
		public static final int  C_FINETUNE_OFFSET 				= 208;
		public static final int  C_COLOUR_SYSTEM_OFFSET 		= 212;
		public static final int  C_DATA_INDICATOR_OFFSET 		= 216;
		public static final int  C_ATTENUATOR_OFFSET 			= 220;
		public static final int  C_TUNED_OFFSET 				= 224;
		public static final int  C_DETUNED_OFFSET 				= 228;
		public static final int  C_AGC_INSTALLAED_OFFSET 		= 232;
		public static final int  C_PREFERRED_FAVORITE_OFFSET 	= 236;

	
		/*TS Table Items*/
	
		public static final int  C_A_SIGNAL_STRENGTH_OFFSET		= 240;
		public static final int  C_V_SIGNAL_STRENGTH_OFFSET		= 244;
		public static final int  C_Q_SIGNAL_STRENGTH_OFFSET		= 248;
		public static final int  C_CDSD_FREQUENCY_OFFSET		= 252;
		public static final int  C_CODERATE_OFFSET 				= 256;
		public static final int  C_HIERARCHYMODE_OFFSET			= 260;	
		public static final int  C_GUARDINTERVAL_OFFSET			= 264;
		public static final int  C_PTC_LIST_VERSION_OFFSET 		= 268;
		public static final int  C_TS_VERSION_OFFSET			= 272;
		public static final int  C_BARKER_MUX_OFFSET			= 276;
	
		/*Preset items*/
	
		public static final int  C_ANALOG_TABLE_PRESET_OFFSET	= 280;
		public static final int  C_TYPE_OFFSET 					= 284;
	

		/*Version*/
	
		public static final int C_VERSION_OFFSET				=	288;
		public static final int C_SERVICETYPE_OFFSET			= 	292;
		public static final int C_LANG_CODE_OFFSET				= 	296;
		public static final int C_BUFFER_OFFSET					=	300; /*Buffer of 200 bytes*/
		public static final int	C_END_OF_DATA					= 	500;
		
		
	
		private byte[] ByteArray;

		private int mIndex[] = {C_BLOB_VERSION_OFFSET,
		C_SIGNAL_STRENGTH_OFFSET,
		C_SIGNAL_QUALITY_OFFSET,
		C_SDT_VERSION_OFFSET,
		C_NIT_VERSION_OFFSET,
		C_DELTAVOLUME_OFFSET,
		C_LOWPRIO_LCN_OFFSET,
		C_LOWPRIO_VISIBLESERVICE_OFFSET,
		C_VIDEODESCPRESENT_OFFSET,
		C_VISIBLESERVICE_OFFSET,
		C_USER_OVERRULED_LOGOURI_OFFSET,
		C_OUI_OFFSET,
		C_SERVICELIST_VERSION_OFFSET,
		C_USER_INSTALLED_OFFSET,
		C_USERMODIFIEDNAME_OFFSET,
		C_PREFERRED_NICAM_OFFSET,
		C_NUM_BRAND_IDS_OFFSET,
		C_SCRAMBLED_STATUS_OFFSET,
		C_REGION_DEPTH_OFFSET,
		C_PRIMARY_REGION_OFFSET,
		C_SECONDARY_REGION_OFFSET,
		C_TERTIARY_REGION_OFFSET,
		C_COUNTRY_CODE_OFFSET,
		C_HDSIMULCASTREP_ONID_OFFSET,
		C_HDSIMULCASTREP_TSID_OFFSET,
		C_HDSIMULCASTREP_SVCID_OFFSET,
		C_FAVOURITENUMBER_OFFSET,
		C_MULTIPLE_LCN_OFFSET,
		C_MULTIPLE_PRESET_OFFSET,
		C_MULTIPLE_FAVOURITE_ID_OFFSET,
		C_FUNETUNE_FREQUENCY_OFFSET,
		C_FINETUNE_OFFSET,
		C_COLOUR_SYSTEM_OFFSET,
		C_DATA_INDICATOR_OFFSET,
		C_ATTENUATOR_OFFSET,
		C_TUNED_OFFSET,
		C_DETUNED_OFFSET,
		C_AGC_INSTALLAED_OFFSET,
		C_PREFERRED_FAVORITE_OFFSET,
		C_A_SIGNAL_STRENGTH_OFFSET,
		C_V_SIGNAL_STRENGTH_OFFSET,
		C_Q_SIGNAL_STRENGTH_OFFSET,
		C_CDSD_FREQUENCY_OFFSET,
		C_CODERATE_OFFSET,
		C_HIERARCHYMODE_OFFSET,
		C_GUARDINTERVAL_OFFSET,
		C_PTC_LIST_VERSION_OFFSET,
		C_TS_VERSION_OFFSET,
		C_BARKER_MUX_OFFSET,
		C_ANALOG_TABLE_PRESET_OFFSET,
		C_TYPE_OFFSET,
		C_VERSION_OFFSET,
		C_SERVICETYPE_OFFSET,
		C_LANG_CODE_OFFSET,
		C_BUFFER_OFFSET,
		C_END_OF_DATA };
		
		private final int numKeys = mIndex.length - 1;
	
		private final int majorVersion = 1;
		private final int minorVersion = 1;
		
		public IntKeyValueablesPrivate(){
			ByteArray = new byte[C_END_OF_DATA];
			
			/*Fill Major/Minor Version*/
			ByteArray[0] = (byte)(majorVersion);
			ByteArray[1] = (byte)(majorVersion >> 8);
			ByteArray[2] = (byte)(minorVersion);
			ByteArray[3] = (byte)(minorVersion >> 8);
		}
		@SuppressWarnings("unchecked")
		public IntKeyValueablesPrivate(byte[] blob){
			ByteArray = Arrays.copyOf(blob,blob.length);
		}
	
		public void setBlob(byte[] blob){
				ByteArray = Arrays.copyOf(blob,blob.length);

		}
		
		public byte[] getBlob(){
	
			return ByteArray;
		}
		
		public int getInt(Integer key){
			int ret = 0;
			if((key < numKeys) && (key > 0)){
				int index = mIndex[key];
				for (int i=0; i<4; i++){
					ret = ret | ((ByteArray[index+i] & 0xff) << (i*8));
				}
			}

			return ret;
		}
	
		public void put(Integer key, int val){
			if((key < numKeys) && (key > 0)){
				int index = mIndex[key];
				for (int i=0; i<4; i++){
					ByteArray[index+i] = (byte)(val >> (i*8));			
				}
			}
		}
	
		public boolean getBoolean(Integer key){
			boolean ret = false;
			if((key < numKeys) && (key > 0)){
				int index = mIndex[key];
				if(ByteArray[index] == 1){
					ret = true;
				}
			}
			return ret;
		}
		
		public void put(Integer key, boolean val){
			if((key < numKeys) && (key > 0)){
				int index = mIndex[key];
				ByteArray[index] = (byte)((val == true) ? 1 : 0);			
			}
		}
	
		public String getString(Integer key){
			String str = null;
			int length = 0, i = 0;
			if((key < numKeys) && (key > 0)){
				int index = mIndex[key];
				int size = mIndex[key+1] - mIndex[key];
				char[] chars = new char[size/2];				
				for (i = 0; i < chars.length; i++){
					if((ByteArray[index] == 0) && (ByteArray[index+1] == 0)){
						break;
					}
					chars[i] = (char)((ByteArray[index] & 0xff) | ((ByteArray[index+1] & 0xff) << 8));
					length++;
					index = index+2;
				}
				if(length != 0){
					char[] trim_chars = Arrays.copyOf(chars,length);
					str = new String(trim_chars);
				}
			}
			return str;
		}
		
		public void put(Integer key, String val){
			int length = 0;
			if(((key < numKeys) && (key > 0)) && (val != null)){
				length = val.length();
				if(length > 0){
					char[] chars = new char[length];
					val.getChars(0,length,chars,0);
					int index = mIndex[key];
					int size = mIndex[key+1] - mIndex[key];
					int lastbyte = (index+size)-2;
					for(int i = 0; (i < length) && ((index+2) <= lastbyte); i++ ){
						ByteArray[index] = (byte)(chars[i]);
						ByteArray[index+1] = (byte)(chars[i] >> 8);
						index = index+2;
					}
					ByteArray[index] = 0;
					ByteArray[index+1] = 0;
				}
			}
		}
	
		public byte[] getByteArray(Integer key){
			byte[] ret = null;
			if((key < numKeys) && (key > 0)){
				int index = mIndex[key];
				int size = mIndex[key+1] - mIndex[key];
				ret = Arrays.copyOfRange(ByteArray,index, (index+size));
			}
		
			return ret;
		}
		
		public void put(Integer key, byte[] val){
			if(((key < numKeys) && (key > 0)) && (val != null)){
				int index = mIndex[key];
				int size = mIndex[key+1] - mIndex[key];
				if(val.length < size){
					size = val.length;
				}
				for (int i=0; i<size; i++){
					ByteArray[index+i] = (byte) val[i];
				}
			}
		}
		
		public int[] getIntArray(Integer key){
			int[] ret = null;
			int val = 0;
			if((key < numKeys) && (key > 0)){
				int index = mIndex[key];
				int size = mIndex[key+1] - mIndex[key];
				if(size > 3){
					ret = new int[size/4];
					for(int i = 0; i < ret.length; i++){
						val = 0;
						for (int j = 0; j < 4; j++){
							val = val | ((ByteArray[index+j] & 0xff) << (j*8));
						}
						ret[i] = val;
						index = index + 4;
					}
				}
			}
			return ret;
		}
		
		public void put(Integer key, int[] val){
			int i = 0;
			if(((key < numKeys) && (key > 0)) && (val != null)){
				int index = mIndex[key];
				int size = mIndex[key+1] - mIndex[key];
				int lastbyte = index+size;
				for(i = 0;((i < val.length) && ((index+4) <= lastbyte)); i++){
					for (int j = 0; j < 4 ; j++){
						ByteArray[index+j] = (byte)(val[i] >> (j*8));			
					}
					index = index + 4;
				}
			}
		}
}

