package org.droidtv.tunerservice.tvmpl;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import android.media.tv.TvContract;
import android.media.tv.TvContract.Channels;
import java.util.Arrays;
import org.droidtv.tunerservice.db.CAMDetails;
import org.droidtv.tunerservice.db.CamInfoDB;
import org.droidtv.tunerservice.tvmplfactory.PlayTVMediaPlayerFactory;
import org.droidtv.tunerservice.util.PlayTvUtils;
import org.droidtv.tunerservice.util.TvURIHelper.Medium;
import org.droidtv.tv.media.ITvMediaCI;
import org.droidtv.tv.media.ITvMediaCI.CICamIdInfo;
import org.droidtv.tv.tvinput.CamInfoImpl;
import android.content.Context;
import android.database.Cursor;
import android.util.Log;

public class CamHelper {

	private PlayTvCIPlusHandler mPlayTvCIPlusHandler;
	private static final String TAG = CamHelper.class.getSimpleName();
	private boolean tcChannelValue;
	private boolean satChannelValue;
	private String mCamID;
	private int mSlotID;
	//private CAMDetails camDetails;
	private Context mContext;
	private CamInfoDB camInfo;
	private int[] camIDarr;
	private CICamIdInfo mCICamIdInfo;
	private static final int TOTAL_NO_CAMS = 2;

	private static final boolean CAM_PRESENT = true;
	private static final boolean CAM_NOTPRESENT = false;

	public CamHelper(PlayTvCIPlusHandler playTvCIPlusHandler, Context context) {
		mPlayTvCIPlusHandler = playTvCIPlusHandler;
		mContext = context;
	}

	/*
	 * It will check whether dual tuner enabled or not and how many mediums
	 * installed will check whether we can show camwiazard or not
	 */
	public boolean isCamWizardCanShow() {
		if (isDualTunerEnabled()) {
			int ANTENNA_MEDIUM = 0, CABLE_MEDIUM = 1, SAT1_MEDIUM = 2, SAT2_MEDIUM = 3, SAT3_MEDIUM = 4, SAT4_MEDIUM = 5;
			if (isChannelInstalled(ANTENNA_MEDIUM)
					|| isChannelInstalled(CABLE_MEDIUM)) {
				tcChannelValue = true;
			}
			if (isChannelInstalled(SAT1_MEDIUM)
					|| isChannelInstalled(SAT2_MEDIUM)
					|| isChannelInstalled(SAT3_MEDIUM)
					|| isChannelInstalled(SAT4_MEDIUM)) {
				satChannelValue = true;
			}
			if (tcChannelValue == true && satChannelValue == true) {
				return getCAMDetails();
			} else if (tcChannelValue) {
				return getCAMDetails();
			} else if (satChannelValue) {
				if (isSatDualTunerEnabled() == true) {
					return getCAMDetails();
				} else {
					mCamID = getCAMIDFROMMW();
					Log.i(TAG, "getCAMDetails slotID:" + mSlotID + "CamID:"
							+ mCamID);
					boolean isSlotExisted = isSlotIDExisted(mSlotID);
					Log.i(TAG, "isSlotExisted:" + isSlotExisted);
					if (isSlotExisted == true) {
						String existedCAMID = getCamId(mSlotID);
						Log.i(TAG, "existedCAMID:" + existedCAMID);
						if (!(existedCAMID.equalsIgnoreCase(mCamID))) {
							Log.i(TAG, "CAMID's are not equal");
							updateCamINDB();
						} else {
							boolean camStatus = getCamStatusInDB(mSlotID);
							Log.i(TAG, "camStatus:" + camStatus);
							//if (camStatus == false) {
								updateCamMedium(mSlotID,CAMDetails.SATINSTALLMEDIUM);
							//} else {
								//updateCamMedium(mSlotID,
								//		CAMDetails.SATINSTALLMEDIUM);
							//}
						}
					} else {
						Log.d(TAG, "new slot adding");
						addCamINDB();
					}
					return false;
				}

			}

		}
		return false;
	}
	
