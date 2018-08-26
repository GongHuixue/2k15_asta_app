#ifndef IHSVALTFREQUENCYSCANNERNOTIFY_H
#define IHSVALTFREQUENCYSCANNERNOTIFY_H
#include <intfparam.h>
#include <provreq.h>
class IHsvAltFrequencyScannerNotify
{
public:
	virtual ~IHsvAltFrequencyScannerNotify(){}
	#define IHsvAltFrequencyScannerNotify_StatusSignalFound		((int)1 )
	#define IHsvAltFrequencyScannerNotify_StatusSignalNotFound		((int)2 )
	#define IHsvAltFrequencyScannerNotify_StatusInterrupted		((int)3 )
	#define IHsvAltFrequencyScannerNotify_StatusStopped		((int)4 )
	virtual void OnAltFrequencyScanRequested(void)= 0;
	virtual void OnAltFrequencyScanInProgress(void)= 0;
	virtual void OnAltFrequencyScanCompleted(int Status)= 0;
	virtual void OnFrequencyListUpdateDetected(void)= 0;
};


#define IHsvAltFrequencyScannerNotifyImpl(Comp,intf)    \
virtual void intf ## _OnAltFrequencyScanRequested(void);\
virtual void intf ## _OnAltFrequencyScanInProgress(void);\
virtual void intf ## _OnAltFrequencyScanCompleted(int Status);\
virtual void intf ## _OnFrequencyListUpdateDetected(void);\
class Comp ## _ ## intf : public IHsvAltFrequencyScannerNotify \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual void OnAltFrequencyScanRequested(void){ return m_parent->intf ## _OnAltFrequencyScanRequested();}\
virtual void OnAltFrequencyScanInProgress(void){ return m_parent->intf ## _OnAltFrequencyScanInProgress();}\
virtual void OnAltFrequencyScanCompleted(int Status){ return m_parent->intf ## _OnAltFrequencyScanCompleted(Status);}\
virtual void OnFrequencyListUpdateDetected(void){ return m_parent->intf ## _OnFrequencyListUpdateDetected();}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
