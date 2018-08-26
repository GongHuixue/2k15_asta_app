package org.droidtv.tunerservice.channellistcopy;

import java.io.File;
import java.io.IOException;
import org.droidtv.tunerservice.channellistcopy.ChannelBinEntry.ChannelMapName;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.persistentstorage.TvSettingsDefinitions;
import org.droidtv.tv.provider.IChannelContract;
import org.droidtv.tv.provider.IFavoriteContract;
import org.droidtv.tv.provider.IFrequencyListContract;
import org.droidtv.tv.provider.IFavoriteContract.ISATFavoriteList1;
import org.droidtv.tv.provider.IFavoriteContract.ISATFavoriteList2;
import org.droidtv.tv.provider.IFavoriteContract.ISATFavoriteList3;
import org.droidtv.tv.provider.IFavoriteContract.ISATFavoriteList4;
import org.droidtv.tv.provider.IFrequencyListContract.ISATFrequencyMap;
import org.droidtv.tv.tvinput.ILogoAssociationControl;
import org.droidtv.tv.tvinput.ILogoAssociationControl.ILogoAssociationListener;
import org.droidtv.tunerservice.R;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.IBinder;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.ComponentName;
import android.content.ContentProviderClient;
import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.content.Intent;
import android.content.ServiceConnection;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.database.sqlite.SQLiteQueryBuilder;
import android.util.Log;
import android.view.ViewGroup.LayoutParams;
import android.widget.ProgressBar;
import org.droidtv.ui.strings.R.string;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialog;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogFooterButtonProp;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface.OnClickListener;
import org.droidtv.ui.tvwidget2k15.dialog.ModalDialogInterface;

/**
 * Copy:Copy from tv to usb and usb to tv 
 * @author sohan.gupta
 *
 */
public class Copy extends Activity 
{
	private Dialog mProgressDialog;
	private final String USBPATH_KEY="USBPath";
	private String USBMountPath;
	private Context cxt;
	File src,dest;
	String TAG="Copy";
	String action;
	String fileNameforLogos="syslogo.tar";
	String fileNameforBinFile="chanLst.bin";
    File srcDir=null,destDir=null;	
    int countryCode;
	int netherlandsCountryCode;
	private Intent intent=null;
	boolean flagToT=false,flagToS=false,flagToC=false;
	long Installation_Complete=0;
	String msg=null;
	String mTitle;
	int CopyType=0;
	int CopyToTV=3;
    int CopyToUSB=4;
    long Copy_Failed=0;
    long Copy_Success=1;
    long starttime=0;
	long endtime=0;
	String CHANNELS_COLUMN_LOGO = "logo";
	private ContentProviderClient mContentProviderClient; 
	
