#ifndef IHSVFLASHFILESYSTEMDIRECTORYSUB_H
#define IHSVFLASHFILESYSTEMDIRECTORYSUB_H
#include <intfparam.h>
#include <provreq.h>
class IHsvFlashFileSystemDirectorySub
{
public:
	virtual ~IHsvFlashFileSystemDirectorySub(){}
	virtual int TxSvc(void)= 0;
	virtual int HySvc(void)= 0;
	virtual int ReadWrite(void)= 0;
	virtual int Boot(void)= 0;
	virtual int Data(void)= 0;
	virtual int GetDirPath(char * direc,int pathtype,int subsystem)= 0;
};


#define IHsvFlashFileSystemDirectorySubImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
virtual int intf ## _GetDirPath(char * direc,int pathtype,int subsystem);\
class Comp ## _ ## intf : public IHsvFlashFileSystemDirectorySub \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_TxSvc; \
    InterfaceParam<Comp,int> m_HySvc; \
    InterfaceParam<Comp,int> m_ReadWrite; \
    InterfaceParam<Comp,int> m_Boot; \
    InterfaceParam<Comp,int> m_Data; \
    Comp ## _ ## intf( Comp *parent):m_TxSvc(parent),m_HySvc(parent),m_ReadWrite(parent),m_Boot(parent),m_Data(parent) \
    {\
        m_parent = parent;\
    }\
virtual int TxSvc(void){ return m_TxSvc.Call();}\
virtual int HySvc(void){ return m_HySvc.Call();}\
virtual int ReadWrite(void){ return m_ReadWrite.Call();}\
virtual int Boot(void){ return m_Boot.Call();}\
virtual int Data(void){ return m_Data.Call();}\
virtual int GetDirPath(char * direc,int pathtype,int subsystem){ return m_parent->intf ## _GetDirPath(direc,pathtype,subsystem);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
