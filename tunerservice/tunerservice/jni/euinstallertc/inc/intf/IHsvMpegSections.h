#ifndef IHSVMPEGSECTIONS_H
#define IHSVMPEGSECTIONS_H
#include <intfparam.h>
#include <provreq.h>
class IHsvMpegSections
{
public:
	virtual ~IHsvMpegSections(){}
	virtual int GetNumberofPrograms(HsvDemux dmx)= 0;
	virtual Nat32 GetProgramNumber(HsvDemux dmx,int indx)= 0;
	virtual Bool GetComponentInfobyProgramNumber(HsvDemux dmx,int prg,HsvComponentInfo * ci)= 0;
	virtual Bool GetComponentInfobyIndex(HsvDemux dmx,int indx,HsvComponentInfo * ci)= 0;
	virtual Nat32 GetCurrentTsId(HsvDemux dmx)= 0;
	virtual void* GetPmtSection(HsvDemux dmx,int prg)= 0;
	virtual void MonitorProgram(HsvDemux dmx,int prg)= 0;
	virtual void MonitorProgram2(HsvDemux dmx,int prg)= 0;
	virtual void MonitorProgramByIndex(HsvDemux dmx,int prg,int index)= 0;
};


#define IHsvMpegSectionsImpl(Comp,intf)    \
virtual int intf ## _GetNumberofPrograms(HsvDemux dmx);\
virtual Nat32 intf ## _GetProgramNumber(HsvDemux dmx,int indx);\
virtual Bool intf ## _GetComponentInfobyProgramNumber(HsvDemux dmx,int prg,HsvComponentInfo * ci);\
virtual Bool intf ## _GetComponentInfobyIndex(HsvDemux dmx,int indx,HsvComponentInfo * ci);\
virtual Nat32 intf ## _GetCurrentTsId(HsvDemux dmx);\
virtual void* intf ## _GetPmtSection(HsvDemux dmx,int prg);\
virtual void intf ## _MonitorProgram(HsvDemux dmx,int prg);\
virtual void intf ## _MonitorProgram2(HsvDemux dmx,int prg);\
virtual void intf ## _MonitorProgramByIndex(HsvDemux dmx,int prg,int index);\
class Comp ## _ ## intf : public IHsvMpegSections \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetNumberofPrograms(HsvDemux dmx){ return m_parent->intf ## _GetNumberofPrograms(dmx);}\
virtual Nat32 GetProgramNumber(HsvDemux dmx,int indx){ return m_parent->intf ## _GetProgramNumber(dmx,indx);}\
virtual Bool GetComponentInfobyProgramNumber(HsvDemux dmx,int prg,HsvComponentInfo * ci){ return m_parent->intf ## _GetComponentInfobyProgramNumber(dmx,prg,ci);}\
virtual Bool GetComponentInfobyIndex(HsvDemux dmx,int indx,HsvComponentInfo * ci){ return m_parent->intf ## _GetComponentInfobyIndex(dmx,indx,ci);}\
virtual Nat32 GetCurrentTsId(HsvDemux dmx){ return m_parent->intf ## _GetCurrentTsId(dmx);}\
virtual void* GetPmtSection(HsvDemux dmx,int prg){ return m_parent->intf ## _GetPmtSection(dmx,prg);}\
virtual void MonitorProgram(HsvDemux dmx,int prg){ return m_parent->intf ## _MonitorProgram(dmx,prg);}\
virtual void MonitorProgram2(HsvDemux dmx,int prg){ return m_parent->intf ## _MonitorProgram2(dmx,prg);}\
virtual void MonitorProgramByIndex(HsvDemux dmx,int prg,int index){ return m_parent->intf ## _MonitorProgramByIndex(dmx,prg,index);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
