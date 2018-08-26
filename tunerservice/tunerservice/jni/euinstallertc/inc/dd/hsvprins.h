/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: hsvprins.h %
 *       %version: TVG_tv550r4dev %
 * %date_modified: Fri Jul 06 15:42:46 2007 %
 *    %derived_by: lakshminb %
 */


/* for tuning */

/*Run-time error codes*/

#define PRINS_INVALID_TURNON                    (1)
#define PRINS_FRONTEND_NOT_INITIALISED          (2)
#define PRINS_USECASE_SELECTION_FAILED          (3)
#define PRINS_FAILED_TO_ADDREF                  (4)
#define PRINS_FAILED_TO_GET_CHANTBL_INTERFACE   (5)
#define PRINS_FAILED_TO_GET_RFAMP_INTERFACE     (6)
#define PRINS_FAILED_TO_GET_SIGSTR_INTERFACE    (7)
#define PRINS_FAILED_TO_SUBSCRIBE_TO_TUNINGNTF  (8)
#define PRINS_FAILED_TO_SUBSCRIBE_TO_SIGSTRNTF  (9)
#define WINDOWID                                (wnddest_GetWindowId(HsvMain))

#define ANTENNA_PRESET (pgdbconst_Antenna | pgdbconst_Preset)
#define ANTENNA_ANALOG (pgdbconst_Antenna | pgdbconst_Analog)
