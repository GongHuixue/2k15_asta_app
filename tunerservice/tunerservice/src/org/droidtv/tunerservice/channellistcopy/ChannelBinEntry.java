package org.droidtv.tunerservice.channellistcopy;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import android.util.Log;

/**
 * class:ChannelbinEntry is used To make channelbin entry 
 * @author sohan.gupta
 *
 */
public class ChannelBinEntry
{
	int version;
	byte []name;  // 10 bytes  filled by zeros
	int country;
	int setTypeSize;
	byte []setType;
	ChannelMapName[] mDBFiles=new ChannelMapName[2];
	ChannelMapName[] mTCFiles;
	int	seperatorSize;
	byte SeperatorString[];//=new byte[15];  ///s2channellib/                   //This is a separator to indicate we are putting info for sat ch table.
	ChannelMapName[] mSATFiles;
	ChannelMapName mFile;
	List<ChannelMapName> mTCFileList;
	List<ChannelMapName> mSATFileList;
	
	private String TAG="ChannelBinEntry";
	
	public ChannelBinEntry()
	{
		name=new byte[10];
	}
	
	public ChannelBinEntry(int sizeOfType,int seperatorSize)
	{
		
		this.setTypeSize=sizeOfType;
		this.seperatorSize=seperatorSize;
		this.setType=new byte[sizeOfType];
		this.SeperatorString=new byte[seperatorSize];  ///s2channellib/                   //This is a separator to indicate we are putting info for sat ch table.
		name=new byte[10];
		Log.d(TAG,"Parameterized Constructor called");
	}
	
	/**
	 * setValues():method is used to initialize the values for channelbin file
	 * @param version:prduct version
	 * @param name:
	 * @param country:installed country code
	 * @param setTypeSize:
	 * @param setType:
	 * @param ChTableName:channelmap array
	 * @param seperatorSize:length of separator between terr/cab and Satellite
	 * @param SeperatorString:separator string for terr/cab and Satellite
	 * @param SatelliteChannelName:satellitechannelmap name
	 */
    public void setValues(int version,byte []name,int country,int setTypeSize,byte []setType,ChannelMapName[] mDBFiles,
    		ChannelMapName []mTCFiles,int seperatorSize,byte []SeperatorString,ChannelMapName[] mSATFiles)
    {
	  this.version=version;
	  this.name=name.clone();
	  this.country=country;
	  this.setTypeSize=setTypeSize;
	  this.setType=setType.clone();
	  this.mDBFiles=mDBFiles.clone();
	  
	  if(mTCFiles!=null)
	  {
		  this.mTCFiles=new ChannelMapName[mTCFiles.length];
	      this.mTCFiles=mTCFiles.clone();
	  }
	  this.seperatorSize=seperatorSize;
	  this.SeperatorString=SeperatorString.clone();
	  this.mSATFiles=new ChannelMapName[mSATFiles.length];
	  this.mSATFiles=mSATFiles.clone();
	  Log.d(TAG,"ChannelBinEntry values Intialized");
    }
    