	public boolean isNewCamInserted(){
		boolean mIsNewCamInserted = false;
		mCamID = getCAMIDFROMMW();
		if (mCamID != null) {
			Log.i(TAG, "getCAMDetails slotID:" + mSlotID + "CamID:" + mCamID);
			boolean isSlotExisted = isSlotIDExisted(mSlotID);
			Log.i(TAG, "isSlotExisted:" + isSlotExisted);
			if (isSlotExisted == true) {
				String existedCAMID = getCamId(mSlotID);
				Log.i(TAG, "existedCAMID:" + existedCAMID);
				if (!(existedCAMID.equalsIgnoreCase(mCamID))) {
					mIsNewCamInserted = true;
				}
			}else {
				mIsNewCamInserted = true;
			}
		}
		return mIsNewCamInserted;
		
	}

	/*
	 * Will update cam info in db
	 */
	private boolean getCAMDetails() {
		Log.d(TAG, "getCAMDetails called:");
		boolean isCamWizardCanShow = false;
		mCamID = getCAMIDFROMMW();
		if (mCamID != null) {
			Log.i(TAG, "getCAMDetails slotID:" + mSlotID + "CamID:" + mCamID);
			boolean isSlotExisted = isSlotIDExisted(mSlotID);
			Log.i(TAG, "isSlotExisted:" + isSlotExisted);
			if (isSlotExisted == true) {
				String existedCAMID = getCamId(mSlotID);
				Log.i(TAG, "existedCAMID:" + existedCAMID);
				if (!(existedCAMID.equalsIgnoreCase(mCamID))) {
					Log.i(TAG, "CAMID's are not equal");
					updateCamINDB();
					isCamWizardCanShow = true;
				} else {
					boolean camStatus = getCamStatusInDB(mSlotID);
					Log.i(TAG, "camStatus:" + camStatus);
					if (camStatus == false) {
						updateCamStatus(mSlotID, CAM_PRESENT);
						String medium = getMedium(mSlotID);
						if (medium.equalsIgnoreCase(CAMDetails.UNKNOWNMEDIUM)) {
							updateCamMedium(mSlotID, null);
							isCamWizardCanShow = true;
						} else {
							int noOfCAMS = getNoOfCAMS();
							Log.i(TAG, "NoOFCAMS:" + noOfCAMS);
							if (noOfCAMS == TOTAL_NO_CAMS) {
								if (mSlotID == ITvMediaCI.SLOT0) {
									String slot0medium = getMedium(ITvMediaCI.SLOT1);
									if (!(slot0medium
											.equalsIgnoreCase(CAMDetails.UNKNOWNMEDIUM))) {
										updateCamMedium(mSlotID, slot0medium);
									}
								} else if (mSlotID == ITvMediaCI.SLOT1) {
									String slot1medium = getMedium(ITvMediaCI.SLOT0);
									if (!(slot1medium
											.equalsIgnoreCase(CAMDetails.UNKNOWNMEDIUM))) {
										updateCamMedium(mSlotID, slot1medium);
									}
								}
							}
						}

					} else {
						String medium = getMedium(mSlotID);
						Log.i(TAG, "CAM is already available:" + medium
								+ "slotID:" + mSlotID);
						if (medium.equalsIgnoreCase(CAMDetails.UNKNOWNMEDIUM)) {
							updateCamINDB();
							isCamWizardCanShow = true;
						}
					}
				}
			} else {
				Log.d(TAG, "new slot adding");
				addCamINDB();
				isCamWizardCanShow = true;
			}
		} else {
			Log.d(TAG, "mCamID is null");
		}
		return isCamWizardCanShow;
	}

	private String getCAMIDFROMMW() {

		mCICamIdInfo = mPlayTvCIPlusHandler
				.getCamIDInfo(ITvMediaCI.SLOT_UNKNOWN);
		if (mCICamIdInfo != null && mCICamIdInfo.SlotID <= 1
				&& mCICamIdInfo.SlotID >= 0) {
			mSlotID = mCICamIdInfo.SlotID;
			Log.i(TAG, "CAMID SlotID:" + mSlotID);
			if (mCICamIdInfo.CamIDLen > 0) {
				camIDarr = Arrays.copyOf(mCICamIdInfo.CamID,
						mCICamIdInfo.CamIDLen);
			} else {
				if (mCICamIdInfo.CamCisDataLen > 0) {
					camIDarr = Arrays.copyOf(mCICamIdInfo.CamCisData,
							mCICamIdInfo.CamCisDataLen);
				}
			}
			if (camIDarr != null) {
				Log.i(TAG, "CAMID Length:" + camIDarr.length);
				for (int i = 0; i < camIDarr.length; i++) {
					Log.i(TAG, "CAMID calues:" + camIDarr[i]);
				}
				/*
				 * Converting camid array to hashcode
				 */
				long camIDhash = getCAMDID(camIDarr);
				/*
				 * concatenate hash code plus slot id
				 */
				String camID = camIDhash + "" + mSlotID;
				return camID;
			} else {
				Log.d(TAG, "getCAMIDFROMMW called camIDarr is null:");
			}
		} else {
			Log.d(TAG, "getCAMIDFROMMW called mCICamIdInfo is null ");
		}

		return null;
	}

