#ifndef IHSVSATGLOBALSETTINGS_H
#define IHSVSATGLOBALSETTINGS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvSatGlobalSettings
{
public:
	virtual ~IHsvSatGlobalSettings(){}	
	virtual void GetValuesFromGlobalSettings(int ID, int *Value)= 0;
};



#define IHsvSatGlobalSettingsImpl(Comp,intf)	 \
virtual void intf ## _GetValuesFromGlobalSettings(int ID,int *Value);\
class Comp ## _ ## intf : public IHsvSatGlobalSettings \
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
