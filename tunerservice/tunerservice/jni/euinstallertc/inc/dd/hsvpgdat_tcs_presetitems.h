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
 *          %name: hsvpgdat_presetitems.h %
 *       %version: cltv1_4.1.1 %
 * %date_modified: Mon Apr 06 16:33:51 2009 %
 *    %derived_by: nituk % 
 */

/*
PRESET_ITEM(prop, stor_spec, decl, decl_func, defaultval, GetFunc, PutFunc)
prop:           PropertyId
stor_spec   :   Type of Storage
decl        :   Indicate whether there is a need to do specific declaration
decl_func   :   Type of declare function
defaultval  :   Default value of the property
GetFunc     :   Get function to be used to read from the file
PutFunc     :   Put function to be used to write to file
*/

/* Prop,             stor_spec, bit_decl, bit_def, DefaultValue,getfn,putfn)*/
PRESET_ITEM(CRC,                     Nat32,   NO,      NONE,  0)

/* Link to PTC table along with stream priority */
PRESET_ITEM(Frequency,               Nat32,   NO,      NONE,  0)
/* PresetNumber is the primary key */          
PRESET_ITEM(PresetNumber,            Nat16,   NO,      NONE,  0)

/* Below is the link to analog table points to PresetNumber of Analog Table */
PRESET_ITEM(AnalogTablePreset,       Nat16,   NO,      NONE,  0)
/* This is another key along with PresetNumber */
PRESET_ITEM(Type,                    Nat16,   NO,      NONE,  0)

/* Below are link to digital service tables */
PRESET_ITEM(OriginalNetworkId,       Nat16,   NO,      NONE,  0)
PRESET_ITEM(Tsid,                    Nat16,   NO,      NONE,  0)
PRESET_ITEM(ServiceId,               Nat16,   NO,      NONE,  0)
PRESET_ITEM(StreamPriority,          Nat16,   NO,      NONE,  0)
PRESET_ITEM(UniqueNodeId,					Nat64, NO, NONE, -1)
PRESET_ITEM(LnbNumber,				 Nat16,   NO,      NONE,  0)			/* Newly Added */
PRESET_ITEM(Polarization,            Nat16,   NO,      NONE,  0)			/* Newly Added */
PRESET_ITEM(Tpid,					 Nat32,	  NO,	   NONE,  0)
PRESET_ITEM(FavoriteNumber, 		Nat16, 	NO,        NONE, 0)
PRESET_ITEM(EmmChannel,				Nat16,	NO,			NONE,	0)