	@Override
	protected void onStart() 
	{
		super.onStart();
		Log.d(TAG,"tunerservice: onStart() for copy called");
		try
	    {
			  try
	          { 
			       Intent intenToMedium=new Intent();
	               intenToMedium.setAction("org.droidtv.tvcontentprovider.LogoService");
			  
		           if(intf==null)
		           {
					    Log.d(TAG,"binding service");
	                    bindService(intenToMedium, mConnection, Context.BIND_AUTO_CREATE);
		           }
	          }
	         catch(Exception e)
	         {
		         Log.d(TAG,"onStart():bindService():Exception"+e);
	         }    
	  
			   Intent intent=getIntent();
			   action=intent.getAction();
			   Log.d(TAG,"Action->"+action);
			   
			   // varify usb is connected or not,if yes than execute block
			   if(intent.getExtras()!=null)
			   {
				   mProgressDialog = new Dialog(this, R.style.channelcopyspinner);
				   mProgressDialog.addContentView(new ProgressBar(this),new LayoutParams(this.getResources()
									.getDimensionPixelSize(R.dimen.progressDialogwidth),
									this.getResources().getDimensionPixelSize(
											R.dimen.progressDialogheight)));
				   mProgressDialog.setCancelable(false);
						
				   //show Progressbar
				   mProgressDialog.show();
				   Log.d(TAG,"Mount path->"+getIntent().getExtras().getString(USBPATH_KEY));
				   
				   //check,mount path is available or not
				   if(getIntent().getExtras().containsKey(USBPATH_KEY))
				   {
						USBMountPath=getIntent().getExtras().getString(USBPATH_KEY);
						Log.d(TAG,"USB Mount Path->"+USBMountPath);
						File params=new File(new String(ICopy.pathForTVDatabases_AND_BinFiles));
					    Log.d(TAG,"Params:"+params);
					    
						// copy,if intent for TV To USB
						if((TvIntent.ACTION_COPY_FROM_TV_TO_USB).equalsIgnoreCase(action))
						{
							    dest = new File(USBMountPath);									
							    src  =  new File(new String(ICopy.pathForTVDatabases_AND_BinFiles));
							    Log.d(TAG,"TvIntent.ACTION_COPY_FROM_TV_TO_USB:SRC:"+src);
							    
							    //copy, if source location is exist
							    if(src.exists())
							    {
								    Log.d(TAG,"TvIntent.ACTION_COPY_FROM_TV_TO_USB:SRC is exist");
							    	if(src.list().length==0)
								    {
								    	Log.d(TAG,"ChannelMaps are not Found");
								    	
								    	//show error message if source location has no channelmaps
								    	showAlertDialog(cxt.getString(string.MAIN_MSG_COPY_TO_USB_FAILED),cxt.getString(string.MAIN_COPY_TO_USB));
								    }
							    	else
							    	{
							    		//copy, if destination location is exist
									    if(dest.exists())
									    {
									        //Creating Directory Structure in USB
									    	if(CopyFromTVToUSB.createDirectoryStructure(dest))
									    	{
									    	     new Progress().execute(params);
									    	}
									    	else
									    	{
									    		Log.d(TAG, "Access Denied To Create Directory Structure in USB");
							  			    	showAlertDialog(cxt.getString(string.MAIN_MSG_COPY_TO_USB_FAILED),cxt.getString(string.MAIN_COPY_TO_USB));
									    	}
									    }
									    else
									    {
									    	Log.d(TAG,"mount path does not exist");
									    	
									    	//show error message if destination location is not exist
									    	showAlertDialog(cxt.getString(string.MAIN_MSG_DEVICE_NOT_PRESENT),cxt.getString(string.MAIN_COPY_TO_USB));
									    }
							    	}
							    }
							    else
							    {
							    	Log.d(TAG,"source path does not exist");
							    	
							    	//show error message if source location is not exist
							    	showAlertDialog(cxt.getString(string.MAIN_MSG_COPY_TO_USB_FAILED),cxt.getString(string.MAIN_COPY_TO_USB));
							    }
							}
							else if((TvIntent.ACTION_COPY_FROM_USB_TO_TV).equalsIgnoreCase(action))
							{	// copy,if intent for USB To TV

								src = new File(USBMountPath);
								dest =new File(new String(ICopy.pathForTVDatabases_AND_BinFiles));
								
						        Log.d(TAG,"Source Path->"+src);
						        Log.d(TAG,"Destination Path->"+dest);
						        
						        //show error message, if destination  is not exist
						        if(!dest.exists())
							    {
							    	Log.d(TAG,"Destination does not exist");
						        	showAlertDialog(cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED),cxt.getString(string.MAIN_COPY_TO_TV));
							    }
						        else if(!src.exists())
						        {
						        	Log.d(TAG,"USB is not Mounted");
						        	showAlertDialog(cxt.getString(string.MAIN_MSG_DEVICE_NOT_PRESENT),cxt.getString(string.MAIN_COPY_TO_TV));
						        }
						        else //if(!showErrorMessage(src))
								{
									 Log.d(TAG, "Action="+action);
									 srcDir=new File(src,ICopy.pathForBinFile_OR_DB_ToUSB);

									 // varify source is exist if true,execute block
									 if(srcDir!=null && srcDir.exists())
									 {
										 showConfirmationDialog(cxt.getString(string.MAIN_DI_COPY_TO_TV_WARNING),cxt.getString(string.MAIN_COPY_TO_TV));
									 }
									 else
									 {
										 // check,DB files and ChanLst.bin file are available or not,if not than show the Message
										 Log.d(TAG,"path for bin file is not available");
										 showAlertDialog(cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED),cxt.getString(string.MAIN_COPY_TO_TV));
									 }
								}
							}
				   }
				   else
				   {
					   Log.d(TAG,"MountPath Variable is not found in Activity Intent");
					   
					   if((TvIntent.ACTION_COPY_FROM_TV_TO_USB).equalsIgnoreCase(action))
			           {
				           showAlertDialog(cxt.getString(string.MAIN_MSG_DEVICE_NOT_PRESENT),cxt.getString(string.MAIN_COPY_TO_USB));
			           }
			           else if((TvIntent.ACTION_COPY_FROM_USB_TO_TV).equalsIgnoreCase(action))
			           {
				            showAlertDialog(cxt.getString(string.MAIN_MSG_DEVICE_NOT_PRESENT),cxt.getString(string.MAIN_COPY_TO_TV));
			           }
				   }
			   }
			   else
			   {
				   Log.d(TAG,"No USB Found");
				   
				   if((TvIntent.ACTION_COPY_FROM_TV_TO_USB).equalsIgnoreCase(action))
			       {
				        showAlertDialog(cxt.getString(string.MAIN_MSG_DEVICE_NOT_PRESENT),cxt.getString(string.MAIN_COPY_TO_USB));
			       }
			       else if((TvIntent.ACTION_COPY_FROM_USB_TO_TV).equalsIgnoreCase(action))
			       {
				        showAlertDialog(cxt.getString(string.MAIN_MSG_DEVICE_NOT_PRESENT),cxt.getString(string.MAIN_COPY_TO_TV));
			       }
			   }
	    }
	   catch (Exception e) 
	   {
		    Log.d(TAG,"Exception in Copy "+e);
			
		    if((TvIntent.ACTION_COPY_FROM_TV_TO_USB).equalsIgnoreCase(action))
			{
				showAlertDialog(cxt.getString(string.MAIN_MSG_COPY_TO_USB_FAILED),cxt.getString(string.MAIN_COPY_TO_USB));
			}
			else if((TvIntent.ACTION_COPY_FROM_USB_TO_TV).equalsIgnoreCase(action))
			{
				showAlertDialog(cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED),cxt.getString(string.MAIN_COPY_TO_TV));
			}
    	}
	}

	@Override
	protected void onDestroy() 
	{
		
		if(mProgressDialog!=null)
		{
			//dismiss dialog if it is showing
			if(mProgressDialog.isShowing())
				mProgressDialog.dismiss();
		}
		
		if(mContentProviderClient!=null)
		{
		    //releasing contentprovider client
			mContentProviderClient.release();
			mContentProviderClient=null;
		}
		
		Log.d(TAG,"onDestroy() called");
		super.onDestroy();
	}

	@Override
	protected void onStop() 
	{
		//dismiss dialog progressbar if it is showing
		if (intf != null) {
			intf.unregisterListenerCallback(listener);
		}
		if(mProgressDialog!=null)
		{
			if(mProgressDialog.isShowing())
				mProgressDialog.dismiss();
		}
		Log.d(TAG,"onStop() called");
		super.onStop();
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.channel_list_copy);
		Log.d(TAG,"onCreate() called");
		
		//getting application context
		cxt=getApplicationContext();
		
		try
		{
			mContentProviderClient=cxt.getContentResolver().acquireContentProviderClient(TvContract.AUTHORITY);
		}
		catch(Exception e)
		{
			Log.d(TAG,"onCreate():Exception:"+e);
		}	
	}

  class Progress extends AsyncTask<File,Long,Long>
  {
	@Override
	protected void onPostExecute(Long result) 
	{
		Log.d(TAG,"tuner:called postExecute()");
		onWorkerThreadComplete(result,CopyType);
        super.onPostExecute(result);		
	}

	@Override
	protected Long doInBackground(File... params) 
	{
		try 
		{ 
		    starttime=System.currentTimeMillis();
		    Log.d(TAG,"start time for copy:"+starttime);
			ITvSettingsManager globalSettings = ITvSettingsManager.Instance.getInterface();
			netherlandsCountryCode=TvSettingsDefinitions.InstallationCountryConstants.NETHERLANDS;
			//creating references to chanLst.bin
			ChannelBinEntry.ChannelMapName []objToSATFiles = null;
			ChannelBinEntry.ChannelMapName []objToTCFiles=null;
			ChannelBinEntry.ChannelMapName []objToDBFiles=new ChannelBinEntry.ChannelMapName[2];
			
			//check,intent for TV TO USB if true,execute block
			if((TvIntent.ACTION_COPY_FROM_TV_TO_USB).equalsIgnoreCase(action))
			{
				CopyType=4;
				
				// declaration of ChanLst.bin file's variable 
				int version,setTypeSize,seperatorSize,size,mVersion,lVersion;
				char crc; 
				String name,setType,SeperatorString;
				String padding;
				File mTCDir=null;
				
				// initialization of ChanLst.bin file's variables
				mVersion=ICopy.majorVersion;
				lVersion=ICopy.minorVersion;
				version=mVersion<<16;
				version|=lVersion;
				countryCode= globalSettings.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
				
				// Write Padding
				padding="0000000000"; 
				name=padding;
				setType=globalSettings.getString(TvSettingsConstants.SETTYPE, 0, null);
				setType=setType+ICopy.nullChar;
				setTypeSize= setType.length();
				SeperatorString=ICopy.s2Folder+ICopy.nullChar;
				seperatorSize= SeperatorString.length();
			    File destDir=dest;
				int dbindex=0;
			    Log.d(TAG,"Destination: "+dest);
		        Log.d(TAG,"Country Code->"+countryCode);
		        
			    try
			    {
			    	    // Iterating the DB files from TV						
  	  				    for(String fileName:src.list())
  	  				    {
  	  				    	  Log.d(TAG,"File="+fileName);
							  
							  if(fileName.equalsIgnoreCase(ICopy.channelDB) ||fileName.equalsIgnoreCase(ICopy.favoriteDB))
  	  				    	  {
	  	  				    		  objToDBFiles[dbindex]=new ChannelMapName();
	  	  				    	 	  destDir=new File(dest,ICopy.pathForDBToUSB);
		  							  Log.d(TAG,"Destination directory->>"+destDir);
		  							  
		  							  //Construct the source and destination file structure for channels db
		  							  File srcFile=new File(ICopy.pathForTVDatabases_AND_BinFiles,fileName);
		  							  File destFile=new File(destDir,fileName);
		  							  Log.d(TAG,"Source File->"+srcFile);
		  							  Log.d(TAG,"Destination File->"+destFile);
		  							  
		  							  //copying database from tv to usb and returning crc
		  							  crc=new CopyFromTVToUSB().copyDatabase(srcFile, destFile);
		  							  
		  							  // check, country code if netherland than execute block
		  							  if(countryCode==netherlandsCountryCode)
		  							  {
		  								  Log.d(TAG,"Country code Is Netherland");
		  								  
		  								  // deleting all the Records except S and S2 services from the USB's database
		  								  updateUSBDatabases(destFile.toString(),fileName);
		  								  crc=new CopyFromTVToUSB().getCRC(destFile);
		  							  }
		  							  int tempcrc=crc;
		  							  Log.d(TAG,"CRC for File "+fileName+"="+tempcrc);
		  							  
		   							  // +1 to null character
		  							  size= (fileName+ICopy.nullChar).length();
		  							  Log.d(TAG,"size for "+fileName+"="+size);
		  							  objToDBFiles[dbindex].setValues(size,(fileName+ICopy.nullChar).getBytes(),crc);
  	  				    			  ++dbindex;
  	  				    		  }
							  
							  // Varify, folder is s2 channellib, if true,Execute block
							  else if(fileName.equalsIgnoreCase(ICopy.mS2Channellib))
  	  						  {
  	  				    		  File mSatDir=new File(ICopy.pathForSatToTV);
  	  				    		
  	  				    		  int numOfSATFiles=mSatDir.list().length;
  	  				    		  Log.d(TAG,"Number of SAT Files for copying To USB:"+numOfSATFiles);
  	  				    		  
  	  				    		  if(numOfSATFiles!=0)
  	  				    		  {
  	  				    			  objToSATFiles=new ChannelMapName[numOfSATFiles];
  	  				    			  int satindex=0;
  	  				    			  destDir=new File(dest,ICopy.pathForSatToUSB);
  	  				    			  
  	  	  				    		  for(String mfile:mSatDir.list())
  	  	  				    		  {
  	  	  				    			  Log.d(TAG,"mFile="+mfile);
  		  	  				    		  
  		  	  	  						  //Construct the source and destination file structure for SatelliteChannelMaps
  		  	  	  						  File srcFile=new File(ICopy.pathForSatToTV,mfile);
  		  	  	  						  File destFile=new File(destDir,mfile);
  		  	  	  						  Log.d(TAG,"Source File->"+srcFile);
  		  	  	  						  Log.d(TAG,"Destination File->"+destFile);
  		  	  	  						
  		  	  	  						  try
  		  	  	  						  {
  		  	  	  						     //copying SatelliteChannelMaps files from tv to usb and returning crc
  	  		  	  	  						  crc=new CopyFromTVToUSB().copyDatabase(srcFile, destFile);
  	  		  	  	  				          objToSATFiles[satindex]=new ChannelMapName();
  	  		  	  	  						  int tempcrc=crc;
  	  		  	  	  						  Log.d(TAG,"CRC value for file "+mfile+"="+tempcrc);
  	  		  	  	  							  
  	  		  	  	  						  //+1 to null character
  	  		  	  	  						  size= (mfile+ICopy.nullChar).length();
  	  		  	  	  						  Log.d(TAG,"Size of "+mfile+"="+size);
  	  		  	  	  						  objToSATFiles[satindex].setValues(size, (mfile+ICopy.nullChar).getBytes(), crc);
  	  		  	  	  					      satindex++;
  		  	  	  						  }
  		  	  	  						  catch(Exception e)
  		  	  	  						  {
  		  	  	  						      Log.d(TAG,"Exception in copying Satellite files to usb->"+e);
  		  	  	  						  }
  	  	  				    		  }
  	  				    		  }
  	  						  }
  	  				    	  else if(fileName.equalsIgnoreCase(ICopy.mChannellib) && netherlandsCountryCode!=countryCode)
  							  {
  	  				    		  mTCDir=new File(ICopy.pathForTerrCabToTV);
  	  				    		  int numOfTCFiles=mTCDir.list().length;
	  				    		  Log.d(TAG,"Number of TC Files for copying To USB:"+numOfTCFiles);
	  				    		  
	  				    		  if(numOfTCFiles!=0)
	  				    		  {
  	  				    			  objToTCFiles=new ChannelBinEntry.ChannelMapName[numOfTCFiles];
	  				    			  int tcindex=0;
	  				    			  destDir=new File(dest,ICopy.pathForTerrCabToUSB);
	  				    			
  	  				    			  for(String mfile:mTCDir.list())
	  								  {
			  							  Log.d(TAG,"Destination directory->>"+destDir);
			  							  
			  							  //Construct the source and destination file structure for TerrestrialChannelMap
			  							  File srcFile=new File(mTCDir,mfile);
			  							  File destFile=new File(destDir,mfile);
			  							  Log.d(TAG,"Source File->"+srcFile);
			  							  Log.d(TAG,"Destination File->"+destFile);
			  							  
			  							  //copying Terrestrial/Cable ChannelMaps files from tv to usb and returning crc
			  							  try
			  							  {
			  								  crc=new CopyFromTVToUSB().copyDatabase(srcFile, destFile);
			  								  objToTCFiles[tcindex]=new ChannelBinEntry.ChannelMapName();
				  							  int tempcrc=crc;
				  							  Log.d(TAG,"CRC value for file "+mfile+"="+tempcrc);
				  							  
				   							  // +1 to null character
				  							  size= (mfile+ICopy.nullChar).length();
				  							  Log.d(TAG,"size for "+mfile+"="+size);
				  							  objToTCFiles[tcindex].setValues(size,(mfile+ICopy.nullChar).getBytes(),crc);
				  							  tcindex++;  
			  							  }
			  							  catch(Exception e)
			  							  {
			  								  Log.d(TAG,"Exception in copying terrestrial/cable files to usb->"+e);
			  							  }
	  								  }	
	  				    		  }
  							  }
  	  				    }
  	  				    
						Log.d (TAG, " -- Copy to USB -- TVP -> Binary ");
						ChannelMapBlobHandler	channelMapBlob = new ChannelMapBlobHandler(USBMountPath);
						channelMapBlob.SetApplicationContext(cxt);
												 
				       if(countryCode!=netherlandsCountryCode)
					   {
				           Log.d(TAG,"country code is not Netherlands");
						   channelMapBlob.StartUpdateBinaryDbForTerrestrial (dest, ICopy.terrestrialChannelMapBinFile);
						   channelMapBlob.StartUpdateBinaryDbForCable (dest, ICopy.cableChannelMapBinFile);	   
					   }
					   else 
					   {
							Log.d(TAG,"Clearing the database for Netherlands");
							channelMapBlob.ClearBinaryDbForTerrestrial (dest, ICopy.terrestrialChannelMapBinFile);
							channelMapBlob.ClearBinaryDbForCable (dest, ICopy.cableChannelMapBinFile);
					   }
						
						channelMapBlob.StartUpdateBinaryDbForSatellite (dest, ICopy.satelliteChannelMapBinFile);
						channelMapBlob.StartUpdateSettingsBinForSatellite (dest, ICopy.satelliteSetttingsBinFile);
						
  	  					ChannelBinEntry channelBinEntry=new ChannelBinEntry(setTypeSize,seperatorSize);
  	  					
  	  					// Initializing the  values for channelbin file 
  	  					channelBinEntry.setValues(version, name.getBytes(), countryCode, setTypeSize, 
  	  							setType.getBytes(),objToDBFiles,objToTCFiles, seperatorSize,
  	  							SeperatorString.getBytes(), objToSATFiles);
  	  					File destBinDir=new File(dest,ICopy.pathForBinFile_OR_DB_ToUSB);
  	  					Log.d(TAG,"Destination path for Bin->"+destBinDir);
  	  					
  	  					// Making Entry in ChannelBin File
  	  					channelBinEntry.writeChannelBin(destBinDir,fileNameforBinFile);
  	  					Log.d(TAG, "Entry is done for channelbin entry");
  	  					
					   // Construct the destination file structure for system logos
  	  		           destDir=new File(dest,ICopy.pathForSystemLogosToUSB);   
					   Log.d(TAG,"interface object"+intf);
	                   if(intf!=null)
					   {						   
						    // copying logos from tv to usb
					        intf.copyLogo(destDir.toString(), fileNameforLogos);
			                Log.d(TAG, "Tar File is Created on Location->"+destDir);
				       }
					   else
					   {
						   msg=cxt.getString(string.MAIN_MSG_COPY_TO_USB_FAILED);
						   mTitle=cxt.getString(string.MAIN_COPY_TO_USB);
						   return Copy_Failed;
					   }
					   
  	  				    msg=cxt.getString(string.MAIN_MSG_COPY_TO_USB_SUCCESS);
						mTitle=cxt.getString(string.MAIN_COPY_TO_USB);
  	  				    return Copy_Success;
			    }
			    catch(Exception e)
			    {
			    	Log.d(TAG,"Exception in copying to usb"+e);
			    	objToDBFiles=null;
  	  				objToTCFiles=null;
  	  				objToSATFiles=null;
  	  				msg=cxt.getString(string.MAIN_MSG_COPY_TO_USB_FAILED);
					mTitle=cxt.getString(string.MAIN_COPY_TO_USB);
  	  				return Copy_Failed;
			    }
	
			}
		    else if((TvIntent.ACTION_COPY_FROM_USB_TO_TV).equalsIgnoreCase(action))
		    { // check,intent for USB TO TV if true,execute block
			
		        CopyType=3;
		        boolean tc_success=false,s_success=false;
                int nCopyChannelMaps=0,nBinChannelMaps=0;			     
		        Installation_Complete=0;
		        int installedCountryCode = 0;
			    int mVersion=0,lVersion=0;
			 	File srcFile=null,destFile=null;
			    File srcDir=null,destDir=null;
			    installedCountryCode=globalSettings.getInt(TvSettingsConstants.INSTALLATIONCOUNTRY, 0, 0);
			    Log.d(TAG, "Action="+action);
			    srcDir=new File(src,ICopy.pathForBinFile_OR_DB_ToUSB);
				ChannelBinEntry channelbinEntry=null;
				
				try
				{
					channelbinEntry=new ChannelBinEntry();
					 
					 // varify chanLst.bin file read successfully if true,execute block
					if(channelbinEntry.readChannelBin(srcDir, fileNameforBinFile))
					{
						 // getting version from .bin file
						 lVersion= channelbinEntry.version;
						 mVersion=(lVersion>>16) & 0xFFFF;
					     lVersion=lVersion & 0xFFFF;
					     Log.d(TAG,"Major Version="+mVersion);     
						 Log.d(TAG,"Minor Version="+lVersion);
						 int crcFromBinFileToSatFile=0,crcFromUSBtoSatFile=0;
						 int crcFromBinFileToTCFile = 0,crcFromUSBtoTCFile=0;
								 
						 // read country code from .bin file
						 countryCode=channelbinEntry.country;
						 
						 if(countryCode!=installedCountryCode)
						 {
							 Log.d(TAG,"Copy Failed : Country Code Does Not Match");
							 msg=cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED);
							 mTitle=cxt.getString(string.MAIN_COPY_TO_TV);
							 return Copy_Failed;
						 }
						 
						if(channelbinEntry.mTCFileList!=null && channelbinEntry.mTCFileList.size()>0)
						{
							tc_success=true;
							for(int i=0;i<channelbinEntry.mTCFileList.size();i++)
							{
								 ChannelMapName obj=channelbinEntry.mTCFileList.get(i);
							     crcFromBinFileToTCFile=obj.crc;
							     String filename=channelbinEntry.mTCFileList.get(i).OriginalFileName;
							     Log.d(TAG,"copy to tv:FileName->"+filename);
							     
								 if(obj.OriginalFileName.equalsIgnoreCase(ICopy.favoriteDB) 
										 || obj.OriginalFileName.equalsIgnoreCase(ICopy.channelDB))
								 {
									 
									 srcDir=new File(src,ICopy.pathForBinFile_OR_DB_ToUSB);
									 srcFile= new File(srcDir,filename);
								     destFile=new File(ICopy.pathForTVDatabases_AND_BinFiles,filename);
									 crcFromBinFileToTCFile=obj.crc;
									 nBinChannelMaps++;
									 
									 try
									 {
										 char p=new CopyFromUSBToTV().getCRC(srcFile);
										 int c=p;
										 Log.d(TAG,"CRC without Reverse integer->"+c);
										 crcFromUSBtoTCFile=Character.reverseBytes(p);
										 Log.d(TAG,"CRC Reverse integer->"+crcFromUSBtoTCFile);
										 Log.d(TAG,"crc from bin file->"+crcFromBinFileToTCFile+" crcFromUSB for TC file->"+crcFromUSBtoTCFile);
									 }
									 catch(IOException e)
									 {
										 Log.d(TAG,"Excepton in crc's calculation:"+e);
										 crcFromUSBtoTCFile=0;
									 }
								 }
								 else
								 {
									 if(countryCode!=netherlandsCountryCode)
									 {
										 srcDir=new File(src,ICopy.pathForTerrCabToUSB);
										 srcFile= new File(srcDir,filename);
									     destFile=new File(ICopy.pathForTerrCabToTV,filename);
										 crcFromBinFileToTCFile=obj.crc;
										 nBinChannelMaps++;
										 
										 try
										 {
											 char p=new CopyFromUSBToTV().getCRC(srcFile);
											 int c=p;
											 Log.d(TAG,"CRC without Reverse integer->"+c);
											 crcFromUSBtoTCFile=Character.reverseBytes(p);
											 Log.d(TAG,"CRC Reverse integer->"+crcFromUSBtoTCFile);
											 Log.d(TAG,"crc from bin file->"+crcFromBinFileToTCFile+" crcFromUSB for Sat file->"+crcFromUSBtoTCFile);
										 }
										 catch(IOException e)
										 {
											 Log.d(TAG,"Exception in crc's calculation:"+e);
											 crcFromUSBtoTCFile=0;
										 }
									 }
									 else
									 {
										 srcFile=null;
										 destFile=null;
									 }
									 
								}
								if(srcFile!=null)
								{
									if(crcFromBinFileToTCFile==crcFromUSBtoTCFile)
								    {
										  Log.d(TAG,"crc match for file:"+srcFile);
										  if(srcFile.exists())
										  {
											try
											{
												
												if((countryCode==netherlandsCountryCode) && (obj.OriginalFileName.equalsIgnoreCase(ICopy.favoriteDB) 
														 || obj.OriginalFileName.equalsIgnoreCase(ICopy.channelDB)))
												{
													// updating the tv databases
													updateTVDatabase(srcFile.toString(),obj.OriginalFileName);
												}
												else
												{
													CopyFromUSBToTV cpToTv = new CopyFromUSBToTV();
													if (obj.OriginalFileName.equalsIgnoreCase(ICopy.channelDB)) {
														destFile = new File(ICopy.pathForTVDatabases_AND_BinFiles, ICopy.channelDB_backup);
														cpToTv.copyDatabase(srcFile, destFile);
														cpToTv.updateTVDB();
													} else {
														cpToTv.copyDatabase(srcFile, destFile);
													}													
												}
												nCopyChannelMaps++;
											    flagToT=true;
											}
											catch(Exception e)
											{
												Log.d(TAG,"Exception in crc's calculation:"+e);
											}
										  }
								    }
									else
									{
										msg=cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED);
										mTitle=cxt.getString(string.MAIN_COPY_TO_TV);
										Log.d(TAG,"TC ChannelMap has currupted");
										flagToT=false;
									}
								}
							}
						}
						else
						{
							tc_success=false;
						}
						 if(channelbinEntry.mSATFileList!=null && channelbinEntry.mSATFileList.size()>0)
						 {
							 s_success=true;
							 srcDir=new File(src,ICopy.pathForSatToUSB);
							 for(int i=0;i<channelbinEntry.mSATFileList.size();i++)
							 {
								 ChannelMapName obj=channelbinEntry.mSATFileList.get(i);
							     crcFromBinFileToSatFile=obj.crc;
							     nBinChannelMaps++;
							     String filename=channelbinEntry.mSATFileList.get(i).OriginalFileName;
							     srcFile= new File(srcDir,filename);
							     destFile=new File(ICopy.pathForSatToTV,filename);
							     try
							     {
							    	 char p=new CopyFromUSBToTV().getCRC(srcFile);
									 int c=p;
									 Log.d(TAG,"CRC without Reverse integer->"+c);
									 crcFromUSBtoSatFile=Character.reverseBytes(p);
									 Log.d(TAG,"CRC Reverse integer->"+crcFromUSBtoSatFile);
									 Log.d(TAG,"crc from bin file->"+crcFromBinFileToSatFile+" crcFromUSB for satellite files->"+crcFromUSBtoSatFile);
							     }
							     catch(IOException e)
							     {
							    	 Log.d(TAG,"Excepton in crc's calculation:"+e);
							    	 crcFromUSBtoSatFile=0;
							     }
								 
								 if(crcFromBinFileToSatFile==crcFromUSBtoSatFile)
							     {
									Log.d(TAG,"crc match for file:"+srcFile);
									if(srcFile.exists())
									{
										try
										{
											new CopyFromUSBToTV().copyDatabase(srcFile, destFile);
											nCopyChannelMaps++;
										    flagToS=true;
										}
										catch(Exception e)
										{
											Log.d(TAG,"Excepton in crc's calculation:"+e);
										}
									}
							     }
								 else
								 {
									   msg=cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED);
									   mTitle=cxt.getString(string.MAIN_COPY_TO_TV);
									   Log.d(TAG,"SatelliteChannelMap has currupted");
									   flagToS=false;
								 }
							 } 
						 }
						 else
						 {
							 s_success=false;
						 }
						 

						 if(tc_success==false && s_success==false)
						 {
							 Log.d(TAG,"COPY FAILED : No ChannelMaps are Found");
							 msg=cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED);
							 mTitle=cxt.getString(string.MAIN_COPY_TO_TV);
							 return Copy_Failed;
						 }
						 
						Log.d (TAG, " -- Copy to USB -- TVP -> Binary ");
						ChannelMapBlobHandler	channelMapBlob = new ChannelMapBlobHandler(USBMountPath);
						channelMapBlob.SetApplicationContext(cxt);
						 if (tc_success == true)
						 {
							Log.d(TAG, " --- Copy To TV --- TC ");
							channelMapBlob.StartUpdateTvDbForTerrestrial (src, ICopy.terrestrialChannelMapBinFile);
							channelMapBlob.StartUpdateTvDbForCable (src,ICopy.cableChannelMapBinFile);		
						 }
						 if (s_success == true)
						 {
							Log.d(TAG, " --- Copy To TV --- SAT ");
							channelMapBlob.StartUpdateTvDbForSatellite (src, ICopy.satelliteChannelMapBinFile);
							channelMapBlob.StartUpdateTvSettingsForSatellite(src, ICopy.satelliteSetttingsBinFile);
						 }
					}
					else
					{
				   		msg=cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED);
						mTitle=cxt.getString(string.MAIN_COPY_TO_TV);
						Log.d(TAG,fileNameforBinFile+" File is not found");
						return Copy_Failed;
					}
					 				
				  if(nCopyChannelMaps==nBinChannelMaps)
				  {
					  msg=cxt.getString(string.MAIN_MSG_COPY_TO_TV_SUCCESS);
					  mTitle=cxt.getString(string.MAIN_COPY_TO_TV);
					  return Copy_Success;
				  }
				  else 
				  {
					  Log.d(TAG,"Copied Successfully : Some Files has Currupted");
					  msg=cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED);
					  mTitle=cxt.getString(string.MAIN_COPY_TO_TV);
					  return Copy_Failed;
				  }
		        }
				catch(Exception e)
				{
					Log.d(TAG,"Exception in Copying Files Copy To TV->"+e);
					msg=cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED);
					mTitle=cxt.getString(string.MAIN_COPY_TO_TV);
		            return Copy_Failed;
				}
		    }
		} 
		catch(Exception e)
		{
			// TODO Auto-generated catch block
			Log.d(TAG,"Exception in Copying Files->"+e);
			if((TvIntent.ACTION_COPY_FROM_TV_TO_USB).equalsIgnoreCase(action))
			{
			    msg=cxt.getString(string.MAIN_MSG_COPY_TO_USB_FAILED);
				mTitle=cxt.getString(string.MAIN_COPY_TO_USB);
			}
			else if((TvIntent.ACTION_COPY_FROM_USB_TO_TV).equalsIgnoreCase(action))
			{
				msg=cxt.getString(string.MAIN_MSG_COPY_TO_TV_FAILED);
				mTitle=cxt.getString(string.MAIN_COPY_TO_TV);
			}
		}
		
		return Copy_Failed;
	}
  }
  
  /**
   * progressBarDismiss():Method is used to come out from current activity
   */
  private void progressBarDismiss()
  {	  
	  super.finish();
  }
  
  
  
  /**
   * showAlertDialog(): Method is used to showing alert Dialog box
   * @param msg:To display error message on alert dialog box
   */
  private void showAlertDialog(final String msg,final String title)
  {
	    
	  /*final AlertDialog.Builder builder = new AlertDialog.Builder(Copy.this);
	  builder.setOnCancelListener(new OnCancelListener() {
		
		@Override
		public void onCancel(DialogInterface dialog) {
			Log.d(TAG, "onCancel called succesfully");
			finish();
		}
	});
	  Log.d(TAG,"set the values in Dialog");
      builder.setCancelable(true);
      builder.setTitle(title);
      builder.setMessage(msg);
      builder.setInverseBackgroundForced(false);
      builder.setPositiveButton(cxt.getString(string.MAIN_BUTTON_OK),
              new DialogInterface.OnClickListener() {
                  @Override
                  public void onClick(DialogInterface dialog,
                          int which) {
                	  Log.d(TAG,"value of pressing button"+which);
                	  switch(which)
                	  {
                	  case -1:
                		  dialog.dismiss();
                		  finish();
                	  break;
                	  default:
                		  Log.d(TAG,"Dialog is value="+which);
                		  dialog.dismiss();
                	  }
                      
                     
                  }
              });
			  
	  runOnUiThread(new Runnable() {
      public void run() 
	  {
           Log.d(TAG,"Dialog is created");
           AlertDialog alert = builder.create();
           Log.d(TAG,"show dialog");
      
      alert.show();
      }
      });
      */
	 
     
	runOnUiThread(new Runnable() {
      public void run() 
	  {
		Log.d(TAG,"Model Dial called");
	    final ModalDialog.Builder builder = new ModalDialog.Builder(Copy.this,
		ModalDialog.HEADING_TYPE_DEFAULT);
		Log.d(TAG,"builder is created");
		builder.setHeading(title, null);
		Log.d(TAG,"Heading is created");
		builder.setMessage(msg);
		Log.d(TAG,"Message is created");
		builder.setButton(ModalDialog.BUTTON_RIGHT,cxt.getString(string.MAIN_BUTTON_OK), true,
				new OnClickListener() {

					@Override
					public void onClick(ModalDialogInterface modalDialogInterface, int which) {
						Log.d(TAG,"showAlertDialog()->OnClickListener() called modalDialogInterface:"+modalDialogInterface+ " which:"+which+" ModalDialog.BUTTON_RIGHT:"+ModalDialog.BUTTON_RIGHT);
						//modalDialogInterface.dismiss();
						finish();
					}
				});
	 Log.d(TAG,"Dialog is created");
           Log.d(TAG,"Dialog is created");
           builder.build().show();
           Log.d(TAG,"show dialog");
	 }});
		
  }
  
	/*DialogInterface.OnClickListener dialogClickListener=  new DialogInterface.OnClickListener() 
	{
        @Override
        public void onClick(DialogInterface dialog,int which) 
        {
          Log.d(TAG,"dialogClickListener");
      	  Log.d(TAG,"onClick() value of pressing button->"+which);
      	  switch(which)
      	  {
      	  case DialogInterface.BUTTON_POSITIVE:
      		  
			  Log.d(TAG,"DialogInterface.BUTTON_POSITIVE"+DialogInterface.BUTTON_POSITIVE);
	          new Progress().execute(new File("param"));
      	  break;
      	  case DialogInterface.BUTTON_NEGATIVE:
      		  Log.d(TAG,"DialogInterface.BUTTON_NEGATIVE"+DialogInterface.BUTTON_NEGATIVE);
      		  dialog.dismiss();
      	      finish();
      	  break;
      	  default:
      		  Log.d(TAG,"Dialog Default values is value="+which);
      		  dialog.dismiss();
      	  }
        }
    };*/
  private void showConfirmationDialog(String msg,String title)
  {
	  /*AlertDialog.Builder builder = new AlertDialog.Builder(Copy.this);
	  Log.d(TAG,"set the values in Dialog");
      builder.setCancelable(true);
      builder.setTitle(title);
      builder.setMessage(msg);
      builder.setInverseBackgroundForced(false);
      builder.setPositiveButton(cxt.getString(string.MAIN_BUTTON_YES),dialogClickListener);
      builder.setNegativeButton(cxt.getString(string.MAIN_BUTTON_NO),dialogClickListener);
      Log.d(TAG,"Dialog is created");
      AlertDialog alert = builder.create();
      Log.d(TAG,"show dialog");
      alert.show();*/
	  
	  final ModalDialog.Builder builder = new ModalDialog.Builder(Copy.this,
				ModalDialog.HEADING_TYPE_DEFAULT);
	  Log.d(TAG,"set the values in Dialog");
	  builder.setHeading(title,null);
	  builder.setMessage(msg);

	  builder.setButtons(new ModalDialogFooterButtonProp(true, cxt.getString(string.MAIN_BUTTON_YES),
				new OnClickListener() {

					@Override
					public void onClick(
							ModalDialogInterface modalDialogInterface, int which) {
						 Log.d(TAG,"showConfirmationDialog()->modalDialogInterface onClick():yes which"+which+" modalDialogInterface:"+modalDialogInterface);
	                     new Progress().execute(new File("param"));
					}
				}), new ModalDialogFooterButtonProp(true, cxt.getString(string.MAIN_BUTTON_NO),
				new OnClickListener() {

					@Override
					public void onClick(
							ModalDialogInterface modalDialogInterface, int which) {
						Log.d(TAG,"modalDialogInterface onClick():no which"+which+" modalDialogInterface:"+modalDialogInterface);
      		            finish();

					}
				}));

		builder.build().show();
  }
  public void deleteAllFiles(File src)
  {
	  if(src!=null)
	  {
		  for(File fileName:src.listFiles())
		  {
			  fileName.delete();
		  }
	  }
  }
  
    ILogoAssociationControl intf = null;  
	public Notify listener = new Notify();

  private ServiceConnection mConnection = new ServiceConnection() {

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) 
		{
			Log.d(TAG, "onServiceConnected called");
			intf =ILogoAssociationControl.Instance.asInterface(service); 
			Log.d(TAG, "ILogoAssociationControl object"+intf);
		}

		@Override
		public void onServiceDisconnected(ComponentName name) 
		{
			// TODO Auto-generated method stub
			Log.d(TAG, "onServiceDisconnected called");
			if(intf!=null)
			{
				Log.d(TAG, "unbinding logo service");
			    intf=null;
			}
		}
  };
  
  class Notify extends ILogoAssociationListener
  {
	    @Override
		public void onLogoAssociationStateChanged(int State) {
			Log.d(TAG, "onLogoAssociationStateChanged called with State - "+State+" !!!");
		
			if (State == ILogoAssociationControl.LOGO_ASSOCIATION_STATE_COMPLETE) {
				Log.d(TAG, "****************LOGO ASSOCIATION COMPLETE RECEIVED !!! ****************");
				//updateChannelMapMajorVersion();
				
				// show dialog "Copy complete"
				showAlertDialog(msg,mTitle);
				endtime=System.currentTimeMillis();
      		    Log.d(TAG,"end time for copy:"+endtime);
  		        long duration=endtime-starttime;
  		        Log.d(TAG,"duration time for copy:"+duration);
			}
		}
  }
 
  
  public void  updateChannelMapMajorVersion()
  {
	  if(flagToT==true || flagToC==true)
	  {
		    ChannelListUtil.updateMajorVersion(ILogoAssociationControl.MEDIUM_TERRESTRIAL);
	  }
	 
	  if(flagToS==true)
	  {
		   ChannelListUtil.updateMajorVersion(ILogoAssociationControl.MEDIUM_SATELLITE);	       
	  }
  }
  
  public void onWorkerThreadComplete(long result, int copyType) 
  { 
	  if ((copyType == CopyToTV) && (result == 1)) 
	  {
		try
	    { 
		   if(intf!=null)
		   {
	            Log.d(TAG, "starting logo association after Copy To TV");
	            
	            // register lister to callback
				intf.registerListenerCallback(listener);
				
				String []projection=new String[]{Channels.COLUMN_VERSION_NUMBER};
				String selectionTerr=Channels.COLUMN_VERSION_NUMBER+" =?";
				String []selectionTerrVersion=new String[]{"0"};
				
				String selectionCab=Channels.COLUMN_VERSION_NUMBER+" =?";
				String []selectionCabVersion=new String[]{"1"};
				
				String selectionSAT=Channels.COLUMN_VERSION_NUMBER+" IN(?,?,?,?)";
				String []selectionSATVersion=new String[]{"2","3","4","5"};
				
				boolean isNoTerrChannels=ChannelListUtil.databaseIsEmpty(mContentProviderClient,projection,selectionTerr,selectionTerrVersion);
				boolean isNoCabChannels=ChannelListUtil.databaseIsEmpty(mContentProviderClient,projection,selectionCab,selectionCabVersion);
				boolean isNoSatChannels=ChannelListUtil.databaseIsEmpty(mContentProviderClient,projection,selectionSAT,selectionSATVersion);
				
				Log.d(TAG,"isNoTerrChannels:"+isNoTerrChannels+" isNoCabChannels"+isNoCabChannels+" isNoSatChannels"+isNoSatChannels);
				ChannelListUtil.setCurrentSelectedMedium(isNoTerrChannels,isNoCabChannels,isNoSatChannels);
				intf.StartLogoAssociation(ChannelListUtil.LOGO_ALL);
		   }
	    }
	    catch(Exception e)
	    {
		    Log.d(TAG,"onWorkerThreadComplete():Exception"+e);
	    }   
	  }
	  else if ((copyType == CopyToUSB) && (result == 1)) 
	  {
			// show dialog Copy complete
		    showAlertDialog(msg,mTitle);
	  }
	  else 
	  {
		  String errorMsg=msg;
		  // show dialog from buffer
		   showAlertDialog(errorMsg,mTitle);
		  
	  }	  
  }
	
  	private ContentProviderOperation deleteDataFromTV(Uri uri,String selection,String []selectionArgs)
  	{
		Log.d(TAG,"deleteDataFromTV(): called: uri"+uri);
		 //operation to delete the S or S2 channels from a TV
  		ContentProviderOperation deleteOperation=ContentProviderOperation.newDelete(uri)
  				.withSelection(selection, selectionArgs).build();
  		return deleteOperation;
  	}
  	
  	private ArrayList<ContentProviderOperation> getFavoriteList(SQLiteDatabase db,Uri uri,String medium,String table)
  	{
		Log.d(TAG,"getFavoriteList(): called medium:"+medium+" table:"+table);
  		ArrayList<ContentProviderOperation> operations=new ArrayList<ContentProviderOperation>();
  		String []columns=null;
  		Cursor cursor=null;
  		
  		if(medium!=null && table!=null)
  		{
  			columns=ChannelListUtil.getFavoriteListProjecion(medium,table);
  		}
  		
  		if(columns!=null)
  		{
			//Log.d(TAG,"getFavoriteList(): called  columns:"+columns);
  			cursor=getServicesFromUSB(db,table,columns,null,null);
  		}
  		
  		if(cursor!=null)
  		{
			ContentProviderOperation addFavListOperation=null;
			ContentValues values=null;
  			try
  	        {
  				if(cursor.moveToFirst())
  		 		{		
			        Log.d(TAG,"getFavoriteList(): called cursor has records");
  					do
  					{
  						values=new ContentValues();
  						
  						String newID=getMap().get(cursor.getString(cursor.getColumnIndex(ISATFavoriteList1.COLUMN_CHANNEL_ID)));
  						Log.d(TAG,"new id"+newID);
  						values.put( ISATFavoriteList1.COLUMN_CHANNEL_ID, newID);
						values.put(ISATFavoriteList1.COLUMN_RANK, cursor.getString(cursor.getColumnIndex(ISATFavoriteList1.COLUMN_RANK)));
  						addFavListOperation=ContentProviderOperation.newInsert(uri).withValues(values)
  								.build();
  						operations.add(addFavListOperation);
  					}while(cursor.moveToNext());
  		 		}
  	        }
  	        finally
  	        {
  	        		cursor.close();
  	        		cursor=null;
  	        }	
  		}
  		return operations;
  	}
  	
  	private ArrayList<ContentProviderOperation> getFrequencyList(SQLiteDatabase db,Uri uri,String medium,String table) throws Exception 
  	{
		Log.d(TAG,"getFrequencyList(): called uri:"+uri);
  		ArrayList<ContentProviderOperation> operations=new ArrayList<ContentProviderOperation>();
  		String []columns=null;
  		Cursor cursor=null;
  	
  		if(medium!=null)
  		{
  			columns=ChannelListUtil.getFrequencyProjection(medium);
  		}

  		if(columns!=null)
  		{
  			cursor=getServicesFromUSB(db,table,columns,null,null);
  			
  			if(cursor!=null)
  	  		{
				ContentProviderOperation addFrequencyOperation=null;
				ContentValues values=null;
  	  			try
  	  	        {
  	  				if(cursor.moveToFirst())
  	  		 		 {
  	  			        Log.d(TAG,"getFrequencyList(): called Cursor has records");		
                        do
                        {
							values=new ContentValues();
                        	for(int i=0;i<columns.length;i++)
      	  					{
      	  						values.put(columns[i], cursor.getString(cursor.getColumnIndex(columns[i])));
      	  					}
      	  					addFrequencyOperation=ContentProviderOperation.newInsert(uri)
      	  							.withValues(values)
      	  							.build();
                            operations.add(addFrequencyOperation);	
                        }while(cursor.moveToNext());
  	  		 		 }
					 
  	  	        }
  	  	        finally
  	  	        {
  	  	        		cursor.close();
  	  	        		cursor=null;
  	  	        }	
  	  		}
  		}
  		return operations;
  	}
  	
	
    private ArrayList<String> mNewChannelIds=new ArrayList<String>();
    private boolean hasFavoriteChannels=false;
	
    private void updateChannelDatabase(String DBPath) throws Exception
    {
    	String selection=Channels.COLUMN_TYPE+" IN (?,?)";
  	    String []selectionArgs=new String[]{Channels.TYPE_DVB_S,Channels.TYPE_DVB_S2};
     
     	ArrayList<ContentProviderOperation> channelOperations=new ArrayList<ContentProviderOperation>();
     	ArrayList<ContentProviderOperation> channelsDelOperations=new ArrayList<ContentProviderOperation>();
 		Log.d(TAG,"updateChannelDatabase():database path"+DBPath);
     	SQLiteDatabase channel_db=ChannelListUtil.openDatabase(DBPath,SQLiteDatabase.OPEN_READWRITE);
		File favoriteDBFile=new File(USBMountPath,ICopy.pathForBinFile_OR_DB_ToUSB +ICopy.favoriteDB);
		
		Log.d(TAG,"favoriteDBPath:"+favoriteDBFile.toString());
		SQLiteDatabase favorite_db=ChannelListUtil.openDatabase(favoriteDBFile.toString(),SQLiteDatabase.OPEN_READWRITE);
        
     	if(channel_db!=null && favorite_db!=null)
         {
     		try
             {		
     			
     			Cursor favoriteListCursor=favorite_db.rawQuery(getFavoriteListView(),null);
     			
                ContentProviderOperation delOperation=null;
  	  			
  	  		    // operation to delete the S or S2 channels from a TV
  	  			delOperation=ContentProviderOperation.newDelete(Channels.CONTENT_URI)
  	  	  				.withSelection(selection, selectionArgs).build();
  	  		    
  	  			//adding a deletion operation with the applybatch
  	  		    channelsDelOperations.add(delOperation);
  	  		   
  	  		    
     			if(favoriteListCursor!=null)
     			{
					Log.d(TAG,"database has favorite services");
					if(favoriteListCursor.getCount()>0)
					{
     				   hasFavoriteChannels=true;
					}
     				favoriteListCursor.close();
					favoriteListCursor=null;
     			}
     			
     			ArrayList<ContentProviderOperation> Operations=getChannelListOperations(channel_db,Channels.CONTENT_URI,ChannelListUtil.TABLE_CHANNEL);
     			
     			if(cxt!=null && Operations!=null)
     			{
     				int operationSize=Operations.size();	
 					int count=0;
 					cxt.getContentResolver().applyBatch(TvContract.AUTHORITY, channelsDelOperations);
 				    Log.d(TAG,"delete all satellite services ");	 
					
 					for(int i=0;i<operationSize;i++)
 					{
 						count++;
 						channelOperations.add(Operations.get(i));
 						
 						if(count==30 || i==operationSize-1)
 	 					{
 							ContentProviderResult[] contentproviderresult=cxt.getContentResolver().applyBatch(TvContract.AUTHORITY, channelOperations);
 							if(hasFavoriteChannels)
 							{
								// caching new generated channel ids
 								for(int j=0;j<contentproviderresult.length;j++)
 	 							{
 	 								mNewChannelIds.add(contentproviderresult[j].uri.getLastPathSegment());
 	 							}	
 							}
 							channelOperations.clear();
 							count=0;
 							
 							try 
 						    {
 								Thread.sleep(30);
 						    } 
 							catch (InterruptedException e) 
 							{
 								Log.d(TAG,"updateChannelDatabase():Exception "+e);
 							}
 	 					}
 					}
 					if(getMap().size()==mNewChannelIds.size())
 					{
						//Collections.sort(mNewChannelIds);
 						Log.d(TAG,"count of new and old channel ids are equal");
						
						// getting all the old channel ids as keys
						String []keys=getMap().keySet().toArray(new String[0]);
						Arrays.sort(keys);
						
 						for(int j=0;j<getMap().size();j++)
 						{
 							String id=mNewChannelIds.get(j);
 							Log.d(TAG,"mNewChannelIds unique id:"+id);
							Log.d(TAG,"keys:"+keys[j]);
							// mapping old channel ids with the new channel ids, here key will be old channel id and value will be new channel id
 						    setMap(keys[j],id);
 						}
 					}
     			}
             }
             finally
             {
             	channel_db.close();
             	channel_db=null;
             }
         }
     }
	 
    private void updateFvFreqDatabase(String DBPath)throws Exception
    {
		 Log.d(TAG,"updateFvFreqDatabase(): called");
    	 ArrayList<ContentProviderOperation> favoriteOperations=new ArrayList<ContentProviderOperation>();
  		 ArrayList<ContentProviderOperation> frequencyOperations=new ArrayList<ContentProviderOperation>();
  		 SQLiteDatabase fre_fav_db=ChannelListUtil.openDatabase(DBPath,SQLiteDatabase.OPEN_READWRITE);
  		
  		 if(fre_fav_db!=null)
         {
       	     try
     		 {
	       		 favoriteOperations.add(deleteDataFromTV(ISATFavoriteList1.CONTENT_URI,null,null));
	       		 if(hasFavoriteChannels)
	       		 {		 
			        Log.d(TAG,"has favorite sat1");
	           	    favoriteOperations.addAll(getFavoriteList(fre_fav_db,ISATFavoriteList1.CONTENT_URI,ILogoAssociationControl.MEDIUM_SATELLITE,ChannelListUtil.TABLE_S_LIST1));
	       		 }
	           	 favoriteOperations.add(deleteDataFromTV(ISATFavoriteList2.CONTENT_URI,null,null));
	           	 if(hasFavoriteChannels)
	       		 {		 
			        Log.d(TAG,"has favorite sat2");
	           		favoriteOperations.addAll(getFavoriteList(fre_fav_db,ISATFavoriteList2.CONTENT_URI,ILogoAssociationControl.MEDIUM_SATELLITE,ChannelListUtil.TABLE_S_LIST2));
	       		 }
	           	 
	           	 favoriteOperations.add(deleteDataFromTV(ISATFavoriteList3.CONTENT_URI,null,null));
	           	 
	           	 if(hasFavoriteChannels)
	       		 {		 
			        Log.d(TAG,"has favorite sat3");
	           		favoriteOperations.addAll(getFavoriteList(fre_fav_db,ISATFavoriteList3.CONTENT_URI,ILogoAssociationControl.MEDIUM_SATELLITE,ChannelListUtil.TABLE_S_LIST3));
	       		 }
	           	 
	           	 favoriteOperations.add(deleteDataFromTV(ISATFavoriteList4.CONTENT_URI,null,null));
	           	 
	           	 if(hasFavoriteChannels)
	       		 {	
                    Log.d(TAG,"has favorite sat4");			 
	           	    favoriteOperations.addAll(getFavoriteList(fre_fav_db,ISATFavoriteList4.CONTENT_URI,ILogoAssociationControl.MEDIUM_SATELLITE,ChannelListUtil.TABLE_S_LIST4));
	       		 }
	           	
	       		 Log.d(TAG,"updateFvFreqDatabase(): called frequency operation");          
	       	     frequencyOperations.add(deleteDataFromTV(ISATFrequencyMap.CONTENT_URI,null,null));
	       		 frequencyOperations.addAll(getFrequencyList(fre_fav_db,ISATFrequencyMap.CONTENT_URI,ILogoAssociationControl.MEDIUM_SATELLITE,ChannelListUtil.TABLE_SAT_FREQUENCY));
				 
	       		 if(cxt!=null)
				 {
					Log.d(TAG,"updateFvFreqDatabase(): calling apply batch for favorite and frequency operation");
					int operationSize=favoriteOperations.size();
 					int count=0;
 					ArrayList<ContentProviderOperation> Operations=new ArrayList<ContentProviderOperation>();
 					for(int i=0;i<operationSize;i++)
 					{
 						count++;
 						Operations.add(favoriteOperations.get(i));
 						
 						if(count==500 || i==operationSize-1)
 	 					{
 							cxt.getContentResolver().applyBatch(IFavoriteContract.AUTHORITY, Operations);
 							Log.d(TAG,"apply batch finished with favorite operations");
 							Operations.clear();
 							count=0;
 							
 							try 
 						    {
 								Thread.sleep(30);
 						    } 
 							catch (InterruptedException e) 
 							{
 								Log.d(TAG,"updateChannelDatabase():Exception "+e);
 							}
 	 					}
 					}
 					hasFavoriteChannels=false;
 					operationSize=frequencyOperations.size();
 					Operations.clear();
 					
 					for(int i=0;i<operationSize;i++)
 					{
 						count++;
 						Operations.add(frequencyOperations.get(i));
 						
 						if(count==500 || i==operationSize-1)
 	 					{
 							cxt.getContentResolver().applyBatch(IFrequencyListContract.AUTHORITY, Operations);
 							Log.d(TAG,"apply batch finished with frequency operations");
 							Operations.clear();
 							count=0;
 							
 							try 
 						    {
 								Thread.sleep(30);
 						    } 
 							catch (InterruptedException e) 
 							{
 								Log.d(TAG,"updateChannelDatabase():Exception "+e);
 							}
 	 					}
 					}
 					
     			}
     		 }
     		 finally
     		 {
     			 fre_fav_db.close();
     			 fre_fav_db=null;
     		 }
         }
    }
	
    private void updateTVDatabase(String DBPath,String fileName) throws Exception
    {
		Log.d(TAG,"database path:"+DBPath+"filename:"+fileName);
		
    	if(fileName.equalsIgnoreCase(ICopy.channelDB))
    	{
			// to update channel database
    		updateChannelDatabase(DBPath);
    	}
    	else if(fileName.equalsIgnoreCase(ICopy.favoriteDB))
    	{
			// to update favorite database 
    		updateFvFreqDatabase(DBPath);
    	}
    		
    }
  	

    Map<String,String> old_new_uniqueId=new HashMap<String,String>();
    private void setMap(String oldChannelId, String newChannelId)
    {
    	old_new_uniqueId.put(oldChannelId, newChannelId);
    }
    private Map<String,String> getMap()
    {
    	return old_new_uniqueId;
    }
  	private ArrayList<ContentProviderOperation> getChannelListOperations(SQLiteDatabase db,Uri uri,String table) throws Exception
  	{
		Log.d(TAG,"getChannelListOperations() called");
  	    Cursor cursor=null;	
  	    String []columns=null;
  	    String selection=Channels.COLUMN_TYPE+" IN (?,?)";
  	    String []selectionArgs=new String[]{Channels.TYPE_DVB_S,Channels.TYPE_DVB_S2};
  		ArrayList<ContentProviderOperation> operations=new ArrayList<ContentProviderOperation>();
  		columns=ChannelListUtil.getAllChannelColumnsAsProjecion();
  		
  		if(columns!=null)
  		{
  			try
  	  		{
				Log.d(TAG,"getChannelListOperations() columns are not null");
  	  			cursor=getServicesFromUSB(db,table,columns,selection,selectionArgs);
  	  				
  	  			if(cursor!=null && cursor.moveToFirst())
  	  	  	  	{
  	  				ContentValues sChannelMapValues=null;
  	  				ContentProviderOperation insertOperation=null;
  	  				
  	  	  	 		// loop for adding new S or S2 services into a database 
  	  	  	  		do
  	  	  	  		{
  	  	  	  		    sChannelMapValues =new ContentValues();
  	  	  	  	        String _ID=cursor.getString(cursor.getColumnIndex(Channels._ID));
						
						// initializing map by old channel id
  	  	  	  	        setMap(_ID,_ID);
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_PACKAGE_NAME, cursor.getString(cursor.getColumnIndex(Channels.COLUMN_PACKAGE_NAME)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_INPUT_ID, cursor.getString(cursor.getColumnIndex(Channels.COLUMN_INPUT_ID)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_TYPE, cursor.getString(cursor.getColumnIndex(Channels.COLUMN_TYPE)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_SERVICE_TYPE, cursor.getString(cursor.getColumnIndex(Channels.COLUMN_SERVICE_TYPE)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_ORIGINAL_NETWORK_ID, cursor.getInt(cursor.getColumnIndex(Channels.COLUMN_ORIGINAL_NETWORK_ID)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_TRANSPORT_STREAM_ID, cursor.getInt(cursor.getColumnIndex(Channels.COLUMN_TRANSPORT_STREAM_ID)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_SERVICE_ID, cursor.getInt(cursor.getColumnIndex(Channels.COLUMN_SERVICE_ID)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_DISPLAY_NUMBER, cursor.getString(cursor.getColumnIndex(Channels.COLUMN_DISPLAY_NUMBER)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_DISPLAY_NAME, cursor.getString(cursor.getColumnIndex(Channels.COLUMN_DISPLAY_NAME)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_NETWORK_AFFILIATION, cursor.getString(cursor.getColumnIndex(Channels.COLUMN_NETWORK_AFFILIATION)));
  	  	  	  	        sChannelMapValues.put(Channels.COLUMN_DESCRIPTION, cursor.getString(cursor.getColumnIndex(Channels.COLUMN_DESCRIPTION)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_BROWSABLE, cursor.getInt(cursor.getColumnIndex(Channels.COLUMN_BROWSABLE)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_SEARCHABLE, cursor.getInt(cursor.getColumnIndex(Channels.COLUMN_SEARCHABLE)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_LOCKED, cursor.getInt(cursor.getColumnIndex(Channels.COLUMN_LOCKED)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_INTERNAL_PROVIDER_DATA, cursor.getBlob(cursor.getColumnIndex(Channels.COLUMN_INTERNAL_PROVIDER_DATA)));
						sChannelMapValues.put(CHANNELS_COLUMN_LOGO, cursor.getBlob(cursor.getColumnIndex(CHANNELS_COLUMN_LOGO)));
  	  	  	  		    sChannelMapValues.put(Channels.COLUMN_VERSION_NUMBER, cursor.getInt(cursor.getColumnIndex(Channels.COLUMN_VERSION_NUMBER)));
  
  	  	  	  		    insertOperation=ContentProviderOperation.newInsert(uri)
  		  	  					.withValues(sChannelMapValues).build();
  	  	  			   
  	  	  			   // adding the insertion operations with applybatch
  	  	  			   operations.add(insertOperation);
  	  	  	  		}while(cursor.moveToNext());
  	  	  	  	}
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
  		return operations;
  	}
  	
  	private Cursor getServicesFromUSB(SQLiteDatabase db,String table,
  			String []projection,String selection,String []selectionArgs) throws SQLiteException
  	{

  		Cursor cursor=null;
  		SQLiteQueryBuilder qb=new SQLiteQueryBuilder();
  		qb.setTables(table);
  		cursor=qb.query(db, projection, selection, selectionArgs, null, null, null);

  		return cursor;
  	}
  	
  	
  	/**
  	 * method to delete the services except S and S2 from the temporary location 
  	 * @param path:USB's path for the tv.db and list.db databases
  	 * @throws SQLiteException
  	 */
  	private void updateUSBDatabases(String path,String fileName) throws SQLiteException
  	{
  		SQLiteDatabase db=null;
  		String selection=null;
  	    String []selectionArgs=null;
  		try
  		{
  			Log.d(TAG,"Database opened path:"+path);
  			
  			// opening a database over a USB's location
  			db=ChannelListUtil.openDatabase(path,SQLiteDatabase.OPEN_READWRITE);
  			
  			if(db!=null  && fileName.equalsIgnoreCase(ICopy.channelDB))
  			{
  				selection=Channels.COLUMN_TYPE+" NOT IN(?,?)";
  				selectionArgs=new String[]{Channels.TYPE_DVB_S,Channels.TYPE_DVB_S2};
  	  		    db.delete(ChannelListUtil.TABLE_CHANNEL, selection, selectionArgs);
  			}
  	  		else if(db!=null && fileName.equalsIgnoreCase(ICopy.favoriteDB))
  	  		{
  	  		    try
  	  		    {
  	  		        // start transaction
  	  	  			db.beginTransaction();
  	  	  		    
  	  	  			/**
  	  	  			 * deleting Terrestrial and Cable Favorite list
  	  	  			 */
  	  	  			db.delete(ChannelListUtil.TABLE_T_LIST1, selection, selectionArgs);
  	  	  		    db.delete(ChannelListUtil.TABLE_T_LIST2, selection, selectionArgs);
  	  	  		    db.delete(ChannelListUtil.TABLE_T_LIST3, selection, selectionArgs);
  	  	  		    db.delete(ChannelListUtil.TABLE_T_LIST4, selection, selectionArgs);
  	  	  		    db.delete(ChannelListUtil.TABLE_C_LIST1, selection, selectionArgs);
  	  	  		    db.delete(ChannelListUtil.TABLE_C_LIST2, selection, selectionArgs);
  	  	  		    db.delete(ChannelListUtil.TABLE_C_LIST3, selection, selectionArgs);
  	  	  		    db.delete(ChannelListUtil.TABLE_C_LIST4, selection, selectionArgs);
  	  	  		    db.delete(ChannelListUtil.TABLE_TC_FREQUENCY, selection, selectionArgs);
  	  	  		    
  	  	  		    // set transaction as successful
  	  	  		    db.setTransactionSuccessful();
  	  		    }
  	  			finally
  	  			{
  	  			    // end transaction
  	  				db.endTransaction();
  	  			}
  	  		}
  		}
  		finally
  		{
  			if(db!=null)
  			{
  				db.close();
  		  	    db=null;
  			}
  		}
  	}
  	
  	private String getFavoriteListView()
  	{
  		
  		String mSelectFor_SAT_FavView1_Schema=  " SELECT "+
	    		ISATFavoriteList1.COLUMN_CHANNEL_ID+
	    		" FROM "+ICopy.TABLE_S_LIST1;
	    		
		 
	 
  		String mSelectFor_SAT_FavView2_Schema= " SELECT "+
	    		ISATFavoriteList2.COLUMN_CHANNEL_ID+
	    		" FROM "+ICopy.TABLE_S_LIST2;

  		String mSelectFor_SAT_FavView3_Schema=  " SELECT "+
	    		ISATFavoriteList3.COLUMN_CHANNEL_ID+
	    		" FROM "+ICopy.TABLE_S_LIST3;
		
  		String mSelectFor_SAT_FavView4_Schema= " SELECT "+
	    		ISATFavoriteList4.COLUMN_CHANNEL_ID+
	    		" FROM "+ICopy.TABLE_S_LIST4;  		   
		 String mDB_S_ALL_FavView_Schema=mSelectFor_SAT_FavView1_Schema+" UNION "+mSelectFor_SAT_FavView2_Schema+
  				  " UNION "+mSelectFor_SAT_FavView3_Schema+" UNION "+mSelectFor_SAT_FavView4_Schema;
  		  Log.d(TAG,"mDB_SAT_ALL_FavView_Schema is created->"+mDB_S_ALL_FavView_Schema);
  		  
 		
  		return mDB_S_ALL_FavView_Schema;
  	}
 }

