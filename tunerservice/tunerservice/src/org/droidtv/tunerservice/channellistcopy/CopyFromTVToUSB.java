package org.droidtv.tunerservice.channellistcopy;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import android.content.Context;
import android.util.Log;

/**
 * class:CopyFromTVToUSB is used for copy data from tv to usb 
 * @author sohan.gupta
 *
 */
public class CopyFromTVToUSB implements ICopy 
{

	static String TAG="CopyFromTVToUSB";
	
	/**
	 * copyFolder(): method is  used to copy the source file into destination
	 * @param src: location of source file
	 * @param dest: location of destination file
	 */
	 @Override
	 public char copyDatabase(File src,File dest) throws Exception
	 {
		
		    char crc = 0;
			if(src!=null && dest!=null)
	        {
			     Log.d(TAG,"source destination->"+src);
		         FileInputStream in = null;
		         FileOutputStream out = null;
				 byte buf[];
			     int length=0;
  			     try
			     {
			    	 Log.d(TAG,"Reading from "+src.getAbsolutePath());
			         in = new FileInputStream(src);
					 Log.d(TAG,"copyDatabase():opened in read mode successfully");
				     out = new FileOutputStream(dest);
					 Log.d(TAG,"copyDatabase():opened in write mode successfully");
					 Log.d(TAG,"size of file=>"+src.length());
					 buf=new byte[(int) src.length()];
					 
				     if(in!=null && out!=null && src.length()!=0)
				     {
					     while((length=in.read(buf, 0, buf.length))!=-1)
					     {
						      out.write(buf, 0, buf.length);
						      crc=crc_CalculateCrc16(buf);
					     }
						 out.flush();
					     setPermission(dest);
				    }
			    } 
			   // catch (Exception e) 
			    //{
				    // TODO Auto-generated catch block
			     //	Log.d(TAG,"Exception in Reading and Writing Database->"+e);
			    //}
			    finally
			    {
			        try
					{
					    if(in!=null)
				        {
				            in.close();
				        }
					}
					catch (Exception e) 
			        {
				        // TODO Auto-generated catch block
			     	    Log.d(TAG,"Exception in closing inputstream->"+e);
				        e.printStackTrace();
			        }
			        try
					{
			        	if(out!=null)
				        {
				            out.close();
				        }
					}
					catch (Exception e) 
			        {
				        // TODO Auto-generated catch block
			     	    Log.d(TAG,"Exception in closing outputstream->"+e);
			        }
			        					
				    in=null;
				    out=null;
				    buf=null;
			    }
				Log.d(TAG,"Copied from "+src+" To "+dest);			 
		    }
            
		return crc; 		 
	  }
	
	/**
	 * createDirectoryStructure()- method is used to create  directory structure in USB 
	 * @returnType:void
	 */
	public  static boolean createDirectoryStructure(File dest)
    {
		File dirpathForTerrCab=null;
		File dirpathForSat=null;
		File dirpathForUserLogos=null;
		String channelMapPath;
		boolean flag=true;
		try
		{
			
			dirpathForTerrCab=new File(dest,pathForTerrCabToUSB);
			Log.d(TAG,"Terr/cable Structure->>"+dirpathForTerrCab);
			dirpathForSat=new File(dest,pathForSatToUSB);
			Log.d(TAG,"dirpathForSat"+dirpathForSat);
			dirpathForUserLogos=new File(dest,pathForUserLogosToUSB);
			Log.d(TAG,"dirpathForUserLogos"+dirpathForUserLogos);
			
			// create a directory structure if not exist for ChannelMap
	    	if(!dirpathForTerrCab.exists())
	    	{
                Log.d(TAG,"dirpathForTerrCab does not exist");
				
	    		//directory structure is created  successfully 
	    		if(dirpathForTerrCab.mkdirs())
	    		{
				    Log.d(TAG,"directory for terr/cable is created");
	    			flag=true;
	    		}
	    		else
	    		{
				    Log.d(TAG,"directory for terr/cable is not created");
	    			return false;
	    		}
	    	}
	    	if(!dirpathForSat.exists())
	    	{
			    Log.d(TAG,"dirpathForSat does not exist");
				
	    		//directory structure is created  successfully
	    		if(dirpathForSat.mkdirs())
	    		{
				    Log.d(TAG,"directory for satellite is created");
	    			flag=true;
	    		}
	    		else
	    		{
				    Log.d(TAG,"directory for satellite is not created");
	    			return false;
	    		}
	    	}
	    	if(!dirpathForUserLogos.exists())
	    	{
			
			    Log.d(TAG,"dirpathForUserLogos does not exist");
	    		//directory structure is created  successfully				
	    		if(dirpathForUserLogos.mkdirs())
	    		{
				    Log.d(TAG,"directory for user logo is created");
	    			flag=true;
	    		}
	    		else
	    		{
				    Log.d(TAG,"directory for user logo is not created");
	    			return false;
	    		}
	    	}
	    	
		}
	    catch(Exception e)
	    {
	    	Log.d(TAG,"Exception in channelmap path"+e);
	    	flag=false;
	    }
		return flag;
    }