	/*
	 * Add new cam in db
	 */
	private void addCamINDB() {
		camInfo = CamInfoDB.getInstace(mContext);
		CAMDetails camDetails = new CAMDetails();
		camDetails.setSlotID(mSlotID);
		camDetails.setCamID(mCamID);
		camDetails.setCamIDBlob(getInt2Byte(camIDarr));
		if (tcChannelValue == true && satChannelValue == true) {
			camDetails.setMedium(CAMDetails.UNKNOWNMEDIUM);
		} else if (tcChannelValue) {
			camDetails.setMedium(CAMDetails.TCINSTALLMEDIUM);
		} else if (satChannelValue) {
			camDetails.setMedium(CAMDetails.SATINSTALLMEDIUM);
		}
		camDetails.setCamStatus(CAM_PRESENT);
		camInfo.addCam(camDetails);
	}
	
	/*
	 * Will give number of inserted cams as per DB
	 */
	public int getNoOfCAMS() {
		CAMDetails camDetails = new CAMDetails();
		camDetails.setMedium(CAMDetails.UNKNOWNMEDIUM);
		camInfo = CamInfoDB.getInstace(mContext);
		int noOfCAMS = camInfo.getNoOfCAMS(camDetails);
		Log.i(TAG, "cifactory noOfCAMS:" + noOfCAMS);
		return noOfCAMS;
	}

	private String getCamId(final int slotID) {
		camInfo = CamInfoDB.getInstace(mContext);
		CAMDetails camDetails = new CAMDetails();
		camDetails.setSlotID(slotID);
		return camInfo.getCamId(camDetails);
	}

	/*
	 * Will return medium for the corresponding
	 */
	private String getMedium(final int slotID) {
		camInfo = CamInfoDB.getInstace(mContext);
		CAMDetails camDetails = new CAMDetails();
		camDetails.setSlotID(slotID);
		return camInfo.getMedium(camDetails);
	}

	/*
	 * Will update the medium in db for the corresponding the slotid
	 */
	public void updateCamMedium(int slotID, String medium) {
		camInfo = CamInfoDB.getInstace(mContext);
		CAMDetails camDetails = new CAMDetails();
		camDetails.setSlotID(slotID);
		Log.i(TAG,"updateCamMedium called slotID :"+slotID+"medium:"+medium);
		if (medium == null) {
			if (tcChannelValue == true && satChannelValue == true) {
				camDetails.setMedium(CAMDetails.UNKNOWNMEDIUM);
			} else if (tcChannelValue) {
				camDetails.setMedium(CAMDetails.TCINSTALLMEDIUM);
			} else if (satChannelValue) {
				camDetails.setMedium(CAMDetails.SATINSTALLMEDIUM);
			}
		} else {
			camDetails.setMedium(medium);
		}
		camInfo.updateMedium(camDetails);
	}

