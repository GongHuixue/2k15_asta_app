/*
 * NativeJNI.cpp
 *
 *  Created on: 13-May-2013
 *      Author: mahesh.mathada
 */


#include "org_droidtv_euinstallertc_model_mwapi_EuInstallerTC.h"
#include "NativeEuInstaller.h"
#include "NativeEuInstallerJNI.h"
#include "CTvInstallTC.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#ifdef AOSP_BUILD_TC
#include <utils/Log.h>
#else
#include <android/Log.h>
#endif

#define Native_JNI "Native_JNI"

extern "C" {
	jmethodID mTune, mGetFreq, mScanStart, mScanAbort, mScanNext, mGetFreqRange = 0; // FrontEnd Tuning method ID's
	jmethodID mGetParamsDvbT,msetStreamPriority,msetBandwidth,msetPLP = 0; // FrontEnd Tuing DVBT method ID's
	jmethodID mGetParamsDvbC,msetScanStep, msetSymbolRate,msetSearchRates = 0; //FrontEnd Tuning DVBC method ID's
	jmethodID mOnEvent,mGetFreqStep,mgetActualCodeRate,mgetSymbolRate,mgetSymbolRateRange,mgetActualChanBandwidth,mgetStreamPriority,mgetHierarchyMode,mgetTPSId = 0;
	jmethodID mgetActualConstellation,msetConstellation,mgetBer,mgetCarrierPresent,mgetSigStrengthRange,mstart,mstop = 0;
	jmethodID mGetT2CarrierPresent, mGetActivePlpId, mSelectPlpId, mGetDetectedPlpIds = 0;;
	jmethodID mgetMeasValid,mgetSigStrength = 0;
	jmethodID msourceSetupApply = 0;
	jmethodID mgetTVsystem,msetTVsystem=0;
	jmethodID mgetValueFromContentProvider = 0;
	jmethodID mRequestStatusInfo, mRequestNit, mSendOperatorSearchStart, mSendOpExit, mSendOpTuneStatus, mSendOpAck, mSendOpSearchCancel,mCacheOperatorData = 0; //Operator Profile method IDs
	HsvConflictServicesData *mConflictListJni = NULL;
	int mNumOfLCNConflictsStruc;
	JNIEnv *nativeenv; // Global env
	jclass nativeclazz;
	jobject objCaller;
	jclass clazz;
	jclass caller;
	jint ret;
	jobject m_jh; // Java Layer instance maintained in m_jh
	JNIEnv *envjava;
	JavaVM *natvm;
    	jint jh;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv *env;

	natvm = vm;
	if(vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv Failure");
	        return JNI_ERR;
	 } else {
		jclass clazz = env->FindClass("org/droidtv/euinstallertc/model/mwapi/EuInstallerTC");
		if(clazz) {
			//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetObjectClass SUCESS");
		} else {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetObjectClass FAIL");
		}
		caller = (jclass)(env->NewGlobalRef(clazz));
		
		mTune  = env->GetMethodID(caller, "tune_JavInst", "(IZ)I");
		if (0 == mTune) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mOnTune GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} 
		mGetFreq  = env->GetMethodID(caller, "getFreq_JavInst", "([I)I");
		if (0 == mGetFreq) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mGetFreq GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mScanStart  = env->GetMethodID(caller, "scanStart_JavInst", "(IIZ)I");
		if (0 == mScanStart) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mScanStart GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mScanAbort  = env->GetMethodID(caller, "scanAbort_JavInst", "()I");
		if (0 == mScanAbort) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mScanAbort GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mScanNext  = env->GetMethodID(caller, "scanNext_JavInst", "()I");
		if (0 == mScanNext) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mScanNext GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mOnEvent  = env->GetMethodID(caller, "javaInstaller_onEvent", "(II)I");
		if (0 == mOnEvent) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mOnEvent GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mGetFreqRange  = env->GetMethodID(caller, "getFreqRange_JavInst", "([I[I)I");
		if (0 == mGetFreqRange) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mGetFreqRange GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		msetSymbolRate = env->GetMethodID(caller, "setSymbolRate_JavInst", "(II)I");
		if (0 == msetSymbolRate) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "setSymbolRate GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		msetSearchRates  = env->GetMethodID(caller, "setSearchRates_JavaInst", "([Lorg/droidtv/tv/frontend/ITuningDvbC$DvbCSearchRateList;I)I");
		if (0 == msetSearchRates) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "setSymbolRate GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} else {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "setSymbolRate GetMethodID SUCESS \n");
		}
		mGetFreqStep = env->GetMethodID(caller, "GetFreqStep_JavaInst", "([I)I");
		if (0 == mGetFreqStep) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mGetFreqStep GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		msetScanStep = env->GetMethodID(caller, "setScanStep_JavInst", "(I)I");
		if (0 == mGetFreqStep) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "setScanStep GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mgetActualCodeRate = env->GetMethodID(caller, "getActualCodeRate_JavInst", "([I)I");
		if (0 == mgetActualCodeRate) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getActualCodeRate GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mgetSymbolRate = env->GetMethodID(caller, "getSymbolRate_JavInst", "([I)I");
		if (0 == mgetSymbolRate) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getSymbolRate GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		
		mgetSymbolRateRange = env->GetMethodID(caller, "getSymbolRateRange_JavInst", "([I)I");
		if (0 == mgetSymbolRateRange) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getSymbolRateRange GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		
		msetBandwidth = env->GetMethodID(caller, "setBandwidth_JavaInst", "(I)I");
		if (0 == msetBandwidth) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "setBandwidth GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mgetActualChanBandwidth = env->GetMethodID(caller, "getActualChanBandwidth_JavaInst", "([I)I");
		if (0 == mgetActualChanBandwidth) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getActualChanBandwidth GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mgetTPSId = env->GetMethodID(caller, "getTPSId_JavaInst", "([I)I");
		if (0 == mgetTPSId) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getTPSId GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}		
		msetStreamPriority = env->GetMethodID(caller, "setStreamPriority_JavaInst", "(I)I");
		if (0 == msetStreamPriority) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "setStreamPriority GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mgetStreamPriority = env->GetMethodID(caller, "getStreamPriority_JavaInst", "([I)I");
		if (0 == mgetStreamPriority) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getStreamPriority GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		
		mgetHierarchyMode = env->GetMethodID(caller, "getHierarchyMode_JavaInst", "([I)I");
		if (0 == mgetHierarchyMode) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mgetHierarchyMode GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mgetActualConstellation = env->GetMethodID(caller, "getActualConstellation_JavaInst", "([I)I");
		if (0 == mgetActualConstellation) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getActualConstellation_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		msetConstellation = env->GetMethodID(caller, "setConstellation_JavaInst", "(I)I");
		if (0 == msetConstellation) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "setConstellation_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mgetBer = env->GetMethodID(caller, "getBer_JavaInst", "([I)I");
		if (0 == mgetBer) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getBer_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mgetCarrierPresent = env->GetMethodID(caller, "getCarrierPresent_JavaInst", "([I)I");
		if (0 == mgetCarrierPresent) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getCarrierPresent_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mgetSigStrengthRange = env->GetMethodID(caller, "getSigStrengthRange_JavaInst", "(II)I");
		if (0 == mgetSigStrengthRange) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getSigStrengthRange_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mstart = env->GetMethodID(caller, "start_JavaInst", "(IZ)I");
		if (0 == mstart) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "start_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mstop = env->GetMethodID(caller, "stop_JavaInst", "(IZ)I");
		if (0 == mstop) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mstop GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mgetMeasValid = env->GetMethodID(caller, "getMeasValid_JavaInst", "(IZ)I");
		if (0 == mgetMeasValid) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mgetMeasValid GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mgetSigStrength = env->GetMethodID(caller, "getSigStrength_JavaInst", "(I[I)I");
		if (0 == mgetSigStrength) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getSigStrength_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		
		msourceSetupApply = env->GetMethodID(caller, "SourceSetupApply_JavaInst", "(I[I)I");
		if (0 == msourceSetupApply) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "SourceSetupApply_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		
		mGetT2CarrierPresent = env->GetMethodID(caller, "GetT2CarrierPresent_JavaInst", "([Z)I");
		if (0 == mGetT2CarrierPresent) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "GetT2CarrierPresent_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mGetActivePlpId = env->GetMethodID(caller, "GetActivePlpId_JavaInst", "([I)I");
		if (0 == mGetActivePlpId) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "GetActivePlpId_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mSelectPlpId = env->GetMethodID(caller, "SelectPlpId_JavaInst", "(I)I");
		if (0 == mSelectPlpId) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "SelectPlpId_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mGetDetectedPlpIds = env->GetMethodID(caller, "GetDetectedPlpIds_JavaInst", "([I[I)I");
		if (0 == mGetDetectedPlpIds) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "GetDetectedPlpIds_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mgetTVsystem = env->GetMethodID(caller, "getTVSystem_JavaInst", "([I[I)I");
		if (0 == mgetTVsystem) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getTVSystem_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}	
		msetTVsystem = env->GetMethodID(caller, "setTVSystem_JavaInst", "(I[I)I");
		if (0 == msetTVsystem) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "setTVSystem_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mRequestStatusInfo  = env->GetMethodID(caller, "RequestStatusInfo_JavaInst", "()V");
		if (0 == mRequestStatusInfo) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "RequestStatusInfo_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} 
		mRequestNit  = env->GetMethodID(caller, "RequestNit_JavaInst", "()V");
		if (0 == mRequestNit) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "RequestNit_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} else {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "RequestNit_JavaInst GetMethodID SUCESS \n");
		}
		mSendOpExit = env->GetMethodID(caller, "SendOpExit_JavaInst", "()V");
		if (0 == mSendOpExit) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "SendOpExit_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} 
		mSendOpAck = env->GetMethodID(caller, "SendOpAck_JavaInst", "()V");
		if (0 == mSendOpAck) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "SendOpAck_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mSendOpSearchCancel = env->GetMethodID(caller, "SendOpSearchCancel_JavaInst", "()V");
		if (0 == mSendOpSearchCancel) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "SendOpSearchCancel_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mCacheOperatorData= env->GetMethodID(caller, "mCacheOperatorData_JavaInst", "()V");
		if (0 == mCacheOperatorData) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "mCacheOperatorData_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mSendOperatorSearchStart = env->GetMethodID(caller, "SendOperatorSearchStart_JavaInst", "(II[II[II[I)V");
		if (0 == mSendOperatorSearchStart) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "SendOperatorSearchStart_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} 
		mSendOpTuneStatus = env->GetMethodID(caller, "SendOpTuneStatus_JavaInst", "(IIIII[I)V");
		if (0 == mSendOpTuneStatus) {
		   __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "SendOpTuneStatus_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} 
		mgetValueFromContentProvider = env->GetMethodID(caller, "getValue_FromContentProvider", "(I[I)I");
		if (0 == mgetValueFromContentProvider) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getValue_FromContentProvider GetMethodID Failure \n");
		   	env->DeleteGlobalRef(caller);
			return JNI_ERR;
		} 
		env->DeleteGlobalRef(caller);
		if(ret == 0)
		{
		  nativeenv = env;
		  nativeclazz = clazz;
		  return JNI_VERSION_1_6;
		} else {
			return JNI_ERR;
		}

	 }

}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    CreateInstance
 * Signature: (ILorg/droidtv/euinstallertc/model/mwapi/EuInstallerTC;)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_CreateInstance
(JNIEnv *env, jobject obj, jint token, jobject nh)
{

	if(nh != NULL) {
		m_jh = env->NewGlobalRef(nh);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","CreateInstance nh is  NULL");
	}
	jint ret = reinterpret_cast<jint> (new NativeInstaller(token,nh));
	jh = ret;
	return ret;
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    StartInstallation
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_StartInstallation
(JNIEnv *env, jobject obj,jint source, jint ptc, jint mode)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->StartInstallation(source,ptc,mode);
	return 0;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    StopInstallation
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_StopInstallation
(JNIEnv *env, jobject obj)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->StopInstallation();
	return 0;
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetManualFrequency
 * Signature: (IIZ)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetManualFrequency
  (JNIEnv *env, jobject obj, jint frequency, jint offset, jboolean finetune)
{
	
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetManualFrequency(frequency,offset,finetune);
}

#if 0
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetManualFrequency
 * Signature: ()Lorg/droidtv/euinstallertc/model/mwapi/ManFreqValues;
 */
JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetManualFrequency
  (JNIEnv *env, jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "GetManualFrequency");
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	int frequency;
	int offset;
	bool finetune;
	jclass manualFreqCls = NULL;
	jmethodID cid = NULL;
	jobject  manualFreqObj = NULL;
	
	natiInsta->GetManualFrequency(&frequency,&offset,(Bool*)&finetune);

	manualFreqCls = (env)->FindClass("Lorg/droidtv/euinstallertc/model/mwapi/ManFreqValues");

	if (manualFreqCls == NULL) {
		return NULL; /* exception thrown */
	}
	cid = (env)->GetMethodID(manualFreqCls, "<init>", "(IIZ)V");

	if (cid == NULL) {
		return NULL; /* exception thrown */
	}

	manualFreqObj = (env)->NewObject(manualFreqCls, cid, frequency, offset, finetune);

	return manualFreqObj;

}
#endif

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsManualInstallationModeSupported
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsManualInstallationModeSupported
  (JNIEnv *env, jobject obj, jint mode)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsManualInstallationModeSupported((int)mode);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetManualInstallationMode
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetManualInstallationMode
(JNIEnv *env, jobject obj, jint mode)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetManualInstallationMode((int)mode);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetManualInstallationMode
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetManualInstallationMode
  (JNIEnv *, jobject)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetManualInstallationMode();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    StoreManualInstallationValues
 * Signature: (Lorg/droidtv/euinstallertc/model/mwapi/HsvChannel;)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_StoreManualInstallationValues
(JNIEnv *env, jobject obj, jint channelNo)
{
	HsvChannel channel;
	
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);

	channel.Type  = AppApiAnalog  ;
	channel.Channel.Digit    = channelNo;
	channel.Channel.AnalogNo    = channelNo;

	natiInsta->StoreManualInstallationValues(channel);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    AutoStoreManualInstallationValues
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_AutoStoreManualInstallationValues
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->AutoStoreManualInstallationValues();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    StartFrequencySearch
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_StartFrequencySearch
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->StartFrequencySearch();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetTunerFrequency
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetTunerFrequency
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetTunerFrequency();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetTunerFrequency
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetTunerFrequency
  (JNIEnv *env, jobject obj, jint freq, jboolean fineTune)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetTunerFrequency(freq,fineTune);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNumberOfAnalogChannelsFound
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNumberOfAnalogChannelsFound
  (JNIEnv *, jobject)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetNumberOfAnalogChannelsFound();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNumberOfDigitalChannelsFound
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNumberOfDigitalChannelsFound
(JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetNumberOfDigitalChannelsFound();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNumberOfDigitalChannelsRemoved
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNumberOfDigitalChannelsRemoved
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetNumberOfDigitalChannelsRemoved();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetInstallationStatus
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetInstallationStatus
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetInstallationStatus();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetInstallationMode
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetInstallationMode
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetInstallationMode();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsUpdateInstallationSupported
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsUpdateInstallationSupported
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsUpdateInstallationSupported();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetManualChannel
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetManualChannel
  (JNIEnv *env, jobject obj, jint channel, jboolean finetune)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetManualChannel(channel,finetune);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetManualChannel
 * Signature: ()Lorg/droidtv/euinstallertc/model/mwapi/ManChanInfo;
 */
JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetManualChannel
(JNIEnv *env, jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG, "OnTuned_JNI", "GetManualChannel");
	int channel;
	Bool finetune;
	jclass manualChannelCls = NULL;
	jmethodID cid = NULL;
	jobject manualChannelObj = NULL;

	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->	GetManualChannel( &channel, &finetune);

	manualChannelCls = (env)->FindClass("org/droidtv/euinstallertc/model/mwapi/ManChanInfo");

	if (manualChannelCls == NULL) {
		return NULL; /* exception thrown */
	}

	cid = (env)->GetMethodID(manualChannelCls, "<init>", "(IZ)V");

	if (cid == NULL) {
		return NULL; /* exception thrown */
	}
	manualChannelObj = (env)->NewObject(manualChannelCls, cid, channel, finetune);

	return manualChannelObj;
}

#if 0
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetSigStrengthRange
 * Signature: (I)Lorg/droidtv/euinstallertc/model/mwapi/SigStrengthRange;
 */
JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetSigStrengthRange
(JNIEnv *env, jobject obj, jint mode)
{

	unsigned int retVal = 0;
	Nat32 min;
	Nat32 max;
	jclass sigStrengthCls = NULL;
	jmethodID cid = NULL;
	jobject sigStrengthObj = NULL;

	__android_log_print(ANDROID_LOG_DEBUG, "OnTuned_JNI", "GetSigStrengthRange");
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);

	retVal = natiInsta->GetSigStrengthRangeMw (mode, &min, &max);
	sigStrengthCls = (env)->FindClass("org/droidtv/euinstallertc/model/mwapi/SigStrengthRange");

	if (sigStrengthCls == NULL) {
		return NULL; /* exception thrown */
	}
	cid = (env)->GetMethodID(sigStrengthCls, "<init>", "(ZII)V");

	if (cid == NULL) {
		return NULL; /* exception thrown */
	}

	sigStrengthObj = (env)->NewObject(sigStrengthCls, cid, retVal, min, max);

	return sigStrengthObj;
}
#endif


/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetSignalstrength
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetSignalstrength
  (JNIEnv *env, jobject obj, jint measmode)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetSignalstrength(measmode);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    StoreWeakSignalInstallationChannel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_StoreWeakSignalInstallationChannel
(JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->StoreWeakSignalInstallationChannel();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetInstalledWeakSignalChannel
 * Signature: ()I;
 */
JNIEXPORT int JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetInstalledWeakSignalChannel
(JNIEnv *env, jobject obj)
{

	HsvChannel retval;
	jclass HsvChannelCls = NULL;
	jmethodID cid = NULL;
	jobject HsvChannelObj = NULL;
 

	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetInstalledWeakSignalChannel();
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsFrequencySearchDirectionSupported
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsFrequencySearchDirectionSupported
  (JNIEnv *env, jobject obj, jboolean searchup)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsFrequencySearchDirectionSupported(searchup);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetFrequencySearchDirection
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetFrequencySearchDirection
  (JNIEnv *env, jobject obj, jboolean searchup)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetFrequencySearchDirection(searchup);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetFrequencySearchDirection
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetFrequencySearchDirection
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetFrequencySearchDirection();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetMinFrequency
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetMinFrequency
  (JNIEnv *env, jobject obj)
{
	
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetMinFrequency();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetMaxFrequency
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetMaxFrequency
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetMaxFrequency();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetCurrentPass
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetCurrentPass
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetCurrentPass();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNoOfPass
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNoOfPass
(JNIEnv *env, jobject obj)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return	natiInsta->GetNoOfPass();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetCurrentPassType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetCurrentPassType
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetCurrentPassType();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsMediumSupported
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsMediumSupported
  (JNIEnv *env, jobject obj, jint medium)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsMediumSupported(medium);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetMedium
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetMedium
(JNIEnv *env, jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetMedium");
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return	natiInsta->GetMedium();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetMedium
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetMedium
  (JNIEnv *env, jobject obj, jint medium)
{
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","SetMedium [%d]",medium);
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetMedium(medium);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetInstalledMedium
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetInstalledMedium
(JNIEnv *env, jobject obj,jint medium)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetInstalledMedium(medium);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsTvSystemSupported
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsTvSystemSupported
  (JNIEnv *env, jobject obj, jint tvsystem)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsTvSystemSupported(tvsystem);

}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetTvSystem
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetTvSystem
(JNIEnv *env, jobject obj, jint system)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetTvSystem(system);
}


/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetTvSystem
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetTvSystem
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetTvSystem();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsColorSystemSupported
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsColorSystemSupported
  (JNIEnv *env, jobject obj, jint colorsystem)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsColorSystemSupported(colorsystem);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetColorSystem
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetColorSystem
  (JNIEnv *env, jobject obj, jint colorsystem)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetColorSystem(colorsystem);
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetColorSystem
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetColorSystem
  (JNIEnv *, jobject)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetColorSystem();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsValidPTC
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsValidPTC
  (JNIEnv *env, jobject obj, jint medium, jint ptc)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsValidPTC(medium,ptc);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetMinPTC
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetMinPTC
  (JNIEnv *env, jobject obj, jint medium)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetMinPTC(medium);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetMaxPTC
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetMaxPTC
  (JNIEnv *env, jobject obj, jint medium)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetMaxPTC(medium);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetLastPTCFound
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetLastPTCFound
  (JNIEnv *, jobject)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetLastPTCFound();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNumberOfPTCsFound
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNumberOfPTCsFound
  (JNIEnv *, jobject)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetNumberOfPTCsFound();

}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    StartSigStrMeas
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_StartSigStrMeas
  (JNIEnv *env, jobject obj, jint measmode)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->StartSigStrMeas(measmode);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    StopSigStrMeas
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_StopSigStrMeas
  (JNIEnv *env, jobject obj, jint measmode)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->StopSigStrMeas(measmode);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsSignalStrengthMeasurementValid
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsSignalStrengthMeasurementValid
  (JNIEnv *env, jobject obj, jint measmode)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsSignalStrengthMeasurementValid(measmode);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetAttributeRange
 * Signature: (II)Lorg/droidtv/euinstallertc/model/mwapi/AttributeRange;
 */
JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetAttributeRange
(JNIEnv *env, jobject obj, jint installationmode, jint attribute)
{
	bool retval;
	int maxValue;
	int minValue;
	jclass AttributeRangeCls = NULL;
	jmethodID cid = NULL;
	jobject AttributeRangeObj = NULL;

	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);


	retval = natiInsta->GetAttributeRange(installationmode, attribute, &minValue, &maxValue);
	
	 
	AttributeRangeCls = (env)->FindClass("org/droidtv/euinstallertc/model/mwapi/AttributeRange");
	if(AttributeRangeCls == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "GetAttributeRange FindClass Failed \n");
	}
	cid = (env)->GetMethodID(AttributeRangeCls, "<init>", "(ZII)V");

	if (cid == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "GetAttributeRange GetMethodID Failed \n");
		return NULL;
	}
	 
	AttributeRangeObj = (env)->NewObject(AttributeRangeCls, cid, (jint) retval, (jint) maxValue, (jint) minValue);
 
	return AttributeRangeObj;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetAttributeMode
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetAttributeMode
  (JNIEnv *env, jobject obj,jint installationmode, jint attribute, jint attributeMode)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->SetAttributeMode(installationmode,attribute,attributeMode);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetAttribute
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetAttribute
(JNIEnv *env, jobject obj, jint installationmode, jint attribute, jint attributeMode)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->SetAttribute(installationmode,attribute,attributeMode);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetAttributeMode
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetAttributeMode
  (JNIEnv *env, jobject obj, jint installationmode, jint attribute)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetAttributeMode(installationmode,attribute);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetAttribute
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetAttribute
  (JNIEnv *env, jobject obj, jint installationmode, jint attribute)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetAttribute(installationmode,attribute);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsAvailable
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsAvailable
  (JNIEnv *env, jobject obj, jint instllationmode, jint attribute)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsAvailable(instllationmode,attribute);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    ResetAttributeToDefault
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_ResetAttributeToDefault
  (JNIEnv *env, jobject obj, jint installationmode, jint attribute)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->ResetAttributeToDefault(installationmode,attribute);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    ResetAttributeToPersistent
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_ResetAttributeToPersistent
  (JNIEnv *env, jobject obj, jint installationmode, jint attribute)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->ResetAttributeToPersistent(installationmode,attribute);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetTargetNitType
 * Signature: ()Lorg/droidtv/euinstallertc/model/mwapi/NitType;
 */
JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetTargetNitType
(JNIEnv *env, jobject obj)
{
	bool retval;
	unsigned short int NetworkId;
	jclass TargetNitTypeCls = NULL;
	jmethodID cid = NULL;
	jobject TargetNitTypeObj = NULL;

	 

	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	retval = natiInsta->GetTargetNitType(&NetworkId);

	TargetNitTypeCls = (env)->FindClass("org/droidtv/euinstallertc/model/mwapi/NitType");

	if (TargetNitTypeCls == NULL) {
		return NULL; /* exception thrown */
	}
	cid = (env)->GetMethodID(TargetNitTypeCls, "<init>", "(II)V");

	if (cid == NULL) {
		return NULL; /* exception thrown */
	}

	TargetNitTypeObj = (env)->NewObject(TargetNitTypeCls, cid, NetworkId, retval);

	return TargetNitTypeObj;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    IsNetworkUpdateDetected
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_IsNetworkUpdateDetected
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->IsNetworkUpdateDetected();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    Initialise
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_Initialise
  (JNIEnv *, jobject)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->Initialise();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SkipInstallationScans
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SkipInstallationScans
  (JNIEnv *env, jobject obj, jint ScanTypes)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->SkipInstallationScans(ScanTypes);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetAltTSValues
 * Signature: ()Lorg/droidtv/euinstallertc/model/mwapi/TsValues;
 */
JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetAltTSValues
(JNIEnv *env, jobject obj)
{
	unsigned short  TSID;
	unsigned short  ONID;
	Bool finetune;
	jclass TSValuesCls = NULL;
	jmethodID cid = NULL;
	jobject  TSValuesObj = NULL;
 
	
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);

	finetune = natiInsta->GetAltTSValues(&ONID,&TSID);

	TSValuesCls = (env)->FindClass("org/droidtv/euinstallertc/model/mwapi/TsValues");

	if (TSValuesCls == NULL) {
		return NULL; /* exception thrown */
	}
	cid = (env)->GetMethodID(TSValuesCls, "<init>", "(IIZ)V");

	if (cid == NULL) {
		return NULL; /* exception thrown */
	}

	TSValuesObj = (env)->NewObject(TSValuesCls, cid, TSID, ONID,finetune);

	return TSValuesObj;
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetUserSymbolRates
 * Signature: (I[II)I
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetUserSymbolRates
(JNIEnv *env, jobject obj, jint installationMode, jintArray arr, jint len)
{

	jint *values;

	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	values = (env)->GetIntArrayElements( arr,0);
	if (values == NULL) {
		/* exception occurred */
	}

	natiInsta->SetUserSymbolRates(installationMode,values,len );
	(env)->ReleaseIntArrayElements( arr, values, 0);
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetUserSymbolRates
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetUserSymbolRates
(JNIEnv *env, jobject obj, jint installationMode)
{
	jint values[2];
	jint len=0,i=0;
		 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->GetUserSymbolRates( installationMode, values, &len );
	
	jintArray result = 0;
	if(len > 0) {
		result = (env)->NewIntArray(len);
		if(result == NULL)
		{
			return NULL;
		}	
		(env)->SetIntArrayRegion(result, 0, len, values);
	}
	return result;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetPredefinedSymbolRates
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetPredefinedSymbolRates
(JNIEnv *env, jobject obj, jint installationMode)
{
	jint values[8]; 
	jint len=0,i=0;
	jintArray result = 0;
	
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->GetPredefinedSymbolRates( installationMode, values, &len );
	 
	if(len > 0) {
		result = (env)->NewIntArray(len);
		if(result == NULL)
		{ 
			return NULL;
		}

		(env)->SetIntArrayRegion(result, 0, len, values); 
	}
	return result;
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNumberOfChannelListIds
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNumberOfChannelListIds
  (JNIEnv *env, jobject obj)
{ 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	
	return natiInsta->GetNumberOfChannelListIds();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetChannelListIDName
 * Signature: (I)[S
 */
JNIEXPORT jstring JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetChannelListIDName
(JNIEnv *env, jobject obj, jint index)
{
	unsigned short values[MAX_CHANNEL_LIST_NAME_SIZE];
	unsigned char channelIdName[MAX_CHANNEL_LIST_NAME_SIZE];
	jint len=0,i=0;
	jstring result = 0;

	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	for(i = 0; i < MAX_CHANNEL_LIST_NAME_SIZE; i++) {
		values[i] = '\0';
		channelIdName[i] = '\0';
	}
	
	natiInsta->GetChannelListIDName(index,values);
	
	for(i = 0; i < MAX_CHANNEL_LIST_NAME_SIZE; i++) {
		channelIdName[i] = (unsigned char)values[i]; 
		if(channelIdName[i] == '\0'){
			break;
		}
	}
	channelIdName[(MAX_CHANNEL_LIST_NAME_SIZE - 1)] = '\0';
	result = env->NewStringUTF((char*)channelIdName);
	
	return result;
}


/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNetworkIDList
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNetworkIDList
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	
	return natiInsta->GetNetworkIDList();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNetworkIDName
 * Signature: (I)[S
 */
JNIEXPORT jstring JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNetworkIDName
(JNIEnv *env, jobject obj, jint index)
{
	unsigned short values[MAX_NETWORK_NAME_SIZE];
	unsigned char networkName[MAX_NETWORK_NAME_SIZE];
	jint len=0,i=0;
	jstring result = 0;

	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	for(i = 0; i < MAX_NETWORK_NAME_SIZE; i++) {
		values[i] = '\0';
		networkName[i] = '\0';
	}
	
	natiInsta->GetNetworkIDName(index,values);
	
	for(i = 0; i < MAX_NETWORK_NAME_SIZE; i++) {
		networkName[i] = (unsigned char)values[i];
		//__android_log_print(ANDROID_LOG_DEBUG, "NativeInstaller","GetNetworkIDName getNetworkName [%c]",(char*)values[i]);
		if(networkName[i] == '\0'){
			break;
		}
	}
	networkName[(MAX_NETWORK_NAME_SIZE - 1)] = '\0';
	result = env->NewStringUTF((char*)networkName);
	
	return result;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetFavouriteNetworkID
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetFavouriteNetworkID
  (JNIEnv *env, jobject obj, jint mode, jint attrib, jint index)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetFavouriteNetworkID(mode,attrib,index);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetFavouriteRegion
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetFavouriteRegion
  (JNIEnv *env, jobject obj, jint mode, jint index, jint regionType)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->SetFavouriteRegion(mode,index,regionType);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetUserSelectConflictService
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetUserSelectConflictService
  (JNIEnv *env, jobject obj, jint LcnIndex, jint SvcIndex)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetUserSelectConflictService(LcnIndex,SvcIndex);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    ConflictsSelectionDone
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_ConflictsSelectionDone
  (JNIEnv *env, jobject obj, jboolean UserSelection)
{
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","ConflictsSelectionDone");
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	if (mConflictListJni)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Freeing conflict memory in JNI");
		delete[] mConflictListJni;
		mConflictListJni = NULL;		
	}

	natiInsta->ConflictsSelectionDone(UserSelection);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetConflictServices
 * Signature: ()[Lorg/droidtv/euinstallertc/model/mwapi/HsvConflictServicesData;
 */
JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetConflictServices
(JNIEnv *env, jobject obj)
{
	 
	HsvConflictServicesData ConflictList;
	jint NumRecords=0;

	jclass ConflictServicesCls = NULL;
	jmethodID cid = NULL;
	jobject  ConflictServicestObj = NULL;
	jobjectArray result;
	int size;

	jclass SInfoArrCls = (env)->FindClass( "org/droidtv/euinstallertc/model/mwapi/ServiceInfo");

	if (SInfoArrCls == NULL) {
		return NULL; /* exception thrown */
	}

	jmethodID sid = (env)->GetMethodID(SInfoArrCls, "<init>", "(I[I)V");

	if (sid == NULL) {
		return NULL; /* exception thrown */
	}

	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->GetConflictServices ( &ConflictList, &NumRecords );

	result = (env)->NewObjectArray( NumRecords, SInfoArrCls,NULL);

	for (size = 0; size < NumRecords; size++) {
		jobject obj = (env)->NewObject(SInfoArrCls,sid,ConflictList.ServiceInfo[size].DbIndex,ConflictList.ServiceInfo[size].ServiceName);
		(env)->SetObjectArrayElement( result,size,obj);
	}
	ConflictServicesCls = (env)->FindClass("org/droidtv/euinstallertc/model/mwapi/HsvConflictServicesData");

	if (ConflictServicesCls == NULL) {
		return NULL; /* exception thrown */
	}
	cid = (env)->GetMethodID(ConflictServicesCls, "<init>", "(IIZI[Lorg/droidtv/euinstallertc/model/mwapi/ServiceInfo;)V");

	if (cid == NULL) { 
		return NULL; /* exception thrown */
	}


	ConflictServicestObj = (env)->NewObject(ConflictServicesCls, cid, ConflictList.LCN,ConflictList.NoOfServices,ConflictList.AutomaticConflictResolution,ConflictList.UserPreferedServiceIndex,result);
	if (ConflictServicestObj == NULL) {
		return NULL; /* exception thrown */
	}

	return ConflictServicestObj;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetInstallationVersion
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetInstallationVersion
  (JNIEnv *env, jobject obj)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetInstallationVersion();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetInstallationState
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetInstallationState
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetInstallationState();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetPLPIds
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetPLPIds
(JNIEnv *env, jobject obj)
{
	jint NumIds;
	jintArray result = 0;
	int PLPIds[20];

	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	NumIds = natiInsta->GetPLPIds(PLPIds);
	if(NumIds > 0) {
		result = (env)->NewIntArray(NumIds);
		if (result == NULL) {
			return NULL;
		}
		(env)->SetIntArrayRegion(result, 0, NumIds, PLPIds);
	}
	return result;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    UserSelectionDone
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_UserSelectionDone
  (JNIEnv *env, jobject obj, jboolean UserSelection)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->UserSelectionDone(UserSelection);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetFavouriteRegion
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetFavouriteRegion
  (JNIEnv *env, jobject obj, jint mode, jint RegionType)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetFavouriteRegion(mode,RegionType);
}


/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetSymbolRate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetSymbolRate
  (JNIEnv *env, jobject obj)
{
	
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetSymbolRateMw();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetHierarchyMode
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetHierarchyMode
(JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetHierarchyMode();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    ZiggoNetworkDataSet
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_ZiggoNetworkDataSet
  (JNIEnv *env, jobject obj, jboolean ActionValue)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->ZiggoNetworkDataSet(ActionValue);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    ClearPersistent
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_ClearPersistent
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->ClearPersistent();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    onScanAborted_CallNative
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_onScanAborted_1CallNative
(JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->OnScanAborted();
	return 0;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    onScanEnded_CallNative
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_onScanEnded_1CallNative
(JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->OnScanEnded();
	return 0;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    onScanningStandardDetected_CallNative
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_onScanningStandardDetected_1CallNative
(JNIEnv *env, jobject obj, jint arg0, jint arg1)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->OnScanningStandardDetected(arg0,arg1);
	return 0;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    onTvSystemDetected_CallNative
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_onTvSystemDetected_1CallNative
  (JNIEnv *env, jobject obj, jint arg0)
  {
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->OnTvSystemDetected(arg0);
	return 0;
  }
  


/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    onTuned_CallNative
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_onTuned_1CallNative
(JNIEnv *env, jobject jobj,jint arg0, jint arg1)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->OnTuned(arg0,arg1);

	return 0;
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetInstallRfSetting
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetRfSetting
  (JNIEnv *env, jobject obj, jint value)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetInstallRfSetting(value);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetPbsMode
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetPbsMode
  (JNIEnv *env, jobject obj, jint value)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetPbsMode(value);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    PrepareChNameUpdate
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_PrepareChNameUpdate
  (JNIEnv *env, jobject obj, jint ChUniID, jint ServID)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->PrepareChNameUpdate(ChUniID, ServID);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetUpdatedChannelName
 * Signature: ()[S
 */
JNIEXPORT jstring JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetUpdatedChannelName
(JNIEnv *env, jobject obj)
{
	Nat16 values[42];
	jchar	ServiceName[40 + 2];
	jsize	StringLen = 0;
	jint len=0,i=0;
	jstring result = 0;


	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	for(i = 0; i < 42; i++) {
		values[i] = '\0';
		ServiceName[i] = '\0';
	}

	natiInsta->GetUpdatedChannelName(values);

	for(i = 0; (i < (40+1) && values[i]); i++) {
		if(values[i] != 0) {
			ServiceName[StringLen] = values[i];
			StringLen++;
		}
	}

	if(StringLen > 0) {
		result = env->NewString(ServiceName, StringLen);
	}
	else
		result = env->NewString(ServiceName, 1);

	return result;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetUpdatedONID
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetUpdatedONID
(JNIEnv *env, jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetUpdatedONID");
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetUpdatedONID();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetUpdatedTsID
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetUpdatedTsID
(JNIEnv *env, jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetUpdatedTsID");
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetUpdatedTsID();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetIsDVBT2Scan
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetIsDVBT2Scan
  (JNIEnv *env, jobject obj, jint abIsTrue)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetIsDVBT2Scan(abIsTrue);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetFocusedPlpId
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetFocusedPlpId
  (JNIEnv *env, jobject obj, jint aiPlpId)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetFocusedPlpId(aiPlpId);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetExtractScanResult
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetExtractScanResult
  (JNIEnv *env, jobject obj, jint abIsTrue)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetExtractScanResult(abIsTrue);
}

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetLastAnalogPresetNumber
  (JNIEnv *env, jobject obj)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetLastAnalogPresetNumber();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetUpdatedSymbolRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetUpdatedSymbolRate
(JNIEnv *env, jobject obj)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetUpdatedSymbolRate();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetLCNSortingControl
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetLCNSortingControl
  (JNIEnv *env, jobject obj, jint mode)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetLCNSortingControl(mode);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetInstallCountry
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetInstallCountry
  (JNIEnv *env, jobject obj, jint countryCode)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetInstallCountry(countryCode);
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetSystemCountry
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetSystemCountry
  (JNIEnv *env, jobject obj, jint countryCode)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetSystemCountry(countryCode);
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    setDigitalOrAnalaog
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_setDigitalOrAnalaog
  (JNIEnv *env, jobject obj, jint analogOrDigital)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->setDigitalOrAnalaog(analogOrDigital);
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    getDigitalOrAnalaog
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_getDigitalOrAnalaog
  (JNIEnv *env, jobject obj)
{
 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->getDigitalOrAnalaog();
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    getPogressStatus
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_getPogressStatus
(JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->getPogressStatus();
}


/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetFirstIntalledAnalogueChannel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetFirstIntalledAnalogueChannel
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetFirstIntalledAnalogueChannel();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetFirstIntalledDigitalChannel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetFirstIntalledDigitalChannel
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetFirstIntalledDigitalChannel();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetFirstIntalledRadioChannel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetFirstIntalledRadioChannel
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetFirstIntalledRadioChannel();
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetFirstInstalledChannel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetFirstInstalledChannel
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	// Mw API required
	return natiInsta->GetFirstInstalledChannel();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    ifValidNetworkFreqEntered
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_ifValidNetworkFreqEntered
  (JNIEnv *env, jobject obj, jint nwtFreq)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->ifValidNetworkFreqEntered(nwtFreq);
}



/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetDigitalChannelOnOrOff
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetDigitalChannelOnOrOff
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->GetDigitalChannelOnOrOff();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    getNetworkName
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_getNetworkName
  (JNIEnv *env, jobject obj, jint nwid)
{
	unsigned short values[MAX_NETWORK_NAME_SIZE];
	jchar 			nwName[MAX_NETWORK_NAME_SIZE];
	jsize			nameLen = 0;
	jint len=0,i=0;
	jstring result = NULL;
	
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	for(i = 0; i < MAX_NETWORK_NAME_SIZE; i++) {
		values[i] = '\0';
	}
	for(i = 0; i < MAX_NETWORK_NAME_SIZE; i++) {
		nwName[i] = '\0';
	}
	natiInsta->getNetworkName(nwid,values);

	for(i = 0; i < MAX_NETWORK_NAME_SIZE; i++) {
		if (values[i] != 0 ) {
			nwName[nameLen] = ((values[i] & 0x0000) >> 8);
			nwName[(nameLen+1)] = (values[i] & 0xFFFF);
			nameLen += 2;
		}
	}
	nwName[(nameLen+1)] = '\0';
	
	if(nameLen > 0) {
		result = env->NewString(nwName,nameLen);
	}
	
	return result;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    getNIDsFound
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_getNIDsFound
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	int Nids[200];
	jint NumIds;
	jintArray result = 0;

	NumIds = natiInsta->getNIDsFound(Nids);
	
	if(NumIds > 0) {
		result = (env)->NewIntArray(NumIds);
		if (result == NULL) {
			return NULL;
		}
		(env)->SetIntArrayRegion(result, 0, NumIds, Nids);
	}
	return result;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    getDefaultNetworkID
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_getDefaultNetworkID
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->getDefaultNetworkID();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    ifValidNetworkIDEntered
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_ifValidNetworkIDEntered
  (JNIEnv *env, jobject obj, jint nwtId)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	return natiInsta->ifValidNetworkIDEntered((int)nwtId);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    getFavNetworkList
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_getFavNetworkList
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	jobjectArray result = NULL;
	int *val = NULL;

	natiInsta->getFavNetworkList(val);

	return result;
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    setFavNetwork
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_setFavNetwork
  (JNIEnv *env, jobject obj, jint nwt)
{
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","setFavNetwork");
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->setFavNetwork(nwt);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetConflictSelectinDone
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetConflictSelectinDone
  (JNIEnv *env, jobject obj, jint val)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetConflictSelectinDone(val);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    skipNetworkFreq
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_skipNetworkFreq
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->skipNetworkFreq();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    skipNetworkID
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_skipNetworkID
  (JNIEnv *env, jobject obj)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->skipNetworkID();
}

/*
 * Class:	  org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:	  getRegionList
 * Signature: (IIII)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_getRegionList
  (JNIEnv *env, jobject, jint pri0_sec1_ter2, jint priID, jint secID)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	HsvNetworkRegionsData RegionList;
	jobjectArray regionlist;
	jint regionIndex = 0;
	jint regionMaxCount = 0;
	
	jint priIndex = 0, secIndex = 0, terIndex = 0;

	jobjectArray ret = NULL;
	int i = 0;
	unsigned char regionName[MAX_REGION_NAME_SIZE];
	
	for (i = 0; i < MAX_REGION_NAME_SIZE;i++)
	{
		regionName[i] = '\0';
	}
	
	for (priIndex = 0; priIndex < MAX_NETWORKS ; priIndex++){
		for(i = 0; i < MAX_REGION_NAME_SIZE; i++) {
			RegionList.Primary[priIndex].RegionName[i] = '\0';
		}
		
		for (secIndex = 0; secIndex < MAX_NETWORKS ; secIndex++){
			for(i = 0; i < MAX_REGION_NAME_SIZE; i++) {
				RegionList.Primary[priIndex].Secondary[secIndex].RegionName[i] = '\0';
			}
			
			for (terIndex = 0; terIndex < MAX_NETWORKS ; terIndex++){
				for(i = 0; i < MAX_REGION_NAME_SIZE; i++) {
					RegionList.Primary[priIndex].Secondary[secIndex].Tertiary[terIndex].RegionName[i] = '\0';
				}
			}
		}
	}
	
	for(i = 0; i < MAX_REGION_NAME_SIZE; i++) {
		RegionList.Primary[regionIndex].RegionName[i] = '\0';
		RegionList.Primary[priID].Secondary[regionIndex].RegionName[i];
	}
	natiInsta->GetRegionList(&RegionList);
	
	if(pri0_sec1_ter2 == 0){
		//primary region
		regionMaxCount = RegionList.NoOfRegions;
	 
		ret = (jobjectArray)env->NewObjectArray(regionMaxCount, (env)->FindClass("java/lang/String"),(env)->NewStringUTF(""));
		for (regionIndex = 0; regionIndex < regionMaxCount; regionIndex++){			
			for(i = 0; i < MAX_REGION_NAME_SIZE; i++) {
				regionName[i] = (unsigned char) RegionList.Primary[regionIndex].RegionName[i];
				 
				if(regionName[i] == '\0'){
					break;
				}				
			}
			regionName[(MAX_REGION_NAME_SIZE - 1)] = '\0';
			env->SetObjectArrayElement(ret,regionIndex,env->NewStringUTF((char*)regionName));
		}
	}else if(pri0_sec1_ter2 == 1){
		//secondary region
		regionMaxCount = RegionList.Primary[priID].NoOfRegions;
		 
		ret = (jobjectArray)env->NewObjectArray(regionMaxCount, (env)->FindClass("java/lang/String"),(env)->NewStringUTF(""));
		for (regionIndex = 0; regionIndex < regionMaxCount; regionIndex++){
			for(i = 0; i < MAX_REGION_NAME_SIZE; i++) {
				regionName[i] = (unsigned char) RegionList.Primary[priID].Secondary[regionIndex].RegionName[i];
				 
				if(regionName[i] == '\0'){
					break;
				}
			}
			regionName[(MAX_REGION_NAME_SIZE - 1)] = '\0';
			env->SetObjectArrayElement(ret,regionIndex,env->NewStringUTF((char*)regionName));
		}
	} else if(pri0_sec1_ter2 == 2){
		//tertirary region
		regionMaxCount = RegionList.Primary[priID].Secondary[secID].NoOfRegions;
		 
		ret = (jobjectArray)env->NewObjectArray(regionMaxCount, (env)->FindClass("java/lang/String"),(env)->NewStringUTF(""));
		for (regionIndex = 0; regionIndex < regionMaxCount; regionIndex++){
			for(i = 0; i < MAX_REGION_NAME_SIZE; i++) {
				regionName[i] = (unsigned char) RegionList.Primary[priID].Secondary[secID].Tertiary[regionIndex].RegionName[i];
				 
				if(regionName[i] == '\0'){
					break;
				}
			}
			regionName[(MAX_REGION_NAME_SIZE - 1)] = '\0';
			env->SetObjectArrayElement(ret,regionIndex,env->NewStringUTF((char*)regionName));
		}
	}
	return ret; 
}

/*
 * Class:	  org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:	  setRegionList
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_setRegionList
  (JNIEnv *env, jobject obj, jint pri0_sec1_ter2, jint regionIndex)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	
	 

	if(pri0_sec1_ter2 == 0){
		natiInsta->SetFavouriteRegion(IHsvInstallation2_InstallationModeAutomatic, regionIndex, HsvPrimaryRegion);
	}else if(pri0_sec1_ter2 == 1){
		natiInsta->SetFavouriteRegion(IHsvInstallation2_InstallationModeAutomatic, regionIndex, HsvSecondaryRegion);
	}else if(pri0_sec1_ter2 == 2){
		natiInsta->SetFavouriteRegion(IHsvInstallation2_InstallationModeAutomatic, regionIndex, HsvTertiaryRegion);
	}
}

/*
 * Class:	  org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:	  setLowestNetworkID
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_setLowestNetworkID
  (JNIEnv *, jobject)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
}


/*
 * Class:	  org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:	  getConflictingChannelNumbers
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_getConflictingChannelNumbers
  (JNIEnv *env, jobject obj)
{

	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	jintArray lcnListArray = NULL;
	int lcnChannelNumbers[500];
	jint lcnIndex = 0, serviceIndex = 0, charIndex = 0;
	
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Allocating conflict memory in JNI");
	mConflictListJni = new HsvConflictServicesData [MAX_SERVICES];
	
	for (lcnIndex = 0; lcnIndex < MAX_SERVICES; lcnIndex++){
		for (serviceIndex = 0; serviceIndex < MAX_CONFLICT_SERVICES; serviceIndex++){
			for(charIndex = 0; charIndex < 33; charIndex++){
				mConflictListJni[lcnIndex].ServiceInfo[serviceIndex].ServiceName[charIndex] = '\0';
			}
		}
	}
			
	// get the list of conflicting services structure
	natiInsta->GetConflictServices ( mConflictListJni, &mNumOfLCNConflictsStruc );
	 
	if(mNumOfLCNConflictsStruc > 0){
		// initialize new int array with number of LCN ids
		lcnListArray = (env)->NewIntArray(mNumOfLCNConflictsStruc);
		if(lcnListArray == NULL)
		{ 
			return NULL;
		}
		
		for (lcnIndex = 0; lcnIndex < mNumOfLCNConflictsStruc; lcnIndex++){
			lcnChannelNumbers[lcnIndex] = mConflictListJni[lcnIndex].LCN;
		//_android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getConflictingChannelNumbers [%d] ",lcnChannelNumbers[lcnIndex]);
		//	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getConflictingChannelNumbers [%c] ",mConflictList->ServiceInfo[lcnIndex].ServiceName);
		}
		(env)->SetIntArrayRegion(lcnListArray, 0, mNumOfLCNConflictsStruc, lcnChannelNumbers);
	}
	
	 
	return lcnListArray;
}

/*
 * Class:	  org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:	  getConflictingChannelNames
 * Signature: (I)[Ljava/lang/String
 */
JNIEXPORT jobjectArray JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_getConflictingChannelNames
  (JNIEnv *env, jobject obj, jint argLCNIndex)
{
		 
		NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
		jobjectArray  serviceNameList = 0;
		int serviceCount = 0;
		jchar svcName[66];
		int serviceIndex = 0;
		int charIndex = 0;
		jint loopCount = 0;
		jsize svcNameLen = 0;
		
		 
		if((mNumOfLCNConflictsStruc > 0) && (argLCNIndex <= mNumOfLCNConflictsStruc)){
			serviceCount = mConflictListJni[argLCNIndex].NoOfServices;
	 
			serviceNameList = (jobjectArray)env->NewObjectArray(serviceCount, (env)->FindClass("java/lang/String"),env->NewString(NULL,0));
			for (serviceIndex = 0; serviceIndex < serviceCount; serviceIndex++){

				for (loopCount = 0; loopCount < 66; loopCount++) {
					svcName[loopCount] = '\0';	
				}
				
				for(charIndex = 0, svcNameLen = 0; charIndex < 33; charIndex++){
				if((mConflictListJni[argLCNIndex].ServiceInfo[serviceIndex].ServiceName[charIndex])!=0)
				{
					svcName[svcNameLen] = ((mConflictListJni[argLCNIndex].ServiceInfo[serviceIndex].ServiceName[charIndex]  & 0xFF00) >> 8); 
					//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getConflictingChannelNames svcName[charIndex] [%d][%c]", svcName[svcNameLen], svcName[svcNameLen]);
					svcNameLen += 1;
					svcName[(svcNameLen)] = (mConflictListJni[argLCNIndex].ServiceInfo[serviceIndex].ServiceName[charIndex]  & 0x00FF); 
					//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getConflictingChannelNames svcName[svcNameLen] [%d][%c]", svcName[svcNameLen], svcName[svcNameLen]);
					svcNameLen += 1;
				}
				else {
					svcName[svcNameLen] = 0;
					++svcNameLen;
					break;
				}
				}
					
				env->SetObjectArrayElement(serviceNameList,serviceIndex,env->NewString(svcName,svcNameLen));
			}
		}
	
		 
		return serviceNameList;
}

JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_setSymbolRatesOneTwo
  (JNIEnv *env, jobject obj, jint installmode, jint symb0_symb1, jint symbRateValue)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);

	int values[2];
	int len;
	
	natiInsta->GetUserSymbolRates( installmode, values, &len );
	//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","setSymbolRatesOneTwo len[%d] val0[%d] val1[%d]",len,values[0],values[1]);

	values[symb0_symb1] = symbRateValue;

	natiInsta->setUserSymbolRate(installmode,values,len);
}


JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_OnSourceSetupApplied(JNIEnv *env, jobject obj, jint status)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->OnSourceSetupApplied(status);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetStreamPriority
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetStreamPriority
  (JNIEnv *env, jobject obj, jint plpid)
 {
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetStreamPriority(plpid);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    OnOpSearchStatus
 * Signature: (jObject)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_OnOpSearchStatus
  (JNIEnv *env, jobject obj, jobject objOpSearchStatus)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	Op_ProfileSearchStatus OpSearchStatus;
	jfieldID fid_Info_Version 				= NULL;
	jfieldID fid_NIT_Version				= NULL;		
	jfieldID fid_Profile_Type				= NULL;
	jfieldID fid_Initialised_Flag			= NULL;		
	jfieldID fid_Entitlement_Change_Flag	= NULL;
	jfieldID fid_Entitlement_Valid_Flag		= NULL;
	jfieldID fid_Refresh_Request_Flag		= NULL;
	jfieldID fid_Error_Flag					= NULL;
	jfieldID fid_Delivery_System_Hint		= NULL;
	jfieldID fid_Refresh_Request_Date		= NULL;
	jfieldID fid_Refresh_Request_Time		= NULL;
	
	 
	
	jclass opSearchStatusClass  = (env)->FindClass( "org/droidtv/euinstallertc/model/mwapi/MwDataTypes$opProfileSearchStatus");
	
	fid_Info_Version 			= (env)->GetFieldID (opSearchStatusClass, "Info_Version", "I");
	fid_NIT_Version				= (env)->GetFieldID (opSearchStatusClass, "NIT_Version", "I");
	fid_Profile_Type			= (env)->GetFieldID (opSearchStatusClass, "Profile_Type", "I");
	fid_Initialised_Flag		= (env)->GetFieldID (opSearchStatusClass, "Initialised_Flag", "I");
	fid_Entitlement_Change_Flag	= (env)->GetFieldID (opSearchStatusClass, "Entitlement_Change_Flag", "I");
	fid_Entitlement_Valid_Flag	= (env)->GetFieldID (opSearchStatusClass, "Entitlement_Valid_Flag", "I");
	fid_Refresh_Request_Flag	= (env)->GetFieldID (opSearchStatusClass, "Refresh_Request_Flag", "I");
	fid_Error_Flag				= (env)->GetFieldID (opSearchStatusClass, "Error_Flag", "I");
	fid_Delivery_System_Hint	= (env)->GetFieldID (opSearchStatusClass, "Delivery_System_Hint", "I");
	fid_Refresh_Request_Date	= (env)->GetFieldID (opSearchStatusClass, "Refresh_Request_Date", "I");
    fid_Refresh_Request_Time	= (env)->GetFieldID (opSearchStatusClass, "Refresh_Request_Time", "I");

	
	OpSearchStatus.op_Status.Info_Version 				= (Nat8)(env)->GetIntField(objOpSearchStatus, fid_Info_Version);	
	OpSearchStatus.op_Status.NIT_Version				= (Nat8)(env)->GetIntField(objOpSearchStatus, fid_NIT_Version);	
	OpSearchStatus.op_Status.Profile_Type			 	= (OP_Profile)(env)->GetIntField(objOpSearchStatus, fid_Profile_Type);	
	OpSearchStatus.op_Status.Initialised_Flag			= (Nat8)(env)->GetIntField(objOpSearchStatus, fid_Initialised_Flag);		
	OpSearchStatus.op_Status.Entitlement_Change_Flag	= (Nat8)(env)->GetIntField(objOpSearchStatus, fid_Entitlement_Change_Flag);		
	OpSearchStatus.op_Status.Entitlement_Valid_Flag		= (Nat8)(env)->GetIntField(objOpSearchStatus, fid_Entitlement_Valid_Flag);		
	OpSearchStatus.op_Status.Refresh_Request_Flag		= (OP_RefreshRequestFlag)(env)->GetIntField(objOpSearchStatus, fid_Refresh_Request_Flag);		
	OpSearchStatus.op_Status.Error_Flag				    = (OP_Error_Flag)(env)->GetIntField(objOpSearchStatus, fid_Error_Flag);	
	OpSearchStatus.op_Status.Delivery_System_Hint	 	= (Nat16)(env)->GetIntField(objOpSearchStatus, fid_Delivery_System_Hint);
	OpSearchStatus.op_Status.Refresh_Request_Date		= (Nat16)(env)->GetIntField(objOpSearchStatus,fid_Refresh_Request_Date); 
	OpSearchStatus.op_Status.Refresh_Request_Time		= (Nat8)(env)->GetIntField(objOpSearchStatus,fid_Refresh_Request_Time); 

	#if 0
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Info_Version [%d] \n",OpSearchStatus.op_Status.Info_Version);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","NIT_Version [%d] \n",OpSearchStatus.op_Status.NIT_Version);				
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Profile_Type [%d] \n",OpSearchStatus.op_Status.Profile_Type);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Initialised_Flag [%d] \n",OpSearchStatus.op_Status.Initialised_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Entitlement_Change_Flag [%d] \n",OpSearchStatus.op_Status.Entitlement_Change_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Entitlement_Valid_Flag [%d] \n",OpSearchStatus.op_Status.Entitlement_Valid_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Refresh_Request_Flag [%d] \n",OpSearchStatus.op_Status.Refresh_Request_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Error_Flag [%d] \n",OpSearchStatus.op_Status.Error_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Delivery_System_Hint [%d] \n",OpSearchStatus.op_Status.Delivery_System_Hint);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Refresh_Request_Date [%d] \n",OpSearchStatus.op_Status.Refresh_Request_Date);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Refresh_Request_Time [%d] \n",OpSearchStatus.op_Status.Refresh_Request_Time);
	
	 #endif
	natiInsta->OnOpSearchStatus(OpSearchStatus);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    OnOpStatusInfo
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_OnOpStatusInfo
  (JNIEnv *env, jobject obj, jobject objOpStatusInfo)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	Op_ProfileStatusInfo OpStatusInfo;
	
	jfieldID fid_Info_Version 				= NULL;
	jfieldID fid_NIT_Version				= NULL;		
	jfieldID fid_Profile_Type				= NULL;
	jfieldID fid_Initialised_Flag			= NULL;		
	jfieldID fid_Entitlement_Change_Flag	= NULL;
	jfieldID fid_Entitlement_Valid_Flag		= NULL;
	jfieldID fid_Refresh_Request_Flag		= NULL;
	jfieldID fid_Error_Flag					= NULL;
	jfieldID fid_Delivery_System_Hint		= NULL;
	jfieldID fid_Refresh_Request_Date		= NULL;
	jfieldID fid_Refresh_Request_Time		= NULL;
	jfieldID fid_InfoValid					= NULL;
	jfieldID fid_ProfileInfoVersion			= NULL;
	jfieldID fid_CiCamOriginalNetworkId		= NULL;
	jfieldID fid_CiCamIdentifier			= NULL;
	jfieldID fid_CharacterCodeTable			= NULL;
	jfieldID fid_CharacterCodeTable2		= NULL;
	jfieldID fid_CharacterCodeTable3		= NULL;
	jfieldID fid_SdtRunningTrusted			= NULL;
	jfieldID fid_EitRunningTrusted			= NULL;
	jfieldID fid_EitPfUsage					= NULL;
	jfieldID fid_EitScheduleUsage			= NULL;
	jfieldID fid_ExtendedEventUsage			= NULL;
	jfieldID fid_SdtOtherTrusted			= NULL;
	jfieldID fid_EitEventTrigger			= NULL;
	jfieldID fid_ISO639LangCode 			= NULL;
	jfieldID fid_ProfileNameLength			= NULL;
	jfieldID fid_ProfileName				= NULL;
	jintArray	ObjProfileNameArray;
	jintArray	ObjLangCodeArray;
	const int* ProfileName = NULL;
	const int* LangCode	= NULL;
	
	 
	
	jclass opProfileStatusInfoClass  = (env)->FindClass( "org/droidtv/euinstallertc/model/mwapi/MwDataTypes$opProfileStatusInfo");
	
	fid_Info_Version 			= (env)->GetFieldID (opProfileStatusInfoClass, "Info_Version", "I");
	fid_NIT_Version				= (env)->GetFieldID (opProfileStatusInfoClass, "NIT_Version", "I");
	fid_Profile_Type			= (env)->GetFieldID (opProfileStatusInfoClass, "Profile_Type", "I");
	fid_Initialised_Flag		= (env)->GetFieldID (opProfileStatusInfoClass, "Initialised_Flag", "I");
	fid_Entitlement_Change_Flag	= (env)->GetFieldID (opProfileStatusInfoClass, "Entitlement_Change_Flag", "I");
	fid_Entitlement_Valid_Flag	= (env)->GetFieldID (opProfileStatusInfoClass, "Entitlement_Valid_Flag", "I");
	fid_Refresh_Request_Flag	= (env)->GetFieldID (opProfileStatusInfoClass, "Refresh_Request_Flag", "I");
	fid_Error_Flag				= (env)->GetFieldID (opProfileStatusInfoClass, "Error_Flag", "I");
	fid_Delivery_System_Hint	= (env)->GetFieldID (opProfileStatusInfoClass, "Delivery_System_Hint", "I");
	fid_Refresh_Request_Date	= (env)->GetFieldID (opProfileStatusInfoClass, "Refresh_Request_Date", "I");
    fid_Refresh_Request_Time	= (env)->GetFieldID (opProfileStatusInfoClass, "Refresh_Request_Time", "I");
	
	fid_InfoValid				= (env)->GetFieldID (opProfileStatusInfoClass, "InfoValid", "I");
	fid_ProfileInfoVersion		= (env)->GetFieldID (opProfileStatusInfoClass, "ProfileInfoVersion", "I");
	fid_CiCamOriginalNetworkId	= (env)->GetFieldID (opProfileStatusInfoClass, "CiCamOriginalNetworkId", "I");
	fid_CiCamIdentifier			= (env)->GetFieldID (opProfileStatusInfoClass, "CiCamIdentifier", "I");
	fid_CharacterCodeTable		= (env)->GetFieldID (opProfileStatusInfoClass, "CharacterCodeTable", "I");
	fid_CharacterCodeTable2		= (env)->GetFieldID (opProfileStatusInfoClass, "CharacterCodeTable2", "I");
	fid_CharacterCodeTable3		= (env)->GetFieldID (opProfileStatusInfoClass, "CharacterCodeTable3", "I");
	fid_SdtRunningTrusted		= (env)->GetFieldID (opProfileStatusInfoClass, "SdtRunningTrusted", "I");
	fid_EitRunningTrusted		= (env)->GetFieldID (opProfileStatusInfoClass, "EitRunningTrusted", "I");
	fid_EitPfUsage				= (env)->GetFieldID (opProfileStatusInfoClass, "EitPfUsage", "I");
    fid_EitScheduleUsage		= (env)->GetFieldID (opProfileStatusInfoClass, "EitScheduleUsage", "I");
	fid_ExtendedEventUsage		= (env)->GetFieldID (opProfileStatusInfoClass, "ExtendedEventUsage", "I");
	fid_SdtOtherTrusted			= (env)->GetFieldID (opProfileStatusInfoClass, "SdtOtherTrusted", "I");
	fid_EitEventTrigger			= (env)->GetFieldID (opProfileStatusInfoClass, "EitEventTrigger", "I");
	fid_ISO639LangCode 			= (env)->GetFieldID (opProfileStatusInfoClass, "ISO639LangCode", "[I");
	fid_ProfileNameLength		= (env)->GetFieldID (opProfileStatusInfoClass, "ProfileNameLength", "I");
	fid_ProfileName				= (env)->GetFieldID (opProfileStatusInfoClass, "ProfileName", "[I");
	
	OpStatusInfo.op_Status.Info_Version 			= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_Info_Version);	
	OpStatusInfo.op_Status.NIT_Version				= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_NIT_Version);	
	OpStatusInfo.op_Status.Profile_Type			 	= (OP_Profile)(env)->GetIntField(objOpStatusInfo, fid_Profile_Type);	
	OpStatusInfo.op_Status.Initialised_Flag			= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_Initialised_Flag);		
	OpStatusInfo.op_Status.Entitlement_Change_Flag	= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_Entitlement_Change_Flag);		
	OpStatusInfo.op_Status.Entitlement_Valid_Flag	= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_Entitlement_Valid_Flag);		
	OpStatusInfo.op_Status.Refresh_Request_Flag		= (OP_RefreshRequestFlag)(env)->GetIntField(objOpStatusInfo, fid_Refresh_Request_Flag);		
	OpStatusInfo.op_Status.Error_Flag				= (OP_Error_Flag)(env)->GetIntField(objOpStatusInfo, fid_Error_Flag);	
	OpStatusInfo.op_Status.Delivery_System_Hint	 	= (Nat16)(env)->GetIntField(objOpStatusInfo, fid_Delivery_System_Hint);
	OpStatusInfo.op_Status.Refresh_Request_Date		= (Nat16)(env)->GetIntField(objOpStatusInfo,fid_Refresh_Request_Date); 
	OpStatusInfo.op_Status.Refresh_Request_Time		= (Nat8)(env)->GetIntField(objOpStatusInfo,fid_Refresh_Request_Time); 


	#if 0
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Info_Version [%d] \n",OpStatusInfo.op_Status.Info_Version);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","NIT_Version [%d] \n",OpStatusInfo.op_Status.NIT_Version);				
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Profile_Type [%d] \n",OpStatusInfo.op_Status.Profile_Type);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Initialised_Flag [%d] \n",OpStatusInfo.op_Status.Initialised_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Entitlement_Change_Flag [%d] \n",OpStatusInfo.op_Status.Entitlement_Change_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Entitlement_Valid_Flag [%d] \n",OpStatusInfo.op_Status.Entitlement_Valid_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Refresh_Request_Flag [%d] \n",OpStatusInfo.op_Status.Refresh_Request_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Error_Flag [%d] \n",OpStatusInfo.op_Status.Error_Flag);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Delivery_System_Hint [%d] \n",OpStatusInfo.op_Status.Delivery_System_Hint);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Refresh_Request_Date [%d] \n",OpStatusInfo.op_Status.Refresh_Request_Date);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Refresh_Request_Time [%d] \n",OpStatusInfo.op_Status.Refresh_Request_Time);
	#endif
	
	OpStatusInfo.op_Info.info_Valid					= (Nat8) (env)->GetIntField(objOpStatusInfo, fid_InfoValid);	
	OpStatusInfo.op_Info.info_Version				= (Nat8) (env)->GetIntField(objOpStatusInfo, fid_ProfileInfoVersion);	
	OpStatusInfo.op_Info.cicam_Original_Network_Id	= (Nat16) (env)->GetIntField(objOpStatusInfo, fid_CiCamOriginalNetworkId);	
	OpStatusInfo.op_Info.cicam_Identifier			= (int) (env)->GetIntField(objOpStatusInfo, fid_CiCamIdentifier);		
	OpStatusInfo.op_Info.character_Code_Table		= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_CharacterCodeTable);		
	OpStatusInfo.op_Info.character_Code_Table_2		= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_CharacterCodeTable2);
	OpStatusInfo.op_Info.character_Code_Table_3		= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_CharacterCodeTable3);		
	OpStatusInfo.op_Info.sDT_Running_Trusted		= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_SdtRunningTrusted);	
	OpStatusInfo.op_Info.eIT_Running_Trusted		= (Nat8)(env)->GetIntField(objOpStatusInfo, fid_EitRunningTrusted);
	OpStatusInfo.op_Info.eIT_Pf_Usage				= (OP_EIT_pfUsage)(env)->GetIntField(objOpStatusInfo,fid_EitPfUsage); 
	OpStatusInfo.op_Info.eIT_Schedule_Usage			= (OP_EIT_schedUsage)(env)->GetIntField(objOpStatusInfo,fid_EitScheduleUsage); 
    OpStatusInfo.op_Info.extended_Event_Usage		= (int)(env)->GetIntField(objOpStatusInfo,fid_ExtendedEventUsage); 
	OpStatusInfo.op_Info.sDT_Other_Trusted			= (Nat8)(env)->GetIntField(objOpStatusInfo,fid_SdtOtherTrusted); 
	OpStatusInfo.op_Info.eIT_Event_Trigger			= (Nat8)(env)->GetIntField(objOpStatusInfo,fid_EitEventTrigger); 
	OpStatusInfo.op_Info.profile_Name_Length		= (short)(env)->GetIntField(objOpStatusInfo,fid_ProfileNameLength); 
	
	/* Lang Code Array */
	ObjLangCodeArray = (jintArray) (env)->GetObjectField(objOpStatusInfo, fid_ISO639LangCode);
	
	if(NULL != ObjLangCodeArray) 
	{
		LangCode = (int *) (env)->GetIntArrayElements(ObjLangCodeArray, 0);
        if(LangCode != NULL)
		{
			for(int i = 0; i < 3; i++)
			{
				OpStatusInfo.op_Info.iSO_639_Lang_Code[i] = (Nat8)LangCode[i];
			}
		}
    }
	
	/* Profile Name Array */
	ObjProfileNameArray = (jintArray) (env)->GetObjectField(objOpStatusInfo, fid_ProfileName);
	
	if(NULL != ObjProfileNameArray) 
	{
		ProfileName = (int *) (env)->GetIntArrayElements(ObjProfileNameArray, 0);
        if(ProfileName != NULL)
		{
			for(int i = 0; i < OpStatusInfo.op_Info.profile_Name_Length; i++)
			{
				OpStatusInfo.op_Info.profile_Name[i] = (Nat8)ProfileName[i];
			}
		}
    }
	else
	{
	   OpStatusInfo.op_Info.profile_Name_Length = 0;
    }

	#if 0
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","InfoValid [%d] \n",OpStatusInfo.op_Info.info_Valid);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","ProfileInfoVersion [%d] \n",OpStatusInfo.op_Info.info_Version);				
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","CiCamOriginalNetworkId [%d] \n",OpStatusInfo.op_Info.cicam_Original_Network_Id);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","CiCamIdentifier [%d] \n",OpStatusInfo.op_Info.cicam_Identifier);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","CharacterCodeTable [%d] \n",OpStatusInfo.op_Info.character_Code_Table);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","CharacterCodeTable2 [%d] \n",OpStatusInfo.op_Info.character_Code_Table_2);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","CharacterCodeTable3 [%d] \n",OpStatusInfo.op_Info.character_Code_Table_3);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","SdtRunningTrusted [%d] \n",OpStatusInfo.op_Info.sDT_Running_Trusted);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","EitRunningTrusted [%d] \n",OpStatusInfo.op_Info.eIT_Running_Trusted);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","EitPfUsage [%d] \n",OpStatusInfo.op_Info.eIT_Pf_Usage);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","EitScheduleUsage [%d] \n",OpStatusInfo.op_Info.eIT_Schedule_Usage);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","ExtendedEventUsage [%d] \n",OpStatusInfo.op_Info.extended_Event_Usage);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","sDT_Other_Trusted [%d] \n",OpStatusInfo.op_Info.sDT_Other_Trusted);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","eIT_Event_Trigger [%d] \n",OpStatusInfo.op_Info.eIT_Event_Trigger);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","profile_Name_Length [%d] \n",OpStatusInfo.op_Info.profile_Name_Length);
	
	__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI","Native OnOpStatusInfo called");
	#endif
	natiInsta->OnOpStatusInfo(OpStatusInfo);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    OnOpNIT
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_OnOpNIT
  (JNIEnv *env, jobject obj, jobject objOpNIT)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);	
	Op_ProfileNitData opNitData;
	jfieldID fid_NitStatus 				= NULL;
	jfieldID fid_NitDataLength			= NULL;		
	jfieldID fid_NitData				= NULL;
	
	jintArray	ObjNitDataArray;
	const int* NitData = NULL;
	 
	
	jclass opNitClass  = (env)->FindClass( "org/droidtv/euinstallertc/model/mwapi/MwDataTypes$opProfileNitData");
	
	fid_NitStatus 		= (env)->GetFieldID (opNitClass, "NitStatus", "I");
	fid_NitDataLength	= (env)->GetFieldID (opNitClass, "NitDataLength", "I");
	fid_NitData			= (env)->GetFieldID (opNitClass, "NitData", "[I");
	
	
	opNitData.NitStatus 	= (Bool)(env)->GetIntField(objOpNIT, fid_NitStatus);	
	opNitData.NitDataLength	= (Nat16)(env)->GetIntField(objOpNIT, fid_NitDataLength);
	
	ObjNitDataArray = (jintArray) (env)->GetObjectField(objOpNIT, fid_NitData);
	if (NULL != ObjNitDataArray) 
	{
		NitData = (int *) (env)->GetIntArrayElements(ObjNitDataArray, 0);
        if(NitData != NULL)
		{
			for(int i = 0; i < opNitData.NitDataLength; i++)
			{
				opNitData.NitData[i] = (Nat8)NitData[i];
			}
		}
    }
	else
	{
	   opNitData.NitDataLength = 0;
    }
			   
	 
	natiInsta->OnOpNIT(opNitData);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    OnOpTune
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_OnOpTune
  (JNIEnv *env, jobject obj, jobject objOpTune)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);	
	Op_ProfileTuneData opTuneData;
	
	jfieldID fid_TuneDataLength			= NULL;		
	jfieldID fid_TuneData				= NULL;
	
	jintArray	ObjTuneDataArray;
	const int* TuneData = NULL;
	
	 
	
	jclass opNitClass  = (env)->FindClass( "org/droidtv/euinstallertc/model/mwapi/MwDataTypes$opProfileTuneData");
	
	fid_TuneDataLength	= (env)->GetFieldID (opNitClass, "TuneDataLength", "I");
	fid_TuneData		= (env)->GetFieldID (opNitClass, "TuneData", "[I");
	
	opTuneData.TuneDataLength	= (Nat16)(env)->GetIntField(objOpTune, fid_TuneDataLength);
	
	ObjTuneDataArray = (jintArray) (env)->GetObjectField(objOpTune, fid_TuneData);
	
	if (NULL != ObjTuneDataArray) 
	{
		TuneData = (int *) (env)->GetIntArrayElements(ObjTuneDataArray, 0);
        if(TuneData != NULL)
		{
			for(int i = 0; i < opTuneData.TuneDataLength; i++)
			{
				opTuneData.TuneData[i] = (Nat8)TuneData[i];
				__android_log_print(ANDROID_LOG_DEBUG,"NativeEuInstallerJNI","Tune Data of Index %d is %d",i,opTuneData.TuneData[i]);
			}
		}
    }
	else
	{
	   opTuneData.TuneDataLength = 0;
    }
			   
	 
	natiInsta->OnOpTune(opTuneData);
}


/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    StartPageDisplay
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_StartPageDisplay
  (JNIEnv *env, jobject obj)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);	
	
	 
	natiInsta->StartPageDisplay ();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNoOfMtpItems
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNoOfMtpItems
  (JNIEnv *env, jobject obj)
{
	jint	noOfMtpItems;
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);	
	
	noOfMtpItems = natiInsta->GetNoOfMtpItems ();
	
	 
	
	return noOfMtpItems;
}


