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
 *          %name: hsvdvbsdm_mstrapi.c %
 *       %version: TVG_tv550r4dev2 %
 * %date_modified: Thu Mar  9 18:59:47 2006 %
 *    %derived_by: vijayan %
 */


#include "_hsvdvbsdm_mstrapi.h"
//TRACESYMBOL(m, "dvb/sitables/hsvdvbsdm_mstrapi")

/*************************IHsvStream Implementation *******************************/



int CHsvDvbStreamingDataManager_mstrapi_Priv::istrapi_GetSize   (HsvDestination inst, int prop)
{
    int retval = 0;

    switch( prop )
    {
#define HSVDVBPROPERTYITEM(property, typ, std, intf)      \
        case Hsv##std##intf##property##Property:  \
                                                  retval = i##intf##strapi_GetSize (inst, prop); \
        break;
#include "hsvproperty.h"
#undef HSVDVBPROPERTYITEM
        default:
            ASSERT (!" Invalid Property");
            break;
    }
    return retval;
}

Bool CHsvDvbStreamingDataManager_mstrapi_Priv::istrapi_GetIndex  (HsvDestination inst, int prop, int key1, int key2, int key3, int *index)
{
    Bool retval = FALSE;

    switch( prop )
    {
#define HSVDVBPROPERTYITEM(property, typ, std, intf)      \
        case Hsv##std##intf##property##Property:  \
                                                  retval = i##intf##strapi_GetIndex (inst, prop, key1, key2, key3, index); \
        break;
#include "hsvproperty.h"
#undef HSVDVBPROPERTYITEM
        default:
            ASSERT (!" Invalid Property");
            break;
    }    
    return retval;
}

Bool CHsvDvbStreamingDataManager_mstrapi_Priv::istrapi_GetByKey  (HsvDestination inst, int prop, int key1, int key2, int key3, void *val)
{
    Bool retval = FALSE;

    switch( prop )
    {
#define HSVDVBPROPERTYITEM(property, typ, std, intf)      \
        case Hsv##std##intf##property##Property:  \
                                                  retval = i##intf##strapi_GetByKey (inst, prop, key1, key2, key3, val); \
        break;
#include "hsvproperty.h"
#undef HSVDVBPROPERTYITEM
        default:
            ASSERT (!" Invalid Property");
            break;
    }    
    return retval;
}

Bool CHsvDvbStreamingDataManager_mstrapi_Priv::istrapi_GetByIndex(HsvDestination inst, int prop, int index, void *val)
{
    Bool retval = FALSE;
    switch( prop )
    {
#define HSVDVBPROPERTYITEM(property, typ, std, intf)      \
        case Hsv##std##intf##property##Property:  \
                                                  retval = i##intf##strapi_GetByIndex (inst, prop, index, val); \
        break;
#include "hsvproperty.h"
#undef HSVDVBPROPERTYITEM
        default:
            ASSERT (!" Invalid Property");
            break;
    }
    return retval;
}

Bool CHsvDvbStreamingDataManager_mstrapi_Priv::istrapi_GetRangeByKey( HsvDestination dest, int prop, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{

	   Bool retval = FALSE;
		switch( prop )
		{
#define HSVDVBPROPERTYITEM(property, typ, std, intf)      \
			case Hsv##std##intf##property##Property:  \
													  retval = i##intf##strapi_GetRangeByKey (dest, prop, noofkeys, key1 , key2, key3, from, to); \
			break;
#include "hsvproperty.h"
#undef HSVDVBPROPERTYITEM
			default:
				ASSERT (!" Invalid Property");
				break;
		}
		return retval;

}

/*********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvdvbsi_strapiN_OnCompleted    ( HsvDestination dest, int spid)
{
    /* fixme: To be implemented */
    /* Routing Notifications */
    if( strapiN_iPresent() )
    {
        strapiN_OnCompleted( dest, spid);
    }
}
/********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvdvbsi_strapiN_OnAdded    ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    /* fixme: To be implemented */
    /* Routing Notifications */
    if( strapiN_iPresent() )
    {
        strapiN_OnAdded( dest, spid, key1, key2, key3);
    }

}
/********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvdvbsi_strapiN_OnChanged  ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    /* fixme: To be implemented */
    /* Routing Notifications */
    if( strapiN_iPresent() )
    {
        strapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
    }

}
/********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvdvbsi_strapiN_OnRemoved  ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    /* fixme: To be implemented */
    /* Routing Notifications */
    if( strapiN_iPresent() )
    {
        strapiN_OnRemoved( dest, spid, key1, key2, key3);
    }
}
/********************************************************************/
void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvdvbcamsdm_strapiN_OnCompleted    ( HsvDestination dest, int spid)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnCompleted( dest, spid);
    }
}

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvdvbcamsdm_strapiN_OnAdded    ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnAdded( dest, spid, key1, key2, key3);
    }

}

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvdvbcamsdm_strapiN_OnChanged  ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
    }

}

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvdvbcamsdm_strapiN_OnRemoved  ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnRemoved( dest, spid, key1, key2, key3);
    }
}


/********************************************************************/
/* STRAPI notifications from hsvmpeg */
void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvmpeg_strapiN_OnCompleted ( HsvDestination dest, int spid)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnCompleted ( dest, spid);
    }
}
/********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvmpeg_strapiN_OnAdded    ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnAdded( dest, spid, key1, key2, key3);
    }
}   /* End of function hsvmpeg_strapiN_OnAdded() */
/********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvmpeg_strapiN_OnChanged  ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
    }
}
/********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvmpeg_strapiN_OnRemoved  ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnRemoved( dest, spid, key1, key2, key3);
    }
}
/********************************************************************/




