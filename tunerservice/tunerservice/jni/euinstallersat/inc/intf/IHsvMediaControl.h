#ifndef IHSVMEDIACONTROL_H
#define IHSVMEDIACONTROL_H
#include <intfparam.h>
#include <provreq.h>
class IHsvMediaControl
{
public:
	virtual ~IHsvMediaControl(){}
	#define IHsvMediaControl_InvalidMedia		((int)0 )
	#define IHsvMediaControl_Video		((int)1 )
	#define IHsvMediaControl_Audio		((int)2 )
	#define IHsvMediaControl_Pcr		((int)3 )
	#define IHsvMediaControl_Subtitle		((int)4 )
	#define IHsvMediaControl_ClosedCaption		((int)5 )
	#define IHsvMediaControl_Teletext		((int)6 )
	#define IHsvMediaControl_IPSubtitle		((int)7 )
	#define IHsvMediaControl_IPClosedCaption		((int)8 )
	#define IHsvMediaControl_InvalidSelector		((int)0 )
	#define IHsvMediaControl_Language		((int)1 )
	#define IHsvMediaControl_Type		((int)2 )
	#define IHsvMediaControl_Pid		((int)3 )
	#define IHsvMediaControl_VIAssociation		((int)4 )
	#define IHsvMediaControl_VIPrimaryAssociation		((int)5 )
	#define IHsvMediaControl_StreamType		((int)6 )
	virtual int GetMediaSize(HsvDestination dest,int media)= 0;
	virtual Bool GetMediaByKey(HsvDestination dest,int media,int selector1,int selector2,void * value)= 0;
	virtual Bool GetMediaIndex(HsvDestination dest,int media,int selector1,int selecto2,int * index)= 0;
	virtual Bool GetMediaByIndex(HsvDestination dest,int media,int index,void * value)= 0;
	virtual Bool SetMedia(HsvDestination dest,int media,int selector,int value)= 0;
	virtual Bool SetMediaWithProgram(HsvDestination dest,int program,int media,int selector,int value)= 0;
	virtual Bool Play(HsvDestination dest)= 0;
	virtual Bool PlayMedia(HsvDestination dest,int media)= 0;
	virtual Bool Stop(HsvDestination dest)= 0;
	virtual Bool StopMedia(HsvDestination dest,int media)= 0;
	virtual Bool Flush(HsvDestination dest)= 0;
	virtual Bool EnableMedia(HsvDestination dest,int media)= 0;
	virtual Bool DisableMedia(HsvDestination dest,int media)= 0;
	virtual int GetCurrentSelection(HsvDestination dest,int media,int selector)= 0;
	virtual Bool IsMediaPlaying(HsvDestination dest,int media)= 0;
	virtual Bool IsMediaEnabled(HsvDestination dest,int media)= 0;
};


#define IHsvMediaControlImpl(Comp,intf)    \
virtual int intf ## _GetMediaSize(HsvDestination dest,int media);\
virtual Bool intf ## _GetMediaByKey(HsvDestination dest,int media,int selector1,int selector2,void * value);\
virtual Bool intf ## _GetMediaIndex(HsvDestination dest,int media,int selector1,int selecto2,int * index);\
virtual Bool intf ## _GetMediaByIndex(HsvDestination dest,int media,int index,void * value);\
virtual Bool intf ## _SetMedia(HsvDestination dest,int media,int selector,int value);\
virtual Bool intf ## _SetMediaWithProgram(HsvDestination dest,int program,int media,int selector,int value);\
virtual Bool intf ## _Play(HsvDestination dest);\
virtual Bool intf ## _PlayMedia(HsvDestination dest,int media);\
virtual Bool intf ## _Stop(HsvDestination dest);\
virtual Bool intf ## _StopMedia(HsvDestination dest,int media);\
virtual Bool intf ## _Flush(HsvDestination dest);\
virtual Bool intf ## _EnableMedia(HsvDestination dest,int media);\
virtual Bool intf ## _DisableMedia(HsvDestination dest,int media);\
virtual int intf ## _GetCurrentSelection(HsvDestination dest,int media,int selector);\
virtual Bool intf ## _IsMediaPlaying(HsvDestination dest,int media);\
virtual Bool intf ## _IsMediaEnabled(HsvDestination dest,int media);\
class Comp ## _ ## intf : public IHsvMediaControl \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int GetMediaSize(HsvDestination dest,int media){ return m_parent->intf ## _GetMediaSize(dest,media);}\
virtual Bool GetMediaByKey(HsvDestination dest,int media,int selector1,int selector2,void * value){ return m_parent->intf ## _GetMediaByKey(dest,media,selector1,selector2,value);}\
virtual Bool GetMediaIndex(HsvDestination dest,int media,int selector1,int selecto2,int * index){ return m_parent->intf ## _GetMediaIndex(dest,media,selector1,selecto2,index);}\
virtual Bool GetMediaByIndex(HsvDestination dest,int media,int index,void * value){ return m_parent->intf ## _GetMediaByIndex(dest,media,index,value);}\
virtual Bool SetMedia(HsvDestination dest,int media,int selector,int value){ return m_parent->intf ## _SetMedia(dest,media,selector,value);}\
virtual Bool SetMediaWithProgram(HsvDestination dest,int program,int media,int selector,int value){ return m_parent->intf ## _SetMediaWithProgram(dest,program,media,selector,value);}\
virtual Bool Play(HsvDestination dest){ return m_parent->intf ## _Play(dest);}\
virtual Bool PlayMedia(HsvDestination dest,int media){ return m_parent->intf ## _PlayMedia(dest,media);}\
virtual Bool Stop(HsvDestination dest){ return m_parent->intf ## _Stop(dest);}\
virtual Bool StopMedia(HsvDestination dest,int media){ return m_parent->intf ## _StopMedia(dest,media);}\
virtual Bool Flush(HsvDestination dest){ return m_parent->intf ## _Flush(dest);}\
virtual Bool EnableMedia(HsvDestination dest,int media){ return m_parent->intf ## _EnableMedia(dest,media);}\
virtual Bool DisableMedia(HsvDestination dest,int media){ return m_parent->intf ## _DisableMedia(dest,media);}\
virtual int GetCurrentSelection(HsvDestination dest,int media,int selector){ return m_parent->intf ## _GetCurrentSelection(dest,media,selector);}\
virtual Bool IsMediaPlaying(HsvDestination dest,int media){ return m_parent->intf ## _IsMediaPlaying(dest,media);}\
virtual Bool IsMediaEnabled(HsvDestination dest,int media){ return m_parent->intf ## _IsMediaEnabled(dest,media);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