/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetCursor
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetCursor
  (JNIEnv *env, jobject obj, jint index)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);	
	
	 
	natiInsta->SetCursor (index);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    RemoveCursor
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_RemoveCursor
  (JNIEnv *env, jobject obj)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);	
	
	 
	natiInsta->RemoveCursor ();
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SelectIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SelectIndex
  (JNIEnv *env, jobject obj, jint index)
{
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);	
	
	 
	natiInsta->SelectIndex(index);
}

/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetGfxHandle
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetGfxHandle
  (JNIEnv *env, jobject obj, jobject objGfxHandle)
{
	ANativeWindow *pAnw;
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);	
	
	 
	pAnw = ANativeWindow_fromSurface(env,objGfxHandle);
	
	natiInsta->SetSurface (pAnw);
}
 
	/*** TVPROVIDER IMPLEMENTATION START ***/
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetNumberOfDatabaseRecords
 * Signature: (I)I
 */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetNumberOfDatabaseRecords
  (JNIEnv *env, jobject obj, jint TSDataOnly)
{
	jint	noOfDatabaseRecords;
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);	

	noOfDatabaseRecords = natiInsta->GetNumberOfDatabaseRecords (TSDataOnly);

	 

	return noOfDatabaseRecords;
} 

/* Class:	  Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:	  setDemuxHandle
 * Signature: (J)V

 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_setDemuxHandle
(JNIEnv *env, jobject obj, jlong demuxHandle)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->setDemuxHandle(demuxHandle);

}
/* Class:	  org_droidtv_euinstallersat_model_mwapi_EuInstallerTC
 * Method:	  setVbiHandle
 * Signature: (J)V

 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_setVbiHandle
(JNIEnv *env, jobject obj, jlong vbiHandle)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->setVbiHandle(vbiHandle);
}
/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    SetFavouriteChannelListId
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_SetFavouriteChannelListId
	(JNIEnv *env, jobject obj, jint mode, jint attrib, jint index)
{
	 
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	natiInsta->SetFavouriteChannelListId(mode,attrib,index);
}


int NativeJNI::tune(jint freq, jboolean value)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
		 
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }

		
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mTune,freq,true);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		 
		natvm->DetachCurrentThread();
	}	

	return 0;
}

int NativeJNI::getValueFromTVContentProvider(jint id,int *val)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;

	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			 
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }

	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getValueFromTVContentProvider out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0;
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetValueFromContentProvider,id,result);
	}  else {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)val);
	threadEnv->DeleteLocalRef(result);
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		 
		natvm->DetachCurrentThread();
	}	
	return 0;
}

int NativeJNI::getFreq(unsigned int *arr)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }

	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreq out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
	//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreq result = %d",result);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mGetFreq,result);
	}  else {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)arr);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		 
		natvm->DetachCurrentThread();
	}	
	return 0;
}

int NativeJNI::scanStart(jint startFreq, jint endFreq, jboolean scanFor)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mScanStart,startFreq,endFreq,scanFor);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) { 
		natvm->DetachCurrentThread();
	}	

	return 0;
}

int NativeJNI::scanAbort()
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mScanAbort);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		 
		natvm->DetachCurrentThread();
	}	
	return 0;
}

int NativeJNI::scanNext()
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mScanNext);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) { 
		natvm->DetachCurrentThread();
	}	
	return 0;
}

int NativeJNI::onEvent(int eventid,int value)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mOnEvent,eventid,value);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) { 
		natvm->DetachCurrentThread();
	}
	return 0;
}


int NativeJNI::getFreqRange(unsigned int *minFreq,unsigned int *maxFreq)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }

	jintArray result;
	jintArray result1;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreqRange out of memory ");
		return false; /* out of memory error thrown */
	}
	result1 = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreqRange out of memory ");
		return false; /* out of memory error thrown */
	}

	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}

	jint fill1[1];
	for (i = 0; i < 1; i++) {
		 fill[i] = 0; 
	}

	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
	threadEnv->SetIntArrayRegion(result1, 0, 1, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mGetFreqRange,minFreq,maxFreq);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}

	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)minFreq);
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)maxFreq);
	if(isAttached) {
		 
		natvm->DetachCurrentThread();
	}
	return 0;
}