	/*
	 * Will update caminfo in db
	 */
	private void updateCamINDB() {
		camInfo = CamInfoDB.getInstace(mContext);
		CAMDetails camDetails = new CAMDetails();
		camDetails.setSlotID(mSlotID);

		if (tcChannelValue == true && satChannelValue == true) {
			if (getNoOfCAMS() == TOTAL_NO_CAMS) {
				if (mSlotID == ITvMediaCI.SLOT0) {
					camDetails.setSlotID(ITvMediaCI.SLOT1);
					String slot0medium = camInfo.getMedium(camDetails);
					if (!(slot0medium
							.equalsIgnoreCase(CAMDetails.UNKNOWNMEDIUM))) {
						camDetails.setSlotID(mSlotID);
						camDetails.setMedium(slot0medium);
					} else {
						camDetails.setSlotID(mSlotID);
						camDetails.setMedium(CAMDetails.UNKNOWNMEDIUM);
					}
				} else if (mSlotID == ITvMediaCI.SLOT1) {
					camDetails.setSlotID(ITvMediaCI.SLOT0);
					String slot1medium = camInfo.getMedium(camDetails);
					if (!(slot1medium
							.equalsIgnoreCase(CAMDetails.UNKNOWNMEDIUM))) {
						CAMDetails camDetails1 = new CAMDetails();
						camDetails1.setSlotID(mSlotID);
						camDetails1.setMedium(slot1medium);
						camInfo.updateMedium(camDetails1);
					} else {
						camDetails.setSlotID(mSlotID);
						camDetails.setMedium(CAMDetails.UNKNOWNMEDIUM);
					}
				}

			} else {
				camDetails.setMedium(CAMDetails.UNKNOWNMEDIUM);
			}
		} else if (tcChannelValue) {
			camDetails.setMedium(CAMDetails.TCINSTALLMEDIUM);
		} else if (satChannelValue) {
			camDetails.setMedium(CAMDetails.SATINSTALLMEDIUM);
		}
		camDetails.setCamID(mCamID);
		camDetails.setCamStatus(CAM_PRESENT);
		camInfo.updateCam(camDetails);
	}

	/*
	 * Will check the camstatus in db
	 */
	public boolean getCamStatusInDB(final int slotID) {
		camInfo = CamInfoDB.getInstace(mContext);
		CAMDetails camDetails = new CAMDetails();
		camDetails.setSlotID(slotID);
		boolean isSlotExisted = isSlotIDExisted(slotID);
		Log.i(TAG, "slotID: " + slotID + " istExisted:" + isSlotExisted);
		if (isSlotExisted) {
			boolean camStatus = camInfo.getCamStatus(camDetails);
			Log.i(TAG, "camStatus:" + camStatus);
			if (camStatus == true) {
				camInfo.close();
				return true;
			}
		}
		camInfo.close();
		return false;
	}

	private boolean isSlotIDExisted(final int slotID) {
		Log.i(TAG, "isSlotIDExisted called slotID:" + slotID);
		camInfo = CamInfoDB.getInstace(mContext);
		CAMDetails camDetails = new CAMDetails();
		camDetails.setSlotID(slotID);
		return camInfo.isSlotIDExisted(camDetails);
	}

	/*
	 * Updating camstatus to false for the corresponding slot
	 */

	public void updateCamStatus(final int slotID, final boolean camStatus) {
		Log.i(TAG, "updateCamStatus called slotID:" + slotID + "camStatus:"
				+ camStatus);
		camInfo = CamInfoDB.getInstace(mContext);
		CAMDetails camDetails1 = new CAMDetails();
		camDetails1.setSlotID(slotID);
		camDetails1.setCamStatus(camStatus);
		camInfo.updateCamStatus(camDetails1);
		camInfo.close();
	}

	/*
	 * Converts Integer array to byte array
	 * 
	 * @Params int[] data
	 * 
	 * @Returns byte[] bytearray;
	 */
	private static byte[] getInt2Byte(int[] data) {

		ByteBuffer byteBuffer = ByteBuffer.allocate(data.length * 4);
		IntBuffer intBuffer = byteBuffer.asIntBuffer();
		intBuffer.put(data);
		byte[] bytearray = byteBuffer.array();
		return bytearray;
	}

	private boolean isSatDualTunerEnabled() {
		Medium medium = PlayTvUtils.getCurrentMedium();
		Log.i(TAG, "isSatDualTunerEnabled medium:" + medium);
		if (medium != null && medium == Medium.MEDIUM_SATELLITE) {
			PlayTVMediaPlayerFactory playTvMPFactory = PlayTVMediaPlayerFactory
					.getInstance();
			if (playTvMPFactory != null) {
				boolean dualTunerStatus = playTvMPFactory
						.IsDualTunerFactoryConfigEnabled(medium);
				Log.i(TAG, "CIFactory isDualTunerEnabled:" + dualTunerStatus);
				return dualTunerStatus;
			}
		}
		return false;
	}

