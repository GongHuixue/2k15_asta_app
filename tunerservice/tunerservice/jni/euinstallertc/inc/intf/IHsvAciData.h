#ifndef IHSVACIDATA_H
#define IHSVACIDATA_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAciData
{
public:
	virtual ~IHsvAciData(){}
	virtual void StorePreset(HsvAciSingleInfo presetInfo,Bool clear)= 0;
	virtual HsvAciLanguage GetAciLanguage(int language)= 0;
};


#define IHsvAciDataImpl(Comp,intf)    \
virtual void intf ## _StorePreset(HsvAciSingleInfo presetInfo,Bool clear);\
virtual HsvAciLanguage intf ## _GetAciLanguage(int language);\
class Comp ## _ ## intf : public IHsvAciData \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void StorePreset(HsvAciSingleInfo presetInfo,Bool clear){ return m_parent->intf ## _StorePreset(presetInfo,clear);}\
virtual HsvAciLanguage GetAciLanguage(int language){ return m_parent->intf ## _GetAciLanguage(language);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
