#ifndef IHSVCAMDATAPARSER_H
#define IHSVCAMDATAPARSER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvCamDataParser
{
public:
	virtual ~IHsvCamDataParser(){}
	virtual Bool ParseCamData(HsvDestination dest,Nat32 cookie,int DataSize,Nat8 * DataPtr)= 0;
	virtual void SetCharacterCode(char* characterCode)= 0;
};


#define IHsvCamDataParserImpl(Comp,intf)    \
virtual Bool intf ## _ParseCamData(HsvDestination dest,Nat32 cookie,int DataSize,Nat8 * DataPtr);\
virtual void intf ## _SetCharacterCode(char* characterCode);\
class Comp ## _ ## intf : public IHsvCamDataParser \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool ParseCamData(HsvDestination dest,Nat32 cookie,int DataSize,Nat8 * DataPtr){ return m_parent->intf ## _ParseCamData(dest,cookie,DataSize,DataPtr);}\
virtual void SetCharacterCode(char* characterCode){ return m_parent->intf ## _SetCharacterCode(characterCode);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
