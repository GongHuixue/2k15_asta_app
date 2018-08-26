#ifndef  _CHSVUTIL_GPIMWCHAR_H
#define  _CHSVUTIL_GPIMWCHAR_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IMultiLingualStringConversion.h>
class CHsvUtil_gpimwchar_Priv;
class CHsvUtil_gpimwchar
{
public:
ProvidesInterface<IMultiLingualStringConversion>	ling;

public:
CHsvUtil_gpimwchar();
virtual ~CHsvUtil_gpimwchar();
private:
CHsvUtil_gpimwchar_Priv	*m_priv;
};

#endif

