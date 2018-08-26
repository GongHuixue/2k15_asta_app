#ifndef IHSVPACKAGEPARSER_H
#define IHSVPACKAGEPARSER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvPackageParser
{
public:
	virtual ~IHsvPackageParser(){}
	virtual FResult IdentifyPackagesAvailable(void)= 0;
	virtual int GetNumberOfPackages(void)= 0;
	virtual FResult GetPackageByIndex(int Index,HsvPackageStructure * Package)= 0;
	virtual FResult GetPackageByKey(HsvPackageStructure * Package)= 0;
	virtual FResult GetPackageGroupId(Nat32 PackageID,Nat16 * PackageGroupId)= 0;
	virtual FResult GetPackageGroupName(Nat32 PackageGroupId,Nat16 * PackageGroupName)= 0;
	virtual void LoadPackageGroupInfo(void)= 0;
	virtual FResult StartPackageParsing(void)= 0;
	virtual FResult StopPackageParsing(void)= 0;
	virtual void SetPackageParserXmlString(char * InputString,int PackageParserXmlStringLen)= 0;
};


#define IHsvPackageParserImpl(Comp,intf)    \
virtual FResult intf ## _IdentifyPackagesAvailable(void);\
virtual int intf ## _GetNumberOfPackages(void);\
virtual FResult intf ## _GetPackageByIndex(int Index,HsvPackageStructure * Package);\
virtual FResult intf ## _GetPackageByKey(HsvPackageStructure * Package);\
virtual FResult intf ## _GetPackageGroupId(Nat32 PackageID,Nat16 * PackageGroupId);\
virtual FResult intf ## _GetPackageGroupName(Nat32 PackageGroupId,Nat16 * PackageGroupName);\
virtual void intf ## _LoadPackageGroupInfo(void);\
virtual FResult intf ## _StartPackageParsing(void);\
virtual FResult intf ## _StopPackageParsing(void);\
virtual void intf ## _SetPackageParserXmlString(char * InputString,int PackageParserXmlStringLen);\
class Comp ## _ ## intf : public IHsvPackageParser \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual FResult IdentifyPackagesAvailable(void){ return m_parent->intf ## _IdentifyPackagesAvailable();}\
virtual int GetNumberOfPackages(void){ return m_parent->intf ## _GetNumberOfPackages();}\
virtual FResult GetPackageByIndex(int Index,HsvPackageStructure * Package){ return m_parent->intf ## _GetPackageByIndex(Index,Package);}\
virtual FResult GetPackageByKey(HsvPackageStructure * Package){ return m_parent->intf ## _GetPackageByKey(Package);}\
virtual FResult GetPackageGroupId(Nat32 PackageID,Nat16 * PackageGroupId){ return m_parent->intf ## _GetPackageGroupId(PackageID,PackageGroupId);}\
virtual FResult GetPackageGroupName(Nat32 PackageGroupId,Nat16 * PackageGroupName){ return m_parent->intf ## _GetPackageGroupName(PackageGroupId,PackageGroupName);}\
virtual void LoadPackageGroupInfo(void){ return m_parent->intf ## _LoadPackageGroupInfo();}\
virtual FResult StartPackageParsing(void){ return m_parent->intf ## _StartPackageParsing();}\
virtual FResult StopPackageParsing(void){ return m_parent->intf ## _StopPackageParsing();}\
virtual void SetPackageParserXmlString(char * InputString,int PackageParserXmlStringLen){ return m_parent->intf ## _SetPackageParserXmlString(InputString,PackageParserXmlStringLen);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
