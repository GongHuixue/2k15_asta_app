#ifndef  _CHSVDVBSTRICOLOR_MSETTINGS_PRIV_H
#define  _CHSVDVBSTRICOLOR_MSETTINGS_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSatelliteSettings.h>
#include <IHsvPower.h>
#include <IHsvErrorCodeEx.h>
#include <CS2MwBase.h>

class CHsvDvbsTricolor_msettings_Priv;
#define CLASSSCOPE CHsvDvbsTricolor_msettings_Priv::
#include "locals_msettings.h"

class CHsvDvbsTricolor_msettings_Priv : public CS2MwBase
{
public:
	virtual ~CHsvDvbsTricolor_msettings_Priv();

private:
	void params__init(void);

private:
#define MEMBERVARS
#include "locals_msettings.h"
#undef MEMBERVARS

//Provided interfaces
private:
	IHsvSatelliteSettingsImpl(CHsvDvbsTricolor_msettings_Priv,idvbset);
	IHsvPowerImpl(CHsvDvbsTricolor_msettings_Priv,idvbsetpow);

//Provided Interfaces
public:

	ProvidesInterface<IHsvSatelliteSettings>	idvbset;
	ProvidesInterface<IHsvPower>				idvbsetpow;

//Required Interfaces
public:

	RequiresInterface<IHsvErrorCodeEx>			err;

public:
	CHsvDvbsTricolor_msettings_Priv():i__idvbset(this),i__idvbsetpow(this)
	{
		idvbset	=	&i__idvbset;
		idvbsetpow	=	&i__idvbsetpow;
		module__init();
		params__init();
	}

};

#ifdef GENERATE__LEGACY__DEFINES

#define err_iPresent() (err.Present())
#define err_Ok	IHsvErrorCodeEx_Ok
#define err_BadParameter	IHsvErrorCodeEx_BadParameter
#define err_ChannelNotInstalled	IHsvErrorCodeEx_ChannelNotInstalled
#define err_SelectionRequestNotHonored	IHsvErrorCodeEx_SelectionRequestNotHonored
#define err_ChannelAlreadySelected	IHsvErrorCodeEx_ChannelAlreadySelected
#define err_ValidSelectionRequest	IHsvErrorCodeEx_ValidSelectionRequest
#define err_InvalidSelectionRequest	IHsvErrorCodeEx_InvalidSelectionRequest
#define err_ChannelTableEmpty	IHsvErrorCodeEx_ChannelTableEmpty
#define err_ChannelTableExhausted	IHsvErrorCodeEx_ChannelTableExhausted
#define err_InvalidChannel	IHsvErrorCodeEx_InvalidChannel
#define err_FileError	IHsvErrorCodeEx_FileError
#define err_ChannelTableVersionError	IHsvErrorCodeEx_ChannelTableVersionError
#define err_ChannelTableCrcError	IHsvErrorCodeEx_ChannelTableCrcError
#define err_NotSupported	IHsvErrorCodeEx_NotSupported
#define err_InstallationModeNotSupported	IHsvErrorCodeEx_InstallationModeNotSupported
#define err_InstallationCommandNotAllowed	IHsvErrorCodeEx_InstallationCommandNotAllowed
#define err_InstallationNotInProgress	IHsvErrorCodeEx_InstallationNotInProgress
#define err_InvalidPTC	IHsvErrorCodeEx_InvalidPTC
#define err_InvalidMajorChannel	IHsvErrorCodeEx_InvalidMajorChannel
#define err_InvalidMinorChannel	IHsvErrorCodeEx_InvalidMinorChannel
#define err_NoNextMinorChannel	IHsvErrorCodeEx_NoNextMinorChannel
#define err_NoPreviousMinorChannel	IHsvErrorCodeEx_NoPreviousMinorChannel
#define err_InvalidSource	IHsvErrorCodeEx_InvalidSource
#define err_NoNextsource	IHsvErrorCodeEx_NoNextsource
#define err_NoPreviousSource	IHsvErrorCodeEx_NoPreviousSource
#define err_InvalidMode	IHsvErrorCodeEx_InvalidMode
#define err_InstallationStoreFailed	IHsvErrorCodeEx_InstallationStoreFailed
#define err_InvalidDestination	IHsvErrorCodeEx_InvalidDestination
#define err_EmptyPreset	IHsvErrorCodeEx_EmptyPreset
#define err_InvalidTypeOfSelection	IHsvErrorCodeEx_InvalidTypeOfSelection
#define err_ControlledSelectionNotAllowed	IHsvErrorCodeEx_ControlledSelectionNotAllowed
#define err_InvalidAttribute	IHsvErrorCodeEx_InvalidAttribute
#define err_AudioLanguageNotAvailable	IHsvErrorCodeEx_AudioLanguageNotAvailable
#define err_InvalidInterface	IHsvErrorCodeEx_InvalidInterface
#define err_DiseqcError	IHsvErrorCodeEx_DiseqcError
#define err_TunerError	IHsvErrorCodeEx_TunerError
#define err_UsbPathNotFound	IHsvErrorCodeEx_UsbPathNotFound
#define idvbset_AttributePackageId	IHsvSatelliteSettings_AttributePackageId
#define idvbset_AttributeTricolorRegionNameData IHsvSatelliteSettings_AttributeTricolorRegionNameData



#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_msettings.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

