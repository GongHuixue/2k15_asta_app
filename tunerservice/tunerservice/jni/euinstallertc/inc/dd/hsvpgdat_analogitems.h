/*
 *  Copyright(C) 2009 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: hsvpgdat_analogitems.h %
 *       %version: cltv1_Fusion_18 %
 * %date_modified: Mon Apr 06 16:33:51 2009 %
 *    %derived_by: nituk % 
 */


/*
ANALOGITEM(prop, stor_spec, decl, decl_func, defaultval, GetFunc, PutFunc)
prop:           PropertyId
stor_spec   :   Type of Storage
decl        :   Indicate whether there is a need to do specific declaration
decl_func   :   Type of declare function
defaultval  :   Default value of the property
GetFunc     :   Get function to be used to read from the file
PutFunc     :   Put function to be used to write to file
*/

//ANALOG_ITEM(CRC,                    Nat32,      NO,     NONE,  0)

ANALOG_ITEM(Frequency,              Nat32,      NO,     NONE,  0)
ANALOG_ITEM(FineTuneFrequency,      Nat32,      NO,     NONE,  0)
ANALOG_ITEM(SignalStrength,         Nat32,        NO,     NONE,  0)
//ANALOG_ITEM(InstallMode,            Nat32,        NO,     NONE,  0)
ANALOG_ITEM(FineTuneOffset,         Nat32,        NO,     NONE,  0)
ANALOG_ITEM(ColourSystem,           Nat32,        NO,     NONE,  0)

ANALOG_ITEM(DeltaVolume,            Nat32,        NO,     NONE,  0)
//ANALOG_ITEM(AppsCookie,             Nat32,      NO,     NONE,  0)
//ANALOG_ITEM(TxtCookie,              Nat32,      NO,     NONE,  0)
//ANALOG_ITEM(CesvcCookie,            Nat32,      NO,     NONE,  0)

ANALOG_ITEM(ChannelName,            Nat16,      NAME,   A(23), 0)
ANALOG_ITEM(CniNi,                  Nat16,      NO,     NONE,  0)
ANALOG_ITEM(PresetNumber,           Int16,      NO,     NONE,  0)

ANALOG_ITEM(DataIndicator,          Nat8,       NO,     NONE,  0)
ANALOG_ITEM(ModulationType,         Nat8,       NO,     NONE,  0)
ANALOG_ITEM(DecoderType,            Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(ChannelVirgin,          Nat8,       NO,     NONE,  0)
ANALOG_ITEM(Attenuator,             Nat8,       NO,     NONE,  0)
ANALOG_ITEM(Tuned,                  Nat8,       NO,     NONE,  0)
ANALOG_ITEM(DeTuned,                Nat8,       NO,     NONE,  0)
ANALOG_ITEM(AgcInstalled,           Nat8,       NO,     NONE,  0)

//ANALOG_ITEM(HMMapChannelNo,         Nat8,       NO,     NONE,  0)
ANALOG_ITEM(UserModifiedName,             Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(Favorite,				Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(Favorite1,              Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(Favorite2,              Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(Favorite3,              Nat8,       NO,     NONE,  0)
ANALOG_ITEM(PreferredFavorite,      Nat8,       NO,     NONE,  0)
ANALOG_ITEM(PreferredStereo,        Nat8,       NO,     NONE,  1)
ANALOG_ITEM(PreferredNicam,         Nat8,       NO,     NONE,  0)
ANALOG_ITEM(SAP,                    Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(HMBlanked,              Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(HMProtectedChannel,     Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(AssociatedDecoder,		Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(UserHidden,				Nat8,       NO,     NONE,  0)
ANALOG_ITEM(ChannelLock,			Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(ExtChannelName,         Nat16,      NAME,   A(33), 0) 
//ANALOG_ITEM(NewChannelMap,			Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(Dummy,			Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(FavoriteNumber1,        Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(FavoriteNumber2,        Nat8,       NO,     NONE,  0)
//ANALOG_ITEM(FavoriteNumber3,        Nat8,       NO,     NONE,  0)
ANALOG_ITEM(FavoriteNumber,			Nat16,      NO,     NONE,  0)
ANALOG_ITEM(TxtPages,               Nat16,      NAME,   A(23), 0x07FF)
ANALOG_ITEM(UserModifiedLogo,       Nat8,       NO,  	NONE, 0)
ANALOG_ITEM(LogoURL,               Nat32,    NO,      NONE,  0     )
ANALOG_ITEM(TextSubTitlePage,               Nat32,    NO,      NONE,  0     )
ANALOG_ITEM(UniqueId,               Nat32,    NO,      NONE,  0     )