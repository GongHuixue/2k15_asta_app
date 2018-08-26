package org.droidtv.tunerservice.overlay;

import android.media.tv.TvContract;
import android.content.Intent;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnKeyListener;
import android.view.LayoutInflater;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToast;
import org.droidtv.ui.tvwidget2k15.tvtoast.TvToastMessenger;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.persistentstorage.TvSettingsConstants;
import org.droidtv.tv.provider.IRecordingsContract;
import org.droidtv.tv.persistentstorage.ITvSettingsManager;
import org.droidtv.tv.context.TvIntent;
import org.droidtv.tunerservice.R;
import org.droidtv.tunerservice.db.CAMDetails;
import org.droidtv.tunerservice.db.CamInfoDB;
import org.droidtv.tunerservice.interfaces.IRecStateChangeListener;
import org.droidtv.tunerservice.recording.RecService;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.TunerServiceHelpContext;
import android.graphics.drawable.Drawable;
import android.widget.ImageView;
import java.util.List;
import java.util.Iterator;
import java.util.LinkedList;
import android.graphics.Bitmap;
import android.view.WindowManager;
import android.util.DisplayMetrics;
import android.graphics.BitmapFactory;

public class ImageChView{
	
	private static final String TAG 							= ImageChView.class.getSimpleName();
	private Handler mHandler 									= null;
	private Uri	mCurrentUri 									= null;
	private Context mContext									= null;	
	private View chView											= null;
	private ImageView tempImage									= null;
	private OverlayManager mOverlayMgr 							= null;
	private TvToast mTimeOutTvToast								= null;
	private TvToastMessenger messenger							= null;
	private TunerServiceHelpContext mTunerServiceHelpContext	= null;
	private List<String> supportImageList						= null;	 
	/*
	*  Support Image format as below 	
	*/
	public static final String JPG_IMAGE_TYPE 					= "jpg";
	public static final String GIF_IMAGE_TYPE 					= "gif";
	public static final String PNG_IMAGE_TYPE 					= "png";
	public static final String BMP_IMAGE_TYPE 					= "bmp";
	public static final String WEB_IMAGE_TYPE 					= "webp";
	public static final String JEPG_IMAGE_TYPE 					= "jepg";
	public static final String TIFF_IMAGE_TYPE					= "tif";
	/*
	*  Support Screen size as below
	*/
	private static final int DEFAULT_WIDTH 						= 1920;
	private static final int DEFAULT_HEIGHT 					= 1080;
	private int mMetricsWidth= DEFAULT_WIDTH;
	private int mMetricsHeight= DEFAULT_HEIGHT;

	public ImageChView(Context context) {  
		Log.d(TAG, "ImageChView :  constructor");
		mContext 					= context;
		mHandler 					= new Handler();
		messenger 					= TvToastMessenger.getInstance(mContext);
		mTimeOutTvToast 			= TvToastMessenger.makeTvToastMessage(TvToastMessenger.TYPE_TIME_OUT, "", -1);
		mTunerServiceHelpContext	= TunerServiceHelpContext.getInstance();
				
		LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		tempImage = (ImageView)inflater.inflate(R.layout.channel_img, null);
		chView = inflater.inflate(R.layout.channel_img, null);
		chView.setId(OverlayManager.VIEW_IMG_CH);
		initWindowsSize();
		initSupportList();
		Runnable r = new Runnable() {
			@Override
			public void run() {
				
			}
		};
		mHandler.post(r);	
	}

	public void setOverlayManager(OverlayManager overlayManager) {
		Log.d(TAG, "ImageChView :  setOverlayManager - "+overlayManager);
		if(overlayManager == null) {
			if(mOverlayMgr!=null){
				Log.d(TAG, "ImageChView :removeImageChView!!!");
				mOverlayMgr.removeImageChView(chView);
			}
			mCurrentUri	= null;
		}
		mOverlayMgr = overlayManager;
	}
	
	public void onPlayStarted(String mediaPlayerUri) {
		Log.d(TAG, "ImageChView :onPlayStarted : "+mediaPlayerUri);
		synchronized(this) {
			if(mediaPlayerUri == null){
				Log.d(TAG,"This channel maybe TV channel");
				Log.d(TAG, "ImageChView :removeImageChView!!!");
				mOverlayMgr.removeImageChView(chView);
			}else{
				Log.d(TAG,"If this channel were to TV channel, then this function wouldn't tune to channel .");
				mCurrentUri = Uri.parse(mediaPlayerUri);
				mCheckImageChView();
			}
		}
	}
	
	public void onPlayCompleted(final Uri mediaPlayerUri) {
		//do nothing
	}

	public void mCheckImageChView() {
		Runnable r = new Runnable() {
			@Override
			public void run() {
				if(mCurrentUri != null){
					if(IsImageFormat(mCurrentUri)) {
						if(mOverlayMgr!=null){
							Log.d(TAG, "ImageChView :addImageChView!!!");
							Bitmap image1 = decodeSampledBitmapFromResource(mCurrentUri.toString(), mMetricsWidth, mMetricsHeight);
//							BitmapFactory.Options option = new BitmapFactory.Options();
//							option.inJustDecodeBounds = true;
//							option.inPurgeable = true;
//							option.inJustDecodeBounds = false;
//							Bitmap image1 =BitmapFactory.decodeFile(mCurrentUri.toString(), option);
							tempImage.setImageBitmap(image1);
							chView = tempImage;
							chView.setVisibility(View.VISIBLE);
							Log.d(TAG, "ImageChView :addImageChView2!!!");
							mOverlayMgr.addImageChView(chView);

						}
					}else {
						if(mOverlayMgr!=null){
							Log.d(TAG, "ImageChView :removeImageChView!!!");
							mOverlayMgr.removeImageChView(chView);
						}
					}
				}				
			}
		};
		mHandler.post(r);	
	}

