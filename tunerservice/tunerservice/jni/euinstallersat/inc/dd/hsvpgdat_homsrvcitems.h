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
HOMSRVC_ITEM(OriginalNetworkId,     Nat16,    NO,      NONE,  0     )
HOMSRVC_ITEM(Tsid,     				Nat16,    NO,      NONE,  0     )
HOMSRVC_ITEM(ServiceId,     		Nat16,    NO,      NONE,  0     )
HOMSRVC_ITEM(LnbNumber,				Nat8,     NO,      NONE,  1     )
HOMSRVC_ITEM(Frequency,             Nat32,    NO,      NONE,  0     )
HOMSRVC_ITEM(Polarization, 			Nat8,     NO,      NONE,  1     )
HOMSRVC_ITEM(HomingServiceType,		Nat8,     NO,      NONE,  0     )

