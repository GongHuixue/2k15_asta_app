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
 *          %name: hsvmpeg_errorids.h %
 *       %version: TVG_tv550r4dev %
 * %date_modified: Wed Nov  3 17:25:00 2004 %
 *    %derived_by: lakshminb %
 */
                                                                    
/* Error  Condition */                                              /* Corresponding error situations, described in 
                                                                       "Error Conditions in components of HySvc.xls" */
                                                    
#define MPEG_MULTIPLE_TURN_ON                        (  1  )        /* 1                */
#define MPEG_INVALID_TURN_OFF                        (  2  )        /* 2,4,6            */
#define MPEG_INVALID_DMX_VALUE                       (  3  )        /* 3                */
#define MPEG_INVALID_QUERY                           (  4  )        /* 5,12, 13, 32     */    
#define MPEG_PMT_NOT_AVAILABLE                       (  5  )        /* 8                */
#define MPEG_DATABASE_QUERY_FAILED                   (  6  )        /* 9,23, 25, 31     */
#define MPEG_INVALID_INPUT_PARAMETER                 (  7  )        /* 7,10,11,14,16,17 */
#define MPEG_CORRUPT_SECTION                         (  8  )        /* 20               */
#define MPEG_EXCESSIVE_NO_OF_PROGRAMS                (  9  )        /* 21               */
#define MPEG_INVALID_SECONDARY_KEY_COMPARISON        ( 10  )        /* 22               */
#define MPEG_PAT_SUBSCRIPTION_FAILED                 ( 11  )        /* 24               */
#define MPEG_INVALID_PID                             ( 12  )        /* 26               */
#define MPEG_MULTIPLE_PROGRAMS_ON_PID                ( 13  )        /* 27               */
#define MPEG_PMT_SUBSCRIPTION_FAILED                 ( 14  )        /* 29               */
#define MPEG_PMT_ON_INCORRECT_PID                    ( 15  )        /*                  */    
#define MPEG_MEMORY_ALLOCATION_FAILED                ( 16  )        /* 33               */
