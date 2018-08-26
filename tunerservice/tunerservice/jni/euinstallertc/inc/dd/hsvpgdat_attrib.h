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
 *          %name: hsvpgdat_attrib.h %
 *       %version: cltv1_Fusion_11 %
 * %date_modified: Mon Apr 06 16:33:51 2009 %
 *    %derived_by: nituk % 
 */


/*      Attribute                     Type    Ptr Supported       FieldName           FieldType*/
SCALAR_ITEM(BoolLock                  ,Bool   ,NO     ,1      ,ChannelLock            ,Nat8     ,COMMON_ATTRIB)
SCALAR_ITEM(BoolPreferredFavorite     ,Bool   ,NO     ,1      ,PreferredFavorite      ,Nat8     ,COMMON_ATTRIB)
SCALAR_ITEM(BoolPreferredStereo       ,Bool   ,NO     ,1      ,PreferredStereo        ,Nat8     ,COMMON_ATTRIB)
SCALAR_ITEM(BoolPreferredNicam        ,Bool   ,NO     ,1      ,PreferredNicam         ,Nat8     ,COMMON_ATTRIB)
SCALAR_ITEM(BoolSAP                   ,Bool   ,NO     ,1      ,SAP                    ,Nat8     ,COMMON_ATTRIB)
SCALAR_ITEM(BoolSystemHidden          ,Bool   ,NO     ,1      ,SystemHidden           ,Nat8     ,DIGITAL_ATTRIB)
SCALAR_ITEM(BoolNumericSelect         ,Bool   ,NO     ,1      ,NumericSelect          ,Nat8     ,DIGITAL_ATTRIB)
SCALAR_ITEM(BoolNewPreset             ,Bool   ,NO     ,1      ,NewPreset              ,Nat8     ,DIGITAL_ATTRIB)
SCALAR_ITEM(BoolFreeCiMode            ,Bool   ,NO     ,1      ,FreeCiMode             ,Nat32    ,DIGITAL_ATTRIB)
SCALAR_ITEM(BoolTuned                   ,Bool  ,NO     ,1      ,Tuned                 ,Nat8   ,ANALOG_ATTRIB)
SCALAR_ITEM(BoolDeTuned                 ,Bool  ,NO     ,1      ,DeTuned               ,Nat8   ,ANALOG_ATTRIB)
SCALAR_ITEM(BoolAttenuator              ,Bool  ,NO     ,1      ,Attenuator            ,Nat8   ,ANALOG_ATTRIB)
SCALAR_ITEM(BoolAgcInstalled            ,Bool  ,NO     ,1      ,AgcInstalled          ,Nat8   ,ANALOG_ATTRIB)
SCALAR_ITEM(BoolUpdateName              ,Bool  ,NO     ,1      ,UserModifiedName            ,Nat8   ,COMMON_ATTRIB)
SCALAR_ITEM(IntDeltaVolume             ,int    ,NO     ,1      ,DeltaVolume            ,Nat8    ,COMMON_ATTRIB)
SCALAR_ITEM(IntFrequency               ,int    ,NO     ,1      ,Frequency              ,Nat32   ,COMMON_ATTRIB)
SCALAR_ITEM(IntPresetNumber            ,int    ,NO     ,1      ,PresetNumber           ,Int16    ,COMMON_ATTRIB)
SCALAR_ITEM(IntTvSystem                ,int    ,NO     ,1      ,ModulationType         ,Nat8    ,ANALOG_ATTRIB)
SCALAR_ITEM(IntModulation              ,int    ,NO     ,1      ,ModulationType         ,Nat8    ,COMMON_ATTRIB)
SCALAR_ITEM(IntSignalStrength          ,int    ,NO     ,1      ,SignalStrength         ,Nat32   ,COMMON_ATTRIB)
SCALAR_ITEM(IntSignalQuality           ,int    ,NO     ,1      ,SignalQuality          ,Nat32   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntColoursystem            ,int    ,NO     ,1      ,ColourSystem           ,int     ,ANALOG_ATTRIB)
SCALAR_ITEM(IntDecoderType             ,int    ,NO     ,1      ,DecoderType            ,Nat8   ,COMMON_ATTRIB)
SCALAR_ITEM(IntFineTuneOffset          ,int    ,NO     ,1      ,FineTuneOffset         ,Nat32   ,ANALOG_ATTRIB)
SCALAR_ITEM(IntFineTuneFrequency       ,int    ,NO     ,1      ,FineTuneFrequency      ,Nat32   ,ANALOG_ATTRIB)
SCALAR_ITEM(IntNetworkId               ,int    ,NO     ,1      ,NetworkId              ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntOriginalNwId            ,int    ,NO     ,1      ,OriginalNetworkId      ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntTsid                    ,int    ,NO     ,1      ,Tsid                   ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntServiceId               ,int    ,NO     ,1      ,ServiceId              ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntServiceType             ,int    ,NO     ,1      ,ServiceType            ,Nat8    ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntPmtPid                  ,int    ,NO     ,1      ,PmtPid                 ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntPcrPid                  ,int    ,NO     ,1      ,PcrPid                 ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntVideoPid                ,int    ,NO     ,1      ,VideoPid               ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntVideoStreamType         ,int    ,NO     ,1      ,VideoStreamType        ,Nat8    ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntAudioPid                ,int    ,NO     ,1      ,AudioPid               ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntAudioStreamType         ,int    ,NO     ,1      ,AudioStreamType        ,Nat8    ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntSecAudioPid             ,int    ,NO     ,1      ,SecAudioPid            ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntSecAudioStreamType      ,int    ,NO     ,1      ,SecAudioStreamType     ,Nat8   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntCniNi                    ,int   ,NO     ,1      ,CniNi                  ,Nat16  ,ANALOG_ATTRIB) 
SCALAR_ITEM(IntModulationType           ,int   ,NO     ,1      ,ModulationType        ,Nat8   ,COMMON_ATTRIB)
SCALAR_ITEM(IntLCN                      ,int   ,NO     ,1      ,LCN                   ,Nat16  ,DIGITAL_ATTRIB)  
SCALAR_ITEM(IntStreamPriority           ,int   ,NO     ,1      ,StreamPriority        ,Nat8   ,DIGITAL_ATTRIB)     
SCALAR_ITEM(IntPtc						,int   ,NO     ,0      ,Ptc					  ,Nat32   ,DIGITAL_ATTRIB)     
SCALAR_ITEM(Nat32SymbolRate            ,Nat32  ,NO     ,1      ,SymbolRate             ,Nat32   ,DIGITAL_ATTRIB)
SCALAR_ITEM(Nat32DvbType               ,Nat32  ,NO     ,1      ,DvbType                ,Nat8    ,DIGITAL_ATTRIB)
VECTOR_ITEM(StringChannelName          ,Nat16  ,PTR    ,1      ,ChannelName            ,Nat16   ,COMMON_ATTRIB)
SCALAR_ITEM(BoolMatchBrandFlag         ,Bool   ,NO     ,1      ,MatchBrandFlag         ,Nat32   ,DIGITAL_ATTRIB)
SCALAR_ITEM(Nat32NumBrandIds           ,Nat32  ,NO     ,1      ,NumBrandIds            ,Nat32   ,DIGITAL_ATTRIB)
VECTOR_ITEM(StringBrandIds			   ,Nat16  ,PTR    ,1      ,BrandIds               ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntChannelBandwidth        ,Nat8   ,NO     ,1      ,Bandwidth       ,Nat8    ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntSystemHidden            ,Nat8   ,NO     ,1      ,SystemHidden           ,Nat8    ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntNumericSelect           ,Nat8   ,NO     ,1      ,NumericSelect          ,Nat8    ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntNewChannel              ,Nat8   ,NO     ,1      ,NewChannel             ,Nat8    ,DIGITAL_ATTRIB)
SCALAR_ITEM(IntSrcambledStatus         ,Nat8   ,NO     ,1      ,SrcambledStatus        ,Nat8    ,DIGITAL_ATTRIB)
SCALAR_ITEM(FavoriteNumber			   ,Nat16  ,NO     ,1     ,FavoriteNumber		   ,Nat16   ,COMMON_ATTRIB)
SCALAR_ITEM(IntHbbTvOption			   ,Nat8   ,NO     ,1      ,HbbTvOption			   ,Nat8    ,DIGITAL_ATTRIB)
SCALAR_ITEM(BoolChannelLock			   ,Nat8   ,NO     ,1      ,ChannelLock			   ,Nat8    ,DIGITAL_ATTRIB)
VECTOR_ITEM(StringTxtPages			   ,Nat16  ,PTR    ,1      ,TxtPages			   ,Nat16   ,COMMON_ATTRIB)
SCALAR_ITEM(IntLogoURL			   	   ,int    ,NO     ,1      ,LogoURL				   ,Nat32   ,COMMON_ATTRIB)
SCALAR_ITEM(Nat16PrimaryRegion		   ,Nat16  ,NO     ,1      ,PrimaryRegion          ,Nat16   ,DIGITAL_ATTRIB)
SCALAR_ITEM(Nat16SecondaryRegion	   ,Nat16  ,NO     ,1      ,SecondaryRegion        ,Nat16   ,DIGITAL_ATTRIB) 
SCALAR_ITEM(IntTertiaryRegion		   ,int    ,NO     ,1      ,TertiaryRegion         ,int     ,DIGITAL_ATTRIB)
SCALAR_ITEM(Nat32CountryCode		   ,Nat32  ,NO     ,1      ,CountryCode            ,Nat32   ,DIGITAL_ATTRIB)
SCALAR_ITEM(BoolUserModifiedLogo       ,Nat8   ,NO     ,1	   ,UserModifiedLogo	   ,Nat8  	,COMMON_ATTRIB)
VECTOR_ITEM(MultipleLCN				   ,Nat16  ,PTR    ,1      ,MultipleLCN            ,Nat16   ,DIGITAL_ATTRIB)
VECTOR_ITEM(MultiplePreset			   ,Int16  ,PTR    ,1      ,MultiplePreset         ,Nat16   ,DIGITAL_ATTRIB)
