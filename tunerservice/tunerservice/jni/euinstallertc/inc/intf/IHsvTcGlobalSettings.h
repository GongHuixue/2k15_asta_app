#ifndef IHSVTCGLOBALSETTINGS_H
#define IHSVTCGLOBALSETTINGS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvTcGlobalSettings
{
public:
	virtual ~IHsvTcGlobalSettings(){}	
	virtual void GetValuesFromGlobalSettings(int ID, int *Value)= 0;
};



#define IHsvTcGlobalSettingsImpl(Comp,intf)	 \
virtual void intf ## _GetValuesFromGlobalSettings(int ID,int *Value);\
class Comp ## _ ## intf : public IHsvTcGlobalSettings \
{\
private:\
	Comp *m_parent; \
public: \
	Comp ## _ ## intf( Comp *parent) \
	{\
		m_parent = parent;\
	}\
virtual void GetValuesFromGlobalSettings(int ID, int *Value){ return m_parent->intf ## _GetValuesFromGlobalSettings(ID,Value);}\
};\
Comp ## _ ## intf i__ ## intf;



#endif
