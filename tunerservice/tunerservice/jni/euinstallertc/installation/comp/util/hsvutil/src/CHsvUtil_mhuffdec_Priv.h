#ifndef  _CHSVUTIL_MHUFFDEC_PRIV_H
#define  _CHSVUTIL_MHUFFDEC_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvHuffmanDecoder.h>
#include <CTCMwBase.h>
class CHsvUtil_mhuffdec_Priv;
#define CLASSSCOPE CHsvUtil_mhuffdec_Priv::
#include "locals_mhuffdec.h"

class CHsvUtil_mhuffdec_Priv : public CTCMwBase
{
public:
virtual ~CHsvUtil_mhuffdec_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mhuffdec.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvHuffmanDecoderImpl(CHsvUtil_mhuffdec_Priv,istringdec);
public:
ProvidesInterface<IHsvHuffmanDecoder>	istringdec;


public:
CHsvUtil_mhuffdec_Priv():i__istringdec(this)
{
istringdec	=	&i__istringdec;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_mhuffdec.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