    /**
     * writeChannelBin():method is used to writing chanLst.bin file
     * @param dest:location where it will saved
     * @param channelBinFileName:name of .bin file
     */
    public void writeChannelBin(File dest,String channelBinFileName)
    {
	  
      try
	  {
		  File fileNameForBinFile=new File(dest,channelBinFileName);
		  OutputStream out=new FileOutputStream(fileNameForBinFile);
		  LittleEndianOutputStream oout=new LittleEndianOutputStream(out);

		  // write file version
		  oout.writeInt(version);

		  // write padding with zero's
		  oout.write(name, 0, name.length);

		  // write country code
		  oout.writeInt(country);

		  // write settype size
		  oout.writeInt(setTypeSize);

		  // write settype
		  oout.write(setType,0,setTypeSize);
		  
		  // execute block if tv.db is available
		  if(mDBFiles!=null && mDBFiles.length>0)
		  {
              if(mDBFiles[0]!=null)
              {
            	  //write string size of tv.db Files
    			  oout.writeInt(mDBFiles[0].size);

    			  // write channels database File name Ex-tv.db
    			  oout.write(mDBFiles[0].fileName,0,mDBFiles[0].size);

    			  // write crc of TC Files
    			  oout.writeChar(mDBFiles[0].crc);  
              }
              
              if(mDBFiles[1]!=null)
              {
            	  // write string size of list.db Files
    			  oout.writeInt(mDBFiles[1].size);

    			  // write Favorite list database file name Ex- list.db
    			  oout.write(mDBFiles[1].fileName,0,mDBFiles[1].size);

    			  // write crc of favorite list db
    			  oout.writeChar(mDBFiles[1].crc);  
              }			  
		  }
		  
		  // execute block if TC Files are available in TV
		  if(mTCFiles!=null && mTCFiles.length>0)
		  {
			  for(int index=0;index<mTCFiles.length;index++)
			  {
				  Log.d(TAG,"mTCFiles["+index+"]->"+mTCFiles[index]);
				  if(mTCFiles[index]!=null)
				  {
					  // write string size of TC Files
					  oout.writeInt(mTCFiles[index].size);

					  // write TC Files string
					  oout.write(mTCFiles[index].fileName,0,mTCFiles[index].size);

					  // write crc of TC Files
					  oout.writeChar(mTCFiles[index].crc);
				  }
			  }
		  }
		  
		  //execute block if Satellite Files are available in TV
		  if(mSATFiles!=null && mSATFiles.length>0)
		  {
			  oout.writeInt(seperatorSize);
			  oout.write(SeperatorString,0,seperatorSize);//Bytes(SeperatorString.toString());

			  for(int index=0;index<mSATFiles.length;index++)
			  {
				  Log.d(TAG,"mSATFiles["+index+"]->"+mSATFiles[index]);
				  if(mSATFiles[index]!=null)
				  {
					  // write string size of Satellite Files
					  oout.writeInt(mSATFiles[index].size);

					  // write Satelite Files string
					  oout.write(mSATFiles[index].fileName,0,mSATFiles[index].size);

					  // write crc of Satellite Files
					  oout.writeChar(mSATFiles[index].crc);
				  }
			  }
		  }
		  oout.flush();
		  oout.close();

		  // free allocated memory
		  mDBFiles=null;
		  mTCFiles=null;
		  mSATFiles=null;
	  }
	  catch(Exception e)
	  {
		  Log.d(TAG,"Exception in Writting ChanLst.bin"+e);
	  }
   }
    
