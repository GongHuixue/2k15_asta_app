#ifndef IHSVFLASHFILESYSTEMRESOURCES_H
#define IHSVFLASHFILESYSTEMRESOURCES_H
#include <intfparam.h>
#include <provreq.h>
class IHsvFlashFileSystemResources
{
public:
	virtual ~IHsvFlashFileSystemResources(){}
	virtual int Directories(void)= 0;
	virtual int Files(void)= 0;
	virtual int Size(void)= 0;
	virtual int FilesOpen(void)= 0;
	virtual int WriteRate(void)= 0;
	virtual int ReadRate(void)= 0;
};


#define IHsvFlashFileSystemResourcesImpl(Comp,intf)    \
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
friend class InterfaceParam<Comp,int>;\
class Comp ## _ ## intf : public IHsvFlashFileSystemResources \
{\
private:\
    Comp *m_parent; \
public: \
    InterfaceParam<Comp,int> m_Directories; \
    InterfaceParam<Comp,int> m_Files; \
    InterfaceParam<Comp,int> m_Size; \
    InterfaceParam<Comp,int> m_FilesOpen; \
    InterfaceParam<Comp,int> m_WriteRate; \
    InterfaceParam<Comp,int> m_ReadRate; \
    Comp ## _ ## intf( Comp *parent):m_Directories(parent),m_Files(parent),m_Size(parent),m_FilesOpen(parent),m_WriteRate(parent),m_ReadRate(parent) \
    {\
        m_parent = parent;\
    }\
virtual int Directories(void){ return m_Directories.Call();}\
virtual int Files(void){ return m_Files.Call();}\
virtual int Size(void){ return m_Size.Call();}\
virtual int FilesOpen(void){ return m_FilesOpen.Call();}\
virtual int WriteRate(void){ return m_WriteRate.Call();}\
virtual int ReadRate(void){ return m_ReadRate.Call();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
