package org.droidtv.tunerservice.channellistcopy;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import android.content.Context;
import android.util.Log;
import android.content.res.AssetManager;

/**
 * class:CopyFromUSBToTV is used to copy data from usb to tv
 * @author sohan.gupta
 *
 */
public class CopyFromUSBToTV implements ICopy
{

	String TAG="CopyFromUSBToTV";
	
	private String MountPath = null;
	
	public void  setMountPath (String path)
	{
		MountPath = path;
	}
	
	public String getMountPath ()
	{
		return MountPath;
	}
	
	/**
	 * copyFolder(): method is  used to copy the source file into destination
	 * @param src:location of source file
	 * @param dest:location of destination file
	 */
	@Override
	 public char copyDatabase(File src,File dest) throws Exception
	  {
	  
    	  char crc = 0;
          if(src!=null && dest!=null)
		  {
		      Log.d(TAG,"source ->"+src);
		      FileInputStream in = null;
			  FileOutputStream out = null;
			  byte buf[];
			  int length=0;
			  Log.d(TAG,"Reading from "+src.getAbsolutePath());
			  try
			  {
			      in = new FileInputStream(src);
				  out = new FileOutputStream(dest);
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
				  Log.d(TAG,"Copied from "+src+" To "+dest);
			  } 
			  //catch (Exception e) 
			//  {
				// TODO Auto-generated catch block
				
				//Log.d(TAG,"Exception in Reading and Writing Database->"+e);
				//e.printStackTrace();
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
				        e.printStackTrace();
			        }
			        					
				    in=null;
				    out=null;
				    buf=null;
			  }
			  
		  }
		return crc; 
	  }

	
	/**
	 * getCRC(): method is  used to find out the CRC value
	 * @param src:location of source file
	 */
	@Override
	public char getCRC(File src) throws IOException
	{
		// TODO Auto-generated method stub
	       int length=0;
 	       char crc = 0;
 	       byte buf[];
		   Log.d(TAG,"source->"+src);
		   FileInputStream in = null;
		   if(src!=null)
           {
 			try 
 			{
 				buf=new byte[(int) src.length()];
 				in = new FileInputStream(src);
 					if(in!=null && src.length()!=0)
 					{
 						while((length=in.read(buf, 0, buf.length))!=-1)
 						{
 							Log.d(TAG,"lenth of file->"+buf.length);
 							crc=crc_CalculateCrc16(buf);
 						}
 					} 				
 			} 
 			/*catch (Exception e) 
 			{
 				// TODO Auto-generated catch block
 				Log.d(TAG,"Exception in Creating InputStream"+e);
 				e.printStackTrace();
 			}*/
 			finally
 			{
 					  try 
 					  {
 						  if(in!=null)
 						  {
 							 in.close();
 						  }
					  }
 					  catch (IOException e) 
 					  {
						// TODO Auto-generated catch block
 						 Log.d(TAG,"Exception in closing streams->"+e);
					     e.printStackTrace();
					  }
					  in=null;
 			}
           }
		return crc;
	}
	
	/**
	 * crc_CalculateCrc16();method is used to calculate 16 bits crc
	 * @param buffer:input bytes array as parameter
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

	/**
	 * copyUserLogos():method is used to copying user logos from usb to tv
	 * @param src:source of logos
	 * @param dest:destination for logos
	 */
	public void copyUserLogos(File src ,File dest)
	{
		 OutputStream out=null;
		 InputStream in = null;
		 File srcFile,destFile;
		 byte []buf=new byte[1024];
		 int length=0;
		  try 
		  {
			  
			  if(src!=null && dest!=null)
			  {
				  for(File logoName:src.listFiles())
				  {
					  Log.d(TAG,"Logo Name->"+logoName.getName());
					  //srcFile=new File(src,logoName);
					  destFile=new File(dest,logoName.getName());
					  in=new FileInputStream(logoName);
					  out=new FileOutputStream(destFile);
					  if(in!=null && out!=null)
					  {
					     while((length=in.read(buf,0,buf.length))!=-1)
					     {
						    out.write(buf, 0, buf.length);
					     } 					  
					  }
					  
				  }
			  }
		  }
		  catch (Exception e) 
		  {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d(TAG,"Exception copying Logos()"+e);
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
				Log.d(TAG,"Exception in closing Streams "+e);
			   }
			   in=null;
			   out=null;
		  }
	   
	}


	@Override
	public void setPermission(File file)
	{
		// TODO Auto-generated method stub
		
		file.setReadable(true, false);
		file.setWritable(true, false);
		
	}
	
	public byte[] writeUserLogosToDB(Context ctx, long logoid)
	{
		byte[] buf = null;
		String path;
		
		if (logoid >= 10000) 
		{
			path = MountPath+ICopy.pathForUserLogosToUSB;
			Log.d(TAG,"USB User Logo Path->"+path);
			File imagefile=new File(path+"/"+logoid+".png");
			InputStream in=null;
			try
			{
				in = new FileInputStream(imagefile);
				buf=new byte[in.available()];
				
				if(in!=null)
				{
					if(buf!=null && buf.length>0){
						in.read(buf);
						
					}
					
				}
			}
			catch (Exception e)
			{
				Log.d(TAG,"writeUserLogosToDB()Exception:"+e);
			}
			finally{
				try{
					if(in!=null){
						in.close();
						in=null;
					}
				 }
				catch(IOException e){
					Log.d(TAG,"writeUserLogosToDB()Exception:"+e);
				}

			}
		}
		else 
		{
			AssetManager am = ctx.getAssets();
			
			path = "Logos/sys/";
			String logopath = path+ logoid+".png";
			Log.d(TAG, "System logopath" + logopath);
			InputStream is =null;
			try
			{
				is= am.open(logopath);

				int size=is.available();
				Log.d(TAG,"image size");
				buf=new byte[size];
				is.read(buf);
			}
			catch (Exception e)
			{
				Log.d(TAG,"writeUserLogosToDB()Exception:"+e);
			}
			finally{
				try{
					if(is!=null){
						is.close();
						is=null;
					}
				}
				catch(IOException e){
					Log.d(TAG,"writeUserLogosToDB()Exception:"+e);
				}
			}
			}
			
		return buf;
	}
	
	public boolean updateTVDB() {
		File srcfile = new File(ICopy.pathForTVDatabases_AND_BinFiles, ICopy.channelDB_backup);
		File destFile = new File(ICopy.pathForTVDatabases_AND_BinFiles, ICopy.channelDB);
		File destJFile = new File(ICopy.pathForTVDatabases_AND_BinFiles, "tv.db-journal");
		boolean success = true;
		// Check if the backup file exists
		try {
			if (srcfile.exists()) {
				if(destJFile.exists()) {
					destJFile.delete();
				}
				InputStream in = new FileInputStream(srcfile);
				FileOutputStream out = new FileOutputStream(destFile, false);
				try {
					byte[] buffer = new byte[4096];
					int bytesRead = 0;
					while ((bytesRead = in.read(buffer)) >= 0) {
						out.write(buffer, 0, bytesRead);
					}
				} catch (Exception e) {
					success = false;
					Log.e(TAG, "ERROR: Exception while trying to copy tv.db - " + e.toString());
				} finally {
					try {
						out.flush();
						out.getFD().sync();
						out.close();
						in.close();
					} catch (Exception e) {
						success = false;
						Log.e(TAG, "ERROR: Exception on tv.db copy cleanup - " + e.toString());
					}
				}
				srcfile.delete();
			}
		} catch (Exception e) {
			success = false;
			Log.e(TAG, "ERROR: Exception on tv.db copy - " + e.toString());
		}
		return success;
	}
}
