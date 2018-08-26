#ifndef  _CHSVUTIL_MHUFFDEC_H
#define  _CHSVUTIL_MHUFFDEC_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvHuffmanDecoder.h>
class CHsvUtil_mhuffdec_Priv;
class CHsvUtil_mhuffdec
{
public:
ProvidesInterface<IHsvHuffmanDecoder>	istringdec;

public:
CHsvUtil_mhuffdec();
virtual ~CHsvUtil_mhuffdec();
private:
CHsvUtil_mhuffdec_Priv	*m_priv;
};

#endif

