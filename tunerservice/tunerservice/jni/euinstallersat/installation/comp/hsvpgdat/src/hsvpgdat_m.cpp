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
 *    %name: hsvpgdat_m.c % 
 *    %version: cltv1_fus_1 %
 *    %date_modified: Mon Apr 06 16:38:23 2009 %
 *    %derived_by: vijayan %
 */

#include "_hsvpgdat_m.h"

TRACESYMBOL(m, "zap/pgdat/hsvpgdat_m")

void CHsvSatProgramData_m_Priv::pow_Init(void)
{
    ipgdatpow_Init();
    ipgdbpow_Init();    
}

void CHsvSatProgramData_m_Priv::pow_TurnOn(void)
{
    //empty function
}

void CHsvSatProgramData_m_Priv::pow_TurnOff(void)
{
    //empty function
}

