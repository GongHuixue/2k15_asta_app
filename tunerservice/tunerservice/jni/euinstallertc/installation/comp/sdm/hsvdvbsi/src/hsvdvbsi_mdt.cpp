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
 *          %name: hsvdvbsi_mdt.c %
 *       %version: TVG_tv550r4dev1 %
 * %date_modified: Fri Dec  9 20:48:27 2005 %
 *    %derived_by: vijayan %
 */



#include "_hsvdvbsi_mdt.h"
//TRACESYMBOL(m, "dvb/sitables/hsvdvbsi_mdt")


/**********************************************************************************
 *   Description:    Decodes MJD Date
 *[In]       :    Date in MJD format (16 bit)
 *[Out]      :    year (Corresponding year)
 *[Out]      :    month (Corresponding month)
 *[Out]      :    day (Corresponding day)
 *Returns    :    None
 ***********************************************************************************/


void CHsvDvbSiDataManager_mdt_Priv::idtconv_DecodeMJD( Nat16 date, int *year, int *month, int *day)
{   
    /*  
        Y' = int [ (MJD - 15 078,2) / 365,25 ]
        M' = int { [ MJD - 14 956,1 - int (Y' × 365,25) ] / 30,6001 }
        D = MJD - 14 956 - int (Y' × 365,25) - int (M' × 30,6001 )
        If M' = 14 or M' = 15, then K = 1; else K = 0
        Y = Y' + K
        M = M' - 1 - K × 12
        */
    int year1, month1, term1, term2,  k = 0;

    ASSERT(year);
    ASSERT(month);
    ASSERT(day);

    year1 = (100 * date - 1507820) / 36525 ;

    term1 = ( year1 * 36525 ) / 100;
    month1 = (10000 * date - 149561000 - 10000 * term1)/306001;

    term2 = (month1 * 306001 )/ 10000 ;
    *day = date - 14956 - term1 - term2;

    if( (month1 == 14) || (month1 == 15))
    {
        k = 1;
    }

    *year = 1900 + year1 + k;
    *month = month1 - 1 - 12*k;    
}


/**********************************************************************************
 *   Description:    Encode Date Time
 *[In]       :    Date in MJD format (16 bit)
 *[In]       :    Time in BCD format (24 bit) 
 *[Out]      :    DateTime in Infra defined format
 *Returns    :    None
 ***********************************************************************************/

void CHsvDvbSiDataManager_mdt_Priv::idtconv_EncodeDataTime( Nat16 Date, Nat32 Time, DateTime *dt)
{
#if 0
    int year, month, day;
    int hour, minute, second;
    DateTime temp_time;

    ASSERT(dt);
    idtconv_DecodeMJD(Date, &year, &month, &day);

    dt_EncodeTimeBcd( &temp_time, Time);
    dt_DecodeTime( temp_time, &hour, &minute, &second);

    dt_EncodeDateTime( (DateTime *)dt, year, month, day, hour, minute, second);
#endif
}


