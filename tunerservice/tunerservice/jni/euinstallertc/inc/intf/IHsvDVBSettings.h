#ifndef IHSVDVBSETTINGS_H
#define IHSVDVBSETTINGS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvDVBSettings
{
public:
	virtual ~IHsvDVBSettings(){}
	virtual Bool SetAttribute(int installationmode,int attribute,int value)= 0;
	virtual int GetAttribute(int installationmode,int attribute)= 0;
	virtual void ResetAttributeToDefault(int installationmode,int attribute)= 0;
	virtual void ResetAttributeToPersistent(int installationmode,int attribute)= 0;
	virtual void ResetAllToDefault(void)= 0;
	virtual void ResetAllToPersistent(void)= 0;
	virtual int GetAttributeLength(int installationmode,int attribute)= 0;
	virtual int GetNextAttributeValue(int installationmode,int attribute,int value)= 0;
	virtual void SetPreferred(int attribute,int value,Bool preferred)= 0;
	virtual Bool GetAttributeRange(int installationmode,int attribute,int * minValue,int * maxValue)= 0;
	virtual int GetAttributeMode(int installationmode,int attribute)= 0;
	virtual Bool SetAttributeMode(int installationmode,int attribute,int attributeMode)= 0;
	virtual void CopyTemporaryToPersistent(void)= 0;
	virtual void ClearPersistent(void)= 0;
	virtual void CommitPreferred(void)= 0;
	virtual Bool IsAvailable(int installationmode,int attribute)= 0;
	virtual void SetUserSymbolRates(int installationmode,int * values,int len)= 0;
	virtual void GetUserSymbolRates(int installationmode,int * values,int * len)= 0;
	virtual void GetPredefinedSymbolRates(int installationmode,int * values,int * len)= 0;
	virtual void ClearUserSymbolRates(void)= 0;
	virtual Nat8 GetONIDNetworkOperator(int ONID)= 0;
};


#define IHsvDVBSettingsImpl(Comp,intf)    \
virtual Bool intf ## _SetAttribute(int installationmode,int attribute,int value);\
virtual int intf ## _GetAttribute(int installationmode,int attribute);\
virtual void intf ## _ResetAttributeToDefault(int installationmode,int attribute);\
virtual void intf ## _ResetAttributeToPersistent(int installationmode,int attribute);\
virtual void intf ## _ResetAllToDefault(void);\
virtual void intf ## _ResetAllToPersistent(void);\
virtual int intf ## _GetAttributeLength(int installationmode,int attribute);\
virtual int intf ## _GetNextAttributeValue(int installationmode,int attribute,int value);\
virtual void intf ## _SetPreferred(int attribute,int value,Bool preferred);\
virtual Bool intf ## _GetAttributeRange(int installationmode,int attribute,int * minValue,int * maxValue);\
virtual int intf ## _GetAttributeMode(int installationmode,int attribute);\
virtual Bool intf ## _SetAttributeMode(int installationmode,int attribute,int attributeMode);\
virtual void intf ## _CopyTemporaryToPersistent(void);\
virtual void intf ## _ClearPersistent(void);\
virtual void intf ## _CommitPreferred(void);\
virtual Bool intf ## _IsAvailable(int installationmode,int attribute);\
virtual void intf ## _SetUserSymbolRates(int installationmode,int * values,int len);\
virtual void intf ## _GetUserSymbolRates(int installationmode,int * values,int * len);\
virtual void intf ## _GetPredefinedSymbolRates(int installationmode,int * values,int * len);\
virtual void intf ## _ClearUserSymbolRates(void);\
virtual Nat8 intf ## _GetONIDNetworkOperator(int ONID);\
class Comp ## _ ## intf : public IHsvDVBSettings \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool SetAttribute(int installationmode,int attribute,int value){ return m_parent->intf ## _SetAttribute(installationmode,attribute,value);}\
virtual int GetAttribute(int installationmode,int attribute){ return m_parent->intf ## _GetAttribute(installationmode,attribute);}\
virtual void ResetAttributeToDefault(int installationmode,int attribute){ return m_parent->intf ## _ResetAttributeToDefault(installationmode,attribute);}\
virtual void ResetAttributeToPersistent(int installationmode,int attribute){ return m_parent->intf ## _ResetAttributeToPersistent(installationmode,attribute);}\
virtual void ResetAllToDefault(void){ return m_parent->intf ## _ResetAllToDefault();}\
virtual void ResetAllToPersistent(void){ return m_parent->intf ## _ResetAllToPersistent();}\
virtual int GetAttributeLength(int installationmode,int attribute){ return m_parent->intf ## _GetAttributeLength(installationmode,attribute);}\
virtual int GetNextAttributeValue(int installationmode,int attribute,int value){ return m_parent->intf ## _GetNextAttributeValue(installationmode,attribute,value);}\
virtual void SetPreferred(int attribute,int value,Bool preferred){ return m_parent->intf ## _SetPreferred(attribute,value,preferred);}\
virtual Bool GetAttributeRange(int installationmode,int attribute,int * minValue,int * maxValue){ return m_parent->intf ## _GetAttributeRange(installationmode,attribute,minValue,maxValue);}\
virtual int GetAttributeMode(int installationmode,int attribute){ return m_parent->intf ## _GetAttributeMode(installationmode,attribute);}\
virtual Bool SetAttributeMode(int installationmode,int attribute,int attributeMode){ return m_parent->intf ## _SetAttributeMode(installationmode,attribute,attributeMode);}\
virtual void CopyTemporaryToPersistent(void){ return m_parent->intf ## _CopyTemporaryToPersistent();}\
virtual void ClearPersistent(void){ return m_parent->intf ## _ClearPersistent();}\
virtual void CommitPreferred(void){ return m_parent->intf ## _CommitPreferred();}\
virtual Bool IsAvailable(int installationmode,int attribute){ return m_parent->intf ## _IsAvailable(installationmode,attribute);}\
virtual void SetUserSymbolRates(int installationmode,int * values,int len){ return m_parent->intf ## _SetUserSymbolRates(installationmode,values,len);}\
virtual void GetUserSymbolRates(int installationmode,int * values,int * len){ return m_parent->intf ## _GetUserSymbolRates(installationmode,values,len);}\
virtual void GetPredefinedSymbolRates(int installationmode,int * values,int * len){ return m_parent->intf ## _GetPredefinedSymbolRates(installationmode,values,len);}\
virtual void ClearUserSymbolRates(void){ return m_parent->intf ## _ClearUserSymbolRates();}\
virtual Nat8 GetONIDNetworkOperator(int ONID){ return m_parent->intf ## _GetONIDNetworkOperator(ONID);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