	/*
	 * Generates hashcode form int[] array
	 * 
	 * @Params int[] camID
	 * 
	 * @Returns long hashCode;
	 */
	private static long getCAMDID(int[] camID) {
		long hashCode = 13323456798L;
		int len = camID.length;
		for (int i = 0; i < len; i++) {
			hashCode = (31 * hashCode) + camID[i];
		}
		Log.d(TAG, "CAMID Id hash code " + hashCode);
		return hashCode;
	}

	/*
	 * It will check the channels installed or not based on the medium
	 * 
	 * @Params medium
	 * 
	 * @Returns boolean value Will return true if channels installed else
	 * returns false
	 */
	private boolean isChannelInstalled(int pMedium) {
		/* Get Dat from Tvprovider */
		boolean lIsInstalled = false;
		String[] lProjection = new String[] { Channels._ID };
		String lSelection = Channels.COLUMN_VERSION_NUMBER + "= ?";
		String[] lSelectionargs = new String[] { String.valueOf(pMedium) };

		Cursor lTCCursor = mContext.getContentResolver().query(
				TvContract.Channels.CONTENT_URI, lProjection, lSelection,
				lSelectionargs, null);
		if (lTCCursor != null && lTCCursor.getCount() > 0) {
			lIsInstalled = true;
		}
		if(lTCCursor != null){
		lTCCursor.close();
		}
		return lIsInstalled;
	}

	
	private boolean isDualTunerEnabled() {
		Log.d(TAG, "isDualTunerEnabled called");
		PlayTVMediaPlayerFactory playTvMPFactory = PlayTVMediaPlayerFactory
				.getInstance();
		if (playTvMPFactory != null) {
			boolean dualTunerStatus = playTvMPFactory
					.isDualTunerFactoryConfigEnabled();
			Log.i(TAG, "CIFactory isDualTunerEnabled:" + dualTunerStatus);
			return dualTunerStatus;
		}
		return false;
	}

	/*
	 * Will be called while removing the cam It will check the camid length and
	 * cisdatalen for the corresponding slotid if both are zero the will the
	 * check camstatus in db if it is true then it will update camstus to false
	 */
	public boolean getCamStatus(final int slotid) {
		if (slotid == ITvMediaCI.SLOT0) {
			mCICamIdInfo = mPlayTvCIPlusHandler.getCamIDInfo(ITvMediaCI.SLOT0);
		} else if (slotid == ITvMediaCI.SLOT1) {
			mCICamIdInfo = mPlayTvCIPlusHandler.getCamIDInfo(ITvMediaCI.SLOT1);
		}
		if (mCICamIdInfo != null) {
			if ((mCICamIdInfo.CamIDLen == 0)
					&& (mCICamIdInfo.CamCisDataLen == 0)) {
				if (getCamStatusInDB(slotid) == true) {
					updateCamStatus(slotid, CAM_NOTPRESENT);
					return true;
				}
			} else {
				Log.d(TAG, "slot0 CICCamIDLen is not zero CAMIDLen:"
						+ mCICamIdInfo.CamIDLen + "CamCisDataLen:"
						+ mCICamIdInfo.CamCisDataLen + "slotID:" + slotid);
			}
		} else {
			Log.d(TAG, "slot0 CICamIdInfo is null:" + slotid);
		}
		return false;
	}

	
	public CamInfoImpl getCamInfo(final int slotId){
		if(isSlotIDExisted(slotId)){
			camInfo = CamInfoDB.getInstace(mContext);
			CAMDetails camDetails1 = new CAMDetails();
			camDetails1.setSlotID(slotId);
			CAMDetails camDetails = camInfo.getCamInfo(camDetails1);
			if(camDetails != null){
			CamInfoImpl camInfoImpl = new CamInfoImpl();
			camInfoImpl.slotId = slotId;
			camInfoImpl.camID = camDetails.getCamID();
			camInfoImpl.medium = camDetails.getMedium();
			camInfoImpl.camStatus = camDetails.isCamStatus();
			Log.i(TAG,"getCamInfo called camInfo.camID:"+camInfoImpl.camID+"camInfoImpl.medium"+camInfoImpl.medium+"status:"+camInfoImpl.camStatus+"slotID:"+camInfoImpl.slotId);
			return camInfoImpl;
			} else {
				return null;
			}
		}else {
			return null;
		}
		
	}
	


}
