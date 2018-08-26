/**********************************************************************
 *
 *  Copyright(C) 2004 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *
 *
 *	C Source:		hsvdvbsins_mpredefinedlistcopy.c
 *	Instance:		
 *	Description:	
 *	%created_by:	    aneeshc %
 *	%date_created:	    Fri Apr 19 16:08:45 2013 %
 *
**********************************************************************/

#include "_hsvdvbsins_mpredefinedlistcopy.h"


TRACESYMBOL(m, "s2/installation/hsvdvbsins_mpredefinedlistcopy")

/****************************************************************************
 * Macros and types
 ****************************************************************************/






/*
typedef struct
{
	PredefCopyEvents	Event;
	int					Param1;
	int					Param2;
} PredefCopyMsg;
*/


/****************************************************************************
 * Static variables
 ****************************************************************************/
int CHsvDvbsInstallation_mpredefinedlistcopy_Priv::s__mModuleLifeCycle;

Pump CHsvDvbsInstallation_mpredefinedlistcopy_Priv::s__UsbPump = -1;

char CHsvDvbsInstallation_mpredefinedlistcopy_Priv::s__UsbUriCache[MAX_CACHE_SIZE][MAX_URI_LENGTH];

int CHsvDvbsInstallation_mpredefinedlistcopy_Priv::s__mPgdatExtTaskId = 0;


/****************************************************************************
 * Static functions
 ****************************************************************************/






 /****************************************************************************
 * External functions
 ****************************************************************************/
