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
 *          %name: freesat.h %
 *       %version:  TVG_1 %
 * %date_modified:  %
 *    %derived_by:  anuma %
 */

/****************************************************************************
 * Macros and types
 ****************************************************************************/

#define REGIONAL 1
#define GLOBAL 2
#define GET_ORDER(PreExistingLCN,CurrentLCN) ((PreExistingLCN * 10)+ CurrentLCN)
/* The above macro gives the order
11 -> PreExisting is Regional & Current is also Regional
12 -> PreExisting is Regional & Current is Global
21 -> PreExisting is Global & Current is Regional
22 -> PreExisting is Global & Current is also Global
*/
#define PRE_REG__CURR_REG 11
#define PRE_REG__CURR_GBL 12
#define PRE_GBL__CURR_REG 21
#define PRE_GBL__CURR_GBL 22
#define INVALIDATE(x)     ((x) |= 0x8000)
#define INVALID_INDEX		(-1)
#define	INVALID_PRESET		(0x1FFF) //(0xFFFF)
#define	SAT_INFO_TABLE		(pgdb->GetCurrentTable() | IHsvProgramDatabaseConstants_SatInfo)
#define	SERVICE_TABLE		(pgdb->GetCurrentTable() | IHsvProgramDatabaseConstants_DigitalService)
#define	PRESET_TABLE		(pgdb->GetCurrentTable() | IHsvProgramDatabaseConstants_Preset)
#define STEP_SIZE (100)
#define INVALID_LCN			(0xC000)
#define PRESET_NOT_ALLOCATED(preset)                (preset == INVALID_PRESET )
#define REVALIDATE(x)     ((x) &= 0x7FFF)
#define AUTO_MODE													(IHsvSatelliteInstallation_InstallationServiceScan)
#define MAX_NUM_LCN_ENTRY			8
#define MIN_VALID_LCN        		(1)
#define MAX_VALID_LCN       		(4095)
#define VALID_LCN_RANGE(x)         (((x) <= MAX_VALID_LCN) && ( MIN_VALID_LCN <= (x)))




/** pump **/
#define pmp_PmpCreateEx( pen, func, replace, name ) m_pfac.PmpCreate(pen,&CHsvDvbsFreesat_mSort::func,replace,(char *)name,this)
#define pmp_PmpSend(p,p1,p2) m_pfac.PmpSend(p,p1,p2)
#define pmp_PmpSendAfter(p,p1,p2,a) m_pfac.PmpSendAfter(p,p1,p2,a)

