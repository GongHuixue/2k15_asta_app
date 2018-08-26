#ifndef IHSVSTREAMWALKER_H
#define IHSVSTREAMWALKER_H
#include <intfparam.h>
#include <provreq.h>
class IHsvStreamWalker
{
public:
	virtual ~IHsvStreamWalker(){}
	#define IHsvStreamWalker_InvalidStreamId		((int)-1 )
	virtual int Register(int StreamId,Address Buffer,int MaxSize)= 0;
	virtual int RegisterEx(int StreamId,Address PrimaryBuffer,Address SecondaryBuffer,int PrimarySize,int SecondarySize)= 0;
	virtual void Unregister(int StreamId)= 0;
	virtual Nat32 GetBits(int StreamId,int numbits)= 0;
	virtual Nat32 ShowBits(int StreamId,int numbits)= 0;
	virtual void SkipBits(int StreamId,int numbits)= 0;
	virtual void CopyBits(int StreamId,Address destination,int numbits)= 0;
	virtual void SeekBits(int StreamId,Address destination,int numbits)= 0;
	virtual void AlignToNextByte(int StreamId)= 0;
	virtual Bool IsEndOfStream(int StreamId)= 0;
	virtual Nat32 GetBitsRead(int StreamId)= 0;
	virtual Nat32 GetBitsUnread(int StreamId)= 0;
	virtual void* GetStreamBuffer(int StreamId)= 0;
	virtual int GetSectionSize(int StreamId)= 0;
	virtual int PutBytes(int StreamId,Address Buffer,int numbits)= 0;
	virtual int PutBits(int StreamId,int numbits,Nat32 val)= 0;
	virtual int PushBits(int StreamId,int numbits,Nat32 val)= 0;
};


#define IHsvStreamWalkerImpl(Comp,intf)    \
virtual int intf ## _Register(int StreamId,Address Buffer,int MaxSize);\
virtual int intf ## _RegisterEx(int StreamId,Address PrimaryBuffer,Address SecondaryBuffer,int PrimarySize,int SecondarySize);\
virtual void intf ## _Unregister(int StreamId);\
virtual Nat32 intf ## _GetBits(int StreamId,int numbits);\
virtual Nat32 intf ## _ShowBits(int StreamId,int numbits);\
virtual void intf ## _SkipBits(int StreamId,int numbits);\
virtual void intf ## _CopyBits(int StreamId,Address destination,int numbits);\
virtual void intf ## _SeekBits(int StreamId,Address destination,int numbits);\
virtual void intf ## _AlignToNextByte(int StreamId);\
virtual Bool intf ## _IsEndOfStream(int StreamId);\
virtual Nat32 intf ## _GetBitsRead(int StreamId);\
virtual Nat32 intf ## _GetBitsUnread(int StreamId);\
virtual void* intf ## _GetStreamBuffer(int StreamId);\
virtual int intf ## _GetSectionSize(int StreamId);\
virtual int intf ## _PutBytes(int StreamId,Address Buffer,int numbits);\
virtual int intf ## _PutBits(int StreamId,int numbits,Nat32 val);\
virtual int intf ## _PushBits(int StreamId,int numbits,Nat32 val);\
class Comp ## _ ## intf : public IHsvStreamWalker \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int Register(int StreamId,Address Buffer,int MaxSize){ return m_parent->intf ## _Register(StreamId,Buffer,MaxSize);}\
virtual int RegisterEx(int StreamId,Address PrimaryBuffer,Address SecondaryBuffer,int PrimarySize,int SecondarySize){ return m_parent->intf ## _RegisterEx(StreamId,PrimaryBuffer,SecondaryBuffer,PrimarySize,SecondarySize);}\
virtual void Unregister(int StreamId){ return m_parent->intf ## _Unregister(StreamId);}\
virtual Nat32 GetBits(int StreamId,int numbits){ return m_parent->intf ## _GetBits(StreamId,numbits);}\
virtual Nat32 ShowBits(int StreamId,int numbits){ return m_parent->intf ## _ShowBits(StreamId,numbits);}\
virtual void SkipBits(int StreamId,int numbits){ return m_parent->intf ## _SkipBits(StreamId,numbits);}\
virtual void CopyBits(int StreamId,Address destination,int numbits){ return m_parent->intf ## _CopyBits(StreamId,destination,numbits);}\
virtual void SeekBits(int StreamId,Address destination,int numbits){ return m_parent->intf ## _SeekBits(StreamId,destination,numbits);}\
virtual void AlignToNextByte(int StreamId){ return m_parent->intf ## _AlignToNextByte(StreamId);}\
virtual Bool IsEndOfStream(int StreamId){ return m_parent->intf ## _IsEndOfStream(StreamId);}\
virtual Nat32 GetBitsRead(int StreamId){ return m_parent->intf ## _GetBitsRead(StreamId);}\
virtual Nat32 GetBitsUnread(int StreamId){ return m_parent->intf ## _GetBitsUnread(StreamId);}\
virtual void* GetStreamBuffer(int StreamId){ return m_parent->intf ## _GetStreamBuffer(StreamId);}\
virtual int GetSectionSize(int StreamId){ return m_parent->intf ## _GetSectionSize(StreamId);}\
virtual int PutBytes(int StreamId,Address Buffer,int numbits){ return m_parent->intf ## _PutBytes(StreamId,Buffer,numbits);}\
virtual int PutBits(int StreamId,int numbits,Nat32 val){ return m_parent->intf ## _PutBits(StreamId,numbits,val);}\
virtual int PushBits(int StreamId,int numbits,Nat32 val){ return m_parent->intf ## _PushBits(StreamId,numbits,val);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
