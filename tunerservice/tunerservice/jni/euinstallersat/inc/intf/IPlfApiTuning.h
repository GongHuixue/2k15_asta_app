#ifndef IPLFAPITUNING_H
#define IPLFAPITUNING_H
#include <intfparam.h>
#include <provreq.h>
class IPlfApiTuning
{
public:
	virtual ~IPlfApiTuning(){}
	#define IPlfApiTuning_TUNING_ERR_NONE		((int)0 )
	#define IPlfApiTuning_TUNING_ERR_BAD_PARAMETER		((int)1 )
	#define IPlfApiTuning_TUNING_ERR_NOT_IMPLEMENTED		((int)2 )
	#define IPlfApiTuning_TUNING_ERR_EXEC_FAILURE		((int)3 )
	#define IPlfApiTuning_TUNING_STANDARD_DVBT		((int)0x00000001 )
	#define IPlfApiTuning_TUNING_STANDARD_DVBT2		((int)0x00000002 )
	#define IPlfApiTuning_TUNING_STANDARD_DVBC		((int)0x00000004 )
	#define IPlfApiTuning_TUNING_STANDARD_DVBC2		((int)0x00000008 )
	#define IPlfApiTuning_TUNING_STANDARD_DVBS2		((int)0x00000010 )
	#define IPlfApiTuning_TUNING_STANDARD_ANALOG		((int)0x00000020 )
	#define IPlfApiTuning_TUNING_RESULT_LOCK		((int)1 )
	#define IPlfApiTuning_TUNING_RESULT_NOLOCK		((int)2 )
	virtual int tune(int freq,Bool finetune)= 0;
	virtual int getFreq(int * freq)= 0;
	virtual int scanStart(int startfreq,int endfreq,Bool scanforward)= 0;
	virtual int scanAbort(void)= 0;
	virtual int scanNext(void)= 0;
};


#define IPlfApiTuningImpl(Comp,intf)    \
virtual int intf ## _tune(int freq,Bool finetune);\
virtual int intf ## _getFreq(int * freq);\
virtual int intf ## _scanStart(int startfreq,int endfreq,Bool scanforward);\
virtual int intf ## _scanAbort(void);\
virtual int intf ## _scanNext(void);\
class Comp ## _ ## intf : public IPlfApiTuning \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int tune(int freq,Bool finetune){ return m_parent->intf ## _tune(freq,finetune);}\
virtual int getFreq(int * freq){ return m_parent->intf ## _getFreq(freq);}\
virtual int scanStart(int startfreq,int endfreq,Bool scanforward){ return m_parent->intf ## _scanStart(startfreq,endfreq,scanforward);}\
virtual int scanAbort(void){ return m_parent->intf ## _scanAbort();}\
virtual int scanNext(void){ return m_parent->intf ## _scanNext();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
