#ifndef IPLFAPIDVBSTUNING_H
#define IPLFAPIDVBSTUNING_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiDvbsTuning
{
public:
	virtual ~IPlfApiDvbsTuning(){}
	#define IPlfApiDvbsTuning_TUNING_DVBS_ERR_NONE		((int)0 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_ERR_BAD_PARAMETER		((int)1 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_ERR_NOT_IMPLEMENTED		((int)2 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_ERR_EXEC_FAILURE		((int)3 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_START_FREQUENCY		((int)10700000 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_END_FREQUENCY		((int)12750000 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_UNKNOWN		((int)0 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_QPSK		((int)1 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_APSK16		((int)2 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_APSK32		((int)3 )
	#define IPlfApiDvbsTuning_TUNING_DVBs_PSK8		((int)4 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_SYMBOLRATE_MIN		((int)1400000 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_SYMBOLRATE_MAX		((int)45000000 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_SR_DETECTMODE_AUTO		((int)0 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_SR_DETECTMODE_MANUAL		((int)1 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_HORIZONTAL		((int)0 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_VERTICAL		((int)1 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_UNIVERSAL		((int)0 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_UNICABLE		((int)1 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_CUSTOM		((int)2 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_CIRCULAR		((int)3 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_MDU1		((int)4 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_MDU2		((int)5 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_MDU3		((int)6 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_MDU4		((int)7 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_MDU5		((int)8 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_BANDLOW	((int)0 )
	#define IPlfApiDvbsTuning_TUNING_DVBS_BANDHIGH	((int)1 )
	/* Custom LNB Power */
	#define IPlfApiDvbsTuning_TUNING_DVBSEX_CUSTOMPOW_OFF	((int)0 )
	#define IPlfApiDvbsTuning_TUNING_DVBSEX_CUSTOMPOW_ON	((int)1 )
	/* TONE For Diseqc Mini and Custom LNB */
	#define IPlfApiDvbsTuning_TUNING_DVBSEX_TONELOW	((int) 0)
	#define IPlfApiDvbsTuning_TUNING_DVBSEX_TONEHIGH	((int)1 )
	#define IPlfApiDvbsTuning_TUNING_DVBSEX_TONENONE	((int)2 )
	/*BurstSelect For Diseqc Mini and Custom LNB */
	#define IPlfApiDvbsTuning_DVBSEX_TONEBURST_SAT_A	((int)0 )
	#define IPlfApiDvbsTuning_DVBSEX_TONEBURST_SAT_B	((int)1 )
	 /** Extensions for SAT-IP */
	  /** ROll OFF Type  */
	#define IPlfApiDvbsTuning_DVBS_ROLLFF_UNKNOWN	((int)0 )
	#define IPlfApiDvbsTuning_DVBS_ROLLFF_0P35	((int)35 )
	#define IPlfApiDvbsTuning_DVBS_ROLLFF_0P25	((int)25 )
	#define IPlfApiDvbsTuning_DVBS_ROLLFF_0P20	((int)20 )
	  /** FEC Type  */	
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_UNKNOWN	((int)0 )
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_12	((int)12 )
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_23 ((int)23 )
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_34 ((int)34 )
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_35 ((int)35 )
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_45 ((int)45 )
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_56 ((int)56 )
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_78 ((int)78 )
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_89 ((int)89 )
	#define IPlfApiDvbsTuning_DVBS_FEC_INNER_910 ((int)910 )
	  /** DVBS Standard   */		
	#define IPlfApiDvbsTuning_DVBS_MOD_SYS_DVBS	((int)0 )
	#define IPlfApiDvbsTuning_DVBS_MOD_SYS_DVBS2	((int)1 )
	/** DVBS Pilots  */
	#define IPlfApiDvbsTuning_DVBS_DVBS_PILOTS_OFF	((int)0 )
	#define IPlfApiDvbsTuning_DVBS_DVBS_PILOTS_OFF	((int)1 )
	
		
	
	virtual int getParams(HsvDvbSParams * par)= 0;
	virtual int configureLNB(HsvDvbSLNBConfig lnbcfg, HsvDvbSCustomLNBConfig customlnbcfg)= 0;
	virtual int configureUnicable(HsvDvbSUnicableConfig uccfg)= 0;
	virtual int setPolarization(int polarization)= 0;
	virtual int setSymbolRate(int srdetectmode,int symbolrate)= 0;
	virtual int setPLP(Nat8 plpid)= 0;
	virtual int setBand(int band) = 0;
	virtual int setLNBConnectionType(int connectiontype) = 0;
	virtual int setSatIPParams(int modsys,int modtype,int RollOff, int fec, int pilots) = 0;
};


#define IPlfApiDvbsTuningImpl(Comp,intf)    \
virtual int intf ## _getParams(HsvDvbSParams * par);\
virtual int intf ## _configureLNB(HsvDvbSLNBConfig lnbcfg, HsvDvbSCustomLNBConfig customlnbcfg);\
virtual int intf ## _configureUnicable(HsvDvbSUnicableConfig uccfg);\
virtual int intf ## _setPolarization(int polarization);\
virtual int intf ## _setSymbolRate(int srdetectmode,int symbolrate);\
virtual int intf ## _setPLP(Nat8 plpid);\
virtual int intf ## _setBand(int band);\
virtual int intf ## _setLNBConnectionType(int connectiontype);\
virtual int intf ## _setSatIPParams(int modsys,int modtype,int RollOff, int fec, int pilots);\
class Comp ## _ ## intf : public IPlfApiDvbsTuning \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int getParams(HsvDvbSParams * par){ return m_parent->intf ## _getParams(par);}\
virtual int configureLNB(HsvDvbSLNBConfig lnbcfg, HsvDvbSCustomLNBConfig customlnbcfg){ return m_parent->intf ## _configureLNB(lnbcfg,customlnbcfg);}\
virtual int configureUnicable(HsvDvbSUnicableConfig uccfg){ return m_parent->intf ## _configureUnicable(uccfg);}\
virtual int setPolarization(int polarization){ return m_parent->intf ## _setPolarization(polarization);}\
virtual int setSymbolRate(int srdetectmode,int symbolrate){ return m_parent->intf ## _setSymbolRate(srdetectmode,symbolrate);}\
virtual int setPLP(Nat8 plpid){ return m_parent->intf ## _setPLP(plpid);}\
virtual int setBand(int band){ return m_parent->intf ## _setBand(band);}\
virtual int setLNBConnectionType(int connectiontype){ return m_parent->intf ## _setLNBConnectionType(connectiontype);}\
virtual int setSatIPParams(int modsys,int modtype,int RollOff, int fec, int pilots){ return m_parent->intf ## _setSatIPParams(modsys,modtype,RollOff,fec,pilots);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
