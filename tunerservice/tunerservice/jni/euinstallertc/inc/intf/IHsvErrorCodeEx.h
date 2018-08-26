#ifndef IHSVERRORCODEEX_H
#define IHSVERRORCODEEX_H
#include <intfparam.h>
#include <provreq.h>
class IHsvErrorCodeEx
{
public:
	virtual ~IHsvErrorCodeEx(){}
	#define IHsvErrorCodeEx_Ok		((FResult)0 )
	#define IHsvErrorCodeEx_BadParameter		((FResult)1 )
	#define IHsvErrorCodeEx_ChannelNotInstalled		((FResult)2 )
	#define IHsvErrorCodeEx_SelectionRequestNotHonored		((FResult)3 )
	#define IHsvErrorCodeEx_ChannelAlreadySelected		((FResult)4 )
	#define IHsvErrorCodeEx_ValidSelectionRequest		((FResult)5 )
	#define IHsvErrorCodeEx_InvalidSelectionRequest		((FResult)6 )
	#define IHsvErrorCodeEx_ChannelTableEmpty		((FResult)7 )
	#define IHsvErrorCodeEx_ChannelTableExhausted		((FResult)8 )
	#define IHsvErrorCodeEx_InvalidChannel		((FResult)9 )
	#define IHsvErrorCodeEx_FileError		((FResult)10 )
	#define IHsvErrorCodeEx_ChannelTableVersionError		((FResult)11 )
	#define IHsvErrorCodeEx_ChannelTableCrcError		((FResult)12 )
	#define IHsvErrorCodeEx_NotSupported		((FResult)13 )
	#define IHsvErrorCodeEx_InstallationModeNotSupported		((FResult)20 )
	#define IHsvErrorCodeEx_InstallationCommandNotAllowed		((FResult)21 )
	#define IHsvErrorCodeEx_InstallationNotInProgress		((FResult)22 )
	#define IHsvErrorCodeEx_InvalidPTC		((FResult)23 )
	#define IHsvErrorCodeEx_InvalidMajorChannel		((FResult)24 )
	#define IHsvErrorCodeEx_InvalidMinorChannel		((FResult)25 )
	#define IHsvErrorCodeEx_NoNextMinorChannel		((FResult)26 )
	#define IHsvErrorCodeEx_NoPreviousMinorChannel		((FResult)27 )
	#define IHsvErrorCodeEx_InvalidSource		((FResult)28 )
	#define IHsvErrorCodeEx_NoNextsource		((FResult)29 )
	#define IHsvErrorCodeEx_NoPreviousSource		((FResult)30 )
	#define IHsvErrorCodeEx_InvalidMode		((FResult)31 )
	#define IHsvErrorCodeEx_InstallationStoreFailed		((FResult)32 )
	#define IHsvErrorCodeEx_InvalidDestination		((FResult)33 )
	#define IHsvErrorCodeEx_EmptyPreset		((FResult)34 )
	#define IHsvErrorCodeEx_InvalidTypeOfSelection		((FResult)35 )
	#define IHsvErrorCodeEx_ControlledSelectionNotAllowed		((FResult)36 )
	#define IHsvErrorCodeEx_InvalidAttribute		((FResult)37 )
	#define IHsvErrorCodeEx_AudioLanguageNotAvailable		((FResult)38 )
	#define IHsvErrorCodeEx_InvalidInterface		((FResult)39 )
};


#define IHsvErrorCodeExImpl(Comp,intf)    \
class Comp ## _ ## intf : public IHsvErrorCodeEx \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
};\
Comp ## _ ## intf i__ ## intf;


#endif
