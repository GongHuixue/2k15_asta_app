package org.droidtv.tunerservice.channellistcopy;

import java.io.File;
import java.io.IOException;

/**
 * Interface:ICopy
 * @author sohan.gupta
 *
 */
public interface ICopy 
{
	/**
	 * majorVersion: major version to channelmap 
	 */
	int majorVersion=30;
	
	/**
	 * minorVersion:minor version to channelmap
	 */
	int minorVersion=1;
	
	/**
	 * channel database name
	 */
	 String channelDB="tv.db";
	 
	/**
	 * channel database name
	 */
	 String channelDB_backup="tv_bak.db";

	 /**
	 * favorite database name
	 */
	 String favoriteDB="list.db";
	 
	/**
	 * s2Folder:seprator for satellitechannelmaps files
	 */
	String s2Folder="/s2channellib/";
	
	/**
	 * tcFolder:seprator for T/C channelmaps
	 */
	String tcFolder="/channellib/";
	
	/**
	 * pathForTerrCabToUSB:path for channellib folder in usb
	 */
    String pathForTerrCabToUSB="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/ChannelList"+tcFolder;
    
    /**
	 * pathForDBToUSB:path for DBs files
	 */
    String pathForDBToUSB="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/ChannelList/";
    
    /**
     * pathForSatToUSB:path for s2channellib folder in usb
     */
    String pathForSatToUSB="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/ChannelList"+s2Folder;
    
    /**
     * pathForUserLogosToUSB:path for user logos folder in usb
     */
	String pathForUserLogosToUSB="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/usr";
	
	/**
	 * Installation_Complete:installation complete code
	 */
	long Installation_Complete=2;
	
	/**
	 * pathForSystemLogosToUSB:logos path in usb
	 */
	String pathForSystemLogosToUSB="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/";
	
	/**
	 * pathForSystemLogosToUSB:system logos path in tv
	 */
	String pathForSystemLogos="Logos/sys";
	
	/**
	 * pathForUserLogos:user logos path in tv
	 */
	String pathForUserLogos="Logos/usr";
	
	/**
	 * pathForLogos:logos directory name
	 */
	String pathForLogos="Logos";
	
	/**
	 * usrDir:user logos directory name
	 */
	String usrDir="usr";
	
	/**
	 * sysDir:system logos directory name
	 */
	String sysDir="sys";
	
	/**
	 * mChannellib:directory name for TC files
	 */
    String mChannellib="channellib";
	
	/**
	 * mS2Channellib:directory name for SAT files
	 */
    String mS2Channellib="s2channellib";
	
	/**
	 * pathForBinFileToUSB:path for ChannelList folder in usb
	 */
	String pathForBinFile_OR_DB_ToUSB="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/ChannelList/";
	/**
	 * nullChar:to adding null character at the end of string
	 */
	String nullChar="\0";
	
     /**
      * pathForTVDatabases:path for databases folder in tv 
      */
     String pathForTVDatabases_AND_BinFiles="/user_setting/rw/tvserver/databases/";
	
	/**
	 * pathForTCToTV:path for Terrestrial/Cable files
	 */
	String pathForTerrCabToTV="/user_setting/rw/tvserver/databases/channellib/";
	
	/**
	 * pathForSatToTV:path for Satellite files
	 */
	String pathForSatToTV="/user_setting/rw/tvserver/databases/s2channellib/";
	
	/** 
	 * terrestrialChannelMapBinFile: Terrestrial binary file name with blob content 
	 */
	String terrestrialChannelMapBinFile="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/ChannelList"+tcFolder+"TerrestrialDb.bin";
	
	/** 
	 * cableChannelMapBinFile: Terrestrial binary file name with blob content 
	 */
	String cableChannelMapBinFile="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/ChannelList"+tcFolder+"CableDb.bin";
	
	/** 
	 * satelliteChannelMapBinFile: Terrestrial binary file name with blob content 
	 */
	String satelliteChannelMapBinFile="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/ChannelList"+s2Folder+"SatelliteDb.bin";
	
	/** 
	 * satelliteSetttingsBinFile: Satellite settings file 
	 */
	String satelliteSetttingsBinFile="/PhilipsChannelMaps/ChannelMap_"+majorVersion+"/ChannelList"+s2Folder+"SatelliteSettings.bin";
	
	
	
	/**
	 * Satellite Favorite List1 Table
	 */
	String TABLE_S_LIST1="SList1";
	
	/**
	 * Satellite Favorite List2 Table
	 */
	String TABLE_S_LIST2="SList2";
	
	/**
	 * Satellite Favorite List3 Table
	 */
	String TABLE_S_LIST3="SList3";
	
	/**
	 * Satellite Favorite List4 Table 
	 */
	String TABLE_S_LIST4="SList4";
	
	 /**
	 * copyDatabase():used to copy data
	 * @param src:source of file
	 * @param dest:destination of file
	 * @return:crc value
	 * @throws IOException
	 */
	public char copyDatabase(File src,File dest)throws Exception;
	
	/**
	 * getCRC():used to calculate crc
	 * @param src:source of file
	 * @return:crc value
	 * @throws IOException
	 */
	public char getCRC(File src)throws IOException;
	
	/**
	 * setPermission():used to set permission on the file
	 * @param file:file structure
	 */
	public void setPermission(File file);
}
 