/*
 * SatInstallerJNI.h
 *
 *  Created on: Jun 21, 2013
 *      Author: mahesh.mathada
 */

#ifndef SATINSTALLERJNI_H_
#define SATINSTALLERJNI_H_


#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>


class SatInstallerJNI;

class SatInstallerJNI
{
	public:
	SatInstallerJNI(){ }
	virtual ~SatInstallerJNI();

	public:
		
		int getParams(HsvDvbSParams * par);
		int configureLNB(HsvDvbSLNBConfig lnbcfg, HsvDvbSCustomLNBConfig customlnbcfg);
		int configureUnicable(HsvDvbSUnicableConfig uccfg);
		int setPolarization(int polarization);
		int setSymbolRate(int srdetectmode,int symbolrate);
		int setPLP(Nat8 plpid);

		//IPlfApiTuning
		int tune(int freq,Bool finetune);
		int getFreq(int * freq);
		int scanStart(int startfreq,int endfreq,Bool scanforward);
		int scanAbort(void);
		int scanNext(void);
		int setBand(int band);
		int setLNBConnectionType(int connectionType);
		int setSatIPParams(int modsys,int modtype,int RollOff, int fec, int pilots);

		int getSigStrength(unsigned int *Strength);
		int getSigStrengthRange(unsigned int *MinStrength,unsigned int *MaxStrength);
		/*
		int getBer(unsigned int *Ber);
		*/
		int onEvent(int eventid,int val);

		//ICesOperatorProfile
		void RequestStatusInfo(void);
		void RequestNit(void);
		void SendOperatorSearchStart(Op_Search_Settings searchstart);
		void SendOpExit(void);
		void SendOpTuneStatus(Op_Tune_Status tuneStatus);
		void SendOpAck(void);
		void SendOpSearchCancel(void);
		void CacheOperatorData(void);
		Op_ProfileStatusInfo GetStoredOperatorData(void);
		
		int GetValuesFromGlobalSettings(jint id,int *val);

		void GetCipStatus (Nat8 * status);
};

#endif /* SATINSTALLERJNI_H_ */
