/*
 * SatInstallerJNI.cpp
 *
 *  Created on: Jun 12, 2013
 *      Author: mahesh.mathada
 */


#include "org_droidtv_euinstallersat_model_mwapi_SatInstaller.h"

#ifdef AOSP_BUILD_SAT
#include <utils/Log.h>
#else
#include <android/Log.h>
#endif

#include "SatInstaller.h"
#include <stdio.h>

extern "C" {
	jobject m_jh; // Java Layer instance maintained in m_jh
	JavaVM *natvm;
	jclass caller;
	jint jh;
	JNIEnv *nativeenv; // Global env
	jclass nativeclazz;
	jint ret;
	jmethodID mOnEvent,mgetParams,mconfigureLNB,mconfigureUnicable,msetPolarization;
	jmethodID msetSymbolRate, msetPLP, mtune, mgetFreq, mscanStart;
	jmethodID mscanAbort, mscanNext, mgetSigStrength, mgetSigStrengthRange;
	jmethodID msetBand, msetLnbConnectionType, msetSatIPParams;
	jmethodID mRequestStatusInfo, mRequestNit, mSendOperatorSearchStart, mSendOpExit, mSendOpTuneStatus, mSendOpAck, mSendOpSearchCancel, mGetStoredOpData, mGetCipStatus, mCacheOperatorData = 0; //Operator Profile method IDs
	jmethodID mgetValueFromContentProvider = 0;
	jclass mOpSearchSettingsCls, mOpTuneStatusCls, mOpProfileStatusInfoCls = 0;
	jmethodID mOpSearchSettingsCId, mOpTuneStatusCId = 0;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv *env;

	natvm = vm;
	if(vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv Failure");
			return JNI_ERR;
	 } else {
		jclass clazz = env->FindClass("org/droidtv/euinstallersat/model/mwapi/SatInstaller");
		if(clazz) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetObjectClass SUCESS");
		} else {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetObjectClass FAIL");
		}
		caller = (jclass)(env->NewGlobalRef(clazz));

		mOnEvent  = env->GetMethodID(caller, "SatInstaller_onEvent", "(II)I");
		if (0 == mOnEvent) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mOnEvent GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mgetParams  = env->GetMethodID(caller, "getParams_SatInst", "([I)I");
		if (0 == mgetParams) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mgetParams GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}


		mconfigureLNB = env->GetMethodID(caller, "configureLNB_SatInst", "(IIIIIIIII)I");
		if (0 == mconfigureLNB) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mconfigureLNB GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		
		
		mconfigureUnicable = env->GetMethodID(caller, "configureUnicable_SatInst", "(II)I");
		if (0 == mconfigureUnicable) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mconfigureUnicable_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		msetPolarization  = env->GetMethodID(caller, "setPolarization_SatInst", "(I)I");
		if (0 == msetPolarization) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "msetPolarization GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		msetSymbolRate  = env->GetMethodID(caller, "setSymbolRate_SatInst", "(II)I");
		if (0 == msetSymbolRate) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "msetSymbolRate GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		msetPLP  = env->GetMethodID(caller, "setPLP_SatInst", "(I)I");
		if (0 == msetPLP) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "msetPLP GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mtune = env->GetMethodID(caller, "tune_SatInst", "(IZ)I");
		if (0 == mtune) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mtune GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mgetFreq = env->GetMethodID(caller, "getFreq_SatInst", "([I)I");
		if (0 == mgetFreq) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mgetFreq GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mscanStart = env->GetMethodID(caller, "scanStart_SatInst", "(IIZ)I");
		if (0 == mscanStart) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mscanStart GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mscanAbort = env->GetMethodID(caller, "scanAbort_SatInst", "()I");
		if (0 == mscanAbort) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mscanAbort GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mscanNext = env->GetMethodID(caller, "mscanNext_SatInst", "()I");
		if (0 == mscanNext) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mscanNext GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}

		mgetSigStrength = env->GetMethodID(caller, "getSigStrength_SatInst", "(II)I");
		if (0 == mgetSigStrength) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "getSigStrength_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mgetSigStrengthRange = env->GetMethodID(caller, "getSigStrengthRange_SatInst", "(II)I");
		if (0 == mgetSigStrengthRange) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "getSigStrengthRange_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		msetBand = env->GetMethodID(caller, "setBand_SatInst", "(I)I");
		if (0 == msetBand) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "setBand_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		msetLnbConnectionType = env->GetMethodID(caller, "setLNBConnectionType_SatInst", "(I)I");
		if (0 == msetLnbConnectionType) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "setLNBConnectionType_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		
		msetSatIPParams = env->GetMethodID(caller, "setSatIPParams_SatInst", "(IIIII)I");
		if (0 == msetSatIPParams) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "setSatIPParams_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		
		mRequestStatusInfo  = env->GetMethodID(caller, "requestStatusInfo_SatInst", "()V");
		if (0 == mRequestStatusInfo) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "requestStatusInfo_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} 		
		mRequestNit  = env->GetMethodID(caller, "requestNit_SatInst", "()V");
		if (0 == mRequestNit) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "requestNit_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}		
		mSendOpExit = env->GetMethodID(caller, "sendOpExit_SatInst", "()V");
		if (0 == mSendOpExit) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "sendOpExit_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} 
		mSendOpAck = env->GetMethodID(caller, "sendOpAck_SatInst", "()V");
		if (0 == mSendOpAck) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "sendOpAck_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mSendOpSearchCancel = env->GetMethodID(caller, "sendOpSearchCancel_SatInst", "()V");
		if (0 == mSendOpSearchCancel) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "sendOpSearchCancel_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mSendOperatorSearchStart = env->GetMethodID(caller, "sendOperatorSearchStart_SatInst", "(Lorg/droidtv/euinstallersat/model/mwapi/OperatorSearchSettings;)V");
		if (0 == mSendOperatorSearchStart) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "sendOperatorSearchStart_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		} 
		mSendOpTuneStatus = env->GetMethodID(caller, "sendOpTuneStatus_SatInst", "(Lorg/droidtv/euinstallersat/model/mwapi/OperatorTuneStatus;)V");
		if (0 == mSendOpTuneStatus) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "sendOpTuneStatus_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mCacheOperatorData = env->GetMethodID(caller, "mCacheOperatorData_JavaInst", "()V");
		if (0 == mCacheOperatorData) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "mCacheOperatorData_JavaInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		mGetStoredOpData = env->GetMethodID(caller, "getStoredOperatorData_SatInst", "()Lorg/droidtv/euinstallersat/model/mwapi/OperatorProfileStatusInfo;");
		if (0 == mGetStoredOpData) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "getStoredOperatorData_SatInst GetMethodID Failure \n");
		   env->DeleteGlobalRef(caller);
		   return JNI_ERR;
		}
		
		mgetValueFromContentProvider = env->GetMethodID(caller, "getValueFromContentProvider_SatInst", "(I[I)I");
		if (0 == mgetValueFromContentProvider) {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getValueFromContentProvider_SatInst GetMethodID Failure \n");
		   	env->DeleteGlobalRef(caller);
			return JNI_ERR;
		} else {
			__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "getValue_FromContentProvider GetMethodID SUCESS \n");
		}
		
		jclass opSearchSettingsCls = env->FindClass ("org/droidtv/euinstallersat/model/mwapi/OperatorSearchSettings");
		if (0 == opSearchSettingsCls) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "OperatorSearchSettings FindClass Failure \n");
		   env->DeleteGlobalRef(clazz);
		   return JNI_ERR;
		} else {
			mOpSearchSettingsCls = reinterpret_cast<jclass>(env->NewGlobalRef(opSearchSettingsCls));
			//env->DeleteLocalRef (opSearchSettingsCls);
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "OperatorSearchSettings FindClass SUCCESS \n");
			
			mOpSearchSettingsCId = env->GetMethodID(opSearchSettingsCls, "<init>", "(II[II[II[I)V");
			
			if (0 == mOpSearchSettingsCId) {
				__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "OperatorSearchSettings <init> GetMethodID Failure \n");
				//env->DeleteGlobalRef(caller);
				return JNI_ERR;
			} else {
				__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "OperatorSearchSettings <init> GetMethodID SUCCESS \n");
			}
			env->DeleteLocalRef (opSearchSettingsCls);
		}
		
		jclass opTuneStatusCls = env->FindClass ("org/droidtv/euinstallersat/model/mwapi/OperatorTuneStatus");
		if (0 == opTuneStatusCls) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "OperatorTuneStatus FindClass Failure \n");
		   env->DeleteGlobalRef(clazz);
		   return JNI_ERR;
		} else {
			mOpTuneStatusCls = reinterpret_cast<jclass>(env->NewGlobalRef(opTuneStatusCls));
			env->DeleteLocalRef (opTuneStatusCls);
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "OperatorTuneStatus FindClass SUCCESS \n");
			
			mOpTuneStatusCId = env->GetMethodID(mOpTuneStatusCls, "<init>", "(IIIII[I)V");
			
			if (0 == mOpTuneStatusCId) {
				__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "OperatorTuneStatus <init> GetMethodID Failure \n");
				//env->DeleteGlobalRef(caller);
				return JNI_ERR;
			} else {
				__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI", "OperatorTuneStatus <init> GetMethodID SUCCESS \n");
			}
		}
		
		jclass opProfileStatusInfoCls = env->FindClass ("org/droidtv/euinstallersat/model/mwapi/OperatorProfileStatusInfo");
		if (0 == opProfileStatusInfoCls) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "OperatorProfileStatusInfo FindClass Failure \n");
		   env->DeleteGlobalRef(clazz);
		   return JNI_ERR;
		} else {
			mOpProfileStatusInfoCls = reinterpret_cast<jclass>(env->NewGlobalRef(opProfileStatusInfoCls));
			env->DeleteLocalRef (opProfileStatusInfoCls);
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "OperatorProfileStatusInfo FindClass SUCESS \n");
		}
        
		mGetCipStatus = env->GetMethodID(caller, "getCipStatus_SatInst", "()I");
		if (0 == mGetCipStatus) {
		   __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "getCipStatus_SatInst GetMethodID Failure \n");
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
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  CreateInstance
 * Signature: (ILorg/droidtv/euinstallersat/model/mwapi/SatInstaller;)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_CreateInstance
(JNIEnv *env, jobject obj, jint token, jobject nh)
{

	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","createInstance");
	if(nh != NULL) {
		m_jh = env->NewGlobalRef(nh);
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI"," Java Instance [%p] \n",m_jh);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","nh is	NULL");
	}
	jint ret = reinterpret_cast<jint> (new SatInstaller(token,nh));
	jh = ret;
	return ret;
}


/*
 * Class:	  org_droidtv_euinstallersat
 * Method:	  GetCurrentInstallationState
 * Signature: ()I */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetCurrentInstallationState
(JNIEnv *env, jobject obj)
{
	jint state;
	jint mode;
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->GetCurrentInstallationState(&mode,&state);

	return state;
}
/*
 * Class:	  org_droidtv_euinstallersat
 * Method:	  GetCurrentInstallationMode
 * Signature: ()I */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetCurrentInstallationMode
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	jint state;
	jint mode;
	natiInsta->GetCurrentInstallationState(&mode,&state);
	
	return mode;
}
/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  StartInstallation
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_StartInstallation
(JNIEnv *env, jobject obj, jint source, jint ptc, jint mode)
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "StartInstallation [%d] [%d] [%d]",source,ptc,mode);
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->StartInstallation(source,ptc,mode);
	return 0;
}


/*
 * Class:	  org_droidtv_euinstallersat
 * Method:	  StopInstallation
 * Signature: ()I*/

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_StopInstallation
(JNIEnv *env, jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "StopInstallation \n");
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->StopInstallation();
	return 0;
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  ResetInstallation
 * Signature: ()V */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_ResetInstallation
(JNIEnv *env, jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "ResetInstallation \n");
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->ResetInstallation();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetNumberOfTvChannelsFound
 * Signature: (I)I*/

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetNumberOfTvChannelsFound
(JNIEnv *env, jobject obj, jint LNBNumber)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	return natiInsta->GetNumberOfTvChannelsFound(LNBNumber);
}


/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  GetNumberofRadioChannelsFound
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetNumberofRadioChannelsFound
  (JNIEnv *env, jobject obj, jint lnb)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetNumberofRadioChannelsFound(lnb);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetNumberOfTvChannelsRemoved
 * Signature: (I)I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetNumberOfTvChannelsRemoved
(JNIEnv *env, jobject obj, jint lnb)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetNumberOfTvChannelsRemoved(lnb);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetNumberofRadioChannelsRemoved
 * Signature: (I)I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetNumberofRadioChannelsRemoved
(JNIEnv *env, jobject obj, jint lnb)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetNumberofRadioChannelsRemoved(lnb);
}


