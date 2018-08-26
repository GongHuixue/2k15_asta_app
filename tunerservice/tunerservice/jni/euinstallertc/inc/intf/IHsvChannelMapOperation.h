#ifndef IHSVCHANNELMAPOPERATION_H
#define IHSVCHANNELMAPOPERATION_H
#include <intfparam.h>
#include <provreq.h>
class IHsvChannelMapOperation
{
public:
	virtual ~IHsvChannelMapOperation(){}
	virtual void Lock(void)= 0;
	virtual void UnLock(void)= 0;
	virtual FResult ReloadFromFlash(int tableid)= 0;
	virtual FResult CommitToFlash(int tableid)= 0;
	virtual FResult LoadChannelTable(int tableid,char * dir)= 0;
	virtual FResult SaveChannelTable(int tableid,char * dir)= 0;
	virtual void SetDirtyBit(void)= 0;
	virtual void EnableAutoCommit(Bool enable)= 0;
	virtual void ChannelTableChanged(void)= 0;
	virtual FResult LoadChannelExternal(char * dir)= 0;
	virtual FResult SaveChannelExternal(char * dir)= 0;
	virtual FResult GetMediumFromTable(char * dir,int * medium)= 0;
};


#define IHsvChannelMapOperationImpl(Comp,intf)    \
virtual void intf ## _Lock(void);\
virtual void intf ## _UnLock(void);\
virtual FResult intf ## _ReloadFromFlash(int tableid);\
virtual FResult intf ## _CommitToFlash(int tableid);\
virtual FResult intf ## _LoadChannelTable(int tableid,char * dir);\
virtual FResult intf ## _SaveChannelTable(int tableid,char * dir);\
virtual void intf ## _SetDirtyBit(void);\
virtual void intf ## _EnableAutoCommit(Bool enable);\
virtual void intf ## _ChannelTableChanged(void);\
virtual FResult intf ## _LoadChannelExternal(char * dir);\
virtual FResult intf ## _SaveChannelExternal(char * dir);\
virtual FResult intf ## _GetMediumFromTable(char * dir,int * medium);\
class Comp ## _ ## intf : public IHsvChannelMapOperation \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Lock(void){ return m_parent->intf ## _Lock();}\
virtual void UnLock(void){ return m_parent->intf ## _UnLock();}\
virtual FResult ReloadFromFlash(int tableid){ return m_parent->intf ## _ReloadFromFlash(tableid);}\
virtual FResult CommitToFlash(int tableid){ return m_parent->intf ## _CommitToFlash(tableid);}\
virtual FResult LoadChannelTable(int tableid,char * dir){ return m_parent->intf ## _LoadChannelTable(tableid,dir);}\
virtual FResult SaveChannelTable(int tableid,char * dir){ return m_parent->intf ## _SaveChannelTable(tableid,dir);}\
virtual void SetDirtyBit(void){ return m_parent->intf ## _SetDirtyBit();}\
virtual void EnableAutoCommit(Bool enable){ return m_parent->intf ## _EnableAutoCommit(enable);}\
virtual void ChannelTableChanged(void){ return m_parent->intf ## _ChannelTableChanged();}\
virtual FResult LoadChannelExternal(char * dir){ return m_parent->intf ## _LoadChannelExternal(dir);}\
virtual FResult SaveChannelExternal(char * dir){ return m_parent->intf ## _SaveChannelExternal(dir);}\
virtual FResult GetMediumFromTable(char * dir,int * medium){ return m_parent->intf ## _GetMediumFromTable(dir,medium);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