int NativeJNI::setSymbolRate(int srdetectmode,  int symbolrate)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }

	if(m_jh != NULL) {
		 
		threadEnv->CallIntMethod(m_jh, msetSymbolRate,srdetectmode,symbolrate);
	}  else {
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) { 
		natvm->DetachCurrentThread();
	}
	return 0;
}
  int  NativeJNI :: SetTvSystem (  Nat32 TvSystem,   Nat32* errorcode )
 {
	 JNIEnv *threadEnv = NULL; 
	 bool isAttached = false;
	 int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	 if (getEnvStat == JNI_EDETACHED) {
		  
		 int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		 if(res != 0) {
			 __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			 return -1;
		 } else {
			 isAttached = true;
		 }
	 } else if (getEnvStat == JNI_OK) {
		 //android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	 }else if (getEnvStat == JNI_EVERSION) {
		 //android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	 }

	 jintArray result;
	 result = threadEnv->NewIntArray(1);
	 if (result == NULL) {
		 __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreq out of memory ");
		 return false; /* out of memory error thrown */
	 }
	int i;
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
	//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreq result = %d",result);
	if(m_jh != NULL) {
		 
		threadEnv->CallIntMethod(m_jh, msetTVsystem,TvSystem,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)errorcode);
	threadEnv->DeleteLocalRef(result);
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		 
		natvm->DetachCurrentThread();
	}
	return 0;
 }