/*
	const int EventPredefinedListCopySuccesful = 24;
	const int EventPredefinedListCopyGenericError = 25;
	const int EventPredefinedListCopyOlderVersion = 26;

	void OnEvent(int eventid, int value);
*/

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::USBPumpHandler(int param1, Nat32 param2)
{
    UNUSED(param1);
    int count;

    if(mModuleLifeCycle == TurnedOn)
    {
        switch (param1)
        {
            case USB_INSERT_NTF:
                {
                    Nat32 devices[usbms_MaxDeviceListSize] = {0}, activedevices = 0;
                    int contType = 0;
                    FResult res0, res1, res2, res3;
                    int i=0, retval1, retval2, j = 0;
                    Bool IsInitDone = 0;
                    Nat32 contId, containerId[recdev_MaxContainerListSize] = {0}, numitems;
                    char uri[recdev_MaxMountPathSize];
                    Bool USBAlreadyMounted = FALSE;

                    if(param2 > 0) // Case when the event came up with a valid Container Id
                    {
                        contId = param2;
                        res1 = recdev_IsInitializationDone(wnddest_GetWindowId( HsvMain ), &IsInitDone);
                        ASSERT(res1 == err_Ok);
                        if(res1 != err_Ok)
                        {
                            TraceNotice (m,"ceapcsmjag_m :: recdev_IsInitializationDone FAILED, ErrorId = %d !!", res1);
                        }
                        else
                        {
                            if(IsInitDone)
                            {
                                res2 = recdev_GetType(wnddest_GetWindowId( HsvMain ), contId, &contType);
                                ASSERT(res2 == err_Ok);
                                if(contType == recdev_ContTypeMedia &&  res2 == err_Ok)
                                {
                                    res3 = recdev_GetPath(wnddest_GetWindowId( HsvMain ), contId, uri);
                                    ASSERT(res3 == err_Ok);
                                    TraceNotice(m,"ceapcsmjag_m :: Drive path = %s ", uri);
                                    count=0;
                                    TraceNotice(m,"ceapcsmjag : Ondrivemounted %s",uri);
                                    while( ( UsbUriCache[count][0] != 0 ) && ( count < MAX_CACHE_SIZE-1 ) )
                                    {
                                        if(strcmp(uri, UsbUriCache[count])==0)
                                        {
                                            USBAlreadyMounted = TRUE;
											TraceNotice (m, "USB already mounted ");
                                            break;
                                        }
                                        ++count;
                                    }
                                    if(USBAlreadyMounted==FALSE)
                                    {
                                        strcpy(UsbUriCache[count] , uri);
                                    }
                                    TraceNotice(m,"ceapcsmjag : Ondrivemounted drvname %s",UsbUriCache[count]);
                                }
                                else
                                {
                                    TraceNotice (m,"ceapcsmjag_m :: recdev_GetType FAILED, ErrorId = %d !!", res2);
                                }
                            }
							else
							{
								TraceNotice (m, "IsInitDone failed ");
							}
                        }
                    }
                    else if(param2 == 0) // Case when the init has send this event, IsInitializationDone already done
                    {
                        res0 = usbms_IsInitializationDone(wnddest_GetWindowId( HsvMain ), &IsInitDone);
                        ASSERT(res0 == err_Ok);
                        if(res0 != err_Ok)
                        {
                            TraceNotice (m,"ceapcsmjag_m :: usbms_IsInitializationDone FAILED, ErrorId = %d !!", res0);
                        }
                        else if(IsInitDone)
                        {
                            res1 = usbms_GetDeviceList(wnddest_GetWindowId( HsvMain ), usbms_PhysTypeUnknown, devices, &activedevices, &retval1);
                            ASSERT((activedevices <= usbms_MaxDeviceListSize) && (res1 ==  err_Ok) && (retval1 == usbms_ErrorOk));
                            if((activedevices > usbms_MaxDeviceListSize) || (res1 !=  err_Ok) || (retval1 != usbms_ErrorOk))
                            {
                                TraceNotice(m,"ceapcsmjag_m :: usbms_GetDeviceList FAILED, ErrorId = %d !!", res1);
                            }
                            else
                            {
                                for(i=0; i < activedevices; i++)
                                {
                                    res2 = recdev_GetContainerList(wnddest_GetWindowId( HsvMain ), recdev_ContTypeMedia, devices[i], containerId, &numitems, &retval2);
                                    ASSERT((res2 == err_Ok) && (retval2 == recdev_ErrorOk) && (numitems <= recdev_MaxContainerListSize));
                                    if((res2 != err_Ok) || (retval2 != recdev_ErrorOk) || (numitems > recdev_MaxContainerListSize))
                                    {
                                        TraceNotice(m,"ceapcsmjag_m :: recdev_GetContainerList FAILED, ErrorId = %d !!", res2);
                                    }
                                    else
                                    {
                                        for(j=0; j < numitems; j++)
                                        {
                                            res3 = recdev_GetPath(wnddest_GetWindowId( HsvMain ), containerId[j], uri);
                                            ASSERT(res3 == err_Ok);
                                            TraceNotice(m,"ceapcsmjag_m :: Container Id = %d, Drive path = %s ", (int) containerId[j], uri);
                                            count=0;
                                            TraceNotice(m,"ceapcsmjag : Ondrivemounted %s",uri);
                                            while( ( UsbUriCache[count][0] != 0 ) && ( count < MAX_CACHE_SIZE-1 ) )
                                            {
                                                if(strcmp(uri, UsbUriCache[count])==0)
                                                {
                                                    USBAlreadyMounted = TRUE;
                                                    break;
                                                }
                                                ++count;
                                            }
                                            if(USBAlreadyMounted==FALSE)
                                            {
                                                strcpy(UsbUriCache[count] , uri);
                                            }
                                            TraceNotice(m,"ceapcsmjag : Ondrivemounted drvname %s",UsbUriCache[count]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                break;

            case USB_REMOVE_NTF:
                {
                    int count=0, contType = 0;
                    FResult res1, res2;
                    char uri[recdev_MaxMountPathSize];
                    Bool IsInitDone = 0;
                    res1 = recdev_IsInitializationDone(wnddest_GetWindowId(HsvMain), &IsInitDone);
                    if(IsInitDone)
                    {
                        res2 = recdev_GetType(wnddest_GetWindowId(HsvMain), param2, &contType);
                        if(contType == recdev_ContTypeMedia)
                        {
                            res2 = recdev_GetPath(wnddest_GetWindowId(HsvMain), param2, uri);
                        }
                    }
                    TraceNotice(m,"ceapcsmjag_m :: recdevN_OnStorageRemoved:: Drive path = %s ", uri);
                    while( (strcmp( UsbUriCache[count] , uri )==0 ) && ( count < MAX_CACHE_SIZE-1 ) )
                        ++count;
                    if( count < MAX_CACHE_SIZE )
                        UsbUriCache[count][0] = 0;
                }
                break;
        }
    }
}

char * CHsvDvbsInstallation_mpredefinedlistcopy_Priv::mGetFirstUsbUri(void)
{
    Nat8 iter = 0;

    while( (0 == UsbUriCache[iter][0]) && (iter<MAX_CACHE_SIZE-1) )
        ++iter;

    return UsbUriCache[iter];
}

int CHsvDvbsInstallation_mpredefinedlistcopy_Priv::RunApp( char* program, char** arglist, Bool wait)
{
    int pid;
    int statloc;
    int retval = 0;

    pid = vfork();
    if ( pid )
    {
        /* Parent */
        if ( wait )
        {
            //waitpid( pid, &statloc, 0 );
            while ((waitpid(pid,&statloc,0) == -1) && (errno == EINTR));
            if ( WIFEXITED( statloc ) )
            {
                retval = WEXITSTATUS( statloc );                
            }           
        }
    }
    else
    {
        /* Child */        
        execvp ( program, arglist );
        perror( "Channelib execvp failure" );
        _exit( 1 );
    }
    return retval;
}   


Bool CHsvDvbsInstallation_mpredefinedlistcopy_Priv::mUntarAndCopyPredefinedBinaryFiles (char *PredefinedBinaryPath)
{
	int		retVal;
	Bool	ret;
	char	tarPath[MAX_DIRECTORY_NAME_SIZE + 16];
	char	*arglist[] = { "tar", "-C" , BIN_FILE_PATH, "-x", "-f" , tarPath,  0 };
	char	*synclist[] = { "sync", 0};

	strcpy (tarPath, PredefinedBinaryPath);
	strcat (tarPath, "PredefinedList.tar");

	TraceNotice (m, "Executing command tar -C %s -x -f %s ", BIN_FILE_PATH, tarPath);
	retVal = RunApp ("/bin/busybox", arglist, TRUE);
	TraceNotice (m, "Tar command returned %d ", retVal);

	if (retVal == 0)
	{
		RunApp ("/bin/busybox", synclist, TRUE);
	}
	ret = (retVal == 0) ? TRUE: FALSE;
	TraceNotice (m, "PredefinedListCopy returned %d ", ret);

	return ret;

}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::PredefindListCopyHandler (int param)
{
	Bool	UsbCopyResult = FALSE;
	char	*UsbUriPath = NULL;
	char	PredefinedBinaryPath[MAX_URI_LENGTH + PREDEF_LIST_PATHLEN_IN_USB];
	PredefCopyEvents	PredefCopyEvent;

	while (1)
	{
		PredefCopyEvent = (PredefCopyEvents) tprtk_EventReceive( TRIGGER_PREDEF_COPY, FALSE, tprtk_TimeoutInfinite);
		if (PredefCopyEvent == TRIGGER_PREDEF_COPY)
		{
			UsbUriPath = mGetFirstUsbUri();
			if(UsbUriPath[0] != 0)
			{
				TraceNotice (m, "GetiFirstUsbUri returned %s ", UsbUriPath);
				/* USB Path detected */
				strcpy (PredefinedBinaryPath , UsbUriPath);
				strcat(PredefinedBinaryPath,"/");
				/*strcat(PredefinedBinaryPath,PREDEF_LIST_PATH_IN_USB);
				status = mkdir(PredefinedBinaryPath, S_IRWXU);
				strcat(PredefinedBinaryPath,"/");*/

				TraceNotice (m, "Predefied binary path %s", PredefinedBinaryPath);
				UsbCopyResult = mUntarAndCopyPredefinedBinaryFiles (PredefinedBinaryPath);
				if (UsbCopyResult == TRUE)
				{
					TraceNotice (m, "Predefinedlist copy succesful ");
					iinsN_OnEvent(iinsN_EventPredefinedListCopySuccesful, UsbCopyResult);
				}
				else
				{
					/* No USB detected. Report Generic Error */
					TraceNotice (m, "Predefinedlist copy not succesful ");
					iinsN_OnEvent(iinsN_EventPredefinedListCopyGenericError, err_UsbPathNotFound);
				}

			}
			else
			{
				TraceNotice (m, "No USB path. Sending failure for predefined list copy ");
				/* No USB detected. Report Generic Error */
				iinsN_OnEvent(iinsN_EventPredefinedListCopyGenericError, err_UsbPathNotFound);
			}
		}
	}
}


void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::usbdevexN_OnInitializationDone( void )
{
	TraceNotice (m, "usbdevexN_OnInitializationDone");
	pmp_PmpSend( UsbPump, USB_INSERT_NTF, 0);
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::usbdevexN_OnDeviceConnected( Nat32 physid )
{
    UNUSED(physid);
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::usbdevexN_OnDeviceDisconnected( Nat32 physid )
{
    UNUSED(physid);
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::usbdevexN_OnDeviceError( Nat32 physid, int errortype )
{
    UNUSED(physid);
    UNUSED(errortype);
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::recdevN_OnStorageAdded( Nat32 contid )
{
	TraceNotice (m, "recdevN_OnStorageAdded contid %d ", (int) contid);
	
    if(UsbPump != -1 && contid != 0)
    {
		TraceNotice (m, "Usb insert ntf ");
        pmp_PmpSend( UsbPump, USB_INSERT_NTF, contid);
    }
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::recdevN_OnStorageRemoved( Nat32 contid )
{
	TraceNotice (m, "recdevN_OnStorageRemoved");
    if(UsbPump != -1 && contid != 0)
    {
        pmp_PmpSend( UsbPump, USB_REMOVE_NTF, contid);
    }
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::recdevN_OnStorageError( Nat32 contid, int errortype )
{
    UNUSED(contid);
    UNUSED(errortype);
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::recdevN_OnInitializationDone( void )
{
	TraceNotice (m, "recdevN_OnInitializationDone");
	pmp_PmpSend( UsbPump, USB_INSERT_NTF, 0);
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::recdevN_OnPrepareProgress(Nat32 id,int step,int maxstep,int progress)
{
    UNUSED(id);
    UNUSED(step);
    UNUSED(maxstep);
    UNUSED(progress);
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::recdevN_OnPrepareDone(Nat32 id,int status)
{
    UNUSED(id);
    UNUSED(status);
}


void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::ipredefpow_Init(void)
{
	int	i = 0;
    UsbPump = pmp_PmpCreateEx ( pen_PumpEngine, USBPumpHandler, FALSE, "ceapcsm:CEApps USB Pump" );

    for (; i<MAX_CACHE_SIZE;++i)
        UsbUriCache[i][0] = 0;

	mPgdatExtTaskId = tprtk_TaskCreate( "PredefinedListCopy",	PREDEF_COPY_TASK_PRIORITY, PREDEF_COPY_TASK_STACK_SIZE, PredefindListCopyHandler, 1);

	mModuleLifeCycle = Initialised;
}
void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::ipredefpow_TurnOn(void)
{
	Bool	retval;
	int		res;
	mModuleLifeCycle = TurnedOn;
	
	res = recdev_IsInitializationDone( wnddest_GetWindowId( HsvMain ), &retval );
	TraceNotice (m, "IsIntializationdone res %d retval %d ", res, retval);
	if(res != err_Ok)
	{
		TraceNotice (m,"ceapcsmjag_m :: recdev_IsInitializationDone FAILED, ErrorId = %d !!", res);
	}
    if(retval)
    {
		TraceNotice (m, "USB INsert ntf ");
        pmp_PmpSend( UsbPump, USB_INSERT_NTF, 0);
    }
}

void CHsvDvbsInstallation_mpredefinedlistcopy_Priv::ipredefpow_TurnOff(void)
{
	mModuleLifeCycle = TurnedOff;
}

FResult CHsvDvbsInstallation_mpredefinedlistcopy_Priv::ipredefcopy_StartPredefinedListCopy (void)
{
	FResult		RetVal = err_BadParameter;

	TraceNotice (m,"Ceapps Calling to Start Predef channel copy ");
	if (mModuleLifeCycle == TurnedOn)
	{
		RetVal = err_Ok;
		TraceNotice (m, "Event Send to copy predef ");
		tprtk_EventSend (mPgdatExtTaskId, TRIGGER_PREDEF_COPY);
	}

	return RetVal;
}
