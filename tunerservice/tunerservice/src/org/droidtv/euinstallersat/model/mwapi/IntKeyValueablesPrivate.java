package org.droidtv.euinstallersat.model.mwapi;


import java.util.Arrays;



public class IntKeyValueablesPrivate {

		public static final String TAG = "IntKeyValueablesPrivate";

		public static final int C_BLOB_VERSION_OFFSET 			=   0;		
		public static final int C_FAVOURITENUMBER_OFFSET		=	4;
		public static final int C_VISIBLESERVICE_OFFSET			=	8;
		public static final int C_LNBTYPE_OFFSET				=	12;
		public static final int C_SATID_OFFSET					=	16;
		public static final int C_ORBITALPOSITION_OFFSET		=	20;
		public static final int C_SIGNALSTRENGTH_OFFSET			=	24;
		public static final int C_SIGNALQUALITY_OFFSET			=	28;
		public static final int C_APPSCOOCKIE_OFFSET			=	32;
		public static final int C_SDTVERSION_OFFSET				=	36;
		public static final int C_NITVERSION_OFFSET				=	40;
		public static final int C_LOWPRIOLCN_OFFSET				=	44;
		public static final int C_LOWPRIOVISIBLESERVICE_OFFSET	=	48;
		public static final int C_VIDEODESCPRESENT_OFFSET 		=	52;
		public static final int C_DUPLICATESERVICE_OFFSET		=	56;
		public static final int C_SERVICELISTVERSION_OFFSET		=	60;
		public static final int C_USERINSTALLED_OFFSET			=	64;
		public static final int C_DVBTYPE_OFFSET				=	68;
		public static final int C_INSTALLEDSATNUMBER_OFFSET		=	72;
		public static final int C_NEWCHANNEL_OFFSET				=	76;
		public static final int C_SDSDFREQUENCY_OFFSET			=	80;
		public static final int C_COUNTRYCODE_OFFSET			=	84;
		public static final int C_HDSIMULCASTREPONID_OFFSET		=	88;
		public static final int C_HDSIMULCASTREPTSID_OFFSET		=	92;
		public static final int C_HDSIMULCASTREPSVCID_OFFSET	=	96;
		public static final int C_ADULTGENERE_OFFSET			=	100; //NOT USED
		public static final int C_FREESATSERVICEIDENTIFIER_OFFSET	=	104; //NOT USED 
		public static final int C_INTERACTIVESERVICEENABLED_OFFSET	=	108; // NOT USED
		public static final int C_ASIGNALSTRENGTH_OFFSET		=	112;
		public static final int C_VSIGNALSTRENGTH_OFFSET		=	116;
		public static final int C_QSIGNALSTRENGTH_OFFSET		=	120;
		public static final int C_CHANNELINFORMATION_OFFSET		=	124;
		public static final int C_CODERATE_OFFSET				=	128;
		public static final int C_PTCLISTVERSION_OFFSET			=	132;
		public static final int C_TSVERSION_OFFSET				=	136;
		public static final int C_PLPID_OFFSET					=	140;
		public static final int C_BARKERMUX_OFFSET				=	144;
		public static final int C_NUMBRANDIDS_OFFSET			=	148;
		public static final int C_FECINNER_OFFSET				=	152;
		public static final int C_ROLLOFF_OFFSET				=	156;

		public static final int C_SATELLITENAME_OFFSET			=	160; //68 bytes - to store string of 33 characters
		public static final int C_MULTIPLEVISIBLESERVICE_OFFSET	=	228; //32 bytes - int array of 8 elements
		public static final int C_MULTIPLELCN_OFFSET			=	260; //32 bytes - int array of 8 elements
		public static final int C_MULTIPLEPRESET_OFFSET			=	292; //32 bytes - int array of 8 elements
		public static final int C_MULTIPLEFAVORITE_OFFSET		=	324; //32 bytes - int array of 8 elements
		public static final int C_MULTIPLENUMERICSELECT_OFFSET	=	356;					

