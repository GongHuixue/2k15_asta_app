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
 *          %name: hsveuins_macids.c %
 *       %version: TVG_tv550r4dev1 %
 * %date_modified: Tue Apr 18 10:49:07 2006 %
 *    %derived_by: lakshminb %
 */
 
#include "_hsveuins_macids.h"

TRACESYMBOL(m, "dvb/installation/hsveuins_macids")




int CHsvEuropeInstallation_macids_Priv::s__currentCursor = iacinv_NoRow;

void CHsvEuropeInstallation_macids_Priv::iacinv_SetCursor( int row )
{
    int verPos;
    int cursorVerSize;
    TraceDebug(m,"%s %d row=%d", __FUNCTION__, __LINE__,row);

    if((row >= iacinv_MinRow) && (row <= iacinv_MaxRow))
    {
	    TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);

        verPos = VER_OFFSET +( SCANLINES_PER_CHAR * row);
        if(SCANLINES_PER_CHAR % 2)
        {
			 TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);

            if(verPos)
            {
				TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);
                verPos = verPos+1;
            }
            cursorVerSize = SCANLINES_PER_CHAR + 1;
        }
        else
        {
			TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);
            cursorVerSize = SCANLINES_PER_CHAR;
        }
//#if ((1) && (gfxtxt_iPresent_CONSTANT) && (dsdrv_iPresent_CONSTANT) && (dsdrv3_iPresent_CONSTANT))
      gfxtxt_SetCursor((dsdrv3_GetBodyPadHeaderId()),
                         ((HOR_OFFSET + PIXEL_PER_CHAR * 8) / 12),
                         ((verPos) / 10),
                         (((HOR_OFFSET + PIXEL_PER_CHAR * 8) / 12) + ((PIXEL_PER_CHAR * 18) / 12)),
                         (((verPos) / 10) + ((cursorVerSize) / 10)) 
                        );  
        gfxtxt_DrawTextPad(/*txtdspcons_WindowA*/0x0, 1);//dsdrv_BodyPad );
//#endif
	    TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);

        currentCursor = row;
    }
    else if( row == iacinv_NoRow)
    {
	    TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);
        currentCursor = row;
    }
    else
    {
		TraceDebug(m,"%s %d ", __FUNCTION__, __LINE__);
        ASSERT(0);
    }
}

int CHsvEuropeInstallation_macids_Priv::iacinv_GetCursor(void)
{
    return currentCursor;
}


void CHsvEuropeInstallation_macids_Priv::svpaci_pgcni_ClearCNIList(void)
{

}


/*Stubs*/
Bool CHsvEuropeInstallation_macids_Priv::svpaci_pgcni_Add(Nat16 cni,int presetId)
{
	return FALSE;
}
Bool CHsvEuropeInstallation_macids_Priv::svpaci_pgcni_Remove(int presetId)
{
	return FALSE;
}
Bool CHsvEuropeInstallation_macids_Priv::svpaci_pgcni_IsCniPresent(Nat16 cni)
{
	return FALSE;
}
int CHsvEuropeInstallation_macids_Priv::svpaci_pgcni_GetPreset(Nat16 cni)
{
	return 0;
}
Nat16 CHsvEuropeInstallation_macids_Priv::svpaci_pgcni_GetCni(int pr)
{
	return 0;
}
/******************************************************************************/

