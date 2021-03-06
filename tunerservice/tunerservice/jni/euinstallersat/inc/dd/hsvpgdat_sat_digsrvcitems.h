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
 *          %name: hsvpgdat_digsrvcitems.h %
 *       %version: TVG_2 %
 * %date_modified: Mon Apr 06 16:33:51 2009 %
 *    %derived_by: aneeshc % 
 */


/*
DIGSRVC_ITEM(prop, stor_spec, decl, decl_func, defaultval, GetFunc, PutFunc)
prop:           PropertyId
stor_spec   :   Type of Storage
decl        :   Indicate whether there is a need to do specific declaration
decl_func   :   Type of declare function
defaultval  :   Default value of the property
GetFunc     :   Get function to be used to read from the file
PutFunc     :   Put function to be used to write to file
*/


/* Prop,                 stor_spec, bit_decl, bit_def, DefaultValue,getfn,putfn)*/

DIGSRVC_ITEM(SignalStrength,        Nat32,    NO,      NONE,  0     )
DIGSRVC_ITEM(SignalQuality,         Nat32,    NO,      NONE,  0     )
DIGSRVC_ITEM(SymbolRate,            Nat32,    NO,      NONE,  0     )
DIGSRVC_ITEM(DateStamp,             Nat32,    NO,      NONE,  0     )
DIGSRVC_ITEM(Ptc,					Nat32,    NO,      NONE,  0     )
DIGSRVC_ITEM(Tpid,					Nat32,    NO,      NONE,  0		)		/* PRIMARY KEY: Newly Added */

DIGSRVC_ITEM(DeltaVolume,           Nat32,      NO,      NONE,  0     )

DIGSRVC_ITEM(Frequency,             Nat32,    NO,      NONE,  0     )

DIGSRVC_ITEM(OriginalNetworkId,     Nat16,    NO,      NONE,  0     )
DIGSRVC_ITEM(ServiceId,             Nat16,    NO,      NONE,  0     )
DIGSRVC_ITEM(Tsid,                  Nat16,    NO,      NONE,  0     )
DIGSRVC_ITEM(NetworkId,             Nat16,    NO,      NONE,  0     )
DIGSRVC_ITEM(PmtPid,                Nat16,    NO,      NONE,  0x1FFF)
DIGSRVC_ITEM(PcrPid,                Nat16,    NO,      NONE,  0x1FFF)
DIGSRVC_ITEM(VideoPid,              Nat16,    NO,      NONE,  0x1FFF)
DIGSRVC_ITEM(AudioPid,              Nat16,    NO,      NONE,  0x1FFF)
DIGSRVC_ITEM(ChannelName,           Nat16,    NAME,    A(33), 0     ) 
DIGSRVC_ITEM(LCN,                   Nat16,    NO,      NONE,  0xC000) 
DIGSRVC_ITEM(SecAudioPid,           Nat16,    NO,      NONE,  0x1FFF)
DIGSRVC_ITEM(PresetNumber,          Int16,    NO,      NONE,  (-1)     ) 

DIGSRVC_ITEM(NumericSelect,         Nat16,     NO,     NONE,  1     )
DIGSRVC_ITEM(MultipleNumericSelect, Nat16,     NAME,   A(8),  1     )
DIGSRVC_ITEM(LnbNumber,				Nat8,     NO,      NONE,  1     )	/*Newly Added */
DIGSRVC_ITEM(Polarization, 			Nat8,     NO,      NONE,  1     )	/*Newly Added */
DIGSRVC_ITEM(FreeCiMode,            Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(ScramblingStatus,      Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(VisibleService,        Nat16,    NO,      NONE,  1     )
DIGSRVC_ITEM(MultipleVisibleService,        Nat16,     NAME,      A(8),  1     )
DIGSRVC_ITEM(ServiceListVersion,    Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(UserInstalled,         Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(ServiceType,           Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(VideoStreamType,       Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(AudioStreamType,       Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(SecAudioStreamType,    Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(SystemHidden,          Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(UserHidden,            Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(NewPreset,             Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(UserModifiedName,            Nat8,     NO,      NONE,  0     )

DIGSRVC_ITEM(ChannelLock,           Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(SAP,                   Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(PreferredStereo,       Nat8,     NO,      NONE,  1     )
DIGSRVC_ITEM(MatchBrandFlag,        Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(NumBrandIds,           Nat32,    NO,      NONE,  0     )
DIGSRVC_ITEM(BrandIds,              Nat16,    NAME,    A(23), 0     )
DIGSRVC_ITEM(ModulationType,        Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(Bandwidth,      Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(ExtChannelName,        Nat16,    NAME,    A(33), 0     )  
DIGSRVC_ITEM(SatelliteName,         Nat16,    NAME,    A(23), 0     )
DIGSRVC_ITEM(ScrambledStatus,		Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(InstalledSatelliteNumber,	Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(IntHbbTvOption,		Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(BoolChannelLock,		Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(TxtPages,              Nat16,    NAME,    A(23), 0     )
DIGSRVC_ITEM(LogoURL,               Nat32,    NO,      NONE,  0     )
DIGSRVC_ITEM(FavoriteNumber,		Nat16,     NO,      NONE,  0     )
DIGSRVC_ITEM(NewChannel,			Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(HbbTvOption,			Nat8,     NO,      NONE,  0     )
DIGSRVC_ITEM(UserModifiedLogo,      Nat8,     NO,  	NONE, 0)
DIGSRVC_ITEM(DpServiceId,           Nat16,    NO,      NONE,  0     )
DIGSRVC_ITEM(DpTsid,                Nat16,    NO,      NONE,  0     )
DIGSRVC_ITEM(SDSDFrequency,         Nat32,    NO,      NONE,  0		)
DIGSRVC_ITEM(PackageGroup,          Nat16,    NO,      NONE,  0     )
DIGSRVC_ITEM(MultipleLCN,           Nat16,    NAME,      A(8),  0xC000)
DIGSRVC_ITEM(MultiplePreset,        Int16,    NAME,      A(8),  (-1)     )
DIGSRVC_ITEM(ParentalRating,        Nat8,     NO,      NONE, 0     )
DIGSRVC_ITEM(ServiceIdentifier,     Nat16,    NO,      NONE, 0     )
DIGSRVC_ITEM(TextSubTitlePage,      Nat32,     NO,  	NONE, 0)
DIGSRVC_ITEM(MultipleFavorite, 		Nat16, 	NAME,      A(8), 0) /*Newly Addded*/
DIGSRVC_ITEM(UniqueIds,				Nat32,	NAME,      A(8),	0)
DIGSRVC_ITEM(AdultGenere,	        Nat8,     NO,      NONE, 0     )
DIGSRVC_ITEM(FreesatServiceIdentifier, Nat16,    NO,      NONE, 0xFFFF)
DIGSRVC_ITEM(InteractiveServiceEnabled, Nat8,    NO,      NONE, 1     )