JNIEXPORT jstring JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetSatelliteName
(JNIEnv *env, jobject obj, jint index)
{
               jint retVal;
               unsigned short satellitename[MAX_SATELLITE_NAME_LEN];
               jchar satname[MAX_SATELLITE_NAME_LEN * 2];
               jsize                                     nameLen = 0;
               const char *str;
               jboolean iscopy;
               jclass ClassId;
               jmethodID cid;
               jobject  ObjectId;
               jstring result = NULL;
               int i = 0;

               
               SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
               for(i = 0; i < MAX_SATELLITE_NAME_LEN; i++) {
               		satellitename[i] = '\0';
               }
               
               natiInsta->GetSatelliteName(index,satellitename);

               for(i = 0; i < MAX_SATELLITE_NAME_LEN; i++) {
	              if(satellitename[i] != 0) {
	                 satname[nameLen] = satellitename[i]; 
					 nameLen++;   	
	              } else {
                     satname[nameLen] = 0;
                     nameLen++;
                     break;
	              }              
               }
               result = env->NewString(satname,nameLen);
                              
               return result;
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetNumberOfDigitalChannelsAdded
 * Signature: ()I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetNumberOfDigitalChannelsAdded
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetNumberOfDigitalChannelsAdded();;
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetNumberOfDigitalChannelsRemoved
 * Signature: ()I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetNumberOfDigitalChannelsRemoved
(JNIEnv *env, jobject obj)
{
		
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetNumberOfDigitalChannelsRemoved();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetNumberOfDigitalChannelsMoved
 * Signature: ()I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetNumberOfDigitalChannelsMoved
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetNumberOfDigitalChannelsMoved();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  IdentifyPackagesAvailable
 * Signature: ()I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_IdentifyPackagesAvailable
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->IdentifyPackagesAvailable();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetTotalNumberOfPackagesFound
 * Signature: ()I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetTotalNumberOfPackagesFound
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetTotalNumberOfPackagesFound();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  InstallAddedSatellites
 * Signature: ()I
 */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_InstallAddedSatellites
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->InstallAddedSatellites();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  ResetAddedSatellites
 * Signature: ()I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_ResetAddedSatellites
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->ResetAddedSatellites();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  RemoveSatelliteEntry
 * Signature: (I)I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_RemoveSatelliteEntry
(JNIEnv *env, jobject obj, jint lnb)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->RemoveSatelliteEntry(lnb);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetSatelliteSignalStrength
 * Signature: (I)I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetSatelliteSignalStrength
(JNIEnv *env, jobject obj, jint lnb)
{

	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetSatelliteSignalStrength(lnb);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetSatelliteSignalQuality
 * Signature: (I)I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetSatelliteSignalQuality
(JNIEnv *env, jobject obj, jint lnb)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetSatelliteSignalQuality(lnb);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  LoadManualInstallationDefaultValues
 * Signature: ()I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_LoadManualInstallationDefaultValues
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->LoadManualInstallationDefaultValues();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  StoreManualInstallationValues
 * Signature: ()I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_StoreManualInstallationValues
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->StoreManualInstallationValues();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetAttribute
 * Signature: (II)I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetAttribute
(JNIEnv *env, jobject obj, jint mode, jint packageid)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetAttribute(mode,packageid);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  SetAttribute
 * Signature: (III)I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_SetAttribute
(JNIEnv *env, jobject obj, jint Mode, jint AttributeId, jint value)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->SetAttribute(Mode,AttributeId,value);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetScanProgressStatus
 * Signature: (I)I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetScanProgressStatus
(JNIEnv *env, jobject obj, jint mode)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetScanProgressStatus(mode);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  EnableUnicable
 * Signature: (IZ)V
 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_EnableUnicable
(JNIEnv *env, jobject obj, jint LnbNumber, jboolean Enable)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->EnableUnicable(LnbNumber,Enable);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  StopSignalStrengthMeas
 * Signature: (I)V
 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_StopSignalStrengthMeas
(JNIEnv *env, jobject obj, jint LnbNumber)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	natiInsta->StopSignalStrengthMeas(LnbNumber);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetSignalQuality
 * Signature: (I)I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetSignalQuality
(JNIEnv *env, jobject obj, jint param)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetSignalQuality(param);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  StartSignalStrengthMeas
 * Signature: (I)V
 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_StartSignalStrengthMeas
(JNIEnv *env, jobject obj, jint LnbNumber)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	natiInsta->StartSignalStrengthMeas(LnbNumber);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetSignalStrength
 * Signature: (I)I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetSignalStrength
(JNIEnv *env, jobject obj, jint param)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetSignalStrength(param);
}



/* Class:	  org_droidtv_euinstallersat
 * Method:	  StartPredefinedListCopy
 * Signature: ()I
 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_StartPredefinedListCopy
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->StartPredefinedListCopy();
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  SetUserPackageIndex
 * Signature: (S)I
 * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_SetUserPackageIndex
(JNIEnv *env, jobject obj, jshort PackageIndex)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->SetUserPackageIndex(PackageIndex);
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetPackageByIndex
 * Signature: (I)Lorg/droidtv/euinstallersat/model/mwapi//HsvPackageStructure;
 * * */

JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetPackageByIndex
(JNIEnv *env, jobject obj, jint index)
{
	jint	ret;
	jint	PackageId;
	jstring PackageName;
	jstring PackageListName;
	jstring PredefinedListBinFile;
	jint retVal;
	HsvPackageStructure package;
	int i = 0;
	unsigned char pkgname[64];
	unsigned char pkglistname[100];
	unsigned char predefinedListbinfile[32];
	jboolean iscopy;
	jclass ClassId;
	jmethodID cid;
	jobject  ObjectId = NULL;

	
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	for(i = 0; i < MAX_PACKAGENAME_LEN; i++) {
		package.PackageListName[i] = '\0';
	}

	ret = natiInsta->GetPackageByIndex (index, &package);

	for(i = 0; i < MAX_PACKAGENAME_LEN; i++) {
		pkglistname[i] = (unsigned char)package.PackageListName[i];
		if(pkglistname[i] == '\0'){
			break;
		}
	}
		
	
	pkglistname[(MAX_PACKAGENAME_LEN - 1)] = '\0';
	PackageListName = env->NewStringUTF((char*)pkglistname);

	
	ClassId = (env)->FindClass("org/droidtv/euinstallersat/model/mwapi/HsvPackageStructure");
	
	if(ClassId != NULL) {
		cid = (env)->GetMethodID(ClassId, "<init>", "(IILjava/lang/String;Ljava/lang/String;)V");
		if (cid == NULL) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetPackageByIndex GetMethodID Failed ");
			return NULL; // exception thrown
		} else {
			ObjectId = (env)->NewObject(ClassId, cid, package.Index, package.PackageId,PackageListName,PackageListName);	
		}
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetPackageByIndex FindClass Failed ");
	}
	return ObjectId;
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetUserPackageIndex
 * Signature: ()Z
 * * */

JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetUserPackageIndex
(JNIEnv *env, jobject obj)
{
	Nat32	Index;
	jboolean  isPackage;
	jint retVal;

	jclass ClassId;
	jmethodID cid;
	jobject  ObjectId;
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	retVal = natiInsta->GetUserPackageIndex(&Index,(Bool*)&isPackage);
	
	return isPackage;
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetInstalledSatellites
 * Signature: (I)Lorg/droidtv/euinstallersat/model/mwapi//HsvInstalledSatellites;
 * * */

JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetInstalledSatellites
(JNIEnv *env, jobject obj, jint mode)
{
	jint LnbType = 0;
	jint LnbNumber = 0;
	jboolean IsLnbFree = false;
	jboolean IsServicesScanComplete = false;
	jstring SatelliteName;
	jint retVal;
	int i = 0,j=0;
	const char *str;
	jboolean iscopy;
	jclass ClassId;
	jmethodID cid;
	jobject  ObjectId = NULL;
	HsvInstalledSatellites SatelliteEntries;
	unsigned char satelliatename[100];
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	for(i = 0; i < 100; i++) {
		for(j = 0; j < 4; j++) {
			SatelliteEntries.SatelliteDetails[j].SatelliteName[i] = '\0';
		}
	}
	
	retVal = natiInsta->GetInstalledSatellites(mode,&SatelliteEntries);

	for(i = 0; i < 100; i++) {
		for(j = 0; j < 4;j++) {
			satelliatename[i] = (unsigned char)SatelliteEntries.SatelliteDetails[j].SatelliteName[i];
		//__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SatName[%c] \n",satname[i]);
		if(satelliatename[i] == '\0'){
			break;
		}
		}
	}
	satelliatename[(100 - 1)] = '\0';
	SatelliteName = (env)->NewStringUTF((char*)satelliatename);

	ClassId = (env)->FindClass("org/droidtv/euinstallersat/model/mwapi/HsvInstalledSatellites");

	if (ClassId != NULL) {
		cid = (env)->GetMethodID(ClassId, "<init>", "(IIZZ[S)V");
		if (cid == NULL) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetInstalledSatellites GetMthodID Failed");	
			return NULL; // exception thrown
		} else {
			ObjectId = (env)->NewObject(ClassId, cid,LnbType,LnbNumber,IsLnbFree,IsServicesScanComplete,SatelliteName,retVal);
		}
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetInstalledSatellites FindClass Failed");
	}
	return ObjectId;
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetSITableIds
 * Signature: ()Lorg/droidtv/euinstallersat/model/mwapi//SITableIds;
 * * */

JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetSITableIds
(JNIEnv *env, jobject obj)
{
	jshort NetworkID;
	jshort BouquetID;
	jint retVal = 0;

	jclass ClassId;
	jmethodID cid;
	jobject  ObjectId = NULL;

	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	
	natiInsta->GetSITableIds((Nat16*)&NetworkID,(Nat16*)&BouquetID);
	ClassId = (env)->FindClass("org/droidtv/euinstallersat/model/mwapi/SITableIds");

	if (ClassId != NULL) {	
		cid = (env)->GetMethodID(ClassId, "<init>", "(SSI)V");
		if (cid == NULL) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetSITableIds GetMethodID failed");
			return NULL; // exception thrown
		} else {
			ObjectId = (env)->NewObject(ClassId, cid,NetworkID,BouquetID,retVal);
		}
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetSITableIds FindClass Failed");
	}

	return ObjectId;

}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetSIDetails
 * Signature: ()Lorg/droidtv/euinstallersat/model/mwapi//HsvSDMSIDataValues;
 * * */

JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetSIDetails
(JNIEnv *env, jobject obj)
{
	jclass ClassId;
	jmethodID cid;
	jobject  ObjectId = NULL;
	HsvSDMSIDataValues SIDetails;


	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->GetSIDetails(&SIDetails);
	ClassId = (env)->FindClass("org/droidtv/euinstallersat/model/mwapi/HsvSDMSIDataValues");

	if (ClassId != NULL) {
		cid = (env)->GetMethodID(ClassId, "<init>", "(SSS)V");
		if (cid == NULL) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetSIDetails GetMethodID Failed");
			return NULL; // exception thrown
		}
		ObjectId = (env)->NewObject(ClassId,cid,SIDetails.Pid,SIDetails.TableId,SIDetails.BouquetId);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetSIDetails FindClass Failed");
	}

	return ObjectId;

}


/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  GetPackageName
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetPackageName
(JNIEnv *env, jobject obj,jint pkgId)
{
	jstring packageName;
	jint retVal;

	const char *str;
	jboolean iscopy;
	jclass ClassId;
	jmethodID cid;
	jobject  ObjectId;
	int i = 0;
	Nat16 PackageName[MAX_PACKAGENAME_LEN];
	unsigned char pkgname[MAX_PACKAGENAME_LEN];


	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	for(int i = 0; i < MAX_PACKAGENAME_LEN; i++) {
		PackageName[i] = '\0';
	}
	retVal = natiInsta->GetPackageName(pkgId,PackageName);

	
	for(i = 0; i < MAX_PACKAGENAME_LEN; i++) {
		pkgname[i] = (unsigned char)PackageName[i];
		if(pkgname[i] == '\0'){
			break;
		}
		
	}
	pkgname[(MAX_PACKAGENAME_LEN- 1)] = '\0';
	packageName = env->NewStringUTF((char*)pkgname);

	return packageName;

}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    onScanAborted_JNICall
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_onScanAborted_1JNICall
(JNIEnv *env, jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","onScanAborted");
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->onScanAborted();
	return 0;
}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    onScanEnded_JNICall
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_onScanEnded_1JNICall
(JNIEnv *env, jobject obj)
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","onScanEnded");
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->onScanEnded();
	return 0;
}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    onScanningStandardDetected_JNICall
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_onScanningStandardDetected_1JNICall
(JNIEnv *env, jobject obj, jint arg0, jint arg1)
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","onScanningStandardDetected");
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->onScanningStandardDetected(arg0,arg1);
	return 0;
}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    onTuned_JNICall
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_onTuned_1JNICall
(JNIEnv *env, jobject jobj,jint arg0, jint arg1)
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","onTuned or OnStation Found");
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->onTuned(arg0,arg1);

	return 0;
}
 /*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  GetSatId
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetSatId
  (JNIEnv *env, jobject obj, jint index)
{

	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	int i = 0;
	HsvLnbSettings LnbSettings;
	jint SatId = 0;

	natiInsta->GetLnbSettings(&LnbSettings);
	SatId = LnbSettings.LnbSettings[index].SatelliteId;

	return SatId;
	
}



/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  GetLNBType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetLNBType
  (JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	HsvLnbSettings LnbSettings;
	natiInsta->GetLnbSettings(&LnbSettings);

	return LnbSettings.ConnectionType;
}

/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  ResetLnbSettings
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_ResetLnbSettings
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->ResetLnbSettings();
	return 0;
}

/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  ResetToDefaultLnbSettings
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_ResetToDefaultLnbSettings
 (JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->ResetToDefaultLnbSettings();
	return 0;
}
/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    SetBouquetIndex
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_SetBouquetIndex
  (JNIEnv *env, jobject obj, jint mBouquetIndex)
{
	HsvPackageStructure BouquetStruct;
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->SetUserPackageIndex(mBouquetIndex);
}


/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  GetFirstInstalledChannel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetFirstInstalledChannel
  (JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	return natiInsta->GetFirstInstalledChannel();
}

/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  SaveSatelliteSettingsToPersistent
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_SaveSatelliteSettingsToPersistent
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->SaveSatelliteSettingsToPersistent();
}

/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  CommitSatelliteSettingsToPersistent
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_CommitSatelliteSettingsToPersistent
(JNIEnv *env, jobject obj)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->CommitSatelliteSettingsToPersistent();
}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    UpdateConfigXmlStrings
 * Signature: (Ljava/lang/String;ILjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_UpdateConfigXmlStrings
  (JNIEnv *env, jobject obj, jstring prescanxml, jint prescanSize, jstring satellitexml, jint satsize)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	jboolean isCp;
	const char *prescanXml = NULL; //env->GetStringUTFChars(prescanxml, &isCp);
	const char *satelliteXml = NULL;//env->GetStringUTFChars(satellitexml, &isCp);
	
	natiInsta->UpdateConfigXmlStrings((char*)prescanXml,prescanSize,(char*)satelliteXml,satsize);

	//env->ReleaseStringUTFChars(prescanxml, prescanXml);
	//env->ReleaseStringUTFChars(satellitexml, satelliteXml);
}

/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  SetUnicableUBNumber
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_SetUnicableUBNumber
 (JNIEnv *env, jobject obj,jint ubNum)
{
	
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	FResult retval = 0;
	
	HsvLnbSettings LnbSettings;
	
	
	natiInsta->GetLnbSettings(&LnbSettings);
	

	if(LnbSettings.LnbSettings[0].UserBand != ubNum)
	{
		/* User band remains common for both LNBs */
		LnbSettings.LnbSettings[0].UserBand = ubNum;
		LnbSettings.LnbSettings[1].UserBand = ubNum;
		natiInsta->GetDefaultValues(&(LnbSettings.LnbSettings[0]));
		natiInsta->GetDefaultValues(&(LnbSettings.LnbSettings[1]));
		natiInsta->SetLnbSettings(&LnbSettings);
	}
	else
	{
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "user band selection is same as previous selection");
	}
	
}
/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  SetUnicableUBNumberTuner2
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_SetUnicableUBNumberTuner2
	(JNIEnv *env, jobject obj,jint ubNum)
{
		
		SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	
		FResult retval = 0;
		
		HsvLnbSettings LnbSettings;
		
		
		natiInsta->GetLnbSettings(&LnbSettings);
		
	
		if(LnbSettings.LnbSettings[2].UserBand != ubNum)
		{
			/* User band remains common for both LNBs */
			natiInsta->GetDefaultValues(&(LnbSettings.LnbSettings[2]));
			natiInsta->GetDefaultValues(&(LnbSettings.LnbSettings[3]));
			LnbSettings.LnbSettings[2].UserBand = ubNum;
			LnbSettings.LnbSettings[3].UserBand = ubNum;
			natiInsta->SetLnbSettings(&LnbSettings);
		}
		else
		{
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "user band selection is same as previous selection");
		}

}




