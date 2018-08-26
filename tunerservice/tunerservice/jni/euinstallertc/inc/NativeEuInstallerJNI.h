/*
 * NativeJNI.h
 *
 *  Created on: 13-May-2013
 *      Author: mahesh.mathada
 */

#ifndef NATIVEJNI_H_
#define NATIVEJNI_H_

#include "Frontend_DVBC_params.h"
#include "Frontend_DVBT_params.h"
#include "CTvInstallTC.h"

class NativeJNI;

class NativeJNI
{
	public:
	NativeJNI(){ }
	virtual ~NativeJNI();

	public:
		int tune(jint freq, jboolean value);
		int getFreq(unsigned int *freq);
		int scanStart( jint startFreq, jint endFreq, jboolean scanFor);
		int scanAbort();
		int scanNext();
		int getFreqRange(unsigned int *minFreq,unsigned int* maxFreq);
		int getFreqStep(unsigned int *step);
		int getActualCodeRate(unsigned int *rate);
		int getSymbolRate(Nat32* rate);
		int getSymbolRateRange(Nat32* MinSymbolRate,Nat32* MaxSymbolRate);
		int SetChanBandwidth(int bandwidth);
		int getActualChanBandwidth(int *bandwidth);
		int getStreamPriority(int *streamPriority);
		int getHierarchyMode(Bool *HierarchyMode);
		int getActualConstellation( int *constellation);
		int setConstellation(int constellation);
		int getBer(unsigned int *Ber);
		int getCarrierPresent(Bool *Present);
		int getSigStrengthRange(unsigned int *MinStrength,unsigned int *MaxStrength);
		int start(Bool *Avail);
		int stop(Bool *Stopped);
		int getMeasValid(Bool *Valid);
		int getSigStrength(int ssm, unsigned int *Strength);
		int getTPSId(HsvDvbTParams* TPSId);
		// DVBT FrontEnd Functions
		int getParamsDvbT(ParamsDvbTer sigInfo,ParamsDvbTSpecific dvbtspecif,ParamsDvbT2Specific dvbt2specif);
		int setStreamPriority(jint stream_prio);
		int setBandwidth(jint bandwidth);
		int setPLP(jbyte plp_id);
		// DVBC FrontEnd Functions
		int getParamsDvbC(DvbCParams par);
		int setScanStep(int value);
		int setSymbolRate(int srdetectmode,  int symbolrate);
		int setSearchRates(tmFe_SearchSymbolRate_t* searchrates,int listsize);
		// Notification from tcinstaller.so
		int onEvent(int eventid,int val);
		// Sourcesetup
		int SourceSetupApply(int Medium);
		// chdecdvbt2
		int GetT2CarrierPresent(Bool * Present);
		int  GetActivePlpId(int * plpid);
		int  SelectPlpId(int plpid);
		int GetDetectedPlpIds(int * nrOfIds,int * plpids);

		int GetTvSystem( Nat32*  tvSystem,  Nat32* errorcode );
		int SetTvSystem (  Nat32 TvSystem,   Nat32* errorcode );
		void RequestStatusInfo(void);
		void RequestNit(void);
		void SendOperatorSearchStart(Op_Search_Settings searchstart);
		void SendOpExit(void);
		void SendOpTuneStatus(Op_Tune_Status tuneStatus);
		void SendOpAck(void);
		void SendOpSearchCancel(void);
		void CacheOperatorData(void);
		
		int getValueFromTVContentProvider(jint id,int *val);
		void setDemuxHandle(long demuxHandle);
		void setVbiHandle(long vbiHandle);
			

};

#endif /* NATIVEJNI_H_ */
