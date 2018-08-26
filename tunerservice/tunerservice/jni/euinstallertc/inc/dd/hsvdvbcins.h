/******************************************************************************* 
*              Copyright(c) 2004 Philips Innovation Campus. 
*           All rights reserved. Reproduction in whole or in part is 
*        prohibited without the written consent of the copyright holder. 
* 
*              Project: PEARS 
*               Source: Include File   
*             Filename: hsvdvbcins.h 
*        Creation date: Tue Feb 05 12:48:31 2008 
*               Author: nareshj 
*       %date_modified: Tue Sep 30 11:02:20 2008 % 
*          %created_by: aneeshc % 
*             %version: TVG_Fusion_4 % 
* 
* Description : 
* 
*******************************************************************************/ 

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <string.h>

#define WINDOWID            (wnddest_GetWindowId(HsvMain))
#define WINDOWID            (wnddest_GetWindowId(HsvMain))
#define START_FREQUENCY     ( ( idvbset_GetAttribute( rins_InstallationModeAutomatic, rins_AttributeFreqStepSize ) == rins_DVBCStepSize8)?   \
                            ( ( ( idvbset_GetAttribute( CURRENT_MODE, rins_AttributeScanMode) == rins_FullScan ) ||                          \
                            ( idvbset_GetAttributeMode ( rins_InstallationModeAutomatic, rins_AttributeNetworkFreq ) == rins_AutomaticValue )   || \
							( eurdiv_GetDVBCMode() == eurdiv_ScanDVBCLite)	) ? (114 * 16) : (108 * 16))  : (108 * 16) )


#define END_FREQUENCY       ((863) * (16))
#define INVALID_SYMBOLRATE  (0)


#define AUTO_MODE       (rins_InstallationModeAutomatic)
#define UPDATE_MODE     (rins_InstallationModeUpdate)
#define MANUAL_MODE     (rins_InstallationModeWeakSignal)
#define BACKGROUND_MODE (rins_InstallationModeBackground)
#define PRESCAN_MODE    (rins_InstallationModePreScan)

#define CURRENT_MODE    (rins_GetInstallationMode()) 

#define AUTO_INSTALL    ((CURRENT_MODE) == (AUTO_MODE))
#define UPDATE_INSTALL  ((CURRENT_MODE) == (UPDATE_MODE))
#define MANUAL_INSTALL  ((CURRENT_MODE) == (MANUAL_MODE))
#define PRE_INSTALL     ((CURRENT_MODE) == (PRESCAN_MODE))
#define	CABLE_DEL_FILEPATH				"HsvCableDelSysDescFile"
#define	SVC_LIST_DESC_FILEPATH			"HsvServiceListDescFile"

