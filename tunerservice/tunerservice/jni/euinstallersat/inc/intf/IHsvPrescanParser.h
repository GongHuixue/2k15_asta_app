#ifndef IHSVPRESCANPARSER_H
#define IHSVPRESCANPARSER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPrescanParser
{
public:
	virtual ~IHsvPrescanParser(){}
	virtual Bool ExtractPreScanTableFromXml(void)= 0;
	virtual int GetNumberOfPrescanEntries(void)= 0;
	virtual Bool GetSatelliteEntryFromPreScanTable(int index,HsvSatelliteList * PreScanTableSatellite)= 0;
	virtual Bool GetSatelliteAttributeById(HsvSatelliteMapping * SatelliteAttribute)= 0;
	virtual Bool GetSatelliteAttributeByPosition(HsvSatelliteMapping * SatelliteAttribute)= 0;
	virtual void SetPrescanParserXmlString(char * PrescanXmlString,int PrescanXmlStringLen)= 0;
	virtual Bool PopulateCountryDependantTable(int Country)= 0;
};


#define IHsvPrescanParserImpl(Comp,intf)    \
virtual Bool intf ## _ExtractPreScanTableFromXml(void);\
virtual int intf ## _GetNumberOfPrescanEntries(void);\
virtual Bool intf ## _GetSatelliteEntryFromPreScanTable(int index,HsvSatelliteList * PreScanTableSatellite);\
virtual Bool intf ## _GetSatelliteAttributeById(HsvSatelliteMapping * SatelliteAttribute);\
virtual Bool intf ## _GetSatelliteAttributeByPosition(HsvSatelliteMapping * SatelliteAttribute);\
virtual void intf ## _SetPrescanParserXmlString(char * PrescanXmlString,int PrescanXmlStringLen);\
virtual Bool intf ## _PopulateCountryDependantTable(int Country);\
class Comp ## _ ## intf : public IHsvPrescanParser \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool ExtractPreScanTableFromXml(void){ return m_parent->intf ## _ExtractPreScanTableFromXml();}\
virtual int GetNumberOfPrescanEntries(void){ return m_parent->intf ## _GetNumberOfPrescanEntries();}\
virtual Bool GetSatelliteEntryFromPreScanTable(int index,HsvSatelliteList * PreScanTableSatellite){ return m_parent->intf ## _GetSatelliteEntryFromPreScanTable(index,PreScanTableSatellite);}\
virtual Bool GetSatelliteAttributeById(HsvSatelliteMapping * SatelliteAttribute){ return m_parent->intf ## _GetSatelliteAttributeById(SatelliteAttribute);}\
virtual Bool GetSatelliteAttributeByPosition(HsvSatelliteMapping * SatelliteAttribute){ return m_parent->intf ## _GetSatelliteAttributeByPosition(SatelliteAttribute);}\
virtual void SetPrescanParserXmlString(char * PrescanXmlString,int PrescanXmlStringLen){ return m_parent->intf ## _SetPrescanParserXmlString(PrescanXmlString,PrescanXmlStringLen);}\
virtual Bool PopulateCountryDependantTable(int Country){ return m_parent->intf ## _PopulateCountryDependantTable(Country);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
