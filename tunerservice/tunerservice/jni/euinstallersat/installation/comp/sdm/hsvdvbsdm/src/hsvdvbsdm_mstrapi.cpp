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
 *       %version: FUSION_TVG_4.2.1 %
 * %date_modified: Thu Mar  9 18:59:47 2006 %
 *    %derived_by: anuma %
 */
 

#include "_hsvdvbsdm_mstrapi.h"
TRACESYMBOL(m, "hsvdvbsdm_mstrapi")

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

Bool CHsvDvbStreamingDataManager_mstrapi_Priv::istrapi_GetRangeByKey( HsvDestination dest, int spid, int noofkeys, int key1, int key2, int key3, int *from, int *to)
{
    Bool retval = FALSE;
    switch( spid )
    {
	case HSVSPID(ServiceList, dvb, fnt):
	retval = ifntstrapi_GetRangeByKey( dest,spid, noofkeys,key1,key2,key3,from,to);
	break;
	case HSVSPID(ActualServiceList, dvb, nit):
	case HSVSPID(ActualNetworkLCN2,dvb,nit):
	/*TODO: servicelist need to be populated from NIT*/
	retval = initstrapi_GetRangeByKey( dest,spid, noofkeys,key1,key2,key3,from,to);
	break;
	case HSVSPID(ActualServiceList, dvb, bat):
	retval = ibatstrapi_GetRangeByKey( dest,spid, noofkeys,key1,key2,key3,from,to);
	 break;
	 case HSVSPID(batECN, dvb, bat):
	retval = ibatstrapi_GetRangeByKey( dest,spid, noofkeys,key1,key2,key3,from,to);
	 break;
    case HSVSPID(CamNITService, dvb, camnit):
	    retval = icamnitstrapi_GetRangeByKey( dest,spid, noofkeys,key1,key2,key3,from,to);
		break;
    case HSVSPID(ActualTSService, dvb, sgt):
        retval = isgtstrapi_GetRangeByKey( dest,spid, noofkeys,key1,key2,key3,from,to);
		break;
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











/********************************************************************/
/* STRAPI notifications from hsvsimplempeg */
void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvsimplempeg_strapiN_OnCompleted ( HsvDestination dest, int spid)
{
	int insMode,insState;
	ins->GetCurrentInstallationState(&insMode, &insState);
	int  mInstalledPackageId = ins->GetAttribute(IHsvSatelliteInstallation_InstallationBackground,IHsvSatelliteInstallation_AttributePackageId);

	TraceNotice(m,"%s %d",__FUNCTION__,__LINE__);
	TraceNotice(m, "TMP_DEBUG PACKAGE ID  %d insmode 0x%x",mInstalledPackageId,insMode);
	if((mInstalledPackageId == FREESAT_PACKAGE_ID) && (insMode == IHsvSatelliteInstallation_InstallationBackground))
	{
		if(spid == HSVSPID(PidInfo,mpeg, simplepmt))
		{
			TraceNotice(m,"%s %d CALLING SDT FREESAT ENABLE",__FUNCTION__,__LINE__);
			chsvdvbsdt_Freesatena->Enable(HSV_MAP_DEST_TO_DMX(dest));
		}
	}
    if( strapiN_iPresent() )
    {
        strapiN_OnCompleted ( dest, spid);
    }
}
/********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvsimplempeg_strapiN_OnAdded    ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnAdded( dest, spid, key1, key2, key3);
    }
}   /* End of function hsvmpeg_strapiN_OnAdded() */
/********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvsimplempeg_strapiN_OnChanged  ( HsvDestination dest, int spid, int key1, int key2, int key3, int eventid)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnChanged( dest, spid, key1, key2, key3, eventid);
    }
}
/********************************************************************/

void CHsvDvbStreamingDataManager_mstrapi_Priv::hsvsimplempeg_strapiN_OnRemoved  ( HsvDestination dest, int spid, int key1, int key2, int key3)
{
    if( strapiN_iPresent() )
    {
        strapiN_OnRemoved( dest, spid, key1, key2, key3);
    }
}
/********************************************************************/


