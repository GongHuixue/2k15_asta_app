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
 *          %name: hsvpgdat_satinfoitems.h %
 *       %version: TVG_1 %
 * %date_modified: Mon Apr 06 16:33:51 2009 %
 *    %derived_by: nareshj % 
 */

/*
SATINFO_ITEM(prop, stor_spec, decl, decl_func, defaultval, GetFunc, PutFunc)
prop:           PropertyId
stor_spec   :   Type of Storage
decl        :   Indicate whether there is a need to do specific declaration
decl_func   :   Type of declare function
defaultval  :   Default value of the property
GetFunc     :   Get function to be used to read from the file
PutFunc     :   Put function to be used to write to file
*/

/* Prop,             stor_spec, bit_decl, bit_def, DefaultValue,getfn,putfn)*/
SATINFO_ITEM(CRC,                     Nat32,   NO,      NONE,  0)

SATINFO_ITEM(LnbNumber,				 Nat16,   NO,      NONE,  0)	/* LnbNumber is the primary key */
SATINFO_ITEM(LnbType,				 Nat16,   NO,      NONE,  0)
SATINFO_ITEM(SatelliteId,			 Nat16,	  NO,	   NONE,  0)
SATINFO_ITEM(OrbitalPosition,		 Nat16,   NO,      NONE, 0)
SATINFO_ITEM(SatelliteName,			 Nat16,   NAME,    A(33), 0)


