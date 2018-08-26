package org.droidtv.tunerservice.channellistcopy;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import android.util.Log;
import android.content.Context;
import android.database.Cursor;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import org.droidtv.tv.tvinput.ITvContractExtras;
import android.content.ContentValues;
import org.droidtv.tv.util.IIntKeyValueables;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import android.media.tv.TvContract.Channels.Logo;

/**
 * class:ChannelbinEntry is used To make channelbin entry 
 * @author sohan.gupta
 *
 */
public class ChannelMapBlobHandler
{
	private Context copyContext;
	public static final String TAG = ChannelMapBlobHandler.class.getName();
	private static final int 	PRIMARY_VERSION = 2000;
	private static final int 	SECONDARY_VERSION = 0;
	int		ANTENNA_MEDIUM =0, CABLE_MEDIUM = 1, SATELLITE_MEDIUM = 2;
	private ITvSettingsManager m_settings =ITvSettingsManager.Instance.getInterface();
	CopyFromUSBToTV			copytotv =	new CopyFromUSBToTV();
	
	private String MountPath = null;
	
	private class BinaryChannelEntry
	{	 
		int	UniqueID;
		int	Frequency;
		int	ChannelNumber;
		int	ChannelType;
		int	OriginalNetworkId;
		int	TsId;
		int	ServiceId;
		int	SymbolRate;
		int	LogoURL;
		int	ScrambleStatus;
		int	ChannelLock;
		int	ModulationType;
		int	Fec;
		int	ServiceType;
		int	SystemHidden;
		int	UserModifiedLogo;
		int	ServiceEdited;	
		int	StreamPriority; /* Applicable only for TC */
		int	AnalogUniqueId;  /* Applicable only for TC */
		int	NetworkId;  /* Applicable only for TC */
		int	Bandwidth;  /* Applicable only for TC */
		int	DecoderType;  /* Applicable only for TC */
		int LnbNumber; /* Applicable only for SAT */
		int Polarization; /* Applicable only for SAT */
		int TPID; /* Applicable only for SAT */
		byte[] ChannelName; 
		byte[] SatelliteName; /* Applicable only for SAT & Provider name same as SatelliteName */
		byte[] Padding;
	};

	private class BinaryChannelMapData
	{
		int PrimaryVersion;
		int SecondaryVersion;
		int NoOfRecords;
	} ;

	private class SatelliteLnbParameters {
		int	LnbType;
		int LnbPower;
		int LowLoFreq;
		int HighLoFreq;
		int ToneControl;
		int SatelliteId;
		byte[] SatelliteName;
	};
	private class SatelliteSettings {
		int ConnectionType;
		int UserBandPrimaryTuner;
		int UserBandFrequencyPrimaryTuner;
		int UserBandSecondaryTuner;
		int UserBandFrequencySecondaryTuner;

		SatelliteLnbParameters[] LnbParameters;
	};
	
	
	public ChannelMapBlobHandler(String path)
	{
		MountPath = path;
	}

	private int IsDigitalOrAnalog (String PresetType)
	{
		int 	IsDigital = 1;
		if (PresetType.equals(Channels.TYPE_PAL) || PresetType.equals(Channels.TYPE_SECAM))
		{
			IsDigital = 0;
		}
		return IsDigital;
	}

	
	private int MapDecoderType (String DecoderType)
	{
		/* Keep values as per below 
			1: DVBT
			2: DVBT2
			3: DVBC
			4: DVBC2
			5: DVBS
			6: DVBS2
			7 : Analog
		*/
		int 	MappedDecoderType = 1;
		if (DecoderType.equals(Channels.TYPE_DVB_T))
		{
			MappedDecoderType = 1;
		}
		else if (DecoderType.equals(Channels.TYPE_DVB_T2))
		{
			MappedDecoderType = 2;
		}
		else if (DecoderType.equals(Channels.TYPE_DVB_C))
		{
			MappedDecoderType = 3;
		}
		else if (DecoderType.equals(Channels.TYPE_DVB_C2))
		{
			MappedDecoderType = 4;
		}
		else if (DecoderType.equals(Channels.TYPE_DVB_S))
		{
			MappedDecoderType = 5;
		}
		else if (DecoderType.equals(Channels.TYPE_DVB_S2))
		{
			MappedDecoderType = 6;
		}
		else if (DecoderType.equals(Channels.TYPE_PAL) || DecoderType.equals(Channels.TYPE_SECAM))
		{
			MappedDecoderType = 7;
		}
		return MappedDecoderType;		
	}
	
