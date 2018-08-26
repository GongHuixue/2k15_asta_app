#ifndef IPRODAPIFLASHFILESYSTEMDIRECTORYEXEX_H
#define IPRODAPIFLASHFILESYSTEMDIRECTORYEXEX_H
#include <intfparam.h>
#include <provreq.h>
class IProdApiFlashFileSystemDirectoryExEx
{
public:
	virtual ~IProdApiFlashFileSystemDirectoryExEx(){}
	#define IProdApiFlashFileSystemDirectoryExEx_AvPlf		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeApps		((int)0 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeDcp		((int)1 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeDvp		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeGs		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeInfra		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeSvc		((int)2 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeTlpod		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeTv		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeVlfw		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_Fac		((int)4 )
	#define IProdApiFlashFileSystemDirectoryExEx_GfxMgr		((int)5 )
	#define IProdApiFlashFileSystemDirectoryExEx_HySvc		((int)6 )
	#define IProdApiFlashFileSystemDirectoryExEx_Infra		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_JagDvp		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_Juice		((int)7 )
	#define IProdApiFlashFileSystemDirectoryExEx_NhApi		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_TvSvc		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_TxPlf		((int)8 )
	#define IProdApiFlashFileSystemDirectoryExEx_TxSvc		((int)9 )
	#define IProdApiFlashFileSystemDirectoryExEx_CeHtv		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_Tv520Avi		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_CbMhg		((int)3 )
	#define IProdApiFlashFileSystemDirectoryExEx_Tv		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_TvPlf		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_NumCustomers		((int)12 )
	#define IProdApiFlashFileSystemDirectoryExEx_SharedRes		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_Ols		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_Demo		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_Home		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_Dfu		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_Upg		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_Broadcast		((int)-1 )
	#define IProdApiFlashFileSystemDirectoryExEx_ReadOnce		((int)0 )
	#define IProdApiFlashFileSystemDirectoryExEx_ReadUpgrade		((int)0 )
	#define IProdApiFlashFileSystemDirectoryExEx_ReadWrite		((int)0 )
	#define IProdApiFlashFileSystemDirectoryExEx_ReadRFS		((int)0 )
	#define IProdApiFlashFileSystemDirectoryExEx_Boot		((int)0 )
	#define IProdApiFlashFileSystemDirectoryExEx_Data		((int)0 )
	#define IProdApiFlashFileSystemDirectoryExEx_NumPaths		((int)0 )
	#define IProdApiFlashFileSystemDirectoryExEx_MaxStringLength		((int)0 )
	virtual int GetDirPath(char * direc,int pathtype,int subsystem)= 0;
	virtual int GetDirPathLength(int pathtype,int subsystem)= 0;
	virtual int GetDirPathStr(char * direc,char * pathtype,char * subsystem)= 0;
	virtual int GetDirPathLengthStr(char * pathtype,char * subsystem)= 0;
};


#define IProdApiFlashFileSystemDirectoryExExImpl(Comp,intf)    \
virtual int intf ## _GetDirPath(char * direc,int pathtype,int subsystem);\
virtual int intf ## _GetDirPathLength(int pathtype,int subsystem);\
virtual int intf ## _GetDirPathStr(char * direc,char * pathtype,char * subsystem);\
virtual int intf ## _GetDirPathLengthStr(char * pathtype,char * subsystem);\
class Comp ## _ ## intf : public IProdApiFlashFileSystemDirectoryExEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetDirPath(char * direc,int pathtype,int subsystem){ return m_parent->intf ## _GetDirPath(direc,pathtype,subsystem);}\
virtual int GetDirPathLength(int pathtype,int subsystem){ return m_parent->intf ## _GetDirPathLength(pathtype,subsystem);}\
virtual int GetDirPathStr(char * direc,char * pathtype,char * subsystem){ return m_parent->intf ## _GetDirPathStr(direc,pathtype,subsystem);}\
virtual int GetDirPathLengthStr(char * pathtype,char * subsystem){ return m_parent->intf ## _GetDirPathLengthStr(pathtype,subsystem);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
