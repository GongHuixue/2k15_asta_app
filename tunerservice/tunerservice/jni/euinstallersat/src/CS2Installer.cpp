#include <CS2Installer.h>
#include <CS2InstallerMw.h>
#include <CTvMwCore.h>
#include <CS2InstallerStub.h>

#ifdef AOSP_BUILD_SAT
#include <utils/Log.h>
#else
#include <android/Log.h>
#endif



CS2Installer::CS2Installer(int token)
{

	__android_log_print(ANDROID_LOG_DEBUG, "CS2Installer","CS2Installer Constru Entering ");	
	tvMwCore = new CTvMwCore(token, 1);
;
	euinstallersat = new CS2InstallerMw();
	stub = new CS2InstallerStub();
	
;
	euinstallersat->pen = tvMwCore->sundry;
	euinstallersat->ctrlpen = tvMwCore->priority;
	euinstallersat->srtdb2 = tvMwCore->db;
	euinstallersat->insN = insN;
	euinstallersat->rtk = tvMwCore->rtk;
	euinstallersat->cids = stub->cids;
	euinstallersat->sysset = stub->sysset;
	euinstallersat->div = stub->div;
	euinstallersat->wnddest =stub->wnddest;
	euinstallersat->srtdb2 = stub->srtdb2;
	euinstallersat->srtdbids = stub->srtdbids;
	euinstallersat->dvbsrtdbids = stub->dvbsrtdbids;
	euinstallersat->err = stub->err;
	euinstallersat->pgsel = stub->pgsel;
	euinstallersat->sync = stub->sync;
	euinstallersat->eurdiv = stub->eurdiv;
	euinstallersat->Timerclk = stub->Timerclk;
	euinstallersat->apperr = stub->apperr;
	euinstallersat->vctl = stub->vctl;
	euinstallersat->mctl = stub->mctl;
	euinstallersat->apsysset = stub->apsysset;
	euinstallersat->plfres = stub->plfres;
	euinstallersat->vssm = ssm;
	euinstallersat->qssm = ssm;
	euinstallersat->pgdatrtk = stub->pgdatrtk;
	euinstallersat->s2div	=	stub->s2div;
	euinstallersat->lngids	=	stub->lngids; 
	euinstallersat->wnddest	=	stub->wnddest;
	euinstallersat->actl3	=	stub->actl3;
	euinstallersat->observer	=	stub->observer;
	euinstallersat->recdev	=	stub->recdev;
	euinstallersat->usbms	=	stub->usbms;
	euinstallersat->tprtk	=	stub->tprtk;
	euinstallersat->utildiv	=	stub->utildiv;
	euinstallersat->pgdaterr	=	stub->pgdaterr;
	stub->tvcoresettings	= tvMwCore->syset;
	stub->dvbset	=	euinstallersat->dvbset;
	stub->globalsettings	= 	globalsettings;
    
	stub->plfApiTsDmx	= tvMwCore->plfdmx;
	
	euinstallersat->dmxena = tvMwCore->ena;
	euinstallersat->secf = tvMwCore->secfltr;

	
	euinstallersat->opins = opins;
	opinsN	= euinstallersat->opinsN;

    euinstallersat->cipStatus = cipStatus; 
	cipStatusN  = euinstallersat->cipStatusN;

	/* Below should become requires */
	euinstallersat->plfdvbs	=	plfdvbs;
	euinstallersat->plftune	=	plftune;

;
	ins = euinstallersat->ins;
	pow = euinstallersat->pow;
	plfapidvbsN = euinstallersat->plfapidvbsN;
	dvbset = euinstallersat->dvbset;


;
	/*demux connections*/
	tvMwCore->dmxsecfN = euinstallersat->pdmxsecfN;
	tvMwCore->hsvdmxN = euinstallersat->phsvdmxN;
	



		
	
	
;
	tvMwCore->Init();
	euinstallersat->pow->Init();
	
	tvMwCore->syset->InitDbJni();
	
	/*****sys_set notification****/
	__android_log_print(ANDROID_LOG_DEBUG, "CTvInstallTC","sysset notfication registered");
	tvMwCore->syssetN = euinstallersat->sysnotifyN;

;
		
			
}

void CS2Installer::setDemuxHandleInterface(long demuxHandle)
{
;
	tvMwCore->SetDemuxInterface(demuxHandle);	
}

CS2Installer::~CS2Installer()
{
	delete euinstallersat;
	
	delete stub;
	delete tvMwCore;
}