int NativeJNI ::  GetTvSystem( Nat32*  tvSystem,  Nat32* errorcode )
{
	JNIEnv *threadEnv = NULL; 
	 bool isAttached = false;
	 int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	 if (getEnvStat == JNI_EDETACHED) {
		 
		 int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		 if(res != 0) {
			 __android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			 return -1;
		 } else {
			 isAttached = true;
		 }
	 } else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	 }else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	 }


	jintArray result;
	jintArray result1;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreq out of memory1");
		return false; /* out of memory error thrown */
	}
	result1 = threadEnv->NewIntArray(1);
	if (result1 == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreq out of memory2");
		return false; /* out of memory error thrown */
	}
	int i;
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
	threadEnv->SetIntArrayRegion(result1, 0, 1, fill);
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetTVsystem,result,result1);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)tvSystem);
	threadEnv->GetIntArrayRegion(result1 , 0 , 1 , (int*)errorcode);
//_android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","gettvsystem = %d ", *tvSystem);
//_android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","gettvsystem = %d ", *errorcode);

	threadEnv->DeleteLocalRef(result);
	threadEnv->DeleteLocalRef(result1);
	if(isAttached) {
		 
		natvm->DetachCurrentThread();
	}
	return 0;	
}
int NativeJNI::setSearchRates(tmFe_SearchSymbolRate_t* searchrates,int listsize)
{
	int i = 0;
	int size = listsize;
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jobjectArray searchrate = NULL;
	
	if(listsize > 0) {
		
		jclass tuningDvbC = threadEnv->FindClass( "org/droidtv/tv/frontend/ITuningDvbC");
		if(tuningDvbC != NULL) { 
			 

			 searchrate = threadEnv->NewObjectArray(listsize, tuningDvbC, NULL);
			 
			jmethodID midDoubleInit = threadEnv->GetMethodID(tuningDvbC, "<init>", "(I)V");
			if (NULL == midDoubleInit) {
				__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","setSearchRates GetMethodID Fail");
				return -1;
			}
			 
			
			
			for(i = 0; i < size; i++) {
				jobject searchRate;
				searchRate = threadEnv->NewObject(tuningDvbC, midDoubleInit, searchrates);
		 		threadEnv->SetObjectArrayElement(searchrate, i, searchRate);
				
			} 
			
		} else {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","setSearchRates FindClass Fail");
		}
			
		if(m_jh != NULL) {
			threadEnv->CallIntMethod(m_jh, msetSearchRates,searchrate,listsize); 
		}  else {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
		}
		if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
		}
	}
	if(isAttached) { 
		natvm->DetachCurrentThread();
	}
	
	return 0;
}



