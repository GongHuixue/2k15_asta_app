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
 *    %name: hsvdmx_errorids.h %
 *    %version: TVG_tv550r4dev %
 *    %date_modified: Thu Aug 02 19:14:33 2007 %
 *    %derived_by: lakshminb %
 */

#define DMX_COULD_NOT_SUBSCRIBE_TO_ROOT_EVENTS      (0x01)
#define DMX_COULD_NOT_OBTAIN_CAPABILITY_INSTANCE    (0x02)
#define DMX_COULD_NOT_SUBSCRIBE_TO_SCT_EVENTS       (0x03)
#define DMX_COULD_NOT_SUBSCRIBE_TO_PES_EVENTS       (0x04)

#define DMX_COULD_NOT_ALLOC_STREAM                  (0x10)
#define DMX_COULD_NOT_OBTAIN_STREAMBUFFER_INSTANCE  (0x11)

#define DMX_COULD_NOT_ALLOC_PID_FILTER              (0x20)
#define DMX_COULD_NOT_START_PID_FILTER              (0x21)
#define DMX_COULD_NOT_STOP_PID_FILTER               (0x22)
#define DMX_COULD_NOT_ALLOC_PES_NOTIFIER            (0x28)
#define DMX_COULD_NOT_ALLOC_PES_FILTER              (0x29)

#define DMX_COULD_NOT_ALLOC_SCT_FILTER              (0x30)
#define DMX_COULD_NOT_START_SCT_FILTER              (0x31)
#define DMX_COULD_NOT_STOP_SCT_FILTER               (0x32)
#define DMX_COULD_NOT_GET_MATCHMASK                 (0x33)
#define DMX_COULD_NOT_SET_MATCHMASK                 (0x34)

#define DMX_COULD_NOT_QUERY_SORTED_LIST             (0x40)
#define DMX_COULD_NOT_DELETE_SORTED_LIST_ITEM       (0x41)
#define DMX_COULD_NOT_UPDATE_SORTED_LIST            (0x42)
#define DMX_COULD_NOT_ALLOC_POOL_MEMORY             (0x43)

#define DMX_STREAMBUFFER_MEMORY_EXHAUSTED           (0x50)
#define DMX_COULD_NOT_FREE_STREAMBUFFER_MEMORY      (0x51)

#define DMX_NULL_COOKIE_FROM_PLF                    (0x60)
#define DMX_SECTIONS_OVERRUN                        (0x61)

#define DMX_NOT_ENOUGH_BITS_IN_SECTION_BUFFER       (0x71)

