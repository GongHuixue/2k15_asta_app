#ifndef IHSVLOG_H
#define IHSVLOG_H
#include <intfparam.h>
#include <provreq.h>
class IHsvLog
{
public:
	virtual ~IHsvLog(){}
	#define IHsvLog_Information		((int)0 )
	#define IHsvLog_SoftErr		((int)1 )
	#define IHsvLog_FatalErr		((int)2 )
	virtual void Error(int prio,int errid)= 0;
	virtual void Trace(int callerid,int arg1,int arg2)= 0;
};


#define IHsvLogImpl(Comp,intf)    \
virtual void intf ## _Error(int prio,int errid);\
virtual void intf ## _Trace(int callerid,int arg1,int arg2);\
class Comp ## _ ## intf : public IHsvLog \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void Error(int prio,int errid){ return m_parent->intf ## _Error(prio,errid);}\
virtual void Trace(int callerid,int arg1,int arg2){ return m_parent->intf ## _Trace(callerid,arg1,arg2);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