/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  SetUnicableUBFreq
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_SetUnicableUBFreq
  (JNIEnv *env, jobject obj,jint value)
{
	
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	
	FResult retval = 0;
	
	
	HsvLnbSettings LnbSettings;
	
	
	natiInsta->GetLnbSettings(&LnbSettings);
	if(retval == 0)
	{
		LnbSettings.LnbSettings[0].UserBandFrequency = (value);
		LnbSettings.LnbSettings[1].UserBandFrequency = (value);
		natiInsta->SetLnbSettings(&LnbSettings);
	}
	
}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    asset_manager_init
 * Signature: (Lorg/droidtv/euinstallersat/model/mwapi/SatInstaller;)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_asset_1manager_1init
  (JNIEnv *env, jobject obj, jobject assMang)
{

	AAssetManager* mgr = AAssetManager_fromJava(env, assMang);
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	natiInsta->assetManager_init(mgr);

}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    OnOpSearchStatus
 * Signature: (jObject)V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_OnOpSearchStatus
  (JNIEnv *env, jobject obj, jobject objOpSearchStatus)
{
    SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
    Op_ProfileSearchStatus OpSearchStatus;
    jfieldID fid_Info_Version = NULL;
    jfieldID fid_NIT_Version = NULL;
    jfieldID fid_Profile_Type = NULL;
    jfieldID fid_Initialised_Flag = NULL;
    jfieldID fid_Entitlement_Change_Flag = NULL;
    jfieldID fid_Entitlement_Valid_Flag = NULL;
    jfieldID fid_Refresh_Request_Flag = NULL;
    jfieldID fid_Error_Flag = NULL;
    jfieldID fid_Delivery_System_Hint = NULL;
    jfieldID fid_Refresh_Request_Date = NULL;
    jfieldID fid_Refresh_Request_Time = NULL;


    jclass opSearchStatusClass  = (env)->FindClass( "org/droidtv/euinstallersat/model/mwapi/OperatorProfileSearchStatus");

    fid_Info_Version = (env)->GetFieldID (opSearchStatusClass, "Info_Version", "I");
    fid_NIT_Version = (env)->GetFieldID (opSearchStatusClass, "NIT_Version", "I");
    fid_Profile_Type = (env)->GetFieldID (opSearchStatusClass, "Profile_Type", "I");
    fid_Initialised_Flag = (env)->GetFieldID (opSearchStatusClass, "Initialised_Flag", "I");
    fid_Entitlement_Change_Flag = (env)->GetFieldID (opSearchStatusClass, "Entitlement_Change_Flag", "I");
    fid_Entitlement_Valid_Flag = (env)->GetFieldID (opSearchStatusClass, "Entitlement_Valid_Flag", "I");
    fid_Refresh_Request_Flag = (env)->GetFieldID (opSearchStatusClass, "Refresh_Request_Flag", "I");
    fid_Error_Flag = (env)->GetFieldID (opSearchStatusClass, "Error_Flag", "I");
    fid_Delivery_System_Hint = (env)->GetFieldID (opSearchStatusClass, "Delivery_System_Hint", "I");
    fid_Refresh_Request_Date = (env)->GetFieldID (opSearchStatusClass, "Refresh_Request_Date", "I");
    fid_Refresh_Request_Time = (env)->GetFieldID (opSearchStatusClass, "Refresh_Request_Time", "I");


    OpSearchStatus.op_Status.Info_Version = (Nat8)(env)->GetIntField(objOpSearchStatus, fid_Info_Version);
    OpSearchStatus.op_Status.NIT_Version = (Nat8)(env)->GetIntField(objOpSearchStatus, fid_NIT_Version);
    OpSearchStatus.op_Status.Profile_Type = (OP_Profile)(env)->GetIntField(objOpSearchStatus, fid_Profile_Type);
    OpSearchStatus.op_Status.Initialised_Flag = (Nat8)(env)->GetIntField(objOpSearchStatus, fid_Initialised_Flag);
    OpSearchStatus.op_Status.Entitlement_Change_Flag = (Nat8)(env)->GetIntField(objOpSearchStatus, fid_Entitlement_Change_Flag);
    OpSearchStatus.op_Status.Entitlement_Valid_Flag = (Nat8)(env)->GetIntField(objOpSearchStatus, fid_Entitlement_Valid_Flag);
    OpSearchStatus.op_Status.Refresh_Request_Flag = (OP_RefreshRequestFlag)(env)->GetIntField(objOpSearchStatus, fid_Refresh_Request_Flag);
    OpSearchStatus.op_Status.Error_Flag = (OP_Error_Flag)(env)->GetIntField(objOpSearchStatus, fid_Error_Flag);
    OpSearchStatus.op_Status.Delivery_System_Hint = (Nat16)(env)->GetIntField(objOpSearchStatus, fid_Delivery_System_Hint);
    OpSearchStatus.op_Status.Refresh_Request_Date = (Nat16)(env)->GetIntField(objOpSearchStatus,fid_Refresh_Request_Date); 
    OpSearchStatus.op_Status.Refresh_Request_Time = (Nat8)(env)->GetIntField(objOpSearchStatus,fid_Refresh_Request_Time); 



    natiInsta->OnOpSearchStatus(OpSearchStatus);
}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    OnOpStatusInfo
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_OnOpStatusInfo
  (JNIEnv *env, jobject obj, jobject objOpStatusInfo)
{
    SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
    Op_ProfileStatusInfo OpStatusInfo;

    jfieldID fid_Info_Version = NULL;
    jfieldID fid_NIT_Version = NULL;
    jfieldID fid_Profile_Type = NULL;
    jfieldID fid_Initialised_Flag = NULL;
    jfieldID fid_Entitlement_Change_Flag = NULL;
    jfieldID fid_Entitlement_Valid_Flag = NULL;
    jfieldID fid_Refresh_Request_Flag = NULL;
    jfieldID fid_Error_Flag = NULL;
    jfieldID fid_Delivery_System_Hint = NULL;
    jfieldID fid_Refresh_Request_Date = NULL;
    jfieldID fid_Refresh_Request_Time = NULL;
    jfieldID fid_InfoValid = NULL;
    jfieldID fid_ProfileInfoVersion = NULL;
    jfieldID fid_CiCamOriginalNetworkId = NULL;
    jfieldID fid_CiCamIdentifier = NULL;
    jfieldID fid_CharacterCodeTable = NULL;
    jfieldID fid_CharacterCodeTable2 = NULL;
    jfieldID fid_CharacterCodeTable3 = NULL;
    jfieldID fid_SdtRunningTrusted = NULL;
    jfieldID fid_EitRunningTrusted = NULL;
    jfieldID fid_EitPfUsage = NULL;
    jfieldID fid_EitScheduleUsage = NULL;
    jfieldID fid_ExtendedEventUsage = NULL;
    jfieldID fid_SdtOtherTrusted = NULL;
    jfieldID fid_EitEventTrigger = NULL;
    jfieldID fid_ISO639LangCode = NULL;
    jfieldID fid_ProfileNameLength = NULL;
    jfieldID fid_ProfileName = NULL;
    jintArray ObjProfileNameArray;
    jintArray ObjLangCodeArray;
    const int* ProfileName = NULL;
    const int* LangCode	= NULL;


    jclass opProfileStatusInfoClass  = (env)->FindClass( "org/droidtv/euinstallersat/model/mwapi/OperatorProfileStatusInfo");

    fid_Info_Version = (env)->GetFieldID (opProfileStatusInfoClass, "Info_Version", "I");
    fid_NIT_Version = (env)->GetFieldID (opProfileStatusInfoClass, "NIT_Version", "I");
    fid_Profile_Type = (env)->GetFieldID (opProfileStatusInfoClass, "Profile_Type", "I");
    fid_Initialised_Flag = (env)->GetFieldID (opProfileStatusInfoClass, "Initialised_Flag", "I");
    fid_Entitlement_Change_Flag = (env)->GetFieldID (opProfileStatusInfoClass, "Entitlement_Change_Flag", "I");
    fid_Entitlement_Valid_Flag = (env)->GetFieldID (opProfileStatusInfoClass, "Entitlement_Valid_Flag", "I");
    fid_Refresh_Request_Flag = (env)->GetFieldID (opProfileStatusInfoClass, "Refresh_Request_Flag", "I");
    fid_Error_Flag = (env)->GetFieldID (opProfileStatusInfoClass, "Error_Flag", "I");
    fid_Delivery_System_Hint = (env)->GetFieldID (opProfileStatusInfoClass, "Delivery_System_Hint", "I");
    fid_Refresh_Request_Date = (env)->GetFieldID (opProfileStatusInfoClass, "Refresh_Request_Date", "I");
    fid_Refresh_Request_Time = (env)->GetFieldID (opProfileStatusInfoClass, "Refresh_Request_Time", "I");

    fid_InfoValid = (env)->GetFieldID (opProfileStatusInfoClass, "InfoValid", "I");
    fid_ProfileInfoVersion = (env)->GetFieldID (opProfileStatusInfoClass, "ProfileInfoVersion", "I");
    fid_CiCamOriginalNetworkId = (env)->GetFieldID (opProfileStatusInfoClass, "CiCamOriginalNetworkId", "I");
    fid_CiCamIdentifier = (env)->GetFieldID (opProfileStatusInfoClass, "CiCamIdentifier", "I");
    fid_CharacterCodeTable = (env)->GetFieldID (opProfileStatusInfoClass, "CharacterCodeTable", "I");
    fid_CharacterCodeTable2 = (env)->GetFieldID (opProfileStatusInfoClass, "CharacterCodeTable2", "I");
    fid_CharacterCodeTable3 = (env)->GetFieldID (opProfileStatusInfoClass, "CharacterCodeTable3", "I");
    fid_SdtRunningTrusted = (env)->GetFieldID (opProfileStatusInfoClass, "SdtRunningTrusted", "I");
    fid_EitRunningTrusted = (env)->GetFieldID (opProfileStatusInfoClass, "EitRunningTrusted", "I");
    fid_EitPfUsage = (env)->GetFieldID (opProfileStatusInfoClass, "EitPfUsage", "I");
    fid_EitScheduleUsage = (env)->GetFieldID (opProfileStatusInfoClass, "EitScheduleUsage", "I");
    fid_ExtendedEventUsage = (env)->GetFieldID (opProfileStatusInfoClass, "ExtendedEventUsage", "I");
    fid_SdtOtherTrusted = (env)->GetFieldID (opProfileStatusInfoClass, "SdtOtherTrusted", "I");
    fid_EitEventTrigger = (env)->GetFieldID (opProfileStatusInfoClass, "EitEventTrigger", "I");
    fid_ISO639LangCode  = (env)->GetFieldID (opProfileStatusInfoClass, "ISO639LangCode", "[I");
    fid_ProfileNameLength = (env)->GetFieldID (opProfileStatusInfoClass, "ProfileNameLength", "I");
    fid_ProfileName = (env)->GetFieldID (opProfileStatusInfoClass, "ProfileName", "[I");

    OpStatusInfo.op_Status.Info_Version = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_Info_Version);
    OpStatusInfo.op_Status.NIT_Version = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_NIT_Version);
    OpStatusInfo.op_Status.Profile_Type = (OP_Profile)(env)->GetIntField(objOpStatusInfo, fid_Profile_Type);
    OpStatusInfo.op_Status.Initialised_Flag = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_Initialised_Flag);
    OpStatusInfo.op_Status.Entitlement_Change_Flag = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_Entitlement_Change_Flag);
    OpStatusInfo.op_Status.Entitlement_Valid_Flag = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_Entitlement_Valid_Flag);
    OpStatusInfo.op_Status.Refresh_Request_Flag = (OP_RefreshRequestFlag)(env)->GetIntField(objOpStatusInfo, fid_Refresh_Request_Flag);
    OpStatusInfo.op_Status.Error_Flag = (OP_Error_Flag)(env)->GetIntField(objOpStatusInfo, fid_Error_Flag);
    OpStatusInfo.op_Status.Delivery_System_Hint = (Nat16)(env)->GetIntField(objOpStatusInfo, fid_Delivery_System_Hint);
    OpStatusInfo.op_Status.Refresh_Request_Date = (Nat16)(env)->GetIntField(objOpStatusInfo,fid_Refresh_Request_Date); 
    OpStatusInfo.op_Status.Refresh_Request_Time = (Nat8)(env)->GetIntField(objOpStatusInfo,fid_Refresh_Request_Time); 



    OpStatusInfo.op_Info.info_Valid = (Nat8) (env)->GetIntField(objOpStatusInfo, fid_InfoValid);
    OpStatusInfo.op_Info.info_Version = (Nat8) (env)->GetIntField(objOpStatusInfo, fid_ProfileInfoVersion);
    OpStatusInfo.op_Info.cicam_Original_Network_Id = (Nat16) (env)->GetIntField(objOpStatusInfo, fid_CiCamOriginalNetworkId);
    OpStatusInfo.op_Info.cicam_Identifier = (int) (env)->GetIntField(objOpStatusInfo, fid_CiCamIdentifier);
    OpStatusInfo.op_Info.character_Code_Table = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_CharacterCodeTable);
    OpStatusInfo.op_Info.character_Code_Table_2 = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_CharacterCodeTable2);
    OpStatusInfo.op_Info.character_Code_Table_3 = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_CharacterCodeTable3);
    OpStatusInfo.op_Info.sDT_Running_Trusted = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_SdtRunningTrusted);
    OpStatusInfo.op_Info.eIT_Running_Trusted = (Nat8)(env)->GetIntField(objOpStatusInfo, fid_EitRunningTrusted);
    OpStatusInfo.op_Info.eIT_Pf_Usage = (OP_EIT_pfUsage)(env)->GetIntField(objOpStatusInfo,fid_EitPfUsage); 
    OpStatusInfo.op_Info.eIT_Schedule_Usage = (OP_EIT_schedUsage)(env)->GetIntField(objOpStatusInfo,fid_EitScheduleUsage); 
    OpStatusInfo.op_Info.extended_Event_Usage = (int)(env)->GetIntField(objOpStatusInfo,fid_ExtendedEventUsage); 
    OpStatusInfo.op_Info.sDT_Other_Trusted = (Nat8)(env)->GetIntField(objOpStatusInfo,fid_SdtOtherTrusted); 
    OpStatusInfo.op_Info.eIT_Event_Trigger = (Nat8)(env)->GetIntField(objOpStatusInfo,fid_EitEventTrigger); 
    OpStatusInfo.op_Info.profile_Name_Length = (short)(env)->GetIntField(objOpStatusInfo,fid_ProfileNameLength); 

    /* Lang Code Array */
    ObjLangCodeArray = (jintArray) (env)->GetObjectField (objOpStatusInfo, fid_ISO639LangCode);

    if(NULL != ObjLangCodeArray) 
    {
        LangCode = (int *) (env)->GetIntArrayElements(ObjLangCodeArray, 0);
        if(LangCode != NULL)
        {
            for (int i = 0; i < 3; i++)
            {
                OpStatusInfo.op_Info.iSO_639_Lang_Code[i] = (Nat8) LangCode[i];
            }
        }
    }

    /* Profile Name Array */
    ObjProfileNameArray = (jintArray) (env)->GetObjectField (objOpStatusInfo, fid_ProfileName);

    if(NULL != ObjProfileNameArray) 
    {
        ProfileName = (int *) (env)->GetIntArrayElements(ObjProfileNameArray, 0);
        if(ProfileName != NULL)
        {
            for(int i = 0; i < OpStatusInfo.op_Info.profile_Name_Length; i++)
            {
                OpStatusInfo.op_Info.profile_Name[i] = (Nat8) ProfileName[i];
            }
        }
    }
    else
    {
       OpStatusInfo.op_Info.profile_Name_Length = 0;
    }

    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","InfoValid [%d] \n",OpStatusInfo.op_Info.info_Valid);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","ProfileInfoVersion [%d] \n",OpStatusInfo.op_Info.info_Version);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CiCamOriginalNetworkId [%d] \n",OpStatusInfo.op_Info.cicam_Original_Network_Id);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CiCamIdentifier [%d] \n",OpStatusInfo.op_Info.cicam_Identifier);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CharacterCodeTable [%d] \n",OpStatusInfo.op_Info.character_Code_Table);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CharacterCodeTable2 [%d] \n",OpStatusInfo.op_Info.character_Code_Table_2);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CharacterCodeTable3 [%d] \n",OpStatusInfo.op_Info.character_Code_Table_3);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SdtRunningTrusted [%d] \n",OpStatusInfo.op_Info.sDT_Running_Trusted);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","EitRunningTrusted [%d] \n",OpStatusInfo.op_Info.eIT_Running_Trusted);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","EitPfUsage [%d] \n",OpStatusInfo.op_Info.eIT_Pf_Usage);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","EitScheduleUsage [%d] \n",OpStatusInfo.op_Info.eIT_Schedule_Usage);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","ExtendedEventUsage [%d] \n",OpStatusInfo.op_Info.extended_Event_Usage);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","sDT_Other_Trusted [%d] \n",OpStatusInfo.op_Info.sDT_Other_Trusted);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","eIT_Event_Trigger [%d] \n",OpStatusInfo.op_Info.eIT_Event_Trigger);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","profile_Name_Length [%d] \n",OpStatusInfo.op_Info.profile_Name_Length);

    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Native OnOpStatusInfo called");
    natiInsta->OnOpStatusInfo(OpStatusInfo);
}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    OnOpNIT
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_OnOpNIT
  (JNIEnv *env, jobject obj, jobject objOpNIT)
{
    SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
    Op_ProfileNitData opNitData;
    jfieldID fid_NitStatus = NULL;
    jfieldID fid_NitDataLength = NULL;
    jfieldID fid_NitData = NULL;

    jintArray ObjNitDataArray;
    const int* NitData = NULL;


    jclass opNitClass  = (env)->FindClass( "org/droidtv/euinstallersat/model/mwapi/OperatorProfileNitData");

    fid_NitStatus = (env)->GetFieldID (opNitClass, "NitStatus", "I");
    fid_NitDataLength = (env)->GetFieldID (opNitClass, "NitDataLength", "I");
    fid_NitData = (env)->GetFieldID (opNitClass, "NitData", "[I");


    opNitData.NitStatus = (Bool)(env)->GetIntField(objOpNIT, fid_NitStatus);
    opNitData.NitDataLength = (Nat16)(env)->GetIntField(objOpNIT, fid_NitDataLength);

    ObjNitDataArray = (jintArray) (env)->GetObjectField(objOpNIT, fid_NitData);
    if (NULL != ObjNitDataArray) 
    {
        NitData = (int *) (env)->GetIntArrayElements(ObjNitDataArray, 0);
        if (NitData != NULL)
        {
            for(int i = 0; i < opNitData.NitDataLength; i++)
            {
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","NitData[%d] %d\n", i, NitData[i]); 
                opNitData.NitData[i] = (Nat8) NitData[i];
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","opNitData.NitData[%d] %d\n", i, opNitData.NitData[i]); 
            }
        }
    }
    else
    {
       opNitData.NitDataLength = 0;
    }   
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","NitStatus [%d] \n",opNitData.NitStatus);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","NitDataLength [%d] \n", opNitData.NitDataLength);
     
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Native OnOpNIT called");
    natiInsta->OnOpNIT(opNitData);
}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    OnOpTune
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_OnOpTune
  (JNIEnv *env, jobject obj, jobject objOpTune)
{
    SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
    Op_ProfileTuneData opTuneData;

    jfieldID fid_TuneDataLength = NULL;
    jfieldID fid_TuneData = NULL;

    jintArray ObjTuneDataArray;
    const int* TuneData = NULL;

    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "OnOpTune");

    jclass opNitClass  = (env)->FindClass( "org/droidtv/euinstallersat/model/mwapi/OperatorProfileTuneData");

    fid_TuneDataLength = (env)->GetFieldID (opNitClass, "TuneDataLength", "I");
    fid_TuneData = (env)->GetFieldID (opNitClass, "TuneData", "[I");

    opTuneData.TuneDataLength = (Nat16)(env)->GetIntField(objOpTune, fid_TuneDataLength);

     __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","TuneDataLength [%d] \n", opTuneData.TuneDataLength);

    ObjTuneDataArray = (jintArray) (env)->GetObjectField(objOpTune, fid_TuneData);

    if (NULL != ObjTuneDataArray) 
    {
        TuneData = (int *) (env)->GetIntArrayElements(ObjTuneDataArray, 0);
        if(TuneData != NULL)
        {
            for (int i = 0; i < opTuneData.TuneDataLength; i++)
            {
                opTuneData.TuneData[i] = (Nat8) TuneData[i];
                 __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","TuneData[%d] %d %d\n", i, opTuneData.TuneData[i], TuneData[i]);
            }
        }
    }
    else
    {
       opTuneData.TuneDataLength = 0;
    }

    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Native OnOpTune called");
    natiInsta->OnOpTune(opTuneData);
} 

/* Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  SetUnicableUBFreqTuner2
 * Signature: (II)V
 * * */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_SetUnicableUBFreqTuner2
(JNIEnv *env, jobject,jint frequency,jint tunerType)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	HsvLnbSettings lnbsettings;
	natiInsta->GetLnbSettings(&lnbsettings);	
	//if(1 == tunerType) {
		if((lnbsettings.ConnectionType == LnbConnectionUnicableLnb) || (lnbsettings.ConnectionType == LnbConnectionUnicableSwitch)) {
			lnbsettings.LnbSettings[2].UserBandFrequency = frequency;
			lnbsettings.LnbSettings[3].UserBandFrequency = frequency;
		}
	//}
	natiInsta->SetLnbSettings(&lnbsettings);	
}

/* Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  GetUnicableUBFreqTuner2
 * Signature: (I)I
 * * */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetUnicableUBFreqTuner2
(JNIEnv *env, jobject obj,jint tunertype)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	HsvLnbSettings lnbsettings;
	natiInsta->GetLnbSettings(&lnbsettings);
	jint frequency = 0;
	jint frequency1 = 0;
	
	if(1 == tunertype) {
		if((lnbsettings.ConnectionType == LnbConnectionUnicableLnb) || (lnbsettings.ConnectionType == LnbConnectionUnicableSwitch))		
		{
			frequency = lnbsettings.LnbSettings[2].UserBandFrequency;
		}
	} else {
		frequency = lnbsettings.LnbSettings[0].UserBandFrequency;
	}
	return frequency;
}


	/*** TVPROVIDER IMPLEMENTATION START ***/
 
/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    GetNumberOfDatabaseRecords
 * Signature: (I)I
 */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetNumberOfDatabaseRecords
  (JNIEnv *env, jobject obj, jint TSDataOnly)
{
	jint	noOfDatabaseRecords;
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);	

	noOfDatabaseRecords = natiInsta->GetNumberOfDatabaseRecords (TSDataOnly);

	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetNumberOfDatabaseRecords = %d , TSDataOnly = %d", noOfDatabaseRecords, TSDataOnly);

	return noOfDatabaseRecords;
} 


/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    GetTvProviderBlobDataByIndex
 * Signature: (I)Lorg/droidtv/euinstallersat/model/mwapi/SatInstallerTvProviderData
 */

