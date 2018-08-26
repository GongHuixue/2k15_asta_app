package org.droidtv.tunerservice.channellistcopy;

import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.tvinput.ILogoAssociationControl;
import org.droidtv.tv.provider.IFrequencyListContract.ISATFrequencyMap;
import org.droidtv.tv.provider.IFrequencyListContract.ITCFrequencyMap;
import org.droidtv.tv.provider.IFavoriteContract.ICFavoriteList1;
import org.droidtv.tv.provider.IFavoriteContract.ICFavoriteList2;
import org.droidtv.tv.provider.IFavoriteContract.ICFavoriteList3;
import org.droidtv.tv.provider.IFavoriteContract.ICFavoriteList4;
import org.droidtv.tv.provider.IFavoriteContract.ISATFavoriteList1;
import org.droidtv.tv.provider.IFavoriteContract.ISATFavoriteList2;
import org.droidtv.tv.provider.IFavoriteContract.ISATFavoriteList3;
import org.droidtv.tv.provider.IFavoriteContract.ISATFavoriteList4;
import org.droidtv.tv.provider.IFavoriteContract.ITFavoriteList1;
import org.droidtv.tv.provider.IFavoriteContract.ITFavoriteList2;
import org.droidtv.tv.provider.IFavoriteContract.ITFavoriteList3;
import org.droidtv.tv.provider.IFavoriteContract.ITFavoriteList4;
import android.media.tv.TvContract.Channels;
import android.os.RemoteException;
import android.content.ContentProviderClient;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

/**
 * Contains the Utility Functions which will be used by the Parser as well the
 * tableRelationship Manager
 * 
 * @author jainish.cs
 * 
 */
public class ChannelListUtil {

	
   private static final String TAG="ChanneListUtil";
   
   private static String CHANNELS_COLUMN_LOGO = "logo";
   
   /**
    * constant to associate the logos with all the mediums 
    */
   public static final String LOGO_ALL = "All";
  
   /**
	* channel table
    */
	public static final String TABLE_CHANNEL="channels";
	
	/**
	 * Terrestrial Favorite List1 Table
	 */
	public static final String TABLE_T_LIST1="TList1";
	
	/**
	 * Terrestrial Favorite List2 Table
	 */
	public static final String TABLE_T_LIST2="TList2";
	
	/**
	 * Terrestrial Favorite List3 Table
	 */
	public static final String TABLE_T_LIST3="TList3";
	
	/**
	 * Terrestrial Favorite List4 Table
	 */
	public static final String TABLE_T_LIST4="TList4";
	
	/**
	 * Cable Favorite List1 Table
	 */
	public static final String TABLE_C_LIST1="CList1";
	
	/**
	 * Cable Favorite List2 Table
	 */
	public static final String TABLE_C_LIST2="CList2";
	
	/**
	 * Cable Favorite List3 Table
	 */
	public static final String TABLE_C_LIST3="CList3";
	
	/**
	 * Cable Favorite List4 Table
	 */
	public static final String TABLE_C_LIST4="CList4";
	
	/**
	 * Satellite Favorite List1 Table
	 */
	public static final String TABLE_S_LIST1="SList1";
	
	/**
	 * Satellite Favorite List2 Table
	 */
	public static final String TABLE_S_LIST2="SList2";
	
	/**
	 * Satellite Favorite List3 Table
	 */
	public static final String TABLE_S_LIST3="SList3";
	
	/**
	 * Satellite Favorite List4 Table 
	 */
	public static final String TABLE_S_LIST4="SList4";
	
	/**
	 * Favorite List table
	 */
	public static final String TABLE_LIST="List";
	
	/**
	 * TC Frequency Table
	 */
	public static final String TABLE_TC_FREQUENCY="TCFrequency";
	   
	/**
	 * Satellite Frequency Table
	 */
	public static final String TABLE_SAT_FREQUENCY="SATFrequency";
 
    /**
  	 * method to open SQLite database
  	 * @param path
  	 * @param mode
  	 * @return database handler
  	 */
  	public  static SQLiteDatabase openDatabase(String path,int mode)
  	{
  		SQLiteDatabase db=SQLiteDatabase.openDatabase(path, null, mode);
  		return db;
  	}
	