    /**
     * readChannelBin(): Method is used to reading chanLst.bin file
     * returntype:boolean-return true if read success otherwise false
     * @param src:Location of chanLst.bin file
     * @param channelBinFileName:Name of .bin file
     */
    public boolean readChannelBin(File src,String channelBinFileName)
    {
      int tempSize;
      byte []tempStr;
      String temp;
	  boolean flag =false;
	  boolean isSeparator=false;
	  
      try
	   {
		  File fileNameForBinFile=new File(src,channelBinFileName);
		  mTCFileList=new ArrayList<ChannelMapName>();
		  
		  // check,ChanLst.bin file is exit or not in USB if exist,execute block
		  if(fileNameForBinFile.exists())
		  {
			  Log.d(TAG,"Location of bin file for reading->"+fileNameForBinFile);
			  InputStream in=new FileInputStream(fileNameForBinFile);
			  LittleEndianInputStream iin=new LittleEndianInputStream(in);
			
			  // read file version 
			  version=iin.readInt();
			  Log.d(TAG,"Version="+version);
			  
			  //read padding with zero's
			  iin.read(name, 0, name.length);//.read(name);
			  String strName = new String(name, "UTF-8"); // for UTF-8 encoding
			  Log.d(TAG,"name="+strName);
			  
			  // read country code
			  country=iin.readInt();
			  Log.d(TAG,"country="+country);
			  
   			  // read settype size
			  setTypeSize=iin.readInt();
			  Log.d(TAG,"setTypeSize="+setTypeSize);
			  setType=new byte[setTypeSize];
			  
			  // read settype
			  iin.read(setType,0,setTypeSize);
			  String strSetType = new String(setType, "UTF-8"); // for UTF-8 encoding
			  Log.d(TAG,"setType="+strSetType);

			  while(iin.available()>0)
			  {
				  tempSize=iin.readInt();
				  tempStr=new byte[tempSize];
				  iin.read(tempStr,0,tempSize);
				  temp= new String(tempStr,0,tempSize-1,"UTF-8");
				  
				  // varify,/s2channellib/ separator is there if true,execute block 
				  if(temp.equalsIgnoreCase(ICopy.s2Folder))
				  {
					  mSATFileList=new ArrayList<ChannelMapName>();
					  isSeparator=true;
					  seperatorSize=tempSize;
					  SeperatorString=tempStr;

				  }
				  else if(isSeparator)
				  {
					  mFile=new ChannelMapName();
					 
					  // read string size of Satellite File
					  mFile.size=tempSize;
					  Log.d(TAG,"File name length="+mFile.size);
					  mFile.fileName=new byte[mFile.size];
					  
					  // read Satellite file name string
					  mFile.fileName=tempStr;
					  mFile.OriginalFileName = temp;
					  Log.d(TAG,"fileName="+mFile.OriginalFileName);
					  
					  // read crc of Satellite File
					  mFile.crc=iin.readChar();
					  Log.d(TAG,"File crc="+mFile.crc);
					  
					  mSATFileList.add(mFile);
				  }
				  else
				  {
					  mFile=new ChannelMapName();
					  
					  // read string size of Terrestrial/Cable file
					  mFile.size=tempSize;
					  Log.d(TAG,"File name length="+mFile.size);
					  mFile.fileName=new byte[mFile.size];
					  
					  // read Terrestrial/Cable file name string
					  mFile.fileName=tempStr;
					  mFile.OriginalFileName = temp;
					  Log.d(TAG,"fileName="+mFile.OriginalFileName);
					  
					  // read crc of Terrestrial/Cable file
					  mFile.crc=iin.readChar();
					  Log.d(TAG,"CRC="+mFile.crc);
					  mTCFileList.add(mFile);
				  }
			  }
			 /* tempSize=iin.readInt();
			  tempStr=new byte[tempSize];
			  iin.read(tempStr,0,tempSize);
			  temp= new String(tempStr,"UTF-8");
			  
			  // varify,/s2channellib/ separator is there if true,execute block 
			  if(temp.equalsIgnoreCase(ICopy.s2Folder+ICopy.nullChar))
			  {
				  success=false;
				  Log.d(TAG,"Only satellitechannelmap is there");
			  }
			  else
			  {
				  success=true;
				  Log.d(TAG,"all channelmaps are there");
			  }
			  Log.d(TAG,"value of success->"+success);
			  
			  // execute block if all channelmaps are exist 
			  if(success)
			  {
			      // creating a object to TerrestrialChannelMaps
				  ChTableName[0]=new ChannelMapName();
				  
				  // read string size of TerrestrialChannelMaps
				  ChTableName[0].size=tempSize;
				  Log.d(TAG,"ChTableName[0].size="+ChTableName[0].size);
				  
		  		  // read TerrestrialChannelMaps string
				  ChTableName[0].fileName=tempStr;
				  String strChTableName = new String(ChTableName[0].fileName, "UTF-8"); // for UTF-8 encoding
				  Log.d(TAG,"ChTableName[0].fileName="+strChTableName);
				  
  				  // read crc of TerrestrialChannelMaps
				  ChTableName[0].crc=iin.readChar();
				  Log.d(TAG,"ChTableName[0].crc="+ChTableName[0].crc);
				  
				  // creating a object to CableChannelMaps				  
				  ChTableName[1]=new ChannelMapName();
				  
				  // read string size of CableChannelMaps
				  ChTableName[1].size=iin.readInt();
				  Log.d(TAG,"ChTableName[1].size="+ChTableName[1].size);
				  ChTableName[1].fileName=new byte[ChTableName[1].size];
				  
				  // read CableChannelMaps string
				  iin.read(ChTableName[1].fileName,0,ChTableName[1].size);
				  strChTableName = new String(ChTableName[1].fileName, "UTF-8"); // for UTF-8 encoding
				  Log.d(TAG,"ChTableName[1].fileName="+strChTableName);
				  
				  // read crc of CableChannelMaps
				  ChTableName[1].crc=iin.readChar();
				  Log.d(TAG,"ChTableName[1].crc="+ChTableName[1].crc);
				  
				  // read separator size
				  seperatorSize=iin.readInt();
				  Log.d(TAG,"seperatorSize="+seperatorSize);
				  SeperatorString=new byte[seperatorSize];
				  
				  // read separator string
				  iin.read(SeperatorString,0,SeperatorString.length);
				  String strSeperatorString = new String(SeperatorString, "UTF-8"); // for UTF-8 encoding
				  Log.d(TAG,"SeperatorString="+strSeperatorString);
				  
				  //creating a object to SatelliteChannelMaps
				  SatelliteChannelName=new ChannelMapName();
				  
				  // read string size of SatelliteChannelMaps
				  SatelliteChannelName.size=iin.readInt();
				  Log.d(TAG,"SatelliteChannelName.size="+SatelliteChannelName.size);
				  SatelliteChannelName.fileName=new byte[SatelliteChannelName.size];

				  // read SatelliteChannelMaps string
				  iin.read(SatelliteChannelName.fileName,0,SatelliteChannelName.size);
				  String strSatelliteChannelName = new String(SatelliteChannelName.fileName, "UTF-8"); // for UTF-8 encoding
				  Log.d(TAG,"SatelliteChannelName.fileName="+strSatelliteChannelName);
				  
				  // read crc of SatelliteChannelMaps
				  SatelliteChannelName.crc=iin.readChar();
				  Log.d(TAG,"SatelliteChannelName.crc="+SatelliteChannelName.crc);
			  }
			  else
			  {
				  //creating a object to SatelliteChannelMaps
				  SatelliteChannelName=new ChannelMapName();
				  
				  // read string size of SatelliteChannelMaps
				  SatelliteChannelName.size=iin.readInt();
				  Log.d(TAG,"SatelliteChannelName.size="+SatelliteChannelName.size);
				  SatelliteChannelName.fileName=new byte[SatelliteChannelName.size];

				  // read SatelliteChannelMaps string
				  iin.read(SatelliteChannelName.fileName,0,SatelliteChannelName.size);
				  String strSatelliteChannelName = new String(SatelliteChannelName.fileName, "UTF-8"); // for UTF-8 encoding
				  Log.d(TAG,"SatelliteChannelName.fileName="+strSatelliteChannelName);
				  
				  // read crc of SatelliteChannelMaps
				  SatelliteChannelName.crc=iin.readChar();
				  Log.d(TAG,"SatelliteChannelName.crc="+SatelliteChannelName.crc);
			  }
			  */
			  iin.close();
              flag=true;
			  return flag;
		  }
		  else
		  {
			  return flag;
		  }
	  }
	  catch(Exception e)
	  {
		  Log.d(TAG,"Exception in reading Bin File"+e);
		  flag=false;
	  }
      return flag;
   }
    
    /**
     * ChannelMapName:To channelMape structure
     * @author sohan.gupta
     *
     */
    static class ChannelMapName
    {
       int size;
       byte []fileName;
       char crc;  // to make unsigned CRC
       String OriginalFileName;
       public void setValues(int size,byte []fileName,char crc)
       {
    	   this.fileName =new byte[size];
    	   this.size=size;
    	   this.fileName=fileName.clone();
    	   this.crc=crc;
       }

    }

    /*private void writeFile(LittleEndianOutputStream oout,ChannelMapName[] files,int size,byte []name,char crc) throws IOException
    {
    	for(int index=0;index<files.length;index++)
		  {
			// write string size of TC Files
			  oout.writeInt(files[index].size);

			  // write TerrestrialChannelMaps string
			  oout.write(files[index].fileName,0,files[index].size);

			  // write crc of TerrestrialChannelMaps
			  oout.writeChar(files[index].crc);
		  }
    	
    }*/
}