JNIEXPORT jobject JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetTvProviderBlobDataByIndex
  (JNIEnv *env, jobject obj, jint Index, jint TSDataOnly)
{
	jobject  ObjectId = NULL;
	HsvPgdatTvProviderBlobData		TvpData;
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	jchar	ServiceName[MAXSERVICENAMELEN + 2];
	jchar	SatelliteName[24];
	jint	MultipleVisibleService[8];
	jint	MultipleNumericSelect[8];
	jint	BrandIds[23], MultipleLCN[8],	MultiplePreset[8], MultipleFavorite[8];
	jchar	Temp[1] = {'t'};
	
	jint	i = 0;
	jsize	StringLen = 0;
	jstring	ServiceNameConverted = NULL, SatelliteNameConverted = NULL;
	jclass ClassId;
	jmethodID cid;
	jintArray TvpRawDataArray;
	jstring TempString = env->NewString(Temp,1);
	jintArray ArrayBrandIds = NULL;
	jintArray ArrayMultipleLCN = NULL;
	jintArray ArrayMultiplePreset = NULL;
	jintArray ArrayMultipleFavorite = NULL;
	jintArray ArrayMultipleVisibleService = NULL;
	jintArray ArrayMultipleNumericSelect = NULL;
	
	jintArray TempArray = env->NewIntArray(8);
	
	
	natiInsta->GetTvProviderBlobDataByIndex(Index,(Address)&TvpData,NULL, TSDataOnly);
	if(!TSDataOnly)
	{
		/* Convert ChannelName to jString */
		for (i =0; i < (MAXSERVICENAMELEN + 2); i++) {
			ServiceName[i] = '\0';
		}
		for (i=0; i<(MAXSERVICENAMELEN + 1); i++) {
			if (TvpData.ChannelName[i] != 0) {
				ServiceName[StringLen] = TvpData.ChannelName[i];
				StringLen++;
			} else {
				break;
			}
		}
		ServiceName[StringLen] = '\0';
		if (StringLen > 0) {
			ServiceNameConverted = env->NewString(ServiceName,StringLen);
		}
		

		/* Convert SatelliteName to jString */
		StringLen = 0;
		for (i =0; i < 24; i++) {
			SatelliteName[i] = '\0';
		}
		for (i=0; i<23; i++) {
			if (TvpData.SatelliteName[i] != 0) {
				SatelliteName[StringLen] = TvpData.SatelliteName[i];
				StringLen++;
			} else {
			  break;
			}
		}
		SatelliteName[StringLen] = '\0';
		if (StringLen > 0) {
			SatelliteNameConverted = env->NewString(SatelliteName,StringLen);
		}

	#if 0
	/* Convert MultipleVisibleService to jString */
	StringLen = 0;
	for (i =0; i < 9; i++) {
		MultipleVisibleService[i] = '\0';
	}
	for (i=0; i<8; i++) {
		if (TvpData.MultipleVisibleService[i] != 0) {
			MultipleVisibleService[StringLen] = TvpData.MultipleVisibleService[i];
			StringLen ++;
		}
	}
	MultipleVisibleService[StringLen] = '\0';
;
	if (StringLen > 0) {
		MultipleVisibleServiceCoverted = env->NewString(MultipleVisibleService,StringLen);
	}

	/* Convert MultipleNumericSelect to jString */
	StringLen = 0;
	for (i =0; i < 9; i++) {
		MultipleNumericSelect[i] = '\0';
	}
	for (i=0; i<8; i++) {
		if (TvpData.MultipleNumericSelect[i] != 0) {
			MultipleNumericSelect[StringLen] = TvpData.MultipleNumericSelect[i];
			StringLen ++;
		}
	}
	MultipleNumericSelect[StringLen] = '\0';
;
	if (StringLen > 0) {
		MultipleNumericSelectConverted = env->NewString(MultipleNumericSelect,StringLen);
	}
	#endif

		/* Convert MultipleVisibleService to jintArray */
		for (i=0; i<8; i++) {
			MultipleVisibleService[i] = TvpData.MultipleVisibleService[i];
		}
		ArrayMultipleVisibleService = env->NewIntArray(8);
		
		env->SetIntArrayRegion(ArrayMultipleVisibleService, 0, 8, MultipleVisibleService);
		
		/* Convert MultipleNumericSelect to jintArray */
		for (i=0; i<8; i++) {
			MultipleNumericSelect[i] = TvpData.MultipleNumericSelect[i];
		}
		ArrayMultipleNumericSelect = env->NewIntArray(8);
		
		env->SetIntArrayRegion(ArrayMultipleNumericSelect, 0, 8, MultipleNumericSelect);
		
		/* Convert BrandIds to jintArray */
		for (i=0; i<23; i++) {
			BrandIds[i] = TvpData.BrandIds[i];
		}
		ArrayBrandIds = env->NewIntArray(23);
		
		env->SetIntArrayRegion(ArrayBrandIds, 0, 23, BrandIds);


		/* Convert MultipleLCN to jintArray*/
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



	ClassId = (env)->FindClass("org/droidtv/euinstallersat/model/mwapi/SatInstallerTvProviderData");
	if(ClassId != NULL) {
			cid = (env)->GetMethodID(ClassId, "<init>", "(IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIILjava/lang/String;Ljava/lang/String;[I[I[I[I[I[I)V");
			if (cid == NULL) {
					__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetPackageByIndex GetMethodID Failed ");
					return NULL; // exception thrown
			} else {
					if(!TSDataOnly)
					{
						ObjectId = (env)->NewObject(ClassId, cid, TvpData.UniqueId, TvpData.PresetNumber, TvpData.OriginalNetworkId, TvpData.Tsid, TvpData.ServiceId,  TvpData.Frequency, 
						TvpData.TextSubTitlePage, 	TvpData.LogoURL, TvpData.DecoderType, TvpData.ModulationType,TvpData.UserModifiedLogo,
						TvpData.SAP, TvpData.PreferredStereo, TvpData.Ptc, TvpData.SymbolRate, TvpData.AudioPid, 
						TvpData.VideoPid, TvpData.PcrPid, TvpData.NetworkId, TvpData.LCN, TvpData.ServiceType,
						TvpData.SystemHidden, TvpData.NumericSelect, TvpData.Bandwidth, TvpData.ScrambledStatus, TvpData.IntHbbTvOption,
						TvpData.UserHidden, TvpData.NewPreset, TvpData.VideoStreamType, TvpData.AudioStreamType, TvpData.LnbNumber,
						TvpData.Polarization, TvpData.DpTsid, TvpData.DpServiceId, TvpData.Tpid, TvpData.PackageGroup,
						TvpData.FavoriteNumber, TvpData.VisibleService, TvpData.LnbType, TvpData.SatelliteId, TvpData.OrbitalPosition, TvpData.SignalStrength, TvpData.SignalQuality, TvpData.AppsCookie, 
						TvpData.SDTVersion, TvpData.NITVersion, TvpData.DateStamp, TvpData.PmtPid, TvpData.SecAudioPid, TvpData.LowPrioLCN, 
						TvpData.LowPrioVisibleService, TvpData.FreeCiMode, TvpData.VideoDescPresent, TvpData.ScramblingStatus, TvpData.DuplicateSvc, TvpData.ServiceListVersion, 
						TvpData.UserInstalled, TvpData.SecAudioStreamType, TvpData.UserModifiedName, TvpData.ChannelLock,
						TvpData.DvbType, TvpData.MatchBrandFlag,TvpData.NumBrandIds, TvpData.ScrambledStatus, TvpData.InstalledSatelliteNumber,
						TvpData.NewChannel, TvpData.HbbTvOption,
						TvpData.CountryCode, TvpData.HDSimulcastRepOnId, TvpData.HDSimulcastRepTsId, TvpData.HDSimulcastRepSvcId, TvpData.ParentalRating, TvpData.ServiceIdentifier, 
						TvpData.AdultGenere, TvpData.FreesatServiceIdentifier, TvpData.InteractiveServiceEnabled, TvpData.ASignalStrength, TvpData.VSignalStrength, TvpData.QSignalStrength, 
						TvpData.ChannelInformation, TvpData.CodeRate, TvpData.PtcListVersion, TvpData.TSVersion, TvpData.SDSDFrequency, TvpData.PlpId, TvpData.BarkerMux, 0 /*TvpData.FECInner*/, 0/*TvpData.RollOff*/,
						ServiceNameConverted, SatelliteNameConverted, ArrayMultipleVisibleService, ArrayMultipleNumericSelect,
						ArrayBrandIds, ArrayMultipleLCN, ArrayMultiplePreset, ArrayMultipleFavorite);
					}
					else
					{
						ObjectId = (env)->NewObject(ClassId, cid, TvpData.UniqueId, TvpData.PresetNumber, TvpData.OriginalNetworkId, TvpData.Tsid, TvpData.ServiceId,  TvpData.Frequency, 
						TvpData.TextSubTitlePage,	TvpData.LogoURL, TvpData.DecoderType, TvpData.ModulationType,TvpData.UserModifiedLogo,
						TvpData.SAP, TvpData.PreferredStereo, TvpData.Ptc, TvpData.SymbolRate, TvpData.AudioPid, 
						TvpData.VideoPid, TvpData.PcrPid, TvpData.NetworkId, TvpData.LCN, TvpData.ServiceType,
						TvpData.SystemHidden, TvpData.NumericSelect, TvpData.Bandwidth, TvpData.ScrambledStatus, TvpData.IntHbbTvOption,
						TvpData.UserHidden, TvpData.NewPreset, TvpData.VideoStreamType, TvpData.AudioStreamType, TvpData.LnbNumber,
						TvpData.Polarization, TvpData.DpTsid, TvpData.DpServiceId, TvpData.Tpid, TvpData.PackageGroup,
						TvpData.FavoriteNumber, TvpData.VisibleService, TvpData.LnbType, TvpData.SatelliteId, TvpData.OrbitalPosition, TvpData.SignalStrength, TvpData.SignalQuality, TvpData.AppsCookie, 
						TvpData.SDTVersion, TvpData.NITVersion, TvpData.DateStamp, TvpData.PmtPid, TvpData.SecAudioPid, TvpData.LowPrioLCN, 
						TvpData.LowPrioVisibleService, TvpData.FreeCiMode, TvpData.VideoDescPresent, TvpData.ScramblingStatus, TvpData.DuplicateSvc, TvpData.ServiceListVersion, 
						TvpData.UserInstalled, TvpData.SecAudioStreamType, TvpData.UserModifiedName, TvpData.ChannelLock,
						TvpData.DvbType, TvpData.MatchBrandFlag,TvpData.NumBrandIds, TvpData.ScrambledStatus, TvpData.InstalledSatelliteNumber,
						TvpData.NewChannel, TvpData.HbbTvOption,
						TvpData.CountryCode, TvpData.HDSimulcastRepOnId, TvpData.HDSimulcastRepTsId, TvpData.HDSimulcastRepSvcId, TvpData.ParentalRating, TvpData.ServiceIdentifier, 
						TvpData.AdultGenere, TvpData.FreesatServiceIdentifier, TvpData.InteractiveServiceEnabled, TvpData.ASignalStrength, TvpData.VSignalStrength, TvpData.QSignalStrength, 
						TvpData.ChannelInformation, TvpData.CodeRate, TvpData.PtcListVersion, TvpData.TSVersion, TvpData.SDSDFrequency, TvpData.PlpId, TvpData.BarkerMux, 0 /*TvpData.FECInner*/, 0/*TvpData.RollOff*/,
						TempString, TempString, TempArray, TempArray,
						TempArray, TempArray, TempArray, TempArray);
					}
			}
	} else {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI", "GetTvProviderBlobDataByIndex FindClass Failed ");
	}
	
	return ObjectId;
} 
	/*** TVPROVIDER IMPLEMENTATION END ***/
// Below methods will call Java Layer


/* Class:       org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:      OnCAMStatusChanged
 * Signature: (I)V
 * * */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_OnCAMStatusChanged
(JNIEnv *env, jobject obj, jint status)
{
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","OnCAMStatusChanged : status [%d] ", status);
    SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

    natiInsta->OnEvent ((CIPlusStatus_e) status);
}

/* Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  setDemuxHandle
 * Signature: (J)V

 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_setDemuxHandle
(JNIEnv *env, jobject obj, jlong demuxHandle)
{

	 SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	 natiInsta->setDemuxHandle(demuxHandle);
	 
}



int SatInstallerJNI::getSigStrength(unsigned int *Strength)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}


	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetSigStrength,Strength);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}

	return 0;
}

int SatInstallerJNI::getSigStrengthRange(unsigned int *MinStrength,unsigned int *MaxStrength)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetSigStrengthRange,MinStrength,MaxStrength);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}

	return 0;
}
int SatInstallerJNI::getParams(HsvDvbSParams * par)
{
	
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	jintArray result;
	result = threadEnv->NewIntArray(8);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","getParams out of memory ");
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
		threadEnv->CallIntMethod(m_jh, mgetParams,result);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	
	threadEnv->GetIntArrayRegion(result , 0 , 8 , (int*)params);
	threadEnv->DeleteLocalRef(result);
	
	memset (par, 0x00, sizeof(HsvDvbSParams));
	
	par->constel = params[0];
	par->symbolrate = params[1];
	par->polarization = params[2];
	par->lockstatus = params[3];
	par->lnbnumber = params[4];
	par->sqi = params[5];
	par->ssi = params[6];
	par->ber = params[7];
	
	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}

	return 0;	
}

int SatInstallerJNI::configureLNB(HsvDvbSLNBConfig lnbcfg, HsvDvbSCustomLNBConfig customlnbcfg)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mconfigureLNB,lnbcfg.LNBType, lnbcfg.LNBNumber, lnbcfg.LUserBandNumber, lnbcfg.LUserBandFrequency, lnbcfg.BurstSelect, lnbcfg.Tone, customlnbcfg.Custom_High_LO_Value, customlnbcfg.Custom_Low_LO_Value, customlnbcfg.CustomPow);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}

	return 0;
}

int SatInstallerJNI::configureUnicable(HsvDvbSUnicableConfig uccfg)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}


	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mconfigureUnicable, uccfg.UserBandNumber, uccfg.UserBandFrequency);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}

	return 0;

}

int SatInstallerJNI::setPolarization(int polarization)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetPolarization,polarization);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}

	return 0;

}

int SatInstallerJNI::setSymbolRate(int srdetectmode,int symbolrate)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetSymbolRate,srdetectmode,symbolrate);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}

	return 0;

}

int SatInstallerJNI::setPLP(Nat8 plpid)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetPLP,plpid);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}

	return 0;

}

//IPlfApiTuning
int SatInstallerJNI::tune(int freq,Bool finetune)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mtune,freq,finetune);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}
	return 0;
}

int SatInstallerJNI::getFreq(int * freq)
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","getFreq "); 	
	
	jintArray result;
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}


	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","getFreq out of memory ");
		return false;
	}
	
	int i;
	// fill a temp structure to use to populate the java int array
	jint fill[1];
	for (i = 0; i < 1; i++) {
	     fill[i] = 0; 
	}
	
	jint freqval[1];
	
	fill[0] = 0; 
	threadEnv->SetIntArrayRegion(result, 0, 1, fill);
	
	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mgetFreq,result);
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)freq);
	threadEnv->DeleteLocalRef(result);
	
	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   natvm->DetachCurrentThread();
	}
	
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","getFreq [%d] \n",*freq);

	return 0;	

}

int SatInstallerJNI::scanStart(int startfreq,int endfreq,Bool scanforward)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mscanStart,startfreq,endfreq,scanforward);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   	natvm->DetachCurrentThread();
	}

	return 0;

}

int SatInstallerJNI::scanAbort(void)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}


	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mscanAbort);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   	natvm->DetachCurrentThread();
	}


	return 0;

}

int SatInstallerJNI::scanNext(void)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;

	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}


	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mscanNext);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   	natvm->DetachCurrentThread();
	}

	return 0;

}
int SatInstallerJNI::setBand(int band)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetBand,band);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   	natvm->DetachCurrentThread();
	}

	return 0;

}

int SatInstallerJNI::setLNBConnectionType(int connectionType)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}


	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetLnbConnectionType,connectionType);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   	natvm->DetachCurrentThread();
	}

	return 0;

}


int SatInstallerJNI::setSatIPParams(int modsys,int modtype,int RollOff, int fec, int pilots)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach setSatIPParams ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}



	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, msetSatIPParams,modsys,modtype,RollOff,fec,pilots);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   	natvm->DetachCurrentThread();
	}

	return 0;

}


int SatInstallerJNI::onEvent(int eventid,int value)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;
	
	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}

	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	if(m_jh != NULL) {
		threadEnv->CallIntMethod(m_jh, mOnEvent,eventid,value);
	}  else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
	}
	if (threadEnv->ExceptionCheck()) {
		threadEnv->ExceptionDescribe();
	}	

	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
 	   	natvm->DetachCurrentThread();
	}

	return 0;
}

void  SatInstallerJNI :: RequestNit(void)
{
    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if(res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
            return ;
        } else {
            isAttached = true;
        }

    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    }else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }

    if(m_jh != NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","RequestNit");
        threadEnv->CallVoidMethod(m_jh, mRequestNit);
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }
    if (threadEnv->ExceptionCheck()) {
        threadEnv->ExceptionDescribe();
    }

    if(isAttached) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
        natvm->DetachCurrentThread();
    }

}

void  SatInstallerJNI :: RequestStatusInfo(void)
{
    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if (res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
            return;
        } else {
            isAttached = true;
        }
    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    } else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }


    if(m_jh != NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","RequestStatusInfo");
        threadEnv->CallVoidMethod(m_jh, mRequestStatusInfo);
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }
    if (threadEnv->ExceptionCheck()) {
        threadEnv->ExceptionDescribe();
    }

    if (isAttached) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
        natvm->DetachCurrentThread();
    }
}

void  SatInstallerJNI :: SendOpExit(void)
{
    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if(res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
            return;
        } else {
            isAttached = true;
        }

    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    } else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }


    if(m_jh != NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOpExit");
        threadEnv->CallVoidMethod(m_jh, mSendOpExit);
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }
    if (threadEnv->ExceptionCheck()) {
        threadEnv->ExceptionDescribe();
    }

    if(isAttached) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
        natvm->DetachCurrentThread();
    }
}

void  SatInstallerJNI :: SendOpAck(void)
{
    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if(res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
            return;
        } else {
            isAttached = true;
        }
    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    } else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }

    if(m_jh != NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOpAck");
        threadEnv->CallVoidMethod(m_jh, mSendOpAck);
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }
    if (threadEnv->ExceptionCheck()) {
        threadEnv->ExceptionDescribe();
    }

    if(isAttached) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
        natvm->DetachCurrentThread();
    }

}

void  SatInstallerJNI :: SendOpSearchCancel(void)
{
    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if(res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
            return;
        } else {
            isAttached = true;
        }

    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    }else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }

    if(m_jh != NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOpSearchCancel");
        threadEnv->CallVoidMethod(m_jh, mSendOpSearchCancel);
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }
    if (threadEnv->ExceptionCheck()) {
        threadEnv->ExceptionDescribe();
    }

    if(isAttached) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
        natvm->DetachCurrentThread();
    }

}

void  SatInstallerJNI :: SendOperatorSearchStart(Op_Search_Settings searchstart)
{
    //jclass opSearchSettingsCls  = NULL;
    //jmethodID opSearchSettingsCId = NULL;
    jobject opSearchSettings = NULL;
    jintArray serviceType	 = NULL;
    jintArray applicationCapability = NULL;
    jintArray deliveryCapability = NULL;
	jint Service_Type_Length = 1;
	jint Delivery_Cap_Length = 1;
	if(searchstart.Service_Type_Length > 0)
	{
		Service_Type_Length = searchstart.Service_Type_Length;
	}
	if(searchstart.Delivery_Cap_Length > 0)
	{
		Delivery_Cap_Length = searchstart.Delivery_Cap_Length;
	}
	
    jint serviceTypeList[searchstart.Service_Type_Length];
    jint deliveryCapList[searchstart.Delivery_Cap_Length];

    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;
    int index=0;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if(res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
            return;
        } else {
            isAttached = true;
        }
    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    } else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }

    if(m_jh != NULL) {
        //opSearchSettingsCls = (threadEnv)->FindClass ("org/droidtv/euinstallersat/model/mwapi/OperatorSearchSettings");
        if (NULL != mOpSearchSettingsCls) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","mOpSearchSettingsCls %d", mOpSearchSettingsCls);
            //opSearchSettingsCId = (threadEnv)->GetMethodID (opSearchSettingsCls, "<init>", "(II[II[II[I)V");
            if (mOpSearchSettingsCId != NULL) {
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","mOpSearchSettingsCId %d", mOpSearchSettingsCId);

                serviceType = (threadEnv)->NewIntArray(searchstart.Service_Type_Length);
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart %d", __LINE__);
                if (serviceType == NULL) {
                    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","serviceType out of memory");
                } else {
                    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart %d", __LINE__);

					if(serviceTypeList != NULL)
					{
	                    for(index=0;index < searchstart.Service_Type_Length;index++){
	                    	serviceTypeList[index] = 0;
	                    }
						
	                    for(index=0;index < searchstart.Service_Type_Length;index++){
	                    	serviceTypeList[index] = searchstart.Service_Type[index];
	                    }
	                    (threadEnv)->SetIntArrayRegion(serviceType, 0, searchstart.Service_Type_Length, serviceTypeList);
					}
					else
					{
						 __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI"," *** serviceTypeList *** out of memory");
					}
                }
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart %d", __LINE__);

                applicationCapability = (threadEnv)->NewIntArray(searchstart.Application_Cap_Length);
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart %d", __LINE__);
                if (applicationCapability == NULL) {
                    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","applicationCapability out of memory");
                } else {
                    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart %d", __LINE__);
                    (threadEnv)->SetIntArrayRegion(applicationCapability, 0, searchstart.Application_Cap_Length, (jint*)(searchstart.Application_Capability));
                }
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart %d", __LINE__);

                deliveryCapability = (threadEnv)->NewIntArray(searchstart.Delivery_Cap_Length);
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart %d", __LINE__);
                if (deliveryCapability == NULL) {
                    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","deliveryCapability out of memory");
                } else {
                    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart %d", __LINE__);
					if(deliveryCapList != NULL)
					{
	                    for(index=0;index < searchstart.Delivery_Cap_Length;index++){
	                    	deliveryCapList[index] = 0;
						}
						for(index=0;index < searchstart.Delivery_Cap_Length;index++){
							deliveryCapList[index] = searchstart.Delivery_Capability[index];
						}
					
	                	(threadEnv)->SetIntArrayRegion(deliveryCapability, 0, searchstart.Delivery_Cap_Length, deliveryCapList);
					}
					else
					{
						__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","*** deliveryCapList *** out of memory");
					}
                }
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart %d", __LINE__);

                opSearchSettings = (threadEnv)->NewObject (mOpSearchSettingsCls, mOpSearchSettingsCId, 
                                                                                    (jint) searchstart.Unattended_Flag, 
                                                                                    (jint) searchstart.Service_Type_Length, serviceType, 
                                                                                    (jint) searchstart.Delivery_Cap_Length, deliveryCapability, 
                                                                                    (jint) searchstart.Application_Cap_Length, applicationCapability);
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOperatorSearchStart");
                threadEnv->CallVoidMethod(m_jh, mSendOperatorSearchStart, opSearchSettings);
            }
        }
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }
    if (threadEnv->ExceptionCheck()) {
        threadEnv->ExceptionDescribe();
    }

    if(isAttached) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
        natvm->DetachCurrentThread();
    }
}

void  SatInstallerJNI :: SendOpTuneStatus(Op_Tune_Status tuneStatus)
{
    //jclass opTuneStatusCls  = NULL;
    //jmethodID opTuneStatusCId = NULL;
    jobject opTuneStatus = NULL;
    jintArray descriptorLoop = NULL;

    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if(res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
            return;
        } else {
            isAttached = true;
        }
    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    } else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }


    if(m_jh != NULL) {
        //opTuneStatusCls = (threadEnv)->FindClass ("org/droidtv/euinstallersat/model/mwapi/OperatorTuneStatus");
        if (NULL != mOpTuneStatusCls) {
            //opTuneStatusCId = (threadEnv)->GetMethodID (opTuneStatusCls, "<init>", "(IIIII[I)V");
            if (mOpTuneStatusCId != NULL) {

				int tempDataArray[1024],i=0;	
				for( i=0;i<tuneStatus.Descriptor_Loop_Length;i++){
					tempDataArray[i] = tuneStatus.Descriptor_Loop[i];		
;
				}

                descriptorLoop = (threadEnv)->NewIntArray(tuneStatus.Descriptor_Loop_Length);
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOpTuneStatus %d", __LINE__);
                if (descriptorLoop == NULL) {
                    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","descriptorLoop out of memory");

                } else {
                    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOpTuneStatus %d", __LINE__);
                    //(threadEnv)->SetIntArrayRegion(descriptorLoop, 0, tuneStatus.Descriptor_Loop_Length, (jint*)(tuneStatus.Descriptor_Loop));
                    (threadEnv)->SetIntArrayRegion(descriptorLoop, 0, tuneStatus.Descriptor_Loop_Length, (jint*)tempDataArray);
                }
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOpTuneStatus %d", __LINE__);

                opTuneStatus = (threadEnv)->NewObject (mOpTuneStatusCls, mOpTuneStatusCId, (jint) tuneStatus.Descriptor_Number, 
                                                                               (jint) tuneStatus.Signal_Strength, (jint) tuneStatus.Signal_Quality, 
                                                                               (jint) tuneStatus.Status, (jint) tuneStatus.Descriptor_Loop_Length, descriptorLoop);
                __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SendOpTuneStatus");
                threadEnv->CallVoidMethod(m_jh, mSendOpTuneStatus, opTuneStatus);
            }
        }
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }
    if (threadEnv->ExceptionCheck()) {
        threadEnv->ExceptionDescribe();
    }

    if(isAttached) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
        natvm->DetachCurrentThread();
    }
}

void  SatInstallerJNI :: CacheOperatorData(void)
{
    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if(res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach CacheOperatorData ");
            return;
        } else {
            isAttached = true;
        }
    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    }else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }

    if(m_jh != NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CacheOperatorData");
        threadEnv->CallVoidMethod(m_jh, mCacheOperatorData);
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }
    if (threadEnv->ExceptionCheck()) {
        threadEnv->ExceptionDescribe();
    }

    if(isAttached) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
        natvm->DetachCurrentThread();
    }

}

Op_ProfileStatusInfo SatInstallerJNI :: GetStoredOperatorData(void)
{
    Op_ProfileStatusInfo statusInfo;

    jclass opProfileStatusInfoCls = NULL;
    jobject objOpStatusInfo = NULL;
    jfieldID fid_Info_Version = NULL;
    jfieldID fid_NIT_Version = NULL;
    jfieldID fid_Profile_Type = NULL;
    jfieldID fid_Initialised_Flag = NULL;
    jfieldID fid_Entitlement_Change_Flag = NULL;
    jfieldID fid_Entitlement_Valid_Flag = NULL;
    jfieldID fid_Refresh_Request_Flag = NULL;
    jfieldID fid_Error_Flag = NULL;
    jfieldID fid_Delivery_System_Hint = NULL;
    jfieldID fid_Refresh_Request_Date = NULL;
    jfieldID fid_Refresh_Request_Time = NULL;
    jfieldID fid_InfoValid = NULL;
    jfieldID fid_ProfileInfoVersion = NULL;
    jfieldID fid_CiCamOriginalNetworkId = NULL;
    jfieldID fid_CiCamIdentifier = NULL;
    jfieldID fid_CharacterCodeTable = NULL;
    jfieldID fid_CharacterCodeTable2 = NULL;
    jfieldID fid_CharacterCodeTable3 = NULL;
    jfieldID fid_SdtRunningTrusted = NULL;
    jfieldID fid_EitRunningTrusted = NULL;
    jfieldID fid_EitPfUsage = NULL;
    jfieldID fid_EitScheduleUsage = NULL;
    jfieldID fid_ExtendedEventUsage = NULL;
    jfieldID fid_SdtOtherTrusted = NULL;
    jfieldID fid_EitEventTrigger = NULL;
    jfieldID fid_ISO639LangCode = NULL;
    jfieldID fid_ProfileNameLength = NULL;
    jfieldID fid_ProfileName 	= NULL;
    jintArray ObjProfileNameArray;
    jintArray ObjLangCodeArray;
    const int* ProfileName = NULL;
    const int* LangCode = NULL;

    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetStoredOperatorData");

    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if(res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
        } else {
            isAttached = true;
        }

    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    }else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }

    if(m_jh != NULL) {
        //opProfileStatusInfoCls = (threadEnv)->FindClass ("org/droidtv/euinstallersat/model/mwapi/OperatorProfileStatusInfo");
        if (NULL != mOpProfileStatusInfoCls) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetStoredOperatorData");
            objOpStatusInfo = threadEnv->CallObjectMethod(m_jh, mGetStoredOpData);
        }
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }

    //opProfileStatusInfoCls  	= (threadEnv)->FindClass( "org/droidtv/euinstallersat/model/mwapi/OperatorProfileStatusInfo");

    fid_Info_Version = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Info_Version", "I");
    fid_NIT_Version = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "NIT_Version", "I");
    fid_Profile_Type = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Profile_Type", "I");
    fid_Initialised_Flag = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Initialised_Flag", "I");
    fid_Entitlement_Change_Flag = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Entitlement_Change_Flag", "I");
    fid_Entitlement_Valid_Flag = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Entitlement_Valid_Flag", "I");
    fid_Refresh_Request_Flag = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Refresh_Request_Flag", "I");
    fid_Error_Flag = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Error_Flag", "I");
    fid_Delivery_System_Hint = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Delivery_System_Hint", "I");
    fid_Refresh_Request_Date = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Refresh_Request_Date", "I");
    fid_Refresh_Request_Time = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "Refresh_Request_Time", "I");

    fid_InfoValid = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "InfoValid", "I");
    fid_ProfileInfoVersion = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "ProfileInfoVersion", "I");
    fid_CiCamOriginalNetworkId = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "CiCamOriginalNetworkId", "I");
    fid_CiCamIdentifier = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "CiCamIdentifier", "I");
    fid_CharacterCodeTable = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "CharacterCodeTable", "I");
    fid_CharacterCodeTable2 = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "CharacterCodeTable2", "I");
    fid_CharacterCodeTable3 = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "CharacterCodeTable3", "I");
    fid_SdtRunningTrusted = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "SdtRunningTrusted", "I");
    fid_EitRunningTrusted = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "EitRunningTrusted", "I");
    fid_EitPfUsage = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "EitPfUsage", "I");
    fid_EitScheduleUsage = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "EitScheduleUsage", "I");
    fid_ExtendedEventUsage = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "ExtendedEventUsage", "I");
    fid_SdtOtherTrusted = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "SdtOtherTrusted", "I");
    fid_EitEventTrigger = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "EitEventTrigger", "I");
    fid_ISO639LangCode = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "ISO639LangCode", "[I");
    fid_ProfileNameLength = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "ProfileNameLength", "I");
    fid_ProfileName = (threadEnv)->GetFieldID (mOpProfileStatusInfoCls, "ProfileName", "[I");

    statusInfo.op_Status.Info_Version = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_Info_Version);
    statusInfo.op_Status.NIT_Version = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_NIT_Version);
    statusInfo.op_Status.Profile_Type = (OP_Profile)(threadEnv)->GetIntField(objOpStatusInfo, fid_Profile_Type);
    statusInfo.op_Status.Initialised_Flag = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_Initialised_Flag);
    statusInfo.op_Status.Entitlement_Change_Flag = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_Entitlement_Change_Flag);
    statusInfo.op_Status.Entitlement_Valid_Flag = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_Entitlement_Valid_Flag);
    statusInfo.op_Status.Refresh_Request_Flag = (OP_RefreshRequestFlag)(threadEnv)->GetIntField(objOpStatusInfo, fid_Refresh_Request_Flag);
    statusInfo.op_Status.Error_Flag = (OP_Error_Flag)(threadEnv)->GetIntField(objOpStatusInfo, fid_Error_Flag);
    statusInfo.op_Status.Delivery_System_Hint = (Nat16)(threadEnv)->GetIntField(objOpStatusInfo, fid_Delivery_System_Hint);
    statusInfo.op_Status.Refresh_Request_Date = (Nat16)(threadEnv)->GetIntField(objOpStatusInfo,fid_Refresh_Request_Date); 
    statusInfo.op_Status.Refresh_Request_Time = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo,fid_Refresh_Request_Time); 


    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Info_Version [%d] \n",statusInfo.op_Status.Info_Version);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","NIT_Version [%d] \n",statusInfo.op_Status.NIT_Version);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Profile_Type [%d] \n",statusInfo.op_Status.Profile_Type);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Initialised_Flag [%d] \n",statusInfo.op_Status.Initialised_Flag);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Entitlement_Change_Flag [%d] \n",statusInfo.op_Status.Entitlement_Change_Flag);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Entitlement_Valid_Flag [%d] \n",statusInfo.op_Status.Entitlement_Valid_Flag);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Refresh_Request_Flag [%d] \n",statusInfo.op_Status.Refresh_Request_Flag);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Error_Flag [%d] \n",statusInfo.op_Status.Error_Flag);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Delivery_System_Hint [%d] \n",statusInfo.op_Status.Delivery_System_Hint);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Refresh_Request_Date [%d] \n",statusInfo.op_Status.Refresh_Request_Date);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Refresh_Request_Time [%d] \n",statusInfo.op_Status.Refresh_Request_Time);

    statusInfo.op_Info.info_Valid = (Nat8) (threadEnv)->GetIntField(objOpStatusInfo, fid_InfoValid);
    statusInfo.op_Info.info_Version = (Nat8) (threadEnv)->GetIntField(objOpStatusInfo, fid_ProfileInfoVersion);
    statusInfo.op_Info.cicam_Original_Network_Id = (Nat16) (threadEnv)->GetIntField(objOpStatusInfo, fid_CiCamOriginalNetworkId);
    statusInfo.op_Info.cicam_Identifier = (int) (threadEnv)->GetIntField(objOpStatusInfo, fid_CiCamIdentifier);
    statusInfo.op_Info.character_Code_Table = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_CharacterCodeTable);
    statusInfo.op_Info.character_Code_Table_2 = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_CharacterCodeTable2);
    statusInfo.op_Info.character_Code_Table_3 = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_CharacterCodeTable3);
    statusInfo.op_Info.sDT_Running_Trusted = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_SdtRunningTrusted);
    statusInfo.op_Info.eIT_Running_Trusted = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo, fid_EitRunningTrusted);
    statusInfo.op_Info.eIT_Pf_Usage = (OP_EIT_pfUsage)(threadEnv)->GetIntField(objOpStatusInfo,fid_EitPfUsage); 
    statusInfo.op_Info.eIT_Schedule_Usage = (OP_EIT_schedUsage)(threadEnv)->GetIntField(objOpStatusInfo,fid_EitScheduleUsage); 
    statusInfo.op_Info.extended_Event_Usage = (int)(threadEnv)->GetIntField(objOpStatusInfo,fid_ExtendedEventUsage); 
    statusInfo.op_Info.sDT_Other_Trusted = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo,fid_SdtOtherTrusted); 
    statusInfo.op_Info.eIT_Event_Trigger = (Nat8)(threadEnv)->GetIntField(objOpStatusInfo,fid_EitEventTrigger); 
    statusInfo.op_Info.profile_Name_Length = (short)(threadEnv)->GetIntField(objOpStatusInfo,fid_ProfileNameLength); 

    /* Lang Code Array */
    ObjLangCodeArray = (jintArray) (threadEnv)->GetObjectField(objOpStatusInfo, fid_ISO639LangCode);

    if(NULL != ObjLangCodeArray) 
    {
        LangCode = (int *) (threadEnv)->GetIntArrayElements(ObjLangCodeArray, 0);
        if(LangCode != NULL)
        {
            for(int i = 0; i < 3; i++)
            {
                statusInfo.op_Info.iSO_639_Lang_Code[i] = (Nat8) LangCode[i];
            }
        }
    }

    /* Profile Name Array */
    ObjProfileNameArray = (jintArray) (threadEnv)->GetObjectField(objOpStatusInfo, fid_ProfileName);

    if(NULL != ObjProfileNameArray) 
    {
        ProfileName = (int *) (threadEnv)->GetIntArrayElements(ObjProfileNameArray, 0);
        if(ProfileName != NULL)
        {
            for(int i = 0; i < statusInfo.op_Info.profile_Name_Length; i++)
            {
                statusInfo.op_Info.profile_Name[i] = (Nat8) ProfileName[i];
            }
            statusInfo.op_Info.profile_Name[statusInfo.op_Info.profile_Name_Length] = '\0';
        }
    }
    else
    {
        statusInfo.op_Info.profile_Name_Length = 0;
    }

    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","InfoValid [%d] \n",statusInfo.op_Info.info_Valid);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","ProfileInfoVersion [%d] \n",statusInfo.op_Info.info_Version);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CiCamOriginalNetworkId [%d] \n",statusInfo.op_Info.cicam_Original_Network_Id);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CiCamIdentifier [%d] \n",statusInfo.op_Info.cicam_Identifier);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CharacterCodeTable [%d] \n",statusInfo.op_Info.character_Code_Table);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CharacterCodeTable2 [%d] \n",statusInfo.op_Info.character_Code_Table_2);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","CharacterCodeTable3 [%d] \n",statusInfo.op_Info.character_Code_Table_3);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","SdtRunningTrusted [%d] \n",statusInfo.op_Info.sDT_Running_Trusted);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","EitRunningTrusted [%d] \n",statusInfo.op_Info.eIT_Running_Trusted);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","EitPfUsage [%d] \n",statusInfo.op_Info.eIT_Pf_Usage);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","EitScheduleUsage [%d] \n",statusInfo.op_Info.eIT_Schedule_Usage);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","ExtendedEventUsage [%d] \n",statusInfo.op_Info.extended_Event_Usage);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","sDT_Other_Trusted [%d] \n",statusInfo.op_Info.sDT_Other_Trusted);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","eIT_Event_Trigger [%d] \n",statusInfo.op_Info.eIT_Event_Trigger);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","profile_Name_Length [%d] \n",statusInfo.op_Info.profile_Name_Length);
    __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","profile_Name [%s] \n", statusInfo.op_Info.profile_Name);

    return statusInfo;
}