	private int MapServiceType(String ServiceType)
	{
		/* Using mapping like this 
			1. TV
			2. Radio
			3. Data
		*/
		int MappedSvcType = 1;
		if (ServiceType.equals(Channels.SERVICE_TYPE_AUDIO_VIDEO))
		{
			MappedSvcType = 1;
		}
		else if (ServiceType.equals(Channels.SERVICE_TYPE_AUDIO))
		{
			MappedSvcType = 2;
		}
		else if (ServiceType.equals(Channels.SERVICE_TYPE_OTHER))
		{
			MappedSvcType = 3;
		}
		
		return MappedSvcType;
	}
	
	private  void ReadFromBinaryChannelMapAndUpdateTVP(File src, String BinaryFileName, int Medium)
	{
	
		int PrimaryVersion = 0, SecondaryVersion = 0, NoOfRecords = 0, RowsUpdated = 0;
		int ChannelNameLen =0;
		byte[]	BlobData = null;
		byte[]  ChannelName = null;
		IIntKeyValueables keyvalues = IIntKeyValueables.Instance.getInterface();
		
		try
		{
			copytotv.setMountPath(MountPath);
			
			File fileNameForTerCableBinFile=new File(src,BinaryFileName);  
			if(fileNameForTerCableBinFile.exists())
			{
				Log.d(TAG,"Location of bin file for reading->"+fileNameForTerCableBinFile);
				InputStream in=new FileInputStream(fileNameForTerCableBinFile);
				LittleEndianInputStream iin=new LittleEndianInputStream(in);
				BinaryChannelEntry	ChannelData = new BinaryChannelEntry();
				  
				PrimaryVersion = iin.readInt();
				SecondaryVersion = iin.readInt();
				NoOfRecords = iin.readInt();
				Log.d (TAG, "Copy To TV: Prim " + PrimaryVersion + "Sec "+ SecondaryVersion + "NoOfRecords " + NoOfRecords+ "For Medium "+ Medium);

				for (int Count = 0; Count < NoOfRecords; Count++)
				{
					/* Reading the channelMap entry back */
					ChannelData.UniqueID = iin.readInt();
					ChannelData.Frequency = iin.readInt();
					ChannelData.ChannelNumber = iin.readInt();
					ChannelData.ChannelType = iin.readInt();
					ChannelData.OriginalNetworkId = iin.readInt();
					ChannelData.TsId = iin.readInt();
					ChannelData.ServiceId = iin.readInt();
					ChannelData.SymbolRate = iin.readInt();
					ChannelData.LogoURL = iin.readInt();
					ChannelData.ScrambleStatus = iin.readInt();
					ChannelData.ChannelLock = iin.readInt();
					ChannelData.ModulationType = iin.readInt();
					ChannelData.Fec = iin.readInt();
					ChannelData.ServiceType = iin.readInt();
					ChannelData.SystemHidden = iin.readInt();
					ChannelData.UserModifiedLogo = iin.readInt();
					ChannelData.ServiceEdited = iin.readInt();
					if ((Medium == ANTENNA_MEDIUM) || (Medium == CABLE_MEDIUM))
					{
						ChannelData.StreamPriority = iin.readInt();
						ChannelData.AnalogUniqueId = iin.readInt();
						ChannelData.NetworkId = iin.readInt();
						ChannelData.Bandwidth = iin.readInt();
						ChannelData.DecoderType = iin.readInt();
					}
					else if (Medium == SATELLITE_MEDIUM)
					{
						ChannelData.LnbNumber = iin.readInt();
						ChannelData.Polarization = iin.readInt();
						ChannelData.TPID = iin.readInt();
					}
					
					ChannelName = new byte [66];
					iin.read(ChannelName, 0, 66);
					if (Medium == SATELLITE_MEDIUM)
					{
						ChannelData.SatelliteName = new byte [66];
						iin.read(ChannelData.SatelliteName, 0, 66);
					}
					
					ChannelData.Padding = new byte [2];
					if ((Medium == ANTENNA_MEDIUM) || (Medium == CABLE_MEDIUM))
					{
						iin.read(ChannelData.Padding, 0, 2);
					}
					
					for (ChannelNameLen = 0; ChannelNameLen < 65; ChannelNameLen++)
					{
						if ((ChannelName[ChannelNameLen] == 0) && (ChannelName[ChannelNameLen+1] == 0))
						{
							break;
						}
					}
					ChannelData.ChannelName = new byte [ChannelNameLen+1];
					for (int TempCount = 0; TempCount <= ChannelNameLen; TempCount++)
					{
						ChannelData.ChannelName[TempCount] = ChannelName[TempCount];
					}
					String ServiceName = new String(ChannelData.ChannelName, "UTF-16LE");
					
					Log.d(TAG , "UniqueID " + ChannelData.UniqueID + "Preset " + ChannelData.ChannelNumber + "ServiceID" + ChannelData.ServiceId + "SvcEdited" + ChannelData.ServiceEdited + "ServiceName " + ServiceName);
					if (ChannelData.ServiceEdited != 0)
					{
						/* Find the matching entry from TVCP and update */
						String[] projection = new String[] {Channels._ID, Channels.COLUMN_INPUT_ID, Channels.COLUMN_TYPE, Channels.COLUMN_SERVICE_TYPE, Channels.COLUMN_ORIGINAL_NETWORK_ID, Channels.COLUMN_TRANSPORT_STREAM_ID, Channels.COLUMN_SERVICE_ID, Channels.COLUMN_BROWSABLE,Channels.COLUMN_SEARCHABLE,Channels.COLUMN_INTERNAL_PROVIDER_DATA,Channels.COLUMN_VERSION_NUMBER};
						String	mselection=Channels._ID+"= ?";
						String[]	mselectionargs=new String[]{String.valueOf(ChannelData.UniqueID)};
						Cursor TCursor = copyContext.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
						if((TCursor != null))
						{   try{
							if(TCursor.moveToFirst())
							{
							  try {
								ContentValues val=new ContentValues();
								val.put (Channels._ID, TCursor.getInt(0));
								val.put (Channels.COLUMN_INPUT_ID,TCursor.getString(1)); /* Check with Mounesh/Pavan what to fill here */
								val.put (Channels.COLUMN_TYPE,TCursor.getString(2));
								val.put (Channels.COLUMN_SERVICE_TYPE,TCursor.getString(3));
								val.put (Channels.COLUMN_ORIGINAL_NETWORK_ID,TCursor.getInt(4));
								val.put (Channels.COLUMN_TRANSPORT_STREAM_ID,TCursor.getInt(5));
								val.put (Channels.COLUMN_SERVICE_ID,TCursor.getInt(6));
								val.put (Channels.COLUMN_DISPLAY_NUMBER,ChannelData.ChannelNumber);
								val.put (Channels.COLUMN_DISPLAY_NAME,ServiceName);
								val.put (Channels.COLUMN_BROWSABLE,TCursor.getInt(7));
								val.put (Channels.COLUMN_SEARCHABLE,TCursor.getInt(8));
								val.put (Channels.COLUMN_LOCKED,ChannelData.ChannelLock);
								BlobData = TCursor.getBlob(9);
								val.put (Channels.COLUMN_VERSION_NUMBER,TCursor.getInt(10));
								
								/* Now check and update the required fields in Blob */
								try
								{
									if (ChannelData.UserModifiedLogo != 0)
									{
										keyvalues.setBlob(BlobData);
										/* TODO: Remove this once SatInstaller updates this flag */
										//if (Medium != SATELLITE_MEDIUM)
										{
											keyvalues.put(ITvContractExtras.C_USEROVERRULEDLOGOURI, ChannelData.UserModifiedLogo);
											keyvalues.put(ITvContractExtras.C_LOGOID, ChannelData.LogoURL);
										}
										val.put(Logo.CONTENT_DIRECTORY,copytotv.writeUserLogosToDB(copyContext, ChannelData.LogoURL));
										
										/* int	LogoURL; */
										Log.d(TAG, "Value updated for UserModified logo ");
										BlobData = keyvalues.getBlob();
									}
								}
								catch (Exception e) 
								{
									Log.d(TAG, "Exception in setBlob() while reading version" + e);
								}
								val.put (Channels.COLUMN_INTERNAL_PROVIDER_DATA,BlobData);	
								
								mselection = Channels._ID+"= ?" ;
								mselectionargs=new String[]{String.valueOf(ChannelData.UniqueID)};
								RowsUpdated = copyContext.getContentResolver().update(TvContract.Channels.CONTENT_URI,val,mselection,mselectionargs);
								Log.d (TAG, "Rows updated  " + RowsUpdated + "for " + ChannelData.UniqueID);
							  } catch (Exception ex) {
								Log.d (TAG, " Update failed with Exception " + ex);
							
							}	
							}
						}
                        finally
						{
							TCursor.close();
							TCursor=null;
						}						
						}
					}
				}
				iin.close();
			}	
		}
		catch (Exception e)
		{
			Log.d(TAG,"Exception in reading Bin File"+e);
		}
	}
	
