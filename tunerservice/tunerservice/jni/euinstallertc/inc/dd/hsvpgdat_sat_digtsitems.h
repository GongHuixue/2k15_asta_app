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
 *          %name: hsvpgdat_digtsitems.h %
 *       %version: TVG_1 %
 * %date_modified: Mon Apr 06 16:33:51 2009 %
 *    %derived_by: nareshj % 
 */

/*
DIGTS_ITEM(prop, stor_spec, decl, defaultval )
prop:           PropertyId
stor_spec   :   Type of Storage
decl        :   Indicate whether there is a need to do specific declaration
defaultval  :   Default value of the property

*/
/*(Prop, stor_spec, bit_decl, bit_def, DefaultValue,getfn,putfn)*/
        /* Prop,                storage     bit     bit         Default
                                spec        decl,   def,        Value       */
DIGTS_ITEM(CRC,                 Nat32,      NO,      NONE,      0)

DIGTS_ITEM(Frequency,           Nat32,      NO,      NONE,      0)		/* SECONDARY Key */
DIGTS_ITEM(TPID,				Nat32,      NO,      NONE,      0)		/* Newly Added */
/*DIGTS_ITEM(QSignalStrength,		Nat32,      NO,      NONE,      0)
DIGTS_ITEM(SSignalStrength,		Nat32,      NO,      NONE,      0)
DIGTS_ITEM(SDTVersion,			Nat32,      NO,      NONE,      0)
DIGTS_ITEM(NITVersion,			Nat32,      NO,      NONE,      0)*/
DIGTS_ITEM(SymbolRate,			Nat32,      NO,      NONE,      0)
DIGTS_ITEM(SDSDFrequency,		Nat32,      NO,      NONE,      0)		/* Modified */
DIGTS_ITEM(PlpId,				Nat32,      NO,      NONE,      0)		/* Added. May be in future will be used as quatenarary key */
DIGTS_ITEM(OriginalNetworkId,   Nat16,      NO,      NONE,      0)
DIGTS_ITEM(NetworkId,           Nat16,      NO,      NONE,      0)
DIGTS_ITEM(Tsid,                Nat16,      NO,      NONE,      0)
//DIGTS_ITEM(ChannelInformation,  Nat16,      NO,      NONE,      0)
DIGTS_ITEM(LnbNumber,			Nat8,		NO,      NONE,      0)		/* PRIMARY KEY: Newly Added */
DIGTS_ITEM(Polarization,		Nat8,		NO,      NONE,      0)		/* TERTIARY KEY: Newly Added */
DIGTS_ITEM(ModulationType,      Nat8,       NO,      NONE,      0)
DIGTS_ITEM(CodeRate,            Nat8,       NO,      NONE,      0)
//DIGTS_ITEM(HierarchyMode,       Nat8,       NO,      NONE,      0)
DIGTS_ITEM(IqMode,              Nat8,       NO,      NONE,      0)
DIGTS_ITEM(Bandwidth,    Nat8,       NO,      NONE,      0)
//DIGTS_ITEM(StreamPriority,      Nat8,       NO,      NONE,      0)
DIGTS_ITEM(PtcListVersion,      Nat8,       NO,      NONE,      0)
DIGTS_ITEM(TSVersion,           Nat8,       NO,      NONE,      0)
DIGTS_ITEM(UserInstalled,       Nat8,       NO,      NONE,      0)
DIGTS_ITEM(BarkerMux,       	Nat8,       NO,      NONE,      0)
//DIGTS_ITEM(GridInfo,            Nat8,       NO,      NONE,      0)


/* GuardInterval, TxMode, DecoderType removed.
	QSignalStrengh, VSignalStrength, ASignalStrength : Removed by SignalStrength */