void  SatInstallerJNI :: GetCipStatus (Nat8 *status)
{
    JNIEnv *threadEnv = NULL; 
    bool isAttached = false;

    int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv : not attached so attach");
        int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
        if(res != 0) {
            __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach GetEnv ");
            return ;
        } else {
            isAttached = true;
        }

    } else if (getEnvStat == JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
    }else if (getEnvStat == JNI_EVERSION) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    }

    if(m_jh != NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetCipStatus");
        *status = threadEnv->CallIntMethod(m_jh, mGetCipStatus);
    }  else {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is null");
    }
    if (threadEnv->ExceptionCheck()) {
        threadEnv->ExceptionDescribe();
    }

    if(isAttached) {
        __android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
        natvm->DetachCurrentThread();
    }

}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    setConnectionType
 * Signature: (II)V;
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_setConnectionType
  (JNIEnv *, jobject,jint connectionType,jint tuner_id)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);

	HsvLnbSettings lnbsettings;
	natiInsta->GetLnbSettings(&lnbsettings);
	if(lnbsettings.ConnectionType != connectionType) {
		natiInsta->GetLnbSettings(&lnbsettings);
		switch(connectionType) {
			case LnbConnectionSingle:
				lnbsettings.LnbSettings[0].LnbType = LnbUniversal;
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[0]));
				break;
			case LnbConnectionDiSeqcMini:
				lnbsettings.LnbSettings[0].LnbType = LnbUniversal;
				lnbsettings.LnbSettings[1].LnbType = LnbUniversal;
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[0]));
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[1]));
				break;
			case LnbConnectionDiSeqc1_0:
				lnbsettings.LnbSettings[0].LnbType = LnbUniversal;
				lnbsettings.LnbSettings[1].LnbType = LnbUniversal;
				lnbsettings.LnbSettings[2].LnbType = LnbUniversal;
				lnbsettings.LnbSettings[3].LnbType = LnbUniversal;
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[0]));
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[1]));
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[2]));
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[3]));
				break;
			case LnbConnectionUnicableLnb:
				lnbsettings.LnbSettings[0].LnbType = LnbUnicable;
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[0]));
				// For Dual Tuner 
				if(1 == tuner_id) {
					lnbsettings.LnbSettings[2].LnbType = LnbUnicable;;
					natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[2]));
				}	
				break;
			case  LnbConnectionUnicableSwitch:
				lnbsettings.LnbSettings[0].LnbType = LnbUnicable;
				lnbsettings.LnbSettings[1].LnbType = LnbUnicable;
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[0]));
				natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[1]));
				//For Dual Tuner 
				if(1 == tuner_id) {
					lnbsettings.LnbSettings[2].LnbType = LnbUnicable;
					lnbsettings.LnbSettings[3].LnbType = LnbUnicable;;
					natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[2]));
					natiInsta->GetDefaultValues(&(lnbsettings.LnbSettings[3]));
				}
				break;
		}	
		lnbsettings.ConnectionType = (HsvLnbConnectionType)connectionType;
	} else {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI"," Connection Type is Same \n");
	}

	natiInsta->SetLnbSettings(&lnbsettings);
}

/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetLnbType
 * Signature: (I)I

 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetLnbType
(JNIEnv *env, jobject obj, jint index)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	int i = 0;
	HsvLnbSettings LnbSettings;
	jint lnbtype = 0;
	
	natiInsta->GetLnbSettings(&LnbSettings);
	lnbtype = LnbSettings.LnbSettings[index].LnbType;
	return lnbtype;
}

/* Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  getLnbStatus
 * Signature: (I)I

 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_getLnbStatus
(JNIEnv *env, jobject obj, jint index)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	int i = 0;
	HsvLnbSettings LnbSettings;
	jint lnbStatus = 0;	
	natiInsta->GetLnbSettings(&LnbSettings);
	lnbStatus = LnbSettings.LnbSettings[index].LnbStatus;

	return lnbStatus;
}

/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetHighLoFreq
 * Signature: (I)I

 * * */
JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetHighLoFreq
(JNIEnv *env, jobject obj, jint index)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	int i = 0;
	HsvLnbSettings LnbSettings;
	jint highLoFreq = 0 ;	
	natiInsta->GetLnbSettings(&LnbSettings);
	highLoFreq = LnbSettings.LnbSettings[index].HighLoFreq;
	return highLoFreq;
}


/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetLowLoFreq
 * Signature: (I)I

 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetLowLoFreq
(JNIEnv *env, jobject obj, jint index)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	int i = 0;
	HsvLnbSettings LnbSettings;
	jint LowLoFreq = 0 ;	
	
	natiInsta->GetLnbSettings(&LnbSettings);
	LowLoFreq = LnbSettings.LnbSettings[index].LowLoFreq;
	return LowLoFreq;

}



/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetToneControl
 * Signature: (I)B

 * * */

JNIEXPORT jbyte JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetToneControl
(JNIEnv *env, jobject obj, jint index)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	int i = 0;
	jobject lnbSettings = NULL;
	HsvLnbSettings LnbSettings;
	jbyte toneControl = 0;
	natiInsta->GetLnbSettings(&LnbSettings);
	toneControl = LnbSettings.LnbSettings[index].ToneControl;
	return toneControl;
}

/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetLnbPower
 * Signature: (I)B


 * * */

JNIEXPORT jbyte JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetLnbPower
(JNIEnv *env, jobject obj, jint index)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	int i = 0;
	jobject lnbSettings = NULL;
	HsvLnbSettings LnbSettings;
	jbyte lnbPower = 0;
	natiInsta->GetLnbSettings(&LnbSettings);
	lnbPower = LnbSettings.LnbSettings[index].LnbPower;
	return lnbPower;
}



/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetUserBand
 * Signature: (I)B

 * * */

JNIEXPORT jbyte JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetUserBand
(JNIEnv *env, jobject obj, jint index)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	int i = 0;
	HsvLnbSettings LnbSettings;
	jbyte userband = 0; 	
	natiInsta->GetLnbSettings(&LnbSettings);
	userband = LnbSettings.LnbSettings[index].UserBand;
	return userband;
}

/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetUserFrequency
 * Signature: (I)I

 * * */

JNIEXPORT jint JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetUserFrequency
(JNIEnv *env, jobject obj, jint index)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	int i = 0;
	HsvLnbSettings LnbSettings;
	jint userFreq = 0;
	natiInsta->GetLnbSettings(&LnbSettings);
	userFreq = LnbSettings.LnbSettings[index].UserBandFrequency;
	return userFreq;

}

/* Class:	  org_droidtv_euinstallersat
 * Method:	  GetUpdateInstallEnabled
 * Signature: (I)Z

 * * */

JNIEXPORT jboolean JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_GetUpdateInstallEnabled
(JNIEnv *env, jobject obj, jint index)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	int i = 0;
	jobject lnbSettings = NULL;
	HsvLnbSettings LnbSettings;
	
	natiInsta->GetLnbSettings(&LnbSettings);
	jboolean updatedInstallEnables = 0;
	updatedInstallEnables = LnbSettings.LnbSettings[index].UpdateInstallEnabled;
	
	return updatedInstallEnables;
}
/* Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  SelectLNBForUpdate
 * Signature: (Z)V

 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_SelectLNBForUpdate
(JNIEnv *env, jobject obj, jint index, jboolean updateInstallFlag)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	HsvLnbSettings LnbSettings;
	
	natiInsta->GetLnbSettings(&LnbSettings);
	
	LnbSettings.LnbSettings[index].UpdateInstallEnabled = updateInstallFlag;

	natiInsta->SetLnbSettings(&LnbSettings);
	
}

/* Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  setLnbpower
 * Signature: (IB)V

 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_setLnbpower
(JNIEnv *env, jobject obj, jint index,jbyte powerstate)
{

	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	HsvLnbSettings LnbSettings;
	
	int  i = 0;
	for(i = 0; i < 4; i++) {
		if(index == i) {
			natiInsta->GetLnbSettings(&LnbSettings);
			LnbSettings.LnbSettings[i].LnbPower = powerstate;
			break;
		}
	}
	natiInsta->SetLnbSettings(&LnbSettings);
}
/* Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  settotone
 * Signature: (IB)V

 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_settotone
(JNIEnv *env, jobject obj, jint index,jbyte toneControl)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	HsvLnbSettings LnbSettings;
	
	int  i = 0;
	for(i = 0; i < 4; i++) {
		if(index == i) {
			natiInsta->GetLnbSettings(&LnbSettings);
			LnbSettings.LnbSettings[i].ToneControl = toneControl;
			break;
		}
	}
	natiInsta->SetLnbSettings(&LnbSettings);
}
/* Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  setlnbLowLoFrequency
 * Signature: (II)V

 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_setlnbLowLoFrequency
(JNIEnv *env, jobject obj, jint index,jint frequency)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	HsvLnbSettings LnbSettings;
	
	int  i = 0;
	for(i = 0; i < 4; i++) {
		if(index == i) {
			natiInsta->GetLnbSettings(&LnbSettings);
			LnbSettings.LnbSettings[i].LowLoFreq = frequency;
			break;
		}
	}
	natiInsta->SetLnbSettings(&LnbSettings);

}
/* Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	  setlnbHighLoFrequency
 * Signature: (II)V

 * * */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_setlnbHighLoFrequency
(JNIEnv *env, jobject obj, jint index,jint frequency)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	HsvLnbSettings LnbSettings;
	
	int  i = 0;
	for(i = 0; i < 4; i++) {
		if(index == i) {
			natiInsta->GetLnbSettings(&LnbSettings);
			LnbSettings.LnbSettings[i].HighLoFreq = frequency;
			break;
		}
	}
	natiInsta->SetLnbSettings(&LnbSettings);

}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    setPostCode
 * Signature: (ILjava/lang/String;)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_setPostCode
  (JNIEnv *env, jobject obj, jint pCodeLen,jstring pCode)
 {
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	jboolean isCp;
	const char *pcode = env->GetStringUTFChars(pCode, &isCp);

	natiInsta->setPostCode(pCodeLen,(char*)pcode);

	env->ReleaseStringUTFChars(pCode,pcode);
 }

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    startTricolorRegionParsing
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_startTricolorRegionParsing
  (JNIEnv *env, jobject)
{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->StartTricolorRegionParsing ();

}

/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    setTricolorRegionIndex
 * Signature: (I)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_setTricolorRegionIndex
  (JNIEnv *env, jobject obj, jint selectedIndex)

{
	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	natiInsta->SetTricolorRegionIndex (selectedIndex);

}


/*
 * Class:     org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:    getTricolorRegionNames
 * Signature: ()[LJava.lang.String
 */

JNIEXPORT jobjectArray JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_getTricolorRegionNames
  (JNIEnv *env, jobject)
{

	Nat16 (**regionNames)=NULL;
	int listLength,i,j;
	jchar  RegionNameConverted[24];	
	jobjectArray arrNames=NULL;
	

	jclass intArrCls = env->FindClass("java/lang/String");



	if(intArrCls != NULL)
	{
		regionNames = (Nat16**) malloc (10 * sizeof(regionNames));

		if(regionNames != NULL)
		{
			SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
			natiInsta->GetTricolorRegionNames ((Nat16 **)&regionNames[0], &listLength);
			
			if (0 != listLength)
			{

				for(i = 0; i < 24; i++) 
				{
	               RegionNameConverted[i] = '\0';
	               
	            }

				arrNames = (jobjectArray)env->NewObjectArray(listLength,intArrCls,NULL);
			
				for(i=0; i<listLength; i++) 
				{
					for (j=0; j<23; j++)
					{
						if (regionNames[i][j] != 0x00)
						{
							RegionNameConverted[j] = regionNames[i][j];
						}
						else
						{
							break;
						}
					}
					
					RegionNameConverted[j] = '\0';
					env->SetObjectArrayElement(arrNames,i,env->NewString(RegionNameConverted,j));			
				}
			}
		}
		free(regionNames);
	}
	else
	{
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","intArrcls is NULL");
	}

	

	
	return arrNames;
}



int SatInstallerJNI::GetValuesFromGlobalSettings(jint id,int *val)
{
	JNIEnv *threadEnv = NULL; 
	bool isAttached = false;

	int getEnvStat = natvm->GetEnv(reinterpret_cast<void**>(&threadEnv), JNI_VERSION_1_6);
	if (getEnvStat == JNI_EDETACHED) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: not attached so attach");
		int res = natvm->AttachCurrentThread(&threadEnv, (void *) NULL);
		if(res != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","Failed to attach getFreq ");
			return -1;
		} else {
			isAttached = true;
		}
	} else if (getEnvStat == JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv AttachtoJavaThread Success \n");
	}else if (getEnvStat == JNI_EVERSION) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: version not supported");
    	}

	jintArray result;
	result = threadEnv->NewIntArray(1);
	if (result == NULL) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","getValueFromTVContentProvider out of memory ");
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
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","m_jh is  null");
	}
	threadEnv->GetIntArrayRegion(result , 0 , 1 , (int*)val);
	threadEnv->DeleteLocalRef(result);
	if (threadEnv->ExceptionCheck()) {
			threadEnv->ExceptionDescribe();
	}
	if(isAttached) {
		__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","GetEnv: attached so detach");
		natvm->DetachCurrentThread();
	}	
	return 0;
}

/*
 * Class:	  org_droidtv_euinstallersat_model_mwapi_SatInstaller_PopulateMW
 * Method:	  PopulateMW
 * Signature: (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_PopulateMW
	(JNIEnv *env, jobject obj, jobject objTvpData, jint Clear)
{

	SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
	HsvPgdatTvProviderBlobData TvpData;

	if(!Clear)
	{
		jstring ObjChannelName;
		jintArray	ObjBrandIds;
		jintArray	ObjMultipleLCN;
		jintArray	ObjMultiplePreset;
		jintArray	ObjMultipleFavorite;
		jstring	ObjSatelliteName;
		jintArray	ObjMultipleVisibleService;
		jintArray	ObjMultipleNumericSelect;

		const jchar* ChannelName = NULL;
		const jint* BrandIds	= NULL;
		const jint* MultipleLCN	= NULL;
		const jint* MultiplePreset	= NULL;
		const jint* MultipleFavorite	= NULL;
		const jchar* SatelliteName	= NULL;
		const jint* MultipleVisibleService = NULL;
		const jint* MultipleNumericSelect = NULL;


		#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)      	jfieldID fid_##item = NULL;
		#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, ana, srv, ts)      	jfieldID fid_##item = NULL;
		#define TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)      	jfieldID fid_##item = NULL;
		#define TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)      jfieldID fid_##item = NULL;
		#define TVPROVIDER_SATINFO_ITEM(item, type, bit, siz, def)      	jfieldID fid_##item = NULL;
		#define TVPROVIDER_VECTOR_ITEM(item, type, bit, siz, def)		jfieldID fid_##item = NULL;

		#include "hsvpgdat_tvproviderblobdata.h"
		
		#undef  TVPROVIDER_PRESET_ITEM
		#undef  TVPROVIDER_DIGSRVC_ITEM
		#undef 	TVPROVIDER_SATINFO_ITEM
		#undef 	TVPROVIDER_COMMON_ITEM
		#undef 	TVPROVIDER_DIGTS_ITEM
		#undef	TVPROVIDER_VECTOR_ITEM


		jclass SatInstallerTvProviderDataClass	= (env)->FindClass( "org/droidtv/euinstallersat/model/mwapi/SatInstallerTvProviderData");


		
		fid_PresetNumber = (env)->GetFieldID ( SatInstallerTvProviderDataClass, "PresetNumber", "I");
		if(fid_PresetNumber == NULL)
		{
		}
		
		fid_OriginalNetworkId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "OriginalNetworkId", "I");
		fid_Tsid = (env)->GetFieldID (SatInstallerTvProviderDataClass, "Tsid", "I");
		fid_ServiceId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ServiceId", "I");
		fid_Frequency = (env)->GetFieldID (SatInstallerTvProviderDataClass, "Frequency", "I");
		fid_TextSubTitlePage = (env)->GetFieldID (SatInstallerTvProviderDataClass, "TextSubTitlePage", "I");
		fid_LogoURL = (env)->GetFieldID (SatInstallerTvProviderDataClass, "LogoURL", "I");
		fid_DecoderType = (env)->GetFieldID (SatInstallerTvProviderDataClass, "DecoderType", "I");
		fid_ModulationType = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ModulationType", "I");
		fid_UserModifiedLogo = (env)->GetFieldID (SatInstallerTvProviderDataClass, "UserModifiedLogo", "I");
		fid_SAP = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SAP", "I");
		fid_PreferredStereo = (env)->GetFieldID (SatInstallerTvProviderDataClass, "PreferredStereo", "I");
		fid_Ptc = (env)->GetFieldID (SatInstallerTvProviderDataClass, "Ptc", "I");
		fid_SymbolRate = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SymbolRate", "I");
		fid_AudioPid = (env)->GetFieldID (SatInstallerTvProviderDataClass, "AudioPid", "I");
		fid_VideoPid = (env)->GetFieldID (SatInstallerTvProviderDataClass, "VideoPid", "I");
		fid_PcrPid = (env)->GetFieldID (SatInstallerTvProviderDataClass, "PcrPid", "I");
		fid_NetworkId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "NetworkId", "I");
		fid_LCN = (env)->GetFieldID (SatInstallerTvProviderDataClass, "LCN", "I");
		fid_ServiceType = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ServiceType", "I");
		fid_SystemHidden = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SystemHidden", "I");
		fid_NumericSelect = (env)->GetFieldID (SatInstallerTvProviderDataClass, "NumericSelect", "I");
		fid_Bandwidth = (env)->GetFieldID (SatInstallerTvProviderDataClass, "Bandwidth", "I");
		fid_ScrambledStatus = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ScrambledStatus", "I");
		fid_IntHbbTvOption = (env)->GetFieldID (SatInstallerTvProviderDataClass, "IntHbbTvOption", "I");
		fid_UserHidden = (env)->GetFieldID (SatInstallerTvProviderDataClass, "UserHidden", "I");
		fid_NewPreset = (env)->GetFieldID (SatInstallerTvProviderDataClass, "NewPreset", "I");
		fid_VideoStreamType = (env)->GetFieldID (SatInstallerTvProviderDataClass, "VideoStreamType", "I");
		fid_AudioStreamType = (env)->GetFieldID (SatInstallerTvProviderDataClass, "AudioStreamType", "I");
		fid_LnbNumber = (env)->GetFieldID (SatInstallerTvProviderDataClass, "LnbNumber", "I");
		fid_Polarization = (env)->GetFieldID (SatInstallerTvProviderDataClass, "Polarization", "I");
		fid_DpTsid = (env)->GetFieldID (SatInstallerTvProviderDataClass, "DpTsid", "I");
		fid_DpServiceId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "DpServiceId", "I");
		fid_Tpid = (env)->GetFieldID (SatInstallerTvProviderDataClass, "Tpid", "I");
		fid_PackageGroup = (env)->GetFieldID (SatInstallerTvProviderDataClass, "PackageGroup", "I");
		fid_FavoriteNumber = (env)->GetFieldID (SatInstallerTvProviderDataClass, "FavoriteNumber", "I");
		fid_VisibleService = (env)->GetFieldID (SatInstallerTvProviderDataClass, "VisibleService", "I");
		fid_LnbType = (env)->GetFieldID (SatInstallerTvProviderDataClass, "LnbType", "I");
		fid_SatelliteId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SatelliteId", "I");
		fid_OrbitalPosition = (env)->GetFieldID (SatInstallerTvProviderDataClass, "OrbitalPosition", "I");
		fid_UniqueId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "UniqueId", "I");
		fid_SignalStrength = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SignalStrength", "I");
		fid_SignalQuality = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SignalQuality", "I");
		fid_AppsCookie = (env)->GetFieldID (SatInstallerTvProviderDataClass, "AppsCookie", "I");
		fid_SDTVersion = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SDTVersion", "I");
		fid_NITVersion = (env)->GetFieldID (SatInstallerTvProviderDataClass, "NITVersion", "I");
		fid_DateStamp = (env)->GetFieldID (SatInstallerTvProviderDataClass, "DateStamp", "I");
		fid_PmtPid = (env)->GetFieldID (SatInstallerTvProviderDataClass, "PmtPid", "I");
		fid_SecAudioPid = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SecAudioPid", "I");
		fid_LowPrioLCN = (env)->GetFieldID (SatInstallerTvProviderDataClass, "LowPrioLCN", "I");
		fid_LowPrioVisibleService = (env)->GetFieldID (SatInstallerTvProviderDataClass, "LowPrioVisibleService", "I");
		fid_FreeCiMode = (env)->GetFieldID (SatInstallerTvProviderDataClass, "FreeCiMode", "I");
		fid_VideoDescPresent = (env)->GetFieldID (SatInstallerTvProviderDataClass, "VideoDescPresent", "I");
		fid_ScramblingStatus = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ScramblingStatus", "I");
		fid_DuplicateSvc = (env)->GetFieldID (SatInstallerTvProviderDataClass, "DuplicateSvc", "I");
		fid_ServiceListVersion = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ServiceListVersion", "I");
		fid_UserInstalled = (env)->GetFieldID (SatInstallerTvProviderDataClass, "UserInstalled", "I");
		fid_SecAudioStreamType = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SecAudioStreamType", "I");
		fid_UserModifiedName = (env)->GetFieldID (SatInstallerTvProviderDataClass, "UserModifiedName", "I");
		fid_ChannelLock = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ChannelLock", "I");
		fid_DvbType = (env)->GetFieldID (SatInstallerTvProviderDataClass, "DvbType", "I");
		fid_MatchBrandFlag = (env)->GetFieldID (SatInstallerTvProviderDataClass, "MatchBrandFlag", "I");
		fid_NumBrandIds = (env)->GetFieldID (SatInstallerTvProviderDataClass, "NumBrandIds", "I");
		fid_InstalledSatelliteNumber = (env)->GetFieldID (SatInstallerTvProviderDataClass, "InstalledSatelliteNumber", "I");
		fid_NewChannel = (env)->GetFieldID (SatInstallerTvProviderDataClass, "NewChannel", "I");
		fid_HbbTvOption = (env)->GetFieldID (SatInstallerTvProviderDataClass, "HbbTvOption", "I");
		fid_SDSDFrequency = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SDSDFrequency", "I");
		fid_CountryCode = (env)->GetFieldID (SatInstallerTvProviderDataClass, "CountryCode", "I");
		fid_HDSimulcastRepOnId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "HDSimulcastRepOnId", "I");
		fid_HDSimulcastRepTsId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "HDSimulcastRepTsId", "I");
		fid_HDSimulcastRepSvcId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "HDSimulcastRepSvcId", "I");
		fid_ParentalRating = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ParentalRating", "I");
		fid_ServiceIdentifier = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ServiceIdentifier", "I");
		fid_AdultGenere = (env)->GetFieldID (SatInstallerTvProviderDataClass, "AdultGenere", "I");
		fid_FreesatServiceIdentifier = (env)->GetFieldID (SatInstallerTvProviderDataClass, "FreesatServiceIdentifier", "I");
		fid_InteractiveServiceEnabled = (env)->GetFieldID (SatInstallerTvProviderDataClass, "InteractiveServiceEnabled", "I");
		fid_ASignalStrength = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ASignalStrength", "I");
		fid_VSignalStrength = (env)->GetFieldID (SatInstallerTvProviderDataClass, "VSignalStrength", "I");
		fid_QSignalStrength = (env)->GetFieldID (SatInstallerTvProviderDataClass, "QSignalStrength", "I");
		fid_ChannelInformation = (env)->GetFieldID (SatInstallerTvProviderDataClass, "ChannelInformation", "I");
		fid_CodeRate = (env)->GetFieldID (SatInstallerTvProviderDataClass, "CodeRate", "I");
		fid_PtcListVersion = (env)->GetFieldID (SatInstallerTvProviderDataClass, "PtcListVersion", "I");
		fid_TSVersion = (env)->GetFieldID (SatInstallerTvProviderDataClass, "TSVersion", "I");
		fid_PlpId = (env)->GetFieldID (SatInstallerTvProviderDataClass, "PlpId", "I");
		fid_BarkerMux = (env)->GetFieldID (SatInstallerTvProviderDataClass, "BarkerMux", "I");
		/*TODO: Use this for SAT-IP*/