	/**
  	 * method to get all columns as a projection
  	 * either Satellite or TC frequency table
  	 * @param medium
  	 * @return all columns
  	 */
    public static String[] getFrequencyProjection(String medium)
    {
    	String [] projection=null;
    	if(medium.equalsIgnoreCase(TABLE_SAT_FREQUENCY))
    	{
    		projection=new String[]{
        			ISATFrequencyMap.COLUMN_FREQUENCY,
        			ISATFrequencyMap.COLUMN_SYMBOLRATE,
        			ISATFrequencyMap.COLUMN_ORIGINALNETWORKID,
        			ISATFrequencyMap.COLUMN_TSID,
        			ISATFrequencyMap.COLUMN_MODULATIONTYPE,
        			ISATFrequencyMap.COLUMN_BANDWIDTH,
        			ISATFrequencyMap.COLUMN_BARKERMUX,
        			ISATFrequencyMap.COLUMN_PACKAGE_MUX,
        			ISATFrequencyMap.COLUMN_LNBNUMBER, 
        			ISATFrequencyMap.COLUMN_POLARIZATION,
        			ISATFrequencyMap.COLUMN_CODERATE, 
        			ISATFrequencyMap.COLUMN_MODULATIONSYSTEM,
        			ISATFrequencyMap.COLUMN_ROLLOFFFACTOR,
        			ISATFrequencyMap.COLUMN_FECINNER
        	       };  
    	}
    	else if(medium.equalsIgnoreCase(TABLE_TC_FREQUENCY))
    	{
    		projection=new String[]{
        			ITCFrequencyMap.COLUMN_FREQUENCY,
        			ITCFrequencyMap.COLUMN_SYMBOLRATE,
        			ITCFrequencyMap.COLUMN_ORIGINALNETWORKID,
        			ITCFrequencyMap.COLUMN_TSID,
        			ITCFrequencyMap.COLUMN_MODULATIONTYPE,
        			ITCFrequencyMap.COLUMN_BANDWIDTH,
        			ITCFrequencyMap.COLUMN_BARKERMUX,
        			ITCFrequencyMap.COLUMN_PACKAGE_MUX,
        			ITCFrequencyMap.COLUMN_GUARDINTERVAL,
        			ITCFrequencyMap.COLUMN_DECODERTYPE
        	       };  
    	}
    	
    	return projection;
    }
	
	/**
  	 * method to get all columns as a projection from the favorite lists
  	 * @param medium
  	 * @param table
  	 * @return all columns
  	 */
  	public static String[] getFavoriteListProjecion(String medium,String table)
  	{
  		String []projection=null;
  		
  		if(medium.equalsIgnoreCase(ILogoAssociationControl.MEDIUM_TERRESTRIAL))
  		{ 
              if(table.equalsIgnoreCase(TABLE_T_LIST1))
              {
            	  projection=new String[]{
            			  ITFavoriteList1.COLUMN_CHANNEL_ID,
            			  ITFavoriteList1.COLUMN_RANK,
            	  };
              }
              else if(table.equalsIgnoreCase(TABLE_T_LIST2))
              {
            	  projection=new String[]{
            			  ITFavoriteList2.COLUMN_CHANNEL_ID,
            			  ITFavoriteList2.COLUMN_RANK,
            	  };
              }
              else if(table.equalsIgnoreCase(TABLE_T_LIST3))
              {
            	  projection=new String[]{
            			  ITFavoriteList3.COLUMN_CHANNEL_ID,
            			  ITFavoriteList3.COLUMN_RANK,
            	  };
              }
              else if(table.equalsIgnoreCase(TABLE_T_LIST4))
              {
            	  projection=new String[]{
            			  ITFavoriteList4.COLUMN_CHANNEL_ID,
            			  ITFavoriteList4.COLUMN_RANK,
            	  };
              }
  		}
  		else if(medium.equalsIgnoreCase(ILogoAssociationControl.MEDIUM_CABLE))
  		{
  			 if(table.equalsIgnoreCase(TABLE_C_LIST1))
             {
           	  projection=new String[]{
           			  ICFavoriteList1.COLUMN_CHANNEL_ID,
           			  ICFavoriteList1.COLUMN_RANK,
           	  };
             }
             else if(table.equalsIgnoreCase(TABLE_C_LIST2))
             {
           	  projection=new String[]{
           			  ICFavoriteList2.COLUMN_CHANNEL_ID,
           			  ICFavoriteList2.COLUMN_RANK,
           	  };
             }
             else if(table.equalsIgnoreCase(TABLE_C_LIST3))
             {
           	  projection=new String[]{
           			  ICFavoriteList3.COLUMN_CHANNEL_ID,
           			  ICFavoriteList3.COLUMN_RANK,
           	  };
             }
             else if(table.equalsIgnoreCase(TABLE_C_LIST4))
             {
           	  projection=new String[]{
           			  ICFavoriteList4.COLUMN_CHANNEL_ID,
           			  ICFavoriteList4.COLUMN_RANK,
           	  };
             }
  		}
  		else if(medium.equalsIgnoreCase(ILogoAssociationControl.MEDIUM_SATELLITE))
  		{
  			 if(table.equalsIgnoreCase(TABLE_S_LIST1))
             {
           	  projection=new String[]{
           			  ISATFavoriteList1.COLUMN_CHANNEL_ID,
           			  ISATFavoriteList1.COLUMN_RANK,
           	  };
             }
             else if(table.equalsIgnoreCase(TABLE_S_LIST2))
             {
           	  projection=new String[]{
           			  ISATFavoriteList2.COLUMN_CHANNEL_ID,
           			  ISATFavoriteList2.COLUMN_RANK,
           	  };
             }
             else if(table.equalsIgnoreCase(TABLE_S_LIST3))
             {
           	  projection=new String[]{
           			  ISATFavoriteList3.COLUMN_CHANNEL_ID,
           			  ISATFavoriteList3.COLUMN_RANK,
           	  };
             }
             else if(table.equalsIgnoreCase(TABLE_S_LIST4))
             {
           	  projection=new String[]{
           			  ISATFavoriteList4.COLUMN_CHANNEL_ID,
           			  ISATFavoriteList4.COLUMN_RANK,
           	  };
             }
  		}
  		return projection;
  	}
	
