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
 *          %name: hsvsrttable2_util.h %
 *       %version: cltv1_TV550r4dev_4 %
 * %date_modified: Mon Apr 06 16:38:28 2009 %
 *    %derived_by: aneeshc %
 */
 
 #ifdef __cplusplus
#define HSVCOMPAREKEY_1( CL, CONF, KEYTYPE, DATATYPE, FIELD )                                    \
       Nat8 CL CONF##_Compare##KEYTYPE##Key( Nat32 key, Address data )                      \
        {                                                                               \
            DATATYPE * Section   = (DATATYPE *)data;                                    \
            Nat8            RetValue     = CONF##_BiggerKey;                            \
                                                                                        \
            if( NULL == data )                                                          \
            {                                                                           \
                ASSERT( "NULL pointer passed to extract and compare key ");             \
            }                                                                           \
            else                                                                        \
            {                                                                           \
                if ( key < (Nat32) Section->FIELD )                                           \
                {                                                                       \
                    RetValue = CONF##_SmallerKey;                                       \
                }                                                                       \
                else                                                                    \
                {                                                                       \
                    if (key == (Nat32) Section->FIELD )                                       \
                    {                                                                   \
                        RetValue = CONF##_Equal;                                        \
                    }                                                                   \
                }                                                                       \
            }                                                                           \
            return RetValue;                                                            \
        }                                                               
#define HSVCOMPAREKEY( CONF, KEYTYPE, DATATYPE, FIELD ) HSVCOMPAREKEY_1( CLASSSCOPE, CONF, KEYTYPE, DATATYPE, FIELD )
#else
#define HSVCOMPAREKEY( CONF, KEYTYPE, DATATYPE, FIELD )                                    \
        Nat8 CONF##_Compare##KEYTYPE##Key( Nat32 key, Address data )                      \
        {                                                                               \
            DATATYPE * Section   = (DATATYPE *)data;                                    \
            Nat8            RetValue     = CONF##_BiggerKey;                            \
                                                                                        \
            if( NULL == data )                                                          \
            {                                                                           \
                ASSERT( "NULL pointer passed to extract and compare key ");             \
            }                                                                           \
            else                                                                        \
            {                                                                           \
                if ( key < (Nat32) Section->FIELD )                                           \
                {                                                                       \
                    RetValue = CONF##_SmallerKey;                                       \
                }                                                                       \
                else                                                                    \
                {                                                                       \
                    if (key == (Nat32) Section->FIELD )                                       \
                    {                                                                   \
                        RetValue = CONF##_Equal;                                        \
                    }                                                                   \
                }                                                                       \
            }                                                                           \
            return RetValue;                                                            \
        }                                                               
#endif

/* For some table we need to return true, check this */