//		fid_FECInner = (env)->GetFieldID (SatInstallerTvProviderDataClass, "FECInner", "I");
//		fid_RollOff = (env)->GetFieldID (SatInstallerTvProviderDataClass, "RollOff", "I");

		fid_ChannelName = 	(env)->GetFieldID (SatInstallerTvProviderDataClass, "ChannelName", "Ljava/lang/String;");
		fid_BrandIds = 	(env)->GetFieldID (SatInstallerTvProviderDataClass, "BrandIds", "[I");
		fid_MultipleLCN = 	(env)->GetFieldID (SatInstallerTvProviderDataClass, "MultipleLCN", "[I");
		fid_MultiplePreset = 	(env)->GetFieldID (SatInstallerTvProviderDataClass, "MultiplePreset", "[I");
		fid_MultipleFavorite = (env)->GetFieldID (SatInstallerTvProviderDataClass, "MultipleFavorite", "[I");
		fid_SatelliteName = (env)->GetFieldID (SatInstallerTvProviderDataClass, "SatelliteName", "Ljava/lang/String;");
		fid_MultipleVisibleService = (env)->GetFieldID (SatInstallerTvProviderDataClass, "MultipleVisibleService", "[I");
		fid_MultipleNumericSelect = (env)->GetFieldID (SatInstallerTvProviderDataClass, "MultipleNumericSelect", "[I");
	
		#define TVPROVIDER_PRESET_ITEM(item, type, bit, siz, def)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
		#define TVPROVIDER_COMMON_ITEM(item, type, bit, siz, def, pre, ana, srv, ts)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
		#define TVPROVIDER_DIGTS_ITEM(item, type, bit, siz, def)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
		#define TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
//		#define TVPROVIDER_DIGSRVC_ITEM(item, type, bit, siz, def)		
		#define TVPROVIDER_SATINFO_ITEM(item, type, bit, siz, def)		TvpData.item = (type)(env)->GetIntField(objTvpData, fid_##item);
		#define TVPROVIDER_VECTOR_ITEM(item, type, bit, siz, def)

		#include "hsvpgdat_tvproviderblobdata.h"
		
		#undef	TVPROVIDER_PRESET_ITEM
		#undef	TVPROVIDER_DIGSRVC_ITEM
		#undef	TVPROVIDER_SATINFO_ITEM
		#undef	TVPROVIDER_COMMON_ITEM
		#undef	TVPROVIDER_DIGTS_ITEM
		#undef	TVPROVIDER_VECTOR_ITEM
		
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
		}


		
		/* BrandIds */
		
		ObjBrandIds = (jintArray) (env)->GetObjectField(objTvpData, fid_BrandIds);
		
		if(NULL != ObjBrandIds) 
		{
		
			int length = (env)->GetArrayLength(ObjBrandIds);
;

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
		}

		/* MultipleLCN */
		
		ObjMultipleLCN = (jintArray) (env)->GetObjectField(objTvpData, fid_MultipleLCN);
		
		if(NULL != ObjMultipleLCN) 
		{
		
			int length = (env)->GetArrayLength(ObjMultipleLCN);

			int  i = 0;
			MultipleLCN = (jint *)(env)->GetIntArrayElements(ObjMultipleLCN, NULL);
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
		}

		/* MultiplePreset */
		
		ObjMultiplePreset = (jintArray) (env)->GetObjectField(objTvpData, fid_MultiplePreset);
		
		if(NULL != ObjMultiplePreset) 
		{
		
			int length = (env)->GetArrayLength(ObjMultiplePreset);
;

			int  i = 0;
			MultiplePreset = (jint *) (env)->GetIntArrayElements(ObjMultiplePreset, NULL);
	        if(MultiplePreset != NULL)
			{
				for(i = 0; (i < length) && (i < 8) ; i++)
				{
					TvpData.MultiplePreset[i] = MultiplePreset[i];
				}
			}
;
	    }
		else
		{
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
		}


		/* SatelliteName */
		
		ObjSatelliteName = (jstring) (env)->GetObjectField(objTvpData, fid_SatelliteName);

		
		if(NULL != ObjSatelliteName) 
		{
		
			int length = (env)->GetStringLength(ObjSatelliteName);

			memset (TvpData.SatelliteName, 0x00, sizeof(TvpData.SatelliteName));

			int  i = 0;
			SatelliteName = (jchar *) (env)->GetStringChars(ObjSatelliteName, NULL);
	        if(SatelliteName != NULL)
			{
				for(i = 0; (i < length) && (i < 23) ; i++)
				{
					TvpData.SatelliteName[i] = SatelliteName[i];
				}
			}
			if( i < 23)
			{
				TvpData.SatelliteName[i] = '\0';
			}

			/*TODO: remove extra print*/
			const jbyte *str;
			str = (jbyte *)(env)->GetStringUTFChars(ObjSatelliteName, NULL);
	    }
		else
		{
		}

		/* MultipleVisibleService */
		
		ObjMultipleVisibleService = (jintArray) (env)->GetObjectField(objTvpData, fid_MultipleVisibleService);

		
		if(NULL != ObjMultipleVisibleService) 
		{
		
			int length = (env)->GetArrayLength(ObjMultipleVisibleService);

			int  i = 0;
			MultipleVisibleService = (jint *) (env)->GetIntArrayElements(ObjMultipleVisibleService, NULL);
	        if(MultipleVisibleService != NULL)
			{
				for(i = 0; (i < length) && (i < 8) ; i++)
				{
					TvpData.MultipleVisibleService[i] = MultipleVisibleService[i];
				}
			}
			
	    }
		else
		{
		}
		



		/* MultipleNumericSelect */
		
		ObjMultipleNumericSelect = (jintArray) (env)->GetObjectField(objTvpData, fid_MultipleNumericSelect);

		
		if(NULL != ObjMultipleNumericSelect) 
		{
		
			int length = (env)->GetArrayLength(ObjMultipleNumericSelect);

		

			int  i = 0;
			MultipleNumericSelect = (jint *) (env)->GetIntArrayElements(ObjMultipleNumericSelect, NULL);
	        if(MultipleNumericSelect != NULL)
			{
				for(i = 0; (i < length) && (i < 8) ; i++)
				{
					TvpData.MultipleNumericSelect[i] = MultipleNumericSelect[i];
				}
			}
		
	    }
		else
		{
		}

	

		natiInsta->AddTvpData(&TvpData,Clear);
	}
    else
	{
		natiInsta->AddTvpData(&TvpData,Clear);
	}
}


/*
 * Class:	        org_droidtv_euinstallersat_model_mwapi_SatInstaller
 * Method:	 syncUniqueIdToMW
 * Signature:   (jObject)V
 */

JNIEXPORT void JNICALL Java_org_droidtv_euinstallersat_model_mwapi_SatInstaller_syncUniqueIdToMW
	(JNIEnv *env, jobject obj, jobject tvpDataObj)
{

    SatInstaller* natiInsta = reinterpret_cast<SatInstaller*>(jh);
    HsvPgdatTvProviderBlobData TvpData;

    jclass SatInstallerTvProviderDataClass	= NULL;
    jintArray	ObjMultiplePreset;
    const jint* MultiplePreset	= NULL;

    jfieldID fid_OriginalNetworkId	= NULL;
    jfieldID fid_Tsid	= NULL;
    jfieldID fid_ServiceId	= NULL;
    jfieldID fid_Tpid	= NULL;
    jfieldID fid_PresetNumber	= NULL;
    jfieldID fid_UniqueId	= NULL;
    jfieldID fid_MultiplePreset	= NULL;

    SatInstallerTvProviderDataClass = (env)->FindClass( "org/droidtv/euinstallersat/model/mwapi/SatInstallerTvProviderData");

    fid_OriginalNetworkId = (env)->GetFieldID ( SatInstallerTvProviderDataClass, "OriginalNetworkId", "I");
    fid_Tsid = (env)->GetFieldID ( SatInstallerTvProviderDataClass, "Tsid", "I");
    fid_ServiceId = (env)->GetFieldID ( SatInstallerTvProviderDataClass, "ServiceId", "I");
    fid_Tpid = (env)->GetFieldID ( SatInstallerTvProviderDataClass, "Tpid", "I");
    fid_PresetNumber = (env)->GetFieldID ( SatInstallerTvProviderDataClass, "PresetNumber", "I");
    fid_UniqueId = (env)->GetFieldID ( SatInstallerTvProviderDataClass, "UniqueId", "I");
    fid_MultiplePreset = (env)->GetFieldID ( SatInstallerTvProviderDataClass, "MultiplePreset", "[I");

    TvpData.OriginalNetworkId = (Nat16)(env)->GetIntField(tvpDataObj, fid_OriginalNetworkId);
    TvpData.Tsid = (Nat16)(env)->GetIntField(tvpDataObj, fid_Tsid);
    TvpData.ServiceId = (Nat16)(env)->GetIntField(tvpDataObj, fid_ServiceId);
    TvpData.Tpid = (Nat32)(env)->GetIntField(tvpDataObj, fid_Tpid);
    TvpData.PresetNumber = (Nat16)(env)->GetIntField(tvpDataObj, fid_PresetNumber);
    TvpData.UniqueId = (Nat32)(env)->GetIntField(tvpDataObj, fid_UniqueId);


    // MultiplePreset	

	ObjMultiplePreset = (jintArray) (env)->GetObjectField(tvpDataObj, fid_MultiplePreset);
	
	if(NULL != ObjMultiplePreset) 
	{
	
		int length = (env)->GetArrayLength(ObjMultiplePreset);

		int  i = 0;
		MultiplePreset = (jint *) (env)->GetIntArrayElements(ObjMultiplePreset, NULL);
		if(MultiplePreset != NULL)
		{
			for(i = 0; (i < length) && (i < 8) ; i++)
			{
				TvpData.MultiplePreset[i] = (Nat16)MultiplePreset[i];
			}
		}
	}
	else
	{
	}

    natiInsta->SyncUniqueIdToMW (&TvpData);

}
   

      
SatInstallerJNI::~SatInstallerJNI()
{
	__android_log_print(ANDROID_LOG_DEBUG, "SatInstallerJNI","~SatInstallerJNI Destructor DetachCurrentThread");
	JNIEnv *env;
	if(natvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
		__android_log_print(ANDROID_LOG_DEBUG, "Native_JNI","GetEnv Failure");
	  
	 } else {
		env->DeleteGlobalRef(m_jh);
	 }
	 
	natvm->DetachCurrentThread();
}