int NativeJNI::getFreqStep(unsigned int *step)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreqStep out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);

	if(m_jh != NULL) {
 		 
 		threadEnv->CallIntMethod(m_jh, mGetFreqStep,result);
 	}  else {
 		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)step);
	threadEnv->DeleteLocalRef(result);
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) { 
		natvm->DetachCurrentThread();
	}

	return 0;
}


int NativeJNI::setScanStep(int step)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetScanStep,step); 
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}
	return 0;
}

int NativeJNI::getActualCodeRate(unsigned int *rate) 
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getActualCodeRate out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetActualCodeRate,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)rate);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) { 
		natvm->DetachCurrentThread();
	}
	return 0;
}

int NativeJNI::getSymbolRate(Nat32 *symbolRate)
{


	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}
	
	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getSymbolRate out of memory ");
		return false; /* out of memory error thrown */
	}
	
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
	
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetSymbolRate,result);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)symbolRate);
	//android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getSymbolRate [%d]",*symbolRate);
	
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}
	return 0;
}

int NativeJNI::getSymbolRateRange(Nat32* MinSymbolRate,Nat32* MaxSymbolRate)
{
	 
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jintArray result;
	result = threadEnv->NewIntArray(2);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getSymbolRateRange out of memory ");
		return false; /* out of memory error thrown */
	}
	
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[2];
	jint symbolRateRange[2];
	
	for (i = 0; i < 2; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 2, fill);
	
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetSymbolRateRange,result);
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getSymbolRate [%d]",symbolRate);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 2 , (int*)symbolRateRange);
	*MinSymbolRate = symbolRateRange[0];
	*MaxSymbolRate = symbolRateRange[1];
	//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getSymbolRateRange MinValue [%d] & MaxValue [%d] \n",*MinSymbolRate,*MaxSymbolRate);

	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}
	return 0;
}

