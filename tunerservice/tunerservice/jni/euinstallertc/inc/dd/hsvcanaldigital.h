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
 *          %name: hsvcanaldigital.h %
 *       %version: MTK_2k14 %
 * %date_modified: Tue Feb 12 11:24:33 2015 %
 *    %derived_by: mahesh.mathada % 
 */
#ifndef __cplusplus
#include    "../hsvdvbcins/hsvdvbcins.h"
#else
#include    "hsvdvbcins.h"
#endif
#include    "string.h"

#define     VALID_SOURCE(source)        ( source == HsvMainTuner )
#define     TURNED_ON                   ( mModuleLifeCycle == TurnedOn )
#define     VALID_INSTALL_MODE(mode)    ( (mode == PRESCAN_MODE) || (mode == AUTO_MODE) || (mode == UPDATE_MODE) )
#define     BACKGROUND_MODE             (rins_InstallationModeBackground)
#define     BACKGROUND_INSTALL          (CURRENT_MODE == BACKGROUND_MODE)