		public static final int  C_SERVICETYPE_OFFSET			=   388;
					
		public static final int C_VERSION_OFFSET				=	392;
		
		public static final int C_BUFFER_OFFSET					=	396; // Buffer of 136 bytes
		
		public static final int C_END_OF_DATA				=	500;
		
	
		private byte[] ByteArray;

		private int mIndex[] = {C_BLOB_VERSION_OFFSET,
			C_FAVOURITENUMBER_OFFSET,
			C_VISIBLESERVICE_OFFSET,
			C_LNBTYPE_OFFSET,
			C_SATID_OFFSET,
			C_ORBITALPOSITION_OFFSET,
			C_SIGNALSTRENGTH_OFFSET,
			C_SIGNALQUALITY_OFFSET,
			C_APPSCOOCKIE_OFFSET,
			C_SDTVERSION_OFFSET,
			C_NITVERSION_OFFSET,
			C_LOWPRIOLCN_OFFSET,
			C_LOWPRIOVISIBLESERVICE_OFFSET,
			C_VIDEODESCPRESENT_OFFSET,
			C_DUPLICATESERVICE_OFFSET,
			C_SERVICELISTVERSION_OFFSET,
			C_USERINSTALLED_OFFSET,
			C_DVBTYPE_OFFSET,
			C_INSTALLEDSATNUMBER_OFFSET,
			C_NEWCHANNEL_OFFSET,
			C_SDSDFREQUENCY_OFFSET,
			C_COUNTRYCODE_OFFSET,
			C_HDSIMULCASTREPONID_OFFSET,
			C_HDSIMULCASTREPTSID_OFFSET,
			C_HDSIMULCASTREPSVCID_OFFSET,
			C_ADULTGENERE_OFFSET,
			C_FREESATSERVICEIDENTIFIER_OFFSET,
			C_INTERACTIVESERVICEENABLED_OFFSET,
			C_ASIGNALSTRENGTH_OFFSET,
			C_VSIGNALSTRENGTH_OFFSET,
			C_QSIGNALSTRENGTH_OFFSET,
			C_CHANNELINFORMATION_OFFSET,
			C_CODERATE_OFFSET,
			C_PTCLISTVERSION_OFFSET,
			C_TSVERSION_OFFSET,
			C_PLPID_OFFSET,
			C_BARKERMUX_OFFSET,
			C_NUMBRANDIDS_OFFSET,
			C_FECINNER_OFFSET,
			C_ROLLOFF_OFFSET,
			C_SATELLITENAME_OFFSET,
			C_MULTIPLEVISIBLESERVICE_OFFSET,
			C_MULTIPLELCN_OFFSET,
			C_MULTIPLEPRESET_OFFSET,
			C_MULTIPLEFAVORITE_OFFSET,
			C_MULTIPLENUMERICSELECT_OFFSET,
			C_SERVICETYPE_OFFSET,
			C_VERSION_OFFSET,
			C_BUFFER_OFFSET,
			C_END_OF_DATA
		};
		
	
		private final int numKeys = mIndex.length - 1;

		private final int majorVersion = 1;
		private final int minorVersion = 1;
	
		
		public IntKeyValueablesPrivate() {
			ByteArray = new byte[C_END_OF_DATA];

			/*Fill Major/Minor Version*/
			ByteArray[0] = (byte)(majorVersion);
			ByteArray[1] = (byte)(majorVersion >> 8);
			ByteArray[2] = (byte)(minorVersion);
			ByteArray[3] = (byte)(minorVersion >> 8);
		}
		@SuppressWarnings("unchecked")
		public IntKeyValueablesPrivate(byte[] blob) {
				 ByteArray = Arrays.copyOf(blob,blob.length);
			
		}
	
		public void setBlob(byte[] blob)  {
			ByteArray = Arrays.copyOf(blob,blob.length);
		}
		
		public byte[] getBlob() {
	
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

