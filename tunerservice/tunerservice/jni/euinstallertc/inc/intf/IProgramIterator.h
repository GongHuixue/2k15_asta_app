#ifndef IPROGRAMITERATOR_H
#define IPROGRAMITERATOR_H
#include <intfparam.h>
#include <provreq.h>
class IProgramIterator
{
public:
	virtual ~IProgramIterator(){}
	virtual Bool GetFirstProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor)= 0;
	virtual Bool GetLastProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor)= 0;
	virtual Bool GetNextProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor)= 0;
	virtual Bool GetPrevProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor)= 0;
	virtual Bool GetFirstProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor)= 0;
	virtual Bool GetLastProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor)= 0;
	virtual Bool GetNextProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor)= 0;
	virtual Bool GetPrevProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor)= 0;
};


#define IProgramIteratorImpl(Comp,intf)    \
virtual Bool intf ## _GetFirstProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor);\
virtual Bool intf ## _GetLastProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor);\
virtual Bool intf ## _GetNextProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor);\
virtual Bool intf ## _GetPrevProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor);\
virtual Bool intf ## _GetFirstProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor);\
virtual Bool intf ## _GetLastProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor);\
virtual Bool intf ## _GetNextProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor);\
virtual Bool intf ## _GetPrevProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor);\
class Comp ## _ ## intf : public IProgramIterator \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual Bool GetFirstProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor){ return m_parent->intf ## _GetFirstProgram(source,majorChannel,minorChannel,descriptor);}\
virtual Bool GetLastProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor){ return m_parent->intf ## _GetLastProgram(source,majorChannel,minorChannel,descriptor);}\
virtual Bool GetNextProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor){ return m_parent->intf ## _GetNextProgram(source,majorChannel,minorChannel,descriptor);}\
virtual Bool GetPrevProgram(TvSource * source,int * majorChannel,int * minorChannel,int descriptor){ return m_parent->intf ## _GetPrevProgram(source,majorChannel,minorChannel,descriptor);}\
virtual Bool GetFirstProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor){ return m_parent->intf ## _GetFirstProgramEx(destination,source,majorChannel,minorChannel,descriptor);}\
virtual Bool GetLastProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor){ return m_parent->intf ## _GetLastProgramEx(destination,source,majorChannel,minorChannel,descriptor);}\
virtual Bool GetNextProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor){ return m_parent->intf ## _GetNextProgramEx(destination,source,majorChannel,minorChannel,descriptor);}\
virtual Bool GetPrevProgramEx(TvDestination destination,TvSource * source,int * majorChannel,int * minorChannel,int descriptor){ return m_parent->intf ## _GetPrevProgramEx(destination,source,majorChannel,minorChannel,descriptor);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