int NativeJNI::setBandwidth(int bandwidth)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetBandwidth,bandwidth);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}
	return 0;
}
int NativeJNI::getActualChanBandwidth(int *bandwidth)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getActualChanBandwidth out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
//	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getActualChanBandwidth result = %d",result);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetActualChanBandwidth,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)bandwidth);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}
int NativeJNI::getTPSId(HsvDvbTParams *TPSId)
{
		
	
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getTPSId ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
    }

	jintArray result;
	result = threadEnv->NewIntArray(8);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getParams out of memory ");
		return false;
	}
	
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[8];
	jint params[8];
	
	for (i = 0; i < 8; i++) {
		 fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 8, fill);
	
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetTPSId,result);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	
	threadEnv->GetIntArrayRegion(result , 0 , 8 , (int*)params);
	threadEnv->DeleteLocalRef(result);
	
	memset (TPSId, 0x00, sizeof(HsvDvbTParams));
	
	TPSId->TPSId = params[0];
	
	//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getTPSId TPSId[%d]\n",TPSId->TPSId);
	

	if(isAttached) {
 	   natvm->DetachCurrentThread();
	}

	return 0;

}
	
int NativeJNI::setStreamPriority(int stream_prio)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}


	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetStreamPriority,stream_prio);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}

int NativeJNI::getStreamPriority(int *streamPriority)
{

	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	
	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getStreamPriority out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
		fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetStreamPriority,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)streamPriority);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}

int NativeJNI::getHierarchyMode(Bool *HierarchyMode)
{

	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	
	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getHierarchyMode out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	fill[0] = 0; 
	
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetHierarchyMode,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)HierarchyMode);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}


int NativeJNI::getActualConstellation(int *constellation)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getActualConstellation out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetActualConstellation,result);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)constellation);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}

int NativeJNI::setConstellation(int constellation)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetConstellation,constellation);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}
int NativeJNI::getBer(unsigned int *Ber)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreq out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetBer,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)Ber);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}
int NativeJNI::getCarrierPresent(Bool *Present)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}


	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreq out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetCarrierPresent,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)Present);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	
	return 0;
}
int NativeJNI::getSigStrengthRange(unsigned int *MinStrength,unsigned int *MaxStrength)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jintArray result;
	result = threadEnv->NewIntArray(2);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getSymbolRateRange out of memory ");
		return false; /* out of memory error thrown */
	}
	
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[2];
	jint SigStrengthRange[2];
	
	for (i = 0; i < 2; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 2, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetSigStrengthRange,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 2 , (int*)SigStrengthRange);
	*MinStrength = SigStrengthRange[0];
	*MaxStrength = SigStrengthRange[1];
	
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}
int NativeJNI::start(Bool *Avail)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mstart,Avail);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}
int NativeJNI::stop(Bool *Stopped)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mstop,Stopped);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}
int NativeJNI::getMeasValid(Bool *Valid)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetMeasValid,Valid);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}
int NativeJNI::getSigStrength(int ssm, unsigned int *Strength)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}
	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","getFreq out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetSigStrength,ssm,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)Strength);
	threadEnv->DeleteLocalRef(result);

	if(isAttached) {
		natvm->DetachCurrentThread();
	}
	

	return 0;
}

int NativeJNI::SourceSetupApply(int Medium)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	int retval;
	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","SourceSetupApply out of memory ");
		return false; /* out of memory error thrown */
	}
	
	// fill a temp structure to use to populate the java int array
	int i;
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
	

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msourceSetupApply,Medium,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , &retval);
	threadEnv->DeleteLocalRef(result);

	/*TODO: Check how to get the return value from Java*/
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return retval;
	
}

int NativeJNI::GetT2CarrierPresent(Bool * Present)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jbooleanArray result;
	result = threadEnv->NewBooleanArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","mGetT2CarrierPresent out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jboolean fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetBooleanArrayRegion(result, 0, 1, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mGetT2CarrierPresent,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	
	threadEnv->GetBooleanArrayRegion(result , 0 , 1 , (jboolean *)Present);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}

int  NativeJNI::GetActivePlpId(int * plpid)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetActivePlpId out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mGetActivePlpId,result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}

	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)plpid);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}


	return 0;
}

int  NativeJNI::SelectPlpId(int plpid)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mSelectPlpId,plpid);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}

int NativeJNI::GetDetectedPlpIds(int * nrOfIds,int * plpids)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}


	jintArray nrofIds;
	nrofIds = threadEnv->NewIntArray(1);
	if (nrofIds == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetDetectedPlpIds1 out of memory ");
		return false; /* out of memory error thrown */
	}
	int j;
	// fill a temp structure to use to populate the java int array
	jint fill1[1];
	for (j = 0; j < 1; j++) {
	     fill1[j] = 0; 
	}
	threadEnv->SetIntArrayRegion(nrofIds, 0, 1, fill1);
	
	
	jintArray result;
	result = threadEnv->NewIntArray(256);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetDetectedPlpIds out of memory ");
		return false; /* out of memory error thrown */
	}
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[256];
	for (i = 0; i < 256; i++) {
	     fill[i] = 0; 
	}
	threadEnv->SetIntArrayRegion(result, 0, 256, fill);

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mGetDetectedPlpIds,nrofIds, result);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is  null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	threadEnv->GetIntArrayRegion(nrofIds , 0 , 1 , (int*)nrOfIds);
	threadEnv->GetIntArrayRegion(result , 0 , 256 , (int*)plpids);

	threadEnv->DeleteLocalRef(nrofIds);
	threadEnv->DeleteLocalRef(result);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

	return 0;
}
void  NativeJNI :: RequestNit(void)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return ;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}


	if(m_jh != NULL) {
		threadEnv->CallVoidMethod(m_jh, mRequestNit);
	}  else {
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

}

void  NativeJNI :: RequestStatusInfo(void)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return ;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallVoidMethod(m_jh, mRequestStatusInfo);
	}  else {
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

}

void  NativeJNI :: SendOpExit(void)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return ;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallVoidMethod(m_jh, mSendOpExit);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

}

void  NativeJNI :: SendOpAck(void)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return ;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}
	if(m_jh != NULL) {
		
		threadEnv->CallVoidMethod(m_jh, mSendOpAck);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	};
}

void  NativeJNI :: SendOpSearchCancel(void)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return ;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallVoidMethod(m_jh, mSendOpSearchCancel);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) { 
		natvm->DetachCurrentThread();
	}

}

void  NativeJNI :: CacheOperatorData(void)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		 
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return ;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	if(m_jh != NULL) {
		threadEnv->CallVoidMethod(m_jh, mCacheOperatorData);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

}
void  NativeJNI :: SendOperatorSearchStart(Op_Search_Settings searchstart)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return ;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}

	int i=0;
	int tempServiceTypeArray[256];
	int tempDeliveryTypeArray[256];
	int tempApplicationTypeArray[256];
	for( i=0;i<searchstart.Service_Type_Length;i++)
		tempServiceTypeArray[i] = searchstart.Service_Type[i];
	for( i=0;i<searchstart.Delivery_Cap_Length;i++)
		tempDeliveryTypeArray[i] = searchstart.Delivery_Capability[i];
	for( i=0;i<searchstart.Application_Cap_Length;i++)
		tempApplicationTypeArray[i] = searchstart.Application_Capability[i];
	

	//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","SearchStart Values  Unattented Flag = %d AppLength Flag = %d Delivery Length Flag = %d ServiceType Length Flag = %d",searchstart.Unattended_Flag,searchstart.Application_Cap_Length,searchstart.Delivery_Cap_Length,searchstart.Service_Type_Length);
	
	jintArray servicetype = NULL;
	servicetype = threadEnv->NewIntArray(searchstart.Service_Type_Length);
	if (servicetype == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Service_Type out of memory ");

	}
	//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Service_Type result = %x",servicetype);
	
	
	threadEnv->SetIntArrayRegion(servicetype, 0, searchstart.Service_Type_Length, (jint*)tempServiceTypeArray);

	//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Service_Type result = %d",servicetype);

	jintArray appCapability;
	appCapability = threadEnv->NewIntArray(searchstart.Application_Cap_Length);
	if (appCapability == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","appCapability out of memory ");

	}

	threadEnv->SetIntArrayRegion(appCapability, 0, searchstart.Application_Cap_Length, (jint*)tempApplicationTypeArray);
//	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","appCapability result = %d",appCapability);
	jintArray Deliverysystem;
	Deliverysystem = threadEnv->NewIntArray(searchstart.Delivery_Cap_Length);
	if (Deliverysystem == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Deliverysystem out of memory ");

	}

	threadEnv->SetIntArrayRegion(Deliverysystem, 0, searchstart.Delivery_Cap_Length, (jint*)tempDeliveryTypeArray);
//	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Deliverysystem result = %d",Deliverysystem);
	if(m_jh != NULL) {
		threadEnv->CallVoidMethod(m_jh, mSendOperatorSearchStart, searchstart.Unattended_Flag, searchstart.Service_Type_Length, servicetype, searchstart.Delivery_Cap_Length, Deliverysystem, searchstart.Application_Cap_Length, appCapability);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}
		
	threadEnv->DeleteLocalRef(servicetype);
	threadEnv->DeleteLocalRef(appCapability);
	threadEnv->DeleteLocalRef(Deliverysystem);

	if(isAttached) {
		
		natvm->DetachCurrentThread();
	}

}

void  NativeJNI :: SendOpTuneStatus(Op_Tune_Status tuneStatus)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","Failed to attach getFreq ");
			return ;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv: version not supported");
	}
	int tempDataArray[1024],i=0;
	for( i=0;i<tuneStatus.Descriptor_Loop_Length;i++)
	{
		tempDataArray[i] = tuneStatus.Descriptor_Loop[i];
		//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","%x",tempDataArray[i] );
		
	}
	//__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","SendOpTuneStatus Values  Desc Number = %d Desc Loop length = %d Signal strength = %d Signal Quality= %d Status= %d",tuneStatus.Descriptor_Number,tuneStatus.Descriptor_Loop_Length,tuneStatus.Signal_Strength,tuneStatus.Signal_Quality,tuneStatus.Status);
	jintArray TuneDescriptor;
	TuneDescriptor = threadEnv->NewIntArray(tuneStatus.Descriptor_Loop_Length);
	if (TuneDescriptor == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","TuneDesc out of memory ");

	}
	
	threadEnv->SetIntArrayRegion(TuneDescriptor, 0, tuneStatus.Descriptor_Loop_Length, (jint*)tempDataArray);
//	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","TuneDesc result = %d",TuneDescriptor);
	if(m_jh != NULL) {
		threadEnv->CallVoidMethod(m_jh, mSendOpTuneStatus, tuneStatus.Descriptor_Number, tuneStatus.Signal_Strength, tuneStatus.Signal_Quality, tuneStatus.Status, tuneStatus.Descriptor_Loop_Length, TuneDescriptor);
	}  else {
	__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	};
	threadEnv->DeleteLocalRef(TuneDescriptor);
	if(isAttached) {
		natvm->DetachCurrentThread();
	}

}


/*
 * Class:     org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:    GetTvProviderBlobDataByIndex
 * Signature: (II)Lorg/droidtv/euinstallertc/model/mwapi/TcInstallerTvProviderData;
 */
JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_GetTvProviderBlobDataByIndex
  (JNIEnv *env, jobject obj, jint Index, jint TSDataOnly)
{
	jobject  ObjectId = NULL;
	HsvPgdatTvProviderBlobData TvpData;
	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	jchar	ServiceName[MAXSERVICENAMELEN + 2];
	jchar	TxtPages[24];
	jint	BrandIds[23];
	jint	MultipleLCN[8];
	jint	MultiplePreset[8];
	jint	MultipleFavorite[8];
	
	
	jchar	Temp[1] = {'t'};
	jint	i = 0;
	jsize	StringLen = 0;
	jstring	ServiceNameConverted = NULL, TxtPagesConverted = NULL;
	jintArray ArrayBrandIds = NULL;
	jintArray ArrayMultipleLCN = NULL;
	jintArray ArrayMultiplePreset = NULL;
	jintArray ArrayMultipleFavorite = NULL;

	jstring TempString = env->NewString(Temp,1);
	jintArray TempArray = env->NewIntArray(8);
	
	
	natiInsta->GetTvProviderBlobDataByIndex(Index,(Address)&TvpData,NULL,TSDataOnly);


	if(!TSDataOnly)
	{
		/* Convert ChannelName to jString */
		for (i =0; i < (MAXSERVICENAMELEN +2); i++) {
			ServiceName[i] = '\0';
		}

		for (i=0; (i<(MAXSERVICENAMELEN + 1)&& (TvpData.ChannelName[i])); i++) {
			if (TvpData.ChannelName[i] != 0) {
				ServiceName[StringLen] = TvpData.ChannelName[i];
				StringLen++;
			}
		}

		if (StringLen > 0) {
			ServiceNameConverted = env->NewString(ServiceName,StringLen);
		}
		
		/* Convert TxtPages to jstring */
		StringLen = 0;
		for (i =0; i < 24; i++) {
			TxtPages[i] = '\0';
		}
		for (i=0; i<23; i++) {
			if (TvpData.TxtPages[i] != 0) {
				TxtPages[StringLen] = TvpData.TxtPages[i];
				StringLen++;
			}
		}
		
		if (StringLen > 0) {
			TxtPagesConverted = env->NewString(TxtPages,StringLen);
		}


		/* Convert BrandIds to jintArray */
		for (i=0; i<23; i++) {
			BrandIds[StringLen] = TvpData.BrandIds[i];
		}
		 ArrayBrandIds = env->NewIntArray(23);
		 env->SetIntArrayRegion(ArrayBrandIds, 0, 23, BrandIds);

		
		
		/* Convert MultipleLCN to jintArray */
		for (i=0; i<8; i++) {
			MultipleLCN[i] = TvpData.MultipleLCN[i];
		}
		ArrayMultipleLCN = env->NewIntArray(8);

		env->SetIntArrayRegion(ArrayMultipleLCN, 0, 8, MultipleLCN);
		

		/* Convert MultiplePreset to jintArray */
		for (i=0; i<8; i++) {
			MultiplePreset[i] = TvpData.MultiplePreset[i];
		}
		ArrayMultiplePreset = env->NewIntArray(8);

		env->SetIntArrayRegion(ArrayMultiplePreset, 0, 8, MultiplePreset);

	
		/* Convert MultipleFavorite to jintArray */

		for (i=0; i<8; i++) {
			MultipleFavorite[i] = TvpData.MultipleFavorite[i];
		}
		ArrayMultipleFavorite = env->NewIntArray(8);

		env->SetIntArrayRegion(ArrayMultipleFavorite, 0, 8, MultipleFavorite);

	}
	
	

	jclass  TvProvClassID = (env)->FindClass("org/droidtv/euinstallertc/model/mwapi/TcInstallerTvProviderData");
	if(TvProvClassID != NULL) {
			jmethodID cid = (env)->GetMethodID(TvProvClassID, "<init>", "(IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIILjava/lang/String;Ljava/lang/String;[I[I[I[I)V");
			if (cid == NULL) {
					__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI", "GetTvProviderBlobDataByIndex GetMethodID Failed ");
					return NULL; // exception thrown
			} else {
					if(!TSDataOnly){
						ObjectId = (env)->NewObject(TvProvClassID, cid, TvpData.UniqueId, TvpData.PresetNumber, TvpData.OriginalNetworkId, TvpData.Tsid, TvpData.ServiceId,  TvpData.Frequency, 
							TvpData.TextSubTitlePage, 	TvpData.LogoURL, TvpData.DecoderType, TvpData.ModulationType,TvpData.UserModifiedLogo,
							TvpData.SAP, TvpData.PreferredStereo, TvpData.Ptc, TvpData.SymbolRate, TvpData.StreamPriority,  
							TvpData.AudioPid, TvpData.VideoPid, TvpData.PcrPid, TvpData.NetworkId, TvpData.LCN, 
							TvpData.ServiceType, TvpData.SystemHidden, TvpData.NumericSelect, TvpData.Bandwidth, TvpData.ScrambledStatus, 
							TvpData.IntHbbTvOption, TvpData.UserHidden, TvpData.NewPreset, TvpData.VideoStreamType, TvpData.AudioStreamType, 
							TvpData.CniNi, 
							TvpData.SignalStrength, TvpData.SignalQuality, TvpData.SDTVersion, TvpData.NITVersion, 
							TvpData.DateStamp, TvpData.DeltaVolume, TvpData.PmtPid, TvpData.SecAudioPid, TvpData.LowPrioLCN, TvpData.LowPrioVisibleService,
							TvpData.FreeCiMode,	TvpData.VideoDescPresent, TvpData.VisibleService, TvpData.OUI, TvpData.ServiceListVersion, TvpData.UserInstalled,
							TvpData.SecAudioStreamType, TvpData.UserModifiedName, TvpData.PreferredNicam, TvpData.MatchBrandFlag, TvpData.NumBrandIds,
							TvpData.SrcambledStatus, TvpData.RegionDepth, TvpData.PrimaryRegion, TvpData.SecondaryRegion, TvpData.TertiaryRegion,
							TvpData.CountryCode, TvpData.HDSimulcastRepOnId, TvpData.HDSimulcastRepTsId, TvpData.HDSimulcastRepSvcId, TvpData.FavoriteNumber,
							TvpData.FineTuneFrequency, TvpData.FineTuneOffset, TvpData.ColourSystem, TvpData.DataIndicator,
							TvpData.Attenuator, TvpData.Tuned, TvpData.DeTuned, TvpData.AgcInstalled, TvpData.PreferredFavorite, TvpData.ASignalStrength,
							TvpData.VSignalStrength, TvpData.QSignalStrength, TvpData.CDSDFrequency, TvpData.CodeRate, TvpData.HierarchyMode,
							TvpData.GuardInterval, TvpData.PtcListVersion, TvpData.TSVersion, TvpData.BarkerMux, TvpData.AnalogTablePreset, TvpData.Type, TvpData.LanguageCode,
							ServiceNameConverted, TxtPagesConverted,ArrayBrandIds,ArrayMultipleLCN,ArrayMultiplePreset,ArrayMultipleFavorite);   			
					}
					else{
						ObjectId = (env)->NewObject(TvProvClassID, cid, TvpData.UniqueId, TvpData.PresetNumber, TvpData.OriginalNetworkId, TvpData.Tsid, TvpData.ServiceId,  TvpData.Frequency, 
							TvpData.TextSubTitlePage, 	TvpData.LogoURL, TvpData.DecoderType, TvpData.ModulationType,TvpData.UserModifiedLogo,
							TvpData.SAP, TvpData.PreferredStereo, TvpData.Ptc, TvpData.SymbolRate, TvpData.StreamPriority,  
							TvpData.AudioPid, TvpData.VideoPid, TvpData.PcrPid, TvpData.NetworkId, TvpData.LCN, 
							TvpData.ServiceType, TvpData.SystemHidden, TvpData.NumericSelect, TvpData.Bandwidth, TvpData.ScrambledStatus, 
							TvpData.IntHbbTvOption, TvpData.UserHidden, TvpData.NewPreset, TvpData.VideoStreamType, TvpData.AudioStreamType, 
							TvpData.CniNi, 
							TvpData.SignalStrength, TvpData.SignalQuality, TvpData.SDTVersion, TvpData.NITVersion, 
							TvpData.DateStamp, TvpData.DeltaVolume, TvpData.PmtPid, TvpData.SecAudioPid, TvpData.LowPrioLCN, TvpData.LowPrioVisibleService,
							TvpData.FreeCiMode,	TvpData.VideoDescPresent, TvpData.VisibleService, TvpData.OUI, TvpData.ServiceListVersion, TvpData.UserInstalled,
							TvpData.SecAudioStreamType, TvpData.UserModifiedName, TvpData.PreferredNicam, TvpData.MatchBrandFlag, TvpData.NumBrandIds,
							TvpData.SrcambledStatus, TvpData.RegionDepth, TvpData.PrimaryRegion, TvpData.SecondaryRegion, TvpData.TertiaryRegion,
							TvpData.CountryCode, TvpData.HDSimulcastRepOnId, TvpData.HDSimulcastRepTsId, TvpData.HDSimulcastRepSvcId, TvpData.FavoriteNumber,
							TvpData.FineTuneFrequency, TvpData.FineTuneOffset, TvpData.ColourSystem, TvpData.DataIndicator,
							TvpData.Attenuator, TvpData.Tuned, TvpData.DeTuned, TvpData.AgcInstalled, TvpData.PreferredFavorite, TvpData.ASignalStrength,
							TvpData.VSignalStrength, TvpData.QSignalStrength, TvpData.CDSDFrequency, TvpData.CodeRate, TvpData.HierarchyMode,
							TvpData.GuardInterval, TvpData.PtcListVersion, TvpData.TSVersion, TvpData.BarkerMux, TvpData.AnalogTablePreset, TvpData.Type, TvpData.LanguageCode,
							TempString, TempString,TempArray,TempArray,TempArray,TempArray);   
					}
			}
	} else {
			__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI", "GetTvProviderBlobDataByIndex FindClass Failed ");
	}
	
	return ObjectId;
}

