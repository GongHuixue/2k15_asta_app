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
 *          %name: hsvpgdat_tvproviderblobdata.h %
 *       %version: cltv1_Fusion_13 %
 * %date_modified: Mon Apr 06 16:33:51 2009 %
 *    %derived_by: nituk % 
 */


/*
TVPROVIDER_DIGSRVC_ITEM(prop, stor_spec, decl, decl_func, defaultval, GetFunc, PutFunc)
prop:           PropertyId
stor_spec   :   Type of Storage
decl        :   Indicate whether there is a need to do specific declaration
decl_func   :   Type of declare function
defaultval  :   Default value of the property
GetFunc     :   Get function to be used to read from the file
PutFunc     :   Put function to be used to write to file
*/

TVPROVIDER_COMMON_ITEM(PresetNumber,      		Nat16,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, NON_DIGTS)
TVPROVIDER_COMMON_ITEM(OriginalNetworkId,      		Nat16,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_COMMON_ITEM(Tsid,      		Nat16,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_COMMON_ITEM(ServiceId,      		Nat16,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, NON_DIGTS)
TVPROVIDER_COMMON_ITEM(Frequency,      		Nat32,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_COMMON_ITEM(LnbNumber,      		Nat8,   NO,      NONE,  	0, PRESET, SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_COMMON_ITEM(Polarization,      		Nat8,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_COMMON_ITEM(DecoderType,      		Nat8,   NO,      NONE,  	0, NON_PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_DIGSRVC_ITEM(TextSubTitlePage,     	Nat32,     NO,  	NONE, 0)
TVPROVIDER_DIGSRVC_ITEM(LogoURL,               	Nat32,    NO,      NONE,  0     )
TVPROVIDER_COMMON_ITEM(ModulationType,      		Nat8,   NO,      NONE,  	0, NON_PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_DIGSRVC_ITEM(UserModifiedLogo,     	Nat8,     NO,  	   NONE, 	0)
TVPROVIDER_DIGSRVC_ITEM(SAP,                  	Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(PreferredStereo,      	Nat8,     NO,      NONE,  1     )
TVPROVIDER_VECTOR_ITEM(ChannelName,			Nat16,	  NAME,    A(41),	0) 
TVPROVIDER_DIGSRVC_ITEM(Ptc,					Nat32,    NO,      NONE,  	0)
TVPROVIDER_COMMON_ITEM(SymbolRate,      		Nat32,   NO,      NONE,  	0, NON_PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_DIGSRVC_ITEM(AudioPid,             	Nat16,    NO,      NONE,  0x1FFF)
TVPROVIDER_DIGSRVC_ITEM(VideoPid,             	Nat16,    NO,      NONE,  0x1FFF)
TVPROVIDER_DIGSRVC_ITEM(PcrPid,               	Nat16,    NO,      NONE,  0x1FFF)
TVPROVIDER_COMMON_ITEM(NetworkId,      		Nat16,   NO,      NONE,  	0, NON_PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_DIGSRVC_ITEM(LCN,                  	Nat16,    NO,      NONE,  0xC000) 
TVPROVIDER_DIGSRVC_ITEM(ServiceType,          	Nat8,     NO,      NONE,  	0)
TVPROVIDER_COMMON_ITEM(SystemHidden,      		Nat16,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, NON_DIGTS)
TVPROVIDER_COMMON_ITEM(NumericSelect,      		Nat8,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, NON_DIGTS)
TVPROVIDER_COMMON_ITEM(Bandwidth,      		Nat8,   NO,      NONE,  	0, NON_PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_DIGSRVC_ITEM(ScrambledStatus,		Nat8,     NO,      NONE,  	0)
TVPROVIDER_DIGSRVC_ITEM(IntHbbTvOption,			Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(UserHidden,           	Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(NewPreset,            	Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(VideoStreamType,      	Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(AudioStreamType,      	Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(DpTsid,                Nat16,    NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(DpServiceId,           Nat16,    NO,      NONE,  0     )
TVPROVIDER_COMMON_ITEM(Tpid,      		Nat32,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_DIGSRVC_ITEM(PackageGroup,          Nat16,    NO,      NONE,  0     )

/*Private Data*/
/*Preset Data*/
TVPROVIDER_COMMON_ITEM(FavoriteNumber,      		Nat16,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, NON_DIGTS)
TVPROVIDER_COMMON_ITEM(VisibleService,      		Nat8,   NO,      NONE,  	0, PRESET, NON_SATINFO, DIGSRVC, NON_DIGTS)

/*Satinfo Data */
TVPROVIDER_SATINFO_ITEM(LnbType,				 Nat16,   NO,      NONE,  0)
TVPROVIDER_SATINFO_ITEM(SatelliteId,			 Nat16,	  NO,	   NONE,  0)
TVPROVIDER_SATINFO_ITEM(OrbitalPosition,		 Nat16,   NO,      NONE, 0)
TVPROVIDER_VECTOR_ITEM(SatelliteName,          	Nat16,    NAME,    A(23), 	0) 


/*Service Data*/
TVPROVIDER_DIGSRVC_ITEM(SignalStrength,        Nat32,    NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(SignalQuality,         Nat32,    NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(AppsCookie,            Nat32,    NO,      NONE,  0     )
TVPROVIDER_COMMON_ITEM(SDTVersion,      		Nat16,   NO,      NONE,  	0, NON_PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_COMMON_ITEM(NITVersion,      		Nat16,   NO,      NONE,  	0, NON_PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_DIGSRVC_ITEM(DateStamp,             Nat32,    NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(PmtPid,                Nat16,    NO,      NONE,  0x1FFF)
TVPROVIDER_DIGSRVC_ITEM(SecAudioPid,           Nat16,    NO,      NONE,  0x1FFF)
TVPROVIDER_DIGSRVC_ITEM(LowPrioLCN,            Nat16,    NO,      NONE,  0xC000) 
TVPROVIDER_DIGSRVC_ITEM(LowPrioVisibleService, Nat8,     NO,      NONE,  1     )
TVPROVIDER_DIGSRVC_ITEM(FreeCiMode,            Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(VideoDescPresent,      Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(ScramblingStatus,      Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(DuplicateSvc,          Nat8,     NO,      NONE,  0     )
TVPROVIDER_VECTOR_ITEM(MultipleVisibleService,          	Nat16,    NAME,    A(8), 	1) 
TVPROVIDER_DIGSRVC_ITEM(ServiceListVersion,    Nat8,     NO,      NONE,  0     )
TVPROVIDER_COMMON_ITEM(UserInstalled,		   Nat8,	 NO,	  NONE, 	0, NON_PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_DIGSRVC_ITEM(SecAudioStreamType,    Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(UserModifiedName,            Nat8,     NO,      NONE,  0     )
TVPROVIDER_VECTOR_ITEM(MultipleNumericSelect,          	Nat16,    NAME,    A(8), 	1) 
TVPROVIDER_DIGSRVC_ITEM(ChannelLock,           Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(DvbType,        		Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(MatchBrandFlag,        Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(NumBrandIds,           Nat32,    NO,      NONE,  0     )
TVPROVIDER_VECTOR_ITEM(BrandIds,          	Nat16,    NAME,    A(23), 	0) 
TVPROVIDER_DIGSRVC_ITEM(InstalledSatelliteNumber,	Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(NewChannel,			Nat8,     NO,      NONE,  0     )
TVPROVIDER_DIGSRVC_ITEM(HbbTvOption,			Nat8,     NO,      NONE,  0     )
TVPROVIDER_COMMON_ITEM(SDSDFrequency,		   Nat32,	 NO,	  NONE, 	0, NON_PRESET, NON_SATINFO, DIGSRVC, DIGTS)
TVPROVIDER_DIGSRVC_ITEM(CountryCode,			Nat32,	  NO,    NONE,  0x1FFFFFF )
TVPROVIDER_DIGSRVC_ITEM(HDSimulcastRepOnId,	Nat16,    NO,      NONE,  0xFFFF    )
TVPROVIDER_DIGSRVC_ITEM(HDSimulcastRepTsId,	Nat16,    NO,      NONE,  0xFFFF    )
TVPROVIDER_DIGSRVC_ITEM(HDSimulcastRepSvcId,	Nat16,    NO,      NONE,  0xFFFF    )
TVPROVIDER_VECTOR_ITEM(MultipleLCN,          	Nat16,    NAME,    A(8), 	0) 
TVPROVIDER_VECTOR_ITEM(MultiplePreset,          	Nat16,    NAME,    A(8), 	0) 
TVPROVIDER_DIGSRVC_ITEM(ParentalRating,        Nat8,     NO,      NONE, 0     )
TVPROVIDER_DIGSRVC_ITEM(ServiceIdentifier,     Nat16,    NO,      NONE, 0     )
TVPROVIDER_VECTOR_ITEM(MultipleFavorite,          	Nat16,    NAME,    A(8), 	0) 
TVPROVIDER_DIGSRVC_ITEM(AdultGenere,	        Nat8,     NO,      NONE, 0     )
TVPROVIDER_DIGSRVC_ITEM(FreesatServiceIdentifier, Nat16,    NO,      NONE, 0xFFFF)
TVPROVIDER_DIGSRVC_ITEM(InteractiveServiceEnabled, Nat8,    NO,      NONE, 1     )
TVPROVIDER_VECTOR_ITEM(UniqueId,     		Nat32,     NO,  	NONE, 0)

/*TS Data*/
TVPROVIDER_DIGTS_ITEM(ASignalStrength,     Nat32,      NO,      NONE,      0)
TVPROVIDER_DIGTS_ITEM(VSignalStrength,     Nat32,      NO,      NONE,      0)
TVPROVIDER_DIGTS_ITEM(QSignalStrength,     Nat32,      NO,      NONE,      0)
TVPROVIDER_DIGTS_ITEM(ChannelInformation,  Nat16,      NO,      NONE,      0)
TVPROVIDER_DIGTS_ITEM(CodeRate,            Nat8,       NO,      NONE,      0)
TVPROVIDER_DIGTS_ITEM(PtcListVersion,      Nat8,       NO,      NONE,      0)
TVPROVIDER_DIGTS_ITEM(TSVersion,           Nat8,       NO,      NONE,      0)
TVPROVIDER_DIGTS_ITEM(PlpId,				Nat32,      NO,      NONE,      0)		/* Added. May be in future will be used as quatenarary key */
TVPROVIDER_DIGTS_ITEM(BarkerMux,       	Nat8,       NO,      NONE,      0)