	private void ReadFromTVPAndWriteToBinaryChannelMap (File dest, String BinaryFileName, int Medium)
	{
		byte[]	BlobData = null;
		byte[]	ChannelNameBytes;
		int		count = 0;
		BinaryChannelEntry	ChannelData = new BinaryChannelEntry();
		String 	ChannelName;
		String 	PresetType, ServiceType;
		Cursor TCursor = null;

		/*Get Data from Tvprovider*/
		String[] projection = new String[] {Channels._ID,Channels.COLUMN_DISPLAY_NUMBER,Channels.COLUMN_TYPE, Channels.COLUMN_ORIGINAL_NETWORK_ID, Channels.COLUMN_TRANSPORT_STREAM_ID,Channels.COLUMN_SERVICE_ID,
												Channels.COLUMN_LOCKED, Channels.COLUMN_BROWSABLE, Channels.COLUMN_DISPLAY_NAME,Channels.COLUMN_SERVICE_TYPE, Channels.COLUMN_INTERNAL_PROVIDER_DATA};		
		if ((Medium == ANTENNA_MEDIUM) || (Medium == CABLE_MEDIUM))
		{
			String	mselection=Channels.COLUMN_VERSION_NUMBER+"= ?";
			String[]	mselectionargs=new String[]{String.valueOf(Medium)};
			
			TCursor = copyContext.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		}
		else if (Medium == SATELLITE_MEDIUM) 
		{
			String	mselection=Channels.COLUMN_VERSION_NUMBER+"= ?"+ " OR " + Channels.COLUMN_VERSION_NUMBER+"= ?"+ " OR " + Channels.COLUMN_VERSION_NUMBER+"= ?"+ " OR " + Channels.COLUMN_VERSION_NUMBER+"= ?";
			String[]	mselectionargs=new String[]{String.valueOf(2),String.valueOf(3),String.valueOf(4),String.valueOf(5)};
			
			TCursor = copyContext.getContentResolver().query(TvContract.Channels.CONTENT_URI, projection, mselection, mselectionargs, null);
		}
		
		if(TCursor != null)
		{
			count = TCursor.getCount();
		}
		Log.d(TAG, "Number of channels in Medium:" + Medium + " :is" +count);	

		try 
		{
			/* Opening the file for writing */
			File fileNameForTerCableBinFile=new File(dest,BinaryFileName);
			OutputStream out=new FileOutputStream(fileNameForTerCableBinFile);
			LittleEndianOutputStream oout=new LittleEndianOutputStream(out);

			/* Writing the header information */
			oout.writeInt(PRIMARY_VERSION);
			oout.writeInt(SECONDARY_VERSION);
			oout.writeInt(count);

			
			if (count > 0)
			{
				if(TCursor != null)
				{
					while(TCursor.moveToNext()) 
					{					
						/* Values which can be read directly from tv.db */
						ChannelData.UniqueID = TCursor.getInt(0);
						ChannelData.ChannelNumber = TCursor.getInt(1); /* This is string. Check this works */
						PresetType = TCursor.getString(2);
						ChannelData.ChannelType = IsDigitalOrAnalog(PresetType);
						ChannelData.DecoderType = MapDecoderType(PresetType);
						ChannelData.OriginalNetworkId = TCursor.getInt (3);
						ChannelData.TsId = TCursor.getInt(4);
						ChannelData.ServiceId = TCursor.getInt (5);
						ChannelData.ChannelLock = TCursor.getInt (6);
						ChannelData.SystemHidden = (TCursor.getInt (7) == 0) ? 1 : 0;
						try {
							ChannelName = new String (TCursor.getString(8));
							Log.d (TAG, "ChannelName " + ChannelName);
							ChannelNameBytes = ChannelName.getBytes("UTF-16LE");
							ChannelData.ChannelName = new byte [66];

							for (int Index =0; Index < 66; Index++)
							{
								if (Index < ChannelNameBytes.length)
								{
									ChannelData.ChannelName[Index] = ChannelNameBytes[Index];
								}
								else
								{
									ChannelData.ChannelName[Index] = 0;
								}
							}
							
						}
						catch (Exception e)
						{
							Log.d(TAG,"Channel name empty. Error handling  "+e);
							for (int Index =0; Index < 66; Index++)
							{
								ChannelData.ChannelName[Index] = 0;
							}
						}
						
						/* This padding bytes are added, as 66 is not aligned by integer. */
						ChannelData.Padding = new byte [2];
						ChannelData.Padding[0] = 0x12;
						ChannelData.Padding[1] = 0x34;
						
						ServiceType = TCursor.getString(9);
						ChannelData.ServiceType = MapServiceType(ServiceType);
						
						/* Filling the values which cannot be read from neither tv.db or Blob. Kept only for future use*/
						ChannelData.AnalogUniqueId = 0;
						ChannelData.Fec = 0;
						ChannelData.ServiceEdited = 0;	

						BlobData = TCursor.getBlob(10);
						
						if (BlobData != null)
						{
							IIntKeyValueables keyvals	 = IIntKeyValueables.Instance.getInterface();
							try
							{
								keyvals.setBlob(BlobData);
							}catch(Exception e){
								Log.d(TAG, "parseBlobData - CAUGHT EXCEPTION keyvals=null");
								keyvals = null;
							}

							/* Reading the values from blob and filling required items */
							if(keyvals != null){
								ChannelData.Frequency = keyvals.getInt(ITvContractExtras.C_FREQUENCY);
								ChannelData.NetworkId = keyvals.getInt(ITvContractExtras.C_NetworkId);
								ChannelData.ScrambleStatus = keyvals.getInt(ITvContractExtras.C_SCRAMBLED);
								ChannelData.ModulationType = keyvals.getInt(ITvContractExtras.C_MODULATION);
								ChannelData.UserModifiedLogo = keyvals.getInt(ITvContractExtras.C_USEROVERRULEDLOGOURI);	
								ChannelData.LogoURL = keyvals.getInt(ITvContractExtras.C_LOGOID);
								if (Medium == CABLE_MEDIUM)
								{
									ChannelData.SymbolRate = keyvals.getInt(ITvContractExtras.C_SYMBOLRATE);
									ChannelData.StreamPriority = 0;
									ChannelData.Bandwidth = 0;
								}
								else if (Medium == ANTENNA_MEDIUM)
								{
									ChannelData.SymbolRate = 0;
									ChannelData.StreamPriority = keyvals.getInt(ITvContractExtras.C_STREAMPRIORITY);
									ChannelData.Bandwidth = keyvals.getInt(ITvContractExtras.C_BANDWIDTH);
								}
								else if (Medium == SATELLITE_MEDIUM)
								{
									ChannelData.SymbolRate = keyvals.getInt(ITvContractExtras.C_SYMBOLRATE);
									ChannelData.LnbNumber = keyvals.getInt(ITvContractExtras.C_LNBNUMBER);
									ChannelData.Polarization = keyvals.getInt(ITvContractExtras.C_POLARIZATION);
									if (m_settings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBTYPE, ChannelData.LnbNumber, 0) == TvSettingsDefinitions.LnbType.TUNING_DVBS_CIRCULAR)
									{
										/* DLL Expects 3 for Left Circular Polarization and 4 for Right Circular */
										ChannelData.Polarization = (ChannelData.Polarization == 0) ? 3: 4;
									}
									ChannelData.TPID = keyvals.getInt(ITvContractExtras.C_TPID);
									if ((ChannelData.LnbNumber >= 0) && (ChannelData.LnbNumber < 4))
									{
										String SatelliteName = m_settings.getString(TvSettingsConstants.INSTALLATIONSETTINGSATELLITENAME, ChannelData.LnbNumber, "sat");
										byte[] SatelliteNameBytes = SatelliteName.getBytes("UTF-16LE");
										ChannelData.SatelliteName = new byte [66];
										for (int Index =0; Index < 66; Index++)
										{
											if (Index < SatelliteNameBytes.length)
											{
												ChannelData.SatelliteName[Index] = SatelliteNameBytes[Index];
											}
											else
											{
												ChannelData.SatelliteName[Index] = 0;
											}
										}
									}
								}
							}
						}
						else
						{
							Log.d( TAG, " BLOB read failed for " + ChannelData.ChannelNumber);
						}

						/* Writing the content to binary file */
						Log.d (TAG, "ONID "+ ChannelData.OriginalNetworkId+"TSID "+ChannelData.TsId+"ChannelNum "+ChannelData.ChannelNumber+"Freq "+ ChannelData.Frequency+ "UniqeID " + ChannelData.UniqueID );
						oout.writeInt(ChannelData.UniqueID);
						oout.writeInt(ChannelData.Frequency);
						oout.writeInt(ChannelData.ChannelNumber);
						oout.writeInt(ChannelData.ChannelType);
						oout.writeInt(ChannelData.OriginalNetworkId);
						oout.writeInt(ChannelData.TsId);
						oout.writeInt(ChannelData.ServiceId);
						oout.writeInt(ChannelData.SymbolRate); 

						oout.writeInt(ChannelData.LogoURL);
						oout.writeInt(ChannelData.ScrambleStatus);
						oout.writeInt(ChannelData.ChannelLock);
						oout.writeInt(ChannelData.ModulationType);
						oout.writeInt(ChannelData.Fec);
						oout.writeInt(ChannelData.ServiceType);
						oout.writeInt(ChannelData.SystemHidden);
						oout.writeInt(ChannelData.UserModifiedLogo);// This is not filled up 
						oout.writeInt(ChannelData.ServiceEdited);
						if ((Medium == ANTENNA_MEDIUM) || (Medium == CABLE_MEDIUM))
						{
							oout.writeInt(ChannelData.StreamPriority);
							oout.writeInt(ChannelData.AnalogUniqueId);
							oout.writeInt(ChannelData.NetworkId);
							oout.writeInt(ChannelData.Bandwidth);
							oout.writeInt(ChannelData.DecoderType);
						}
						else if (Medium == SATELLITE_MEDIUM)
						{
							oout.writeInt(ChannelData.LnbNumber);
							oout.writeInt(ChannelData.Polarization);
							oout.writeInt(ChannelData.TPID);
						}
						oout.write(ChannelData.ChannelName, 0, 66);
						if (Medium == SATELLITE_MEDIUM)
						{
							oout.write(ChannelData.SatelliteName, 0, 66);
						}
						else
						{
							oout.write(ChannelData.Padding, 0, 2);
						}
										
						/* TODO: Explore the chance of optimizing this */
						//oout.writeObject (ChannelData);
					}
				}
			}
			else
			{
				Log.d(TAG, "No Channels present ");
			}
			oout.flush();
			oout.close();
			Log.d(TAG, "File write success for "+BinaryFileName);
		}
		catch (Exception e)
		{
			Log.d(TAG,"Exception in Writting "+BinaryFileName + ":"+e);
		}
		finally
		{
			if(TCursor!=null)
			{
				TCursor.close();
				TCursor=null;
			}
		}
	}

	private void ClearToBinaryChannelMap (File dest, String BinaryFileName, int Medium)
	{
		Log.d(TAG, "Clearing channels in Medium:" + Medium);	

		try 
		{
			/* Opening the file for writing */
			File fileNameForTerCableBinFile=new File(dest,BinaryFileName);
			OutputStream out=new FileOutputStream(fileNameForTerCableBinFile);
			LittleEndianOutputStream oout=new LittleEndianOutputStream(out);

			/* Writing the header information */
			oout.writeInt(PRIMARY_VERSION);
			oout.writeInt(SECONDARY_VERSION);
			oout.writeInt(0);
			
			oout.flush();
			oout.close();
			Log.d(TAG, "File write success for "+BinaryFileName);
		}
		catch (Exception e)
		{
			Log.d(TAG,"Exception in Writting "+BinaryFileName + ":"+e);
		}
		finally
		{
		}
	}
	
	
	public void ReadFromBinarySettingsBinAndUpdateInTvSettings (File src, String SatelliteSettingsBinName)
	{
		try
		{
			copytotv.setMountPath(MountPath);
			
			File fileNameForSatelliteSettingsBinFile=new File(src,SatelliteSettingsBinName);  
			if(fileNameForSatelliteSettingsBinFile.exists())
			{
				Log.v(TAG,"Location of bin file for reading->"+fileNameForSatelliteSettingsBinFile);
				InputStream in=new FileInputStream(fileNameForSatelliteSettingsBinFile);
				LittleEndianInputStream iin=new LittleEndianInputStream(in);
				
				SatelliteSettings		SatSettings = new SatelliteSettings();
				SatSettings.LnbParameters = new SatelliteLnbParameters[4];
				
				SatSettings.ConnectionType = iin.readInt();
				SatSettings.UserBandPrimaryTuner = iin.readInt();
				SatSettings.UserBandFrequencyPrimaryTuner = iin.readInt();
				SatSettings.UserBandSecondaryTuner = iin.readInt();
				SatSettings.UserBandFrequencySecondaryTuner = iin.readInt();
				for (int count =0; count < 4; count++)
				{
					SatSettings.LnbParameters[count] = new SatelliteLnbParameters();
					SatSettings.LnbParameters[count].LnbType = iin.readInt();
					SatSettings.LnbParameters[count].LnbPower = iin.readInt();
					SatSettings.LnbParameters[count].LowLoFreq = iin.readInt();
					SatSettings.LnbParameters[count].HighLoFreq = iin.readInt();
					SatSettings.LnbParameters[count].ToneControl = iin.readInt();
					SatSettings.LnbParameters[count].SatelliteId = iin.readInt();
					
					SatSettings.LnbParameters[count].SatelliteName = new byte [66];
					iin.read(SatSettings.LnbParameters[count].SatelliteName, 0, 66);

					
				}
				
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSCONNECTIONTYPE, 0, SatSettings.ConnectionType);
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER, 0, SatSettings.UserBandPrimaryTuner);
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER, 0, SatSettings.UserBandFrequencyPrimaryTuner);
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER, 0, SatSettings.UserBandSecondaryTuner);
				m_settings.putInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER, 0, SatSettings.UserBandFrequencySecondaryTuner);				
				for (int count =0; count < 4; count++)
				{
					m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLNBTYPE, count, SatSettings.LnbParameters[count].LnbType);
					m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLNBPOWER, count, SatSettings.LnbParameters[count].LnbPower);
					m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGLOWLOFREQ, count, SatSettings.LnbParameters[count].LowLoFreq);
					m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGHIGHLOFREQ, count, SatSettings.LnbParameters[count].HighLoFreq);
					m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGTONECONTROL, count, SatSettings.LnbParameters[count].ToneControl);
					m_settings.putInt(TvSettingsConstants.INSTALLATIONSETTINGSATELLITEID, count, SatSettings.LnbParameters[count].SatelliteId);
					
					try {
						String SatelliteName = new  String(SatSettings.LnbParameters[count].SatelliteName);
						m_settings.putString(TvSettingsConstants.INSTALLATIONSETTINGSATELLITENAME, count, SatelliteName);						
					}
					catch (Exception e)
					{
						Log.v (TAG, "SatelliteName exception "+ e);
					}
				}
			}
			else 
			{
				Log.d(TAG,"No Satellite Settings file present->"+fileNameForSatelliteSettingsBinFile);
			}
		}
		catch (Exception e) 
		{
			Log.v (TAG, "Exception in updating TV Settings from Satellite Settings "+ e);
		}

		
	}
	
	public void ReadFromTvSettingsAndUpdateInBinarySettings (File dest, String SatelliteSettingsBinName)
	{
		try {
			File fileNameForSatelliteSettingsBinFile=new File(dest,SatelliteSettingsBinName);
			OutputStream out=new FileOutputStream(fileNameForSatelliteSettingsBinFile);
			LittleEndianOutputStream oout=new LittleEndianOutputStream(out);

			SatelliteSettings		SatSettings = new SatelliteSettings();
			/* Scalar Items */
			SatSettings.ConnectionType = m_settings.getInt(TvSettingsConstants.INSTSETTINGSCONNECTIONTYPE, 0, 0);
			SatSettings.UserBandPrimaryTuner = m_settings.getInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER, 0, 0);
			SatSettings.UserBandFrequencyPrimaryTuner = m_settings.getInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER, 0, 0);
			SatSettings.UserBandSecondaryTuner = m_settings.getInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER, 0, 0);
			SatSettings.UserBandFrequencySecondaryTuner = m_settings.getInt(TvSettingsConstants.INSTSETTINGSUNICABLEBANDPRIMARYTUNER, 0, 0);

			/* Vector Items */
			SatSettings.LnbParameters = new SatelliteLnbParameters[4];
			for (int count =0; count < 4; count++)
			{
				SatSettings.LnbParameters[count] = new SatelliteLnbParameters();
				SatSettings.LnbParameters[count].LnbType = m_settings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBTYPE, count, 0);
				SatSettings.LnbParameters[count].LnbPower = m_settings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLNBPOWER, count, 0);
				SatSettings.LnbParameters[count].LowLoFreq = m_settings.getInt(TvSettingsConstants.INSTALLATIONSETTINGLOWLOFREQ, count, 9750000);
				SatSettings.LnbParameters[count].HighLoFreq = m_settings.getInt(TvSettingsConstants.INSTALLATIONSETTINGHIGHLOFREQ, count, 10600000);
				SatSettings.LnbParameters[count].ToneControl = m_settings.getInt(TvSettingsConstants.INSTALLATIONSETTINGTONECONTROL, count, 0);
				SatSettings.LnbParameters[count].SatelliteId = m_settings.getInt(TvSettingsConstants.INSTALLATIONSETTINGSATELLITEID, count, 0);
				try {
					String SatelliteName = m_settings.getString(TvSettingsConstants.INSTALLATIONSETTINGSATELLITENAME, count, "sat");
					byte[] SatelliteNameBytes = SatelliteName.getBytes("UTF-16LE");
					SatSettings.LnbParameters[count].SatelliteName = new byte [66];
					for (int Index =0; Index < 66; Index++)
					{
						if (Index < SatelliteNameBytes.length)
						{
							SatSettings.LnbParameters[count].SatelliteName[Index] = SatelliteNameBytes[Index];
						}
						else
						{
							SatSettings.LnbParameters[count].SatelliteName[Index] = 0;
						}
					}					
				}
				catch (Exception e)
				{
					for (int Index =0; Index < 66; Index++)
					{
						SatSettings.LnbParameters[count].SatelliteName[Index] = 0;
					}					
					
				}

			}
			
			Log.v (TAG, "Reading the Satellite Settings from TVSettings Complete. Start writing to binary file in USB ");
			oout.writeInt(SatSettings.ConnectionType);
			oout.writeInt(SatSettings.UserBandPrimaryTuner);
			oout.writeInt(SatSettings.UserBandFrequencyPrimaryTuner);
			oout.writeInt(SatSettings.UserBandSecondaryTuner);
			oout.writeInt(SatSettings.UserBandFrequencySecondaryTuner);
			for (int count =0; count < 4; count++)
			{
				oout.writeInt(SatSettings.LnbParameters[count].LnbType);
				oout.writeInt(SatSettings.LnbParameters[count].LnbPower);
				oout.writeInt(SatSettings.LnbParameters[count].LowLoFreq);
				oout.writeInt(SatSettings.LnbParameters[count].HighLoFreq);
				oout.writeInt(SatSettings.LnbParameters[count].ToneControl);
				oout.writeInt(SatSettings.LnbParameters[count].SatelliteId);
				oout.write(SatSettings.LnbParameters[count].SatelliteName);
			}
			
		}
		catch (Exception e)
		{
			Log.d (TAG, "Exception happening in writing Satellite Settings to binary file "+e);
		}		
	}



	
	public void StartUpdateBinaryDbForTerrestrial (File dest, String AirDbName)
	{
		Log.d(TAG, "StartUpdateBinaryDbForTerrestrial");
		ReadFromTVPAndWriteToBinaryChannelMap (dest, AirDbName, ANTENNA_MEDIUM);
	}
	
	public void StartUpdateBinaryDbForCable (File dest, String CableDbName)
	{
		Log.d(TAG, "StartUpdateBinaryDbForCable");
		ReadFromTVPAndWriteToBinaryChannelMap (dest, CableDbName, CABLE_MEDIUM);
	}
	
	public void StartUpdateBinaryDbForSatellite (File dest, String SatelliteDbName)
	{
		ReadFromTVPAndWriteToBinaryChannelMap (dest, SatelliteDbName, SATELLITE_MEDIUM);
	}
	

	public void ClearBinaryDbForTerrestrial (File dest, String AirDbName)
	{
		Log.d(TAG, "ClearToBinaryChannelMapTerrestrial");
		ClearToBinaryChannelMap (dest, AirDbName, ANTENNA_MEDIUM);
	}
	
	public void ClearBinaryDbForCable (File dest, String CableDbName)
	{
		Log.d(TAG, "ClearToBinaryChannelMapCable");
		ClearToBinaryChannelMap (dest, CableDbName, CABLE_MEDIUM);
	}

	public void StartUpdateTvDbForTerrestrial (File dest, String AirDbName)
	{
		ReadFromBinaryChannelMapAndUpdateTVP(dest, AirDbName, ANTENNA_MEDIUM);
	}
	
	public void StartUpdateTvDbForCable (File dest, String CableDbName)
	{
		ReadFromBinaryChannelMapAndUpdateTVP(dest, CableDbName, CABLE_MEDIUM);
	}
	
	public void StartUpdateTvDbForSatellite (File dest, String SatelliteDbName)
	{
		ReadFromBinaryChannelMapAndUpdateTVP(dest, SatelliteDbName, SATELLITE_MEDIUM);
	}
	
	public void SetApplicationContext (Context cxt)
	{
		copyContext = cxt;
	}

	public void StartUpdateTvSettingsForSatellite  (File dest, String SatelliteSettingsBinName) 
	{
		ReadFromBinarySettingsBinAndUpdateInTvSettings (dest, SatelliteSettingsBinName);
	}
	
	public void  StartUpdateSettingsBinForSatellite(File dest, String SatelliteSettingsBinName)
	{
		ReadFromTvSettingsAndUpdateInBinarySettings (dest, SatelliteSettingsBinName);
	}
		
}


