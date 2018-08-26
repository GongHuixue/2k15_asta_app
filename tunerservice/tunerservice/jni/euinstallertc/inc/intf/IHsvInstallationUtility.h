#ifndef IHSVINSTALLATIONUTILITY_H
#define IHSVINSTALLATIONUTILITY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvInstallationUtility
{
public:
	virtual ~IHsvInstallationUtility(){}
	virtual void LogError(int Priority,int ErrorId)= 0;
	virtual Nat16* AsciiToUnicode(char * str,int len)= 0;
};


#define IHsvInstallationUtilityImpl(Comp,intf)    \
virtual void intf ## _LogError(int Priority,int ErrorId);\
virtual Nat16* intf ## _AsciiToUnicode(char * str,int len);\
class Comp ## _ ## intf : public IHsvInstallationUtility \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void LogError(int Priority,int ErrorId){ return m_parent->intf ## _LogError(Priority,ErrorId);}\
virtual Nat16* AsciiToUnicode(char * str,int len){ return m_parent->intf ## _AsciiToUnicode(str,len);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
