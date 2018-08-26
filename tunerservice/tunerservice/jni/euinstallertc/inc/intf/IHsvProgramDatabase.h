#ifndef IHSVPROGRAMDATABASE_H
#define IHSVPROGRAMDATABASE_H
#include <intfparam.h>
#include <provreq.h>
class IHsvProgramDatabase
{
public:
	virtual ~IHsvProgramDatabase(){}
	#define	IHsvProgramDatabase_SqliteDatabase		((int)0x01)
	#define	IHsvProgramDatabase_TempDatabase		((int)0x02)
	#define IHsvProgramDatabase_DatabaseModeNormal	1
	#define IHsvProgramDatabase_DatabaseModeCam 	2
	virtual int GetCurrentTable(void)= 0;
	virtual Bool SelectTable(int tableid)= 0;
	virtual Bool ClearTable(int tableid)= 0;
	virtual Bool IsSupported(int tableid)= 0;
	virtual Bool CommitTable(int tableid)= 0;
	virtual Bool LoadTable(int tableid)= 0;
	virtual int GetNoRecords(int tableid)= 0;
	virtual Bool GetByKey(int tableid,Address channeldata)= 0;
	virtual int GetIndex(int tableid,int * index,Address channeldata)= 0;
	virtual Bool GetByIndex(int tableid,int index,Address channeldata)= 0;
	virtual Bool GetRange(int tableid,int noofkeys,Address channeldata,int * from,int * to)= 0;
	virtual Bool Add(int tableid,Address channeldata)= 0;
	virtual Bool Update(int tableid,Address channeldata)= 0;
	virtual Bool Delete(int tableid,Address channeldata)= 0;
	virtual void EnableAutoCommit(Bool enable)= 0;
	virtual void ChannelTableChanged(void)= 0;
	virtual void Initialise(int tableid,Address channeldata)= 0;
	virtual void MasterEnableEvents(Bool Status)= 0;
	virtual void SaveChannelMapsToBackup(void)= 0;
	virtual void LoadChannelMapsFromBackup(void)= 0;
	virtual void SelectActiveChannelDatabase(int ActiveDb) = 0;
	virtual Bool AddInIndex (int tableid, int index, Address channeldata)= 0;
	virtual void BeginSqliteTransaction(void)=0;
	virtual void CommitSqliteTransaction(void)=0;
	virtual void SetDatabaseOperationMode (int mode) = 0;

};


#define IHsvProgramDatabaseImpl(Comp,intf)    \
virtual int intf ## _GetCurrentTable(void);\
virtual Bool intf ## _SelectTable(int tableid);\
virtual Bool intf ## _ClearTable(int tableid);\
virtual Bool intf ## _IsSupported(int tableid);\
virtual Bool intf ## _CommitTable(int tableid);\
virtual Bool intf ## _LoadTable(int tableid);\
virtual int intf ## _GetNoRecords(int tableid);\
virtual Bool intf ## _GetByKey(int tableid,Address channeldata);\
virtual int intf ## _GetIndex(int tableid,int * index,Address channeldata);\
virtual Bool intf ## _GetByIndex(int tableid,int index,Address channeldata);\
virtual Bool intf ## _GetRange(int tableid,int noofkeys,Address channeldata,int * from,int * to);\
virtual Bool intf ## _Add(int tableid,Address channeldata);\
virtual Bool intf ## _Update(int tableid,Address channeldata);\
virtual Bool intf ## _Delete(int tableid,Address channeldata);\
virtual void intf ## _EnableAutoCommit(Bool enable);\
virtual void intf ## _ChannelTableChanged(void);\
virtual void intf ## _Initialise(int tableid,Address channeldata);\
virtual void intf ## _MasterEnableEvents(Bool Status);\
virtual void intf ## _SaveChannelMapsToBackup(void);\
virtual void intf ## _LoadChannelMapsFromBackup(void);\
virtual void intf ## _SelectActiveChannelDatabase(int ActiveDb);\
virtual Bool intf ## _AddInIndex (int tableid, int index, Address channeldata);\
virtual void intf ## _BeginSqliteTransaction(void);\
virtual void intf ## _CommitSqliteTransaction(void);\
virtual void intf ## _SetDatabaseOperationMode(int mode);\
class Comp ## _ ## intf : public IHsvProgramDatabase \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetCurrentTable(void){ return m_parent->intf ## _GetCurrentTable();}\
virtual Bool SelectTable(int tableid){ return m_parent->intf ## _SelectTable(tableid);}\
virtual Bool ClearTable(int tableid){ return m_parent->intf ## _ClearTable(tableid);}\
virtual Bool IsSupported(int tableid){ return m_parent->intf ## _IsSupported(tableid);}\
virtual Bool CommitTable(int tableid){ return m_parent->intf ## _CommitTable(tableid);}\
virtual Bool LoadTable(int tableid){ return m_parent->intf ## _LoadTable(tableid);}\
virtual int GetNoRecords(int tableid){ return m_parent->intf ## _GetNoRecords(tableid);}\
virtual Bool GetByKey(int tableid,Address channeldata){ return m_parent->intf ## _GetByKey(tableid,channeldata);}\
virtual int GetIndex(int tableid,int * index,Address channeldata){ return m_parent->intf ## _GetIndex(tableid,index,channeldata);}\
virtual Bool GetByIndex(int tableid,int index,Address channeldata){ return m_parent->intf ## _GetByIndex(tableid,index,channeldata);}\
virtual Bool GetRange(int tableid,int noofkeys,Address channeldata,int * from,int * to){ return m_parent->intf ## _GetRange(tableid,noofkeys,channeldata,from,to);}\
virtual Bool Add(int tableid,Address channeldata){ return m_parent->intf ## _Add(tableid,channeldata);}\
virtual Bool Update(int tableid,Address channeldata){ return m_parent->intf ## _Update(tableid,channeldata);}\
virtual Bool Delete(int tableid,Address channeldata){ return m_parent->intf ## _Delete(tableid,channeldata);}\
virtual void EnableAutoCommit(Bool enable){ return m_parent->intf ## _EnableAutoCommit(enable);}\
virtual void ChannelTableChanged(void){ return m_parent->intf ## _ChannelTableChanged();}\
virtual void Initialise(int tableid,Address channeldata){ return m_parent->intf ## _Initialise(tableid,channeldata);}\
virtual void MasterEnableEvents(Bool Status){ return m_parent->intf ## _MasterEnableEvents(Status);}\
virtual void SaveChannelMapsToBackup(void){ return m_parent->intf ## _SaveChannelMapsToBackup();}\
virtual void LoadChannelMapsFromBackup(void){ return m_parent->intf ## _LoadChannelMapsFromBackup();}\
virtual void SelectActiveChannelDatabase(int ActiveDb){ return m_parent->intf ## _SelectActiveChannelDatabase(ActiveDb);}\
virtual Bool AddInIndex (int tableid, int index, Address channeldata){ return m_parent->intf ## _AddInIndex(tableid,index,channeldata);}\
virtual void BeginSqliteTransaction(void){ return m_parent->intf ## _BeginSqliteTransaction();}\
virtual void CommitSqliteTransaction(void){ return m_parent->intf ## _CommitSqliteTransaction();}\
virtual void SetDatabaseOperationMode(int mode){ return m_parent->intf ## _SetDatabaseOperationMode(mode);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