	/**
	 * getCRC(): method is  used to find out the CRC value
	 * @param src:location of source file
	 */
	@Override
	public char getCRC(File src) 
	{
		   // TODO Auto-generated method stub
		   int length=0;
    	   char crc=0;
    	   byte buf[];
		   FileInputStream in = null;
		   if(src!=null)
		   {
		        Log.d(TAG,"source destination->"+src);
				try
				{
				    buf=new byte[(int) src.length()];
				    in = new FileInputStream(src);
					if(in!=null)
					{
						while((length=in.read(buf, 0, buf.length))!=-1)
						{
							Log.d(TAG,"lenth of file->"+buf.length);
							crc=crc_CalculateCrc16(buf);
						}	
					}
				 } 
				catch (Exception e) 
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
					Log.d(TAG,"Exception in Calculating CRC "+e);
				}
				finally
				{
					try
					{
				    	if(in!=null)
					    {
					        in.close();
					    }
					
					}
					catch (Exception e) 
				    { 
					    // TODO Auto-generated catch block
				    	e.printStackTrace();
					    Log.d(TAG,"Exception in Closing stream "+e);
				    }
					in=null;
				}
			}
		return crc;
	}
	
/**
 * copyUserLogos(): method is used to copy user logos to usb
 * @param cxt: context of application
 * @param dest: destination directory
 */
public static void copyUserLogos(Context cxt,File dest)
{
	 String []logos;
	 OutputStream out=null;
	 InputStream in=null;
	 byte []buf=new byte[1024];
	 File destFile;
	 int length=0;
	  try 
	  {
		String []listOfFolder=  cxt.getAssets().list(pathForLogos);
		for(String folder:listOfFolder)
		 {
			if(folder.equalsIgnoreCase(usrDir))
     		{
				logos=cxt.getAssets().list(pathForUserLogos);
    		    for(String logoName:logos)
	    	    {
    		    	in=cxt.getAssets().open(pathForUserLogos+"/"+logoName);
   			        destFile=new File(dest,logoName);
   			        out=new FileOutputStream(destFile);
   			        while((length=in.read(buf,0,buf.length))!=-1)
   			        {
   			    	   out.write(buf, 0,buf.length);
   			        }
    		    	
		        }
		    }
		 }
	  }
	  catch (Exception e) 
	  {
		// TODO Auto-generated catch block
		e.printStackTrace();
		Log.d(TAG,"Exception in ZipLogs()"+e);
	  } 
	  finally
	  {
		  try 
		  {
			  if(in!=null)
			  {
					in.close();
			  }
			  if(out!=null)
			  {
			  	   out.close();				  
			  }
		  }
		  catch (Exception e) 
		  {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d(TAG,"Exception in closing the Streams "+e);
		   }
		   in=null;
		   out=null;
	  }
}

/**
 * crc_CalculateCrc16():used to calculate 16 bits crc value
 * @param buffer:inputs as bytes array
 * @return:crc value
 */
char crc_CalculateCrc16(byte buffer[])
{
    char   Crc16 =  0xFFFF;
    int   Temp  = 0;
    int   i     = 0;
    int   j     = 0;
    byte[]buf   = buffer;
    char	unsigval;
    for (j = 0; j<buf.length; j++)
    {
    	unsigval = (char) (buf[j] & 0xFF);
    	Crc16 ^= unsigval;
        for(i = 0; i < 8; i++ )
        {
            Temp = Crc16;
            Crc16 >>= 1;
            if ( (Temp & 1)!=0 )
            {
                Crc16 ^= 0xA001;
            }
        }
    }
    return Crc16;
}

@Override
public void setPermission(File file)
{
	// TODO Auto-generated method stub
	
	file.setReadable(true, false);
	file.setWritable(true, false);
	
}
}