/*
 * Class:	  org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:	  PopulateMW
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_PopulateMW
  (JNIEnv *env, jobject obj, jobject objTvpData, jint Clear)
{

	NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
	HsvPgdatTvProviderBlobData TvpData;

	if(!Clear)
	{
		jstring ObjChannelName;
		jstring	ObjTxtPages;
		jintArray	ObjBrandIds;
		jintArray	ObjMultipleLCN;
		jintArray	ObjMultiplePreset;
		jintArray	ObjMultipleFavorite;

		const jchar* ChannelName = NULL;
		const jchar* TxtPages	= NULL;
		const jint* BrandIds	= NULL;
		const jint* MultipleLCN	= NULL;
		const jint* MultiplePreset	= NULL;
		const jint* MultipleFavorite	= NULL;


		#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      	jfieldID fid_##item = NULL;
		#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, ana, srv, ts)      	jfieldID fid_##item = NULL;
		#define TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)      	jfieldID fid_##item = NULL;
		#define TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)      jfieldID fid_##item = NULL;
		#define TVPROVIDER_ANALOG_ITEM(item, type, bit, siz, def)      	jfieldID fid_##item = NULL;
		#define TVPROVIDER_COMMON_VECTOR_ITEM(item, type, bit, siz, def)		jfieldID fid_##item = NULL;
		#define TVPROVIDER_DIGSRVC_VECTOR_ITEM(item, type, bit, siz, def)      	jfieldID fid_##item = NULL;


		#include "hsvpgdat_tvproviderblobdata.h"
		
		#undef  TVPROVIDER_PRESET_ITEM
		#undef  TVPROVIDER_DIGSRVC_ITEM
		#undef 	TVPROVIDER_ANALOG_ITEM
		#undef 	TVPROVIDER_COMMON_ITEM
		#undef 	TVPROVIDER_DIGTS_ITEM
		#undef	TVPROVIDER_COMMON_VECTOR_ITEM
		#undef	TVPROVIDER_DIGSRVC_VECTOR_ITEM

		
		jclass TcInstallerTvProviderDataClass	= (env)->FindClass( "org/droidtv/euinstallertc/model/mwapi/TcInstallerTvProviderData");

		fid_PresetNumber = (env)->GetFieldID (TcInstallerTvProviderDataClass, "PresetNumber", "I");
		
		fid_OriginalNetworkId = (env)->GetFieldID (TcInstallerTvProviderDataClass, "OriginalNetworkId", "I");
		fid_Tsid = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Tsid", "I");
		fid_ServiceId = (env)->GetFieldID (TcInstallerTvProviderDataClass, "ServiceId", "I");
		fid_Frequency = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Frequency", "I"); 
		fid_TextSubTitlePage = (env)->GetFieldID (TcInstallerTvProviderDataClass, "TextSubTitlePage", "I");
		fid_LogoURL = (env)->GetFieldID (TcInstallerTvProviderDataClass, "LogoURL", "I");
		fid_DecoderType = (env)->GetFieldID (TcInstallerTvProviderDataClass, "DecoderType", "I");
		fid_ModulationType = (env)->GetFieldID (TcInstallerTvProviderDataClass, "ModulationType", "I");
		fid_UserModifiedLogo = (env)->GetFieldID (TcInstallerTvProviderDataClass, "UserModifiedLogo", "I");
		fid_SAP = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SAP", "I"); 
		fid_PreferredStereo = (env)->GetFieldID (TcInstallerTvProviderDataClass, "PreferredStereo", "I"); 
		fid_Ptc = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Ptc", "I"); 
		fid_SymbolRate = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SymbolRate", "I");
		fid_StreamPriority = (env)->GetFieldID (TcInstallerTvProviderDataClass, "StreamPriority", "I"); 
		fid_AudioPid = (env)->GetFieldID (TcInstallerTvProviderDataClass, "AudioPid", "I"); 
		fid_VideoPid = (env)->GetFieldID (TcInstallerTvProviderDataClass, "VideoPid", "I"); 
		fid_PcrPid = (env)->GetFieldID (TcInstallerTvProviderDataClass, "PcrPid", "I"); 
		fid_NetworkId = (env)->GetFieldID (TcInstallerTvProviderDataClass, "NetworkId", "I"); 
		fid_LCN = (env)->GetFieldID (TcInstallerTvProviderDataClass, "LCN", "I"); 
		fid_ServiceType = (env)->GetFieldID (TcInstallerTvProviderDataClass, "ServiceType", "I"); 
		fid_SystemHidden = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SystemHidden", "I"); 
		fid_NumericSelect = (env)->GetFieldID (TcInstallerTvProviderDataClass, "NumericSelect", "I"); 
		fid_Bandwidth = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Bandwidth", "I"); 
		fid_ScrambledStatus = (env)->GetFieldID (TcInstallerTvProviderDataClass, "ScrambledStatus", "I"); 
		fid_IntHbbTvOption = (env)->GetFieldID (TcInstallerTvProviderDataClass, "IntHbbTvOption", "I"); 
		fid_UserHidden = (env)->GetFieldID (TcInstallerTvProviderDataClass, "UserHidden", "I"); 
		fid_NewPreset = (env)->GetFieldID (TcInstallerTvProviderDataClass, "NewPreset", "I"); 
		fid_VideoStreamType = (env)->GetFieldID (TcInstallerTvProviderDataClass, "VideoStreamType", "I"); 
		fid_AudioStreamType = (env)->GetFieldID (TcInstallerTvProviderDataClass, "AudioStreamType", "I"); 
		fid_CniNi = (env)->GetFieldID (TcInstallerTvProviderDataClass, "CniNi", "I"); 
		fid_SignalStrength = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SignalStrength", "I"); 
		fid_SignalQuality = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SignalQuality", "I"); 
		fid_SDTVersion = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SDTVersion", "I"); 
		fid_NITVersion = (env)->GetFieldID (TcInstallerTvProviderDataClass, "NITVersion", "I"); 
		fid_DateStamp = (env)->GetFieldID (TcInstallerTvProviderDataClass, "DateStamp", "I"); 
		fid_DeltaVolume = (env)->GetFieldID (TcInstallerTvProviderDataClass, "DeltaVolume", "I"); 
		fid_PmtPid = (env)->GetFieldID (TcInstallerTvProviderDataClass, "PmtPid", "I"); 
		fid_SecAudioPid = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SecAudioPid", "I"); 
		fid_LowPrioLCN = (env)->GetFieldID (TcInstallerTvProviderDataClass, "LowPrioLCN", "I"); 
		fid_LowPrioVisibleService = (env)->GetFieldID (TcInstallerTvProviderDataClass, "LowPrioVisibleService", "I");
		fid_FreeCiMode = (env)->GetFieldID (TcInstallerTvProviderDataClass, "FreeCiMode", "I");	
		fid_VideoDescPresent = (env)->GetFieldID (TcInstallerTvProviderDataClass, "VideoDescPresent", "I"); 
		fid_VisibleService = (env)->GetFieldID (TcInstallerTvProviderDataClass, "VisibleService", "I"); 
		fid_OUI = (env)->GetFieldID (TcInstallerTvProviderDataClass, "OUI", "I"); 
		fid_ServiceListVersion = (env)->GetFieldID (TcInstallerTvProviderDataClass, "ServiceListVersion", "I"); 
		fid_UserInstalled = (env)->GetFieldID (TcInstallerTvProviderDataClass, "UserInstalled", "I");
		fid_SecAudioStreamType = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SecAudioStreamType", "I"); 
		fid_UserModifiedName = (env)->GetFieldID (TcInstallerTvProviderDataClass, "UserModifiedName", "I"); 
		fid_PreferredNicam = (env)->GetFieldID (TcInstallerTvProviderDataClass, "PreferredNicam", "I"); 
		fid_MatchBrandFlag = (env)->GetFieldID (TcInstallerTvProviderDataClass, "MatchBrandFlag", "I"); 
		fid_NumBrandIds = (env)->GetFieldID (TcInstallerTvProviderDataClass, "NumBrandIds", "I");
		fid_SrcambledStatus = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SrcambledStatus", "I"); 
		fid_RegionDepth = (env)->GetFieldID (TcInstallerTvProviderDataClass, "RegionDepth", "I"); 
		fid_PrimaryRegion = (env)->GetFieldID (TcInstallerTvProviderDataClass, "PrimaryRegion", "I"); 
		fid_SecondaryRegion = (env)->GetFieldID (TcInstallerTvProviderDataClass, "SecondaryRegion", "I"); 
		fid_TertiaryRegion = (env)->GetFieldID (TcInstallerTvProviderDataClass, "TertiaryRegion", "I");
		fid_CountryCode = (env)->GetFieldID (TcInstallerTvProviderDataClass, "CountryCode", "I"); 
		fid_HDSimulcastRepOnId = (env)->GetFieldID (TcInstallerTvProviderDataClass, "HDSimulcastRepOnId", "I"); 
		fid_HDSimulcastRepTsId = (env)->GetFieldID (TcInstallerTvProviderDataClass, "HDSimulcastRepTsId", "I"); 
		fid_HDSimulcastRepSvcId = (env)->GetFieldID (TcInstallerTvProviderDataClass, "HDSimulcastRepSvcId", "I"); 
		fid_FavoriteNumber = (env)->GetFieldID (TcInstallerTvProviderDataClass, "FavoriteNumber", "I");
		fid_FineTuneFrequency = (env)->GetFieldID (TcInstallerTvProviderDataClass, "FineTuneFrequency", "I"); 
		fid_FineTuneOffset = (env)->GetFieldID (TcInstallerTvProviderDataClass, "FineTuneOffset", "I"); 
		fid_ColourSystem = (env)->GetFieldID (TcInstallerTvProviderDataClass, "ColourSystem", "I"); 
		fid_DataIndicator = (env)->GetFieldID (TcInstallerTvProviderDataClass, "DataIndicator", "I");
		fid_Attenuator = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Attenuator", "I"); 
		fid_Tuned = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Tuned", "I"); 
		fid_DeTuned = (env)->GetFieldID (TcInstallerTvProviderDataClass, "DeTuned", "I"); 
		fid_AgcInstalled = (env)->GetFieldID (TcInstallerTvProviderDataClass, "AgcInstalled", "I"); 
		fid_PreferredFavorite = (env)->GetFieldID (TcInstallerTvProviderDataClass, "PreferredFavorite", "I"); 
		fid_ASignalStrength = (env)->GetFieldID (TcInstallerTvProviderDataClass, "ASignalStrength", "I");
		fid_VSignalStrength = (env)->GetFieldID (TcInstallerTvProviderDataClass, "VSignalStrength", "I"); 
		fid_QSignalStrength = (env)->GetFieldID (TcInstallerTvProviderDataClass, "QSignalStrength", "I"); 
		fid_CDSDFrequency = (env)->GetFieldID (TcInstallerTvProviderDataClass, "CDSDFrequency", "I"); 
		fid_CodeRate = (env)->GetFieldID (TcInstallerTvProviderDataClass, "CodeRate", "I"); 
		fid_HierarchyMode = (env)->GetFieldID (TcInstallerTvProviderDataClass, "HierarchyMode", "I");
		fid_GuardInterval = (env)->GetFieldID (TcInstallerTvProviderDataClass, "GuardInterval", "I"); 
		fid_PtcListVersion = (env)->GetFieldID (TcInstallerTvProviderDataClass, "PtcListVersion", "I"); 
		fid_TSVersion = (env)->GetFieldID (TcInstallerTvProviderDataClass, "TSVersion", "I"); 
		fid_BarkerMux = (env)->GetFieldID (TcInstallerTvProviderDataClass, "BarkerMux", "I"); 
		fid_AnalogTablePreset = (env)->GetFieldID (TcInstallerTvProviderDataClass, "AnalogTablePreset", "I"); 
		fid_Type = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Type", "I");
		fid_LanguageCode = (env)->GetFieldID (TcInstallerTvProviderDataClass, "LanguageCode", "I");

        fid_UniqueId =  (env)->GetFieldID (TcInstallerTvProviderDataClass, "UniqueId", "I");

		fid_ChannelName = 	(env)->GetFieldID (TcInstallerTvProviderDataClass, "ChannelName", "Ljava/lang/String;");
		fid_TxtPages = 	(env)->GetFieldID (TcInstallerTvProviderDataClass, "TxtPages", "Ljava/lang/String;");
		fid_BrandIds = 	(env)->GetFieldID (TcInstallerTvProviderDataClass, "BrandIds", "[I");
		fid_MultipleLCN = 	(env)->GetFieldID (TcInstallerTvProviderDataClass, "MultipleLCN", "[I");
		fid_MultiplePreset = 	(env)->GetFieldID (TcInstallerTvProviderDataClass, "MultiplePreset", "[I");
		fid_MultipleFavorite = (env)->GetFieldID (TcInstallerTvProviderDataClass, "MultipleFavorite", "[I");
	
		#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
		#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, ana, srv, ts)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
		#define TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
		#define TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
		#define TVPROVIDER_ANALOG_ITEM(item, type, bit, siz, def)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
		#define TVPROVIDER_COMMON_VECTOR_ITEM(item, type, bit, siz, def)
		#define TVPROVIDER_DIGSRVC_VECTOR_ITEM(item, type, bit, siz, def)

		#include "hsvpgdat_tvproviderblobdata.h"
		
		#undef	TVPROVIDER_PRESET_ITEM
		#undef	TVPROVIDER_DIGSRVC_ITEM
		#undef	TVPROVIDER_ANALOG_ITEM
		#undef	TVPROVIDER_COMMON_ITEM
		#undef	TVPROVIDER_DIGTS_ITEM
		#undef	TVPROVIDER_COMMON_VECTOR_ITEM
		#undef	TVPROVIDER_DIGSRVC_VECTOR_ITEM


		//UniqueId
		TvpData.UniqueId = (Nat32)(env)->GetIntField(objTvpData, fid_UniqueId);


		/*Channel Name*/
		
		ObjChannelName = (jstring)(env)->GetObjectField(objTvpData, fid_ChannelName);

		if(NULL != ObjChannelName) 
		{

			int  index = 0;
			int length = (env)->GetStringLength(ObjChannelName);
			
			memset (TvpData.ChannelName, 0x00, sizeof(TvpData.ChannelName));


			index = 0;
			ChannelName = (jchar *) (env)->GetStringChars(ObjChannelName, NULL);
	        if(ChannelName != NULL)
			{
				for(index = 0; (index < length) && (index < (MAXSERVICENAMELEN + 1)) ; index++)
				{
					TvpData.ChannelName[index] = ChannelName[index];
				}
			}
			if( index < (MAXSERVICENAMELEN + 1))
			{
				TvpData.ChannelName[index] = '\0';
			}

			/*TODO: remove extra prints*/
			const jbyte *str;
			str = (jbyte *)(env)->GetStringUTFChars(ObjChannelName, NULL);
			
	    }
		else
		{
			//__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI", "ERROR: ChannelName is NULL");
		}


		
		/* TxtPages */	
		
		ObjTxtPages = (jstring) (env)->GetObjectField(objTvpData, fid_TxtPages);


		if(NULL != ObjTxtPages) 
		{
		
			int length = (env)->GetStringLength(ObjTxtPages);
			
			memset (TvpData.TxtPages, 0x00, sizeof(TvpData.TxtPages));
			
			int  i = 0;
			TxtPages = (jchar *) (env)->GetStringChars(ObjTxtPages, NULL);
	        if(TxtPages != NULL)
			{
				for(i = 0; (i < length) && (i < 23) ; i++)
				{
					TvpData.TxtPages[i] = TxtPages[i];
				}
			}
			if( i < 23)
			{
				TvpData.TxtPages[i] = '\0';
			}

			/*TODO: remove extra prints*/
			const jbyte *str;
			str = (jbyte *)(env)->GetStringUTFChars(ObjTxtPages, NULL);
			
	    }
		else
		{
			//__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI", "ERROR: ObjTxtPages is NULL");
		}

		/* BrandIds */
		
		ObjBrandIds = (jintArray) (env)->GetObjectField(objTvpData, fid_BrandIds);
		
		if(NULL != ObjBrandIds) 
		{
		
			int length = (env)->GetArrayLength(ObjBrandIds);
			
			int  i = 0;
			BrandIds = (jint *) (env)->GetIntArrayElements(ObjBrandIds, NULL);
	        if(BrandIds != NULL)
			{
				for(i = 0; (i < length) && (i < 23) ; i++)
				{
					TvpData.BrandIds[i] = BrandIds[i];
				}
			}
			
			
	    }
		else
		{
			//__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI", "ERROR: ObjBrandIds is NULL");
		}

		/* MultipleLCN */
		
		ObjMultipleLCN = (jintArray) (env)->GetObjectField(objTvpData, fid_MultipleLCN);
		
		if(NULL != ObjMultipleLCN) 
		{
		
			int length = (env)->GetArrayLength(ObjMultipleLCN);
			
			int  i = 0;
			MultipleLCN = (jint *) (env)->GetIntArrayElements(ObjMultipleLCN, NULL);
	        if(MultipleLCN != NULL)
			{
				for(i = 0; (i < length) && (i < 8) ; i++)
				{
					TvpData.MultipleLCN[i] = MultipleLCN[i];
				}
			}
			
	    }
		else
		{
			//__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI", "ERROR: ObjMultipleLCN is NULL");
		}

		/* MultiplePreset */
		
		ObjMultiplePreset = (jintArray) (env)->GetObjectField(objTvpData, fid_MultiplePreset);
		
		if(NULL != ObjMultiplePreset) 
		{
		
			int length = (env)->GetArrayLength(ObjMultiplePreset);

			int  i = 0;
			MultiplePreset = (jint *) (env)->GetIntArrayElements(ObjMultiplePreset, NULL);
	        if(MultiplePreset != NULL)
			{
				for(i = 0; (i < length) && (i < 8) ; i++)
				{
					TvpData.MultiplePreset[i] = MultiplePreset[i];
				}
			}
			
	    }
		else
		{
			//__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI", "ERROR: ObjMultiplePreset is NULL");
		}


		/* MultipleFavorite */
		
		ObjMultipleFavorite = (jintArray) (env)->GetObjectField(objTvpData, fid_MultipleFavorite);

		
		if(NULL != ObjMultipleFavorite) 
		{
		
			int length = (env)->GetArrayLength(ObjMultipleFavorite);
		
			int  i = 0;
			MultipleFavorite = (jint *) (env)->GetIntArrayElements(ObjMultipleFavorite, NULL);
	        if(MultipleFavorite != NULL)
			{
				for(i = 0; (i < length) && (i < 8) ; i++)
				{
					TvpData.MultipleFavorite[i] = MultipleFavorite[i];
				}
			}
			
	    }
		else
		{
			//__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI", "ERROR: ObjMultipleFavorite is NULL");
		}

		natiInsta->AddTvpData(&TvpData,Clear);
	}
	else
	{
		natiInsta->AddTvpData(&TvpData,Clear);
	}

}

/*
 * Class:	  org_droidtv_euinstallertc_model_mwapi_EuInstallerTC
 * Method:	  syncUniqueIdToMW
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallertc_model_mwapi_EuInstallerTC_syncUniqueIdToMW
	(JNIEnv *env, jobject obj, jobject tvpDataObj)
{

    NativeInstaller* natiInsta = reinterpret_cast<NativeInstaller*>(jh);
    HsvPgdatTvProviderBlobData TvpData;

    jclass TcInstallerTvProviderDataClass = NULL;
    jintArray	ObjMultiplePreset;
    const jint* MultiplePreset	= NULL;

    jfieldID fid_OriginalNetworkId	= NULL;
    jfieldID fid_Tsid	= NULL;
    jfieldID fid_ServiceId	= NULL;
    jfieldID fid_Frequency	= NULL;
    jfieldID fid_StreamPriority	= NULL;
    jfieldID fid_PresetNumber	= NULL;
    jfieldID fid_UniqueId	= NULL;
    jfieldID fid_MultiplePreset	= NULL;
    jfieldID fid_Type	= NULL;
    jfieldID fid_AnalogTablePreset = NULL;

    TcInstallerTvProviderDataClass = (env)->FindClass( "org/droidtv/euinstallertc/model/mwapi/TcInstallerTvProviderData");

    fid_OriginalNetworkId = (env)->GetFieldID (TcInstallerTvProviderDataClass, "OriginalNetworkId", "I");
    fid_Tsid = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Tsid", "I");
    fid_ServiceId = (env)->GetFieldID (TcInstallerTvProviderDataClass, "ServiceId", "I");
    fid_Frequency = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Frequency", "I");
    fid_StreamPriority = (env)->GetFieldID (TcInstallerTvProviderDataClass, "StreamPriority", "I");
    fid_PresetNumber = (env)->GetFieldID (TcInstallerTvProviderDataClass, "PresetNumber", "I");
   // fid_Type = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Type", "I");
    fid_UniqueId = (env)->GetFieldID (TcInstallerTvProviderDataClass, "UniqueId", "I");
    fid_MultiplePreset = (env)->GetFieldID (TcInstallerTvProviderDataClass, "MultiplePreset", "[I");
    fid_Type = (env)->GetFieldID (TcInstallerTvProviderDataClass, "Type", "I");
    fid_AnalogTablePreset = (env)->GetFieldID (TcInstallerTvProviderDataClass, "AnalogTablePreset", "I"); 

    TvpData.OriginalNetworkId = (Nat16)(env)->GetIntField(tvpDataObj, fid_OriginalNetworkId);
    TvpData.Tsid = (Nat16)(env)->GetIntField(tvpDataObj, fid_Tsid);
    TvpData.ServiceId = (Nat16)(env)->GetIntField(tvpDataObj, fid_ServiceId);
    TvpData.Frequency = (Nat32)(env)->GetIntField(tvpDataObj, fid_Frequency);
    TvpData.StreamPriority = (Nat16)(env)->GetIntField(tvpDataObj, fid_StreamPriority);
    TvpData.PresetNumber = (Nat16)(env)->GetIntField(tvpDataObj, fid_PresetNumber);
    TvpData.UniqueId = (Nat32)(env)->GetIntField(tvpDataObj, fid_UniqueId);
    TvpData.Type = (Nat16)(env)->GetIntField(tvpDataObj, fid_Type);
    TvpData.AnalogTablePreset = (Nat16)(env)->GetIntField(tvpDataObj, fid_AnalogTablePreset);

    // MultiplePreset	
    ObjMultiplePreset = (jintArray) (env)->GetObjectField(tvpDataObj, fid_MultiplePreset);

	
    if (NULL != ObjMultiplePreset) 
    {

        int length = (env)->GetArrayLength (ObjMultiplePreset);
        
        int  loopCount = 0;
        MultiplePreset = (jint *) (env)->GetIntArrayElements(ObjMultiplePreset, NULL);
        if(MultiplePreset != NULL)
        {
            for (loopCount = 0; (loopCount < length) && (loopCount < 8) ; ++loopCount)
            {
                TvpData.MultiplePreset[loopCount] = (Nat16)MultiplePreset[loopCount];
            }
        }
       
    }
    else
    {
        //__android_log_print(ANDROID_LOG_DEBUG, "NativeEuInstallerJNI", "ERROR: ObjMultiplePreset is NULL");
    }

    
    natiInsta->SyncUniqueIdToMW (&TvpData);

}
	

NativeJNI::~NativeJNI()
{
		
	JNIEnv *env;
	if(natvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
	  
	 } else {
		env->DeleteGlobalRef(m_jh);
	 }
	 natvm->DetachCurrentThread();
}