	/**
  	 * method to get all columns as projection from the channel table(tv.db)
  	 * @return all columns 
  	 */
  	public static String[] getAllChannelColumnsAsProjecion()
  	{
  		String []projection=new String[]{
			    Channels._ID,
  				Channels.COLUMN_PACKAGE_NAME,
  				Channels.COLUMN_INPUT_ID,
  				Channels.COLUMN_TYPE,
  				Channels.COLUMN_SERVICE_TYPE,
  				Channels.COLUMN_ORIGINAL_NETWORK_ID,
  				Channels.COLUMN_TRANSPORT_STREAM_ID,
  				Channels.COLUMN_SERVICE_ID,
  				Channels.COLUMN_DISPLAY_NUMBER,
  				Channels.COLUMN_DISPLAY_NAME,
  				Channels.COLUMN_NETWORK_AFFILIATION,
  				Channels.COLUMN_DESCRIPTION,
  				Channels.COLUMN_VIDEO_FORMAT,
  				Channels.COLUMN_BROWSABLE,
  				Channels.COLUMN_SEARCHABLE,
  				Channels.COLUMN_LOCKED,
  				Channels.COLUMN_INTERNAL_PROVIDER_DATA,
				CHANNELS_COLUMN_LOGO,
  				Channels.COLUMN_VERSION_NUMBER
  		};
  		return projection;
  	}
	