	private boolean IsImageFormat(Uri uri){

		boolean IsImageFormat = false;
		String extformat = "";
		
		if(uri != null){
			extformat 	= findExtension(uri.toString());
		}
		//String extformat 	= findExtension(uri.toString());
		Iterator itsupport	= supportImageList.iterator();

		while(itsupport.hasNext()){
			String str = (String)itsupport.next();
			if(str.compareTo(extformat) == 0 ){
				IsImageFormat = true; 
				break;
			}
		}
		
		return IsImageFormat;
	}

	private String findExtension(String filename){
		String extformat = "";

		String filenameArray[] = filename.split("\\.");
        extformat = filenameArray[filenameArray.length-1];

		return extformat.toLowerCase();
	}
	
	private boolean initSupportList(){
		boolean ret_value = false;

		if(supportImageList == null){
			supportImageList = new LinkedList<String>();
		}

		addSupportList();

		return ret_value;
	}

	private boolean addSupportList(){

		supportImageList.add(JPG_IMAGE_TYPE);
		supportImageList.add(GIF_IMAGE_TYPE);
		supportImageList.add(PNG_IMAGE_TYPE);
		supportImageList.add(BMP_IMAGE_TYPE);
		supportImageList.add(JEPG_IMAGE_TYPE);
		supportImageList.add(TIFF_IMAGE_TYPE);

		return true;
	}

	private void initWindowsSize(){
		try {
			DisplayMetrics outMetrics = new DisplayMetrics();

			WindowManager mWindowManager = (WindowManager) mContext.getSystemService(Context.WINDOW_SERVICE);
			mWindowManager.getDefaultDisplay().getMetrics(outMetrics);
			float density = outMetrics.density;
			mMetricsWidth = (int)(outMetrics.widthPixels*density);
			mMetricsHeight = (int)(outMetrics.heightPixels*density);
			Log.d(TAG,"mMetricsWidth : "+mMetricsWidth +" mMetricsHeight : "+mMetricsHeight + " density :"+density);
		} catch(Exception e) {
			Log.d(TAG,"Exception getting metrics");
		}

	}

	public static Bitmap decodeSampledBitmapFromResource(String pathName,
														 int reqWidth, int reqHeight) {

		// First decode with inJustDecodeBounds=true to check dimensions
		Log.d(TAG,"reqWidth : "+reqWidth+"reqHeight : "+reqHeight);
		Bitmap bitmap = null;
		final BitmapFactory.Options options = new BitmapFactory.Options();
		options.inJustDecodeBounds = true;
		options.inPurgeable = true;
//		try {
//
//			BitmapFactory.Options.class.getField("inNativeAlloc").setBoolean(options,true);
//
//		} catch (IllegalArgumentException e) {
//			e.printStackTrace();
//		} catch (SecurityException e) {
//			e.printStackTrace();
//		} catch (IllegalAccessException e) {
//			e.printStackTrace();
//		} catch (NoSuchFieldException e) {
//			e.printStackTrace();
//		}
		try{
			bitmap = BitmapFactory.decodeFile(pathName, options);
		}catch (Exception e)
		{
			e.printStackTrace();
		}

		options.inSampleSize = calculateInSampleSize(options, reqWidth,
				reqHeight);

		options.inJustDecodeBounds = false;
		try{
			bitmap = BitmapFactory.decodeFile(pathName, options);
		}catch (Exception e)
		{
			e.printStackTrace();
		}
		return bitmap;
	}

	public static int calculateInSampleSize(BitmapFactory.Options options,
											int reqWidth, int reqHeight) {
//		final int height = options.outHeight;
//		final int width = options.outWidth;
//		int inSampleSize = 1;
//		if (height > reqHeight || width > reqWidth) {
//
//			final int halfHeight = height / 2;
//			final int halfWidth = width / 2;
//
//			while ((halfHeight / inSampleSize) > reqHeight
//					&& (halfWidth / inSampleSize) > reqWidth) {
//				inSampleSize *= 2;
//			}
//		}
//
//		return inSampleSize;
        // Raw height and width of image
        final int height = options.outHeight;
        final int width = options.outWidth;
        int inSampleSize = 1;

        if (height > reqHeight || width > reqWidth) {
            // Calculate ratios of height and width to requested height and width
            final int heightRatio = Math.round((float) height / (float) reqHeight);
            final int widthRatio = Math.round((float) width / (float) reqWidth);

            // Choose the smallest ratio as inSampleSize value, this will guarantee
            // a final image with both dimensions larger than or equal to the
            // requested height and width.
            inSampleSize = heightRatio < widthRatio ? heightRatio : widthRatio;
        }
        return inSampleSize;
	}
}