	/**
	 * method to update major version based on medium
	 * @param medium
	 */
	public static void updateMajorVersion(String medium)
	{
	    int lCurrentVersion;
	    
	    ITvSettingsManager globalSetting = ITvSettingsManager.Instance.getInterface();
	    
	    if(medium.equalsIgnoreCase(ILogoAssociationControl.MEDIUM_TERRESTRIAL) ||
		       medium.equalsIgnoreCase(ILogoAssociationControl.MEDIUM_CABLE))
		{
	    	lCurrentVersion = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION , 0, 0);
	    	lCurrentVersion++;
	    	Log.d(TAG,"Setting new version to  " + lCurrentVersion + " for TC");
	    	globalSetting.putInt(TvSettingsConstants.INSTSETTINGSTCCHANNELTABLEVERSION, 0, lCurrentVersion);
		}
	    else
		{
			lCurrentVersion = globalSetting.getInt(TvSettingsConstants.INSTSETTINGSSATCHANNELTABLEVERSION, 0, 0);
			lCurrentVersion++;
			Log.d(TAG,"Setting new version to  " + lCurrentVersion + " for satellite");
			globalSetting.putInt(TvSettingsConstants.INSTSETTINGSSATCHANNELTABLEVERSION, 0, lCurrentVersion);
		}
	}
	  
  /**
   * Method to get last selected source(Terrestrial/Cable/Satellite)
   * @return:source
   */
   public static String getLastSelecetedTunerSource()
   {
	    ITvSettingsManager globalSetting = ITvSettingsManager.Instance.getInterface();
		int mCurrentMode=globalSetting.getInt(TvSettingsConstants.LASTSELECTEDTUNER, 0, 0);
		Log.d(TAG, "getLastSelecetedTuner():mCurrentMode->"+mCurrentMode);
		String source=null;
		
		if(mCurrentMode==TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC)
		{
			int mCurrentMedium=globalSetting.getInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, 0);
			Log.d(TAG, "getLastSelecetedTunerSource():mCurrentMedium->"+mCurrentMedium);
			if(mCurrentMedium==TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA)
			{
				source=ILogoAssociationControl.MEDIUM_TERRESTRIAL;
			}
			else if(mCurrentMedium==TvSettingsDefinitions.InstSettingsInstallMode.CABLE)
			{
				source=ILogoAssociationControl.MEDIUM_CABLE;
			}
		}
		else if(mCurrentMode==TvSettingsDefinitions.LastSelectedTunerConstants.DVBSTUNER)
		{
			source=ILogoAssociationControl.MEDIUM_SATELLITE;
		}
		return source;
   }
   
   /**
    * method to reset last selected tuner if need it
	*/
 	public static void setCurrentSelectedMedium(boolean isNoTerrChannels,boolean isNoCabChannels,boolean isNoSatChannels) 
	{
		String source=null;
		ITvSettingsManager globalSettings;
		
		try 
		{
			globalSettings = ITvSettingsManager.Instance.getInterface();
			
			// get last selected source
			source=getLastSelecetedTunerSource();
			Log.d(TAG,"setCurrentSelectedMedium():source"+source);
			
			if(source!=null)
			{
			    if(source.equalsIgnoreCase(ILogoAssociationControl.MEDIUM_SATELLITE))
			    {
			       if (isNoSatChannels == false) 
			       {
				       updateMajorVersion(ILogoAssociationControl.MEDIUM_SATELLITE);
			       }
			       else if (isNoTerrChannels == false) 
			       {  
			          globalSettings.putInt(TvSettingsConstants.LASTSELECTEDTUNER,0,TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC);	
				      globalSettings.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA);
			       }
			       else if (isNoCabChannels == false) 
			       {
				      globalSettings.putInt(TvSettingsConstants.LASTSELECTEDTUNER,0,TvSettingsDefinitions.LastSelectedTunerConstants.ANALOGDVBTC);	
				      globalSettings.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, TvSettingsDefinitions.InstSettingsInstallMode.CABLE);
			       }
			    }
			    else
			    {
				    if(source.equalsIgnoreCase(ILogoAssociationControl.MEDIUM_TERRESTRIAL) && (isNoTerrChannels == false))
				    {
				        updateMajorVersion(ILogoAssociationControl.MEDIUM_TERRESTRIAL);	
				    }
				    else if (source.equalsIgnoreCase(ILogoAssociationControl.MEDIUM_CABLE) && (isNoCabChannels == false)) 
				    {    
				        updateMajorVersion(ILogoAssociationControl.MEDIUM_CABLE);
			        }
				    else if(isNoTerrChannels==false)
				    {
					   globalSettings.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, TvSettingsDefinitions.InstSettingsInstallMode.ANTENNA);
				    }
			        else if (isNoCabChannels == false) 
				    {
				       globalSettings.putInt(TvSettingsConstants.INSTSETTINGSINSTALLMODE, 0, TvSettingsDefinitions.InstSettingsInstallMode.CABLE);
			        }
				    else if(isNoSatChannels == false)
				    {
					   globalSettings.putInt(TvSettingsConstants.LASTSELECTEDTUNER,0,TvSettingsDefinitions.LastSelectedTunerConstants.DVBSTUNER);
				    }
			    }
		    }
		}
		catch (Exception e) 
		{
			Log.d(TAG, "Exception in setCurrentSelectedMedium : "+ e.toString());
		}
	}
 	
 	/**
 	 * method to check whether channel database is empty or not  
 	 * @param providerclient
 	 * @param version
 	 * @return
 	 */
 	public static boolean databaseIsEmpty(ContentProviderClient providerclient,String[] projection, String selection,String[] selectionArgsVersion)
 	{
 		
 		Cursor cursor=null;
 		int count=0;
 		
 		if(providerclient!=null)
 		{
			Log.d(TAG,"databaseIsEmpty() called");
 			try {
				cursor=providerclient.query(Channels.CONTENT_URI,projection , selection, selectionArgsVersion, null);
				
				if(cursor!=null)
 		        {
 			         count=cursor.getCount();
 		        }
				
			} catch (RemoteException e) {
				Log.d(TAG,"databaseIsEmpty() called:exception:"+e);
			}
			finally
			{
				if(cursor!=null)
				{
					cursor.close();
					cursor=null;
				}
			}
 		}
 		
 		
 		if(count<1)
 		{
 			return true;
 		}
 		
 		return false;
 	}
}