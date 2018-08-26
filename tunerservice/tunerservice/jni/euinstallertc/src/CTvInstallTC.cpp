#include <CTvInstallTC.h>
#include <CEuInstallerMw.h>
#include <CEuInstallerStub.h>
#include <CGfxNativeWindow.h>

#ifdef AOSP_BUILD_TC
#include <utils/Log.h>
#else
#include <android/Log.h>
#endif

#define CHECK_GFX()   {if(GfxNative == 0) { __android_log_print(ANDROID_LOG_DEBUG, "CHsvtxtPlfsvc_m_Priv"," GfxNative is NULL"); return 0;}}



CTvInstallTC::CTvInstallTC(int token)
{
//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);
	tvMwCore = new CTvMwCore(token, 1);
//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);
    euinstalltc = new CEuInstallerMw();
	GfxNative = new IGfxANWabs();
//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);
	stub = new CEuInstallerStub();
//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);
	euinstalltc->pen = tvMwCore->sundry;
	euinstalltc->ctrlpen = tvMwCore->priority;
	euinstalltc->srtdb2 = tvMwCore->db;
    euinstalltc->fetun = fetun;
	installN = this;
	euinstalltc->insN = installN;
    euinstalltc->rtk = tvMwCore->rtk;
//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);
    //stubs
    euinstalltc->dt = stub->dt;
    euinstalltc->cids = stub->cids;
    euinstalltc->cids = stub->cids;
    euinstalltc->sysset = stub->sysset;
    euinstalltc->sysset5 = stub->sysset5;
    euinstalltc->div = stub->div;
    euinstalltc->nvmids = stub->nvmids;
    euinstalltc->subid = stub->subid;
    euinstalltc->nvmpa = stub->nvmpa;
    euinstalltc->wnddestmap =stub->wnddestmap;
    euinstalltc->srtdb2 = stub->srtdb2;
    euinstalltc->srtdbids = stub->srtdbids;
    euinstalltc->dvbsrtdbids = stub->dvbsrtdbids;
    euinstalltc->sdmdiv = stub->sdmdiv;
    euinstalltc->mpegsecnN = stub->mpegsecnN;
    euinstalltc->strmfltrN = stub->strmfltrN;
    euinstalltc->mpegN = stub->mpegN;
    euinstalltc->ffsdir = stub->ffsdir;
    euinstalltc->err = stub->err;
    euinstalltc->inserr = stub->inserr;
    euinstalltc->pgsel = stub->pgsel;
    euinstalltc->eurdiv = stub->eurdiv;
    euinstalltc->plferrids = stub->plferrids;
    euinstalltc->pgdiv = stub->pgdiv;
    euinstalltc->sync = stub->sync;
    euinstalltc->pgdatN = stub->pgdatN;
    euinstalltc->pgdatNxx = stub->pgdatNxx;
    euinstalltc->pgdatNxxx = stub->pgdatNxxx;
    euinstalltc->destconfig = stub->destconfig;
    euinstalltc->Timerclk = stub->Timerclk;
    euinstalltc->hpool = stub->hpool;
    euinstalltc->apperr = stub->apperr;
    euinstalltc->vctl = stub->vctl;
    euinstalltc->actl = stub->actl;
    euinstalltc->log = stub->log;
    euinstalltc->pgitr = stub->pgitr;
    euinstalltc->pgctl3 = stub->pgctl3;
    euinstalltc->pgctl = stub->pgctl;
    euinstalltc->insdiv = stub->insdiv;
    euinstalltc->str = stub->str;
    euinstalltc->syssetx = stub->syssetx;
    euinstalltc->memo = stub->memo;
    euinstalltc->nvmapps = stub->nvmapps;
    euinstalltc->nvmcesvc = stub->nvmcesvc;
    euinstalltc->nvmtxt = stub->nvmtxt;
    euinstalltc->mctl = stub->mctl;
    euinstalltc->srcstp = srcstp;
    euinstalltc->plfsrcid = stub->plfsrcid;
    euinstalltc->plfdesigid = stub->plfdesigid;
    euinstalltc->chanlibret = stub->chanlibret;
    euinstalltc->cityids = stub->cityids;
    euinstalltc->apsysset = stub->apsysset;
    euinstalltc->powctlx = stub->powctlx;
    euinstalltc->chdecdvbt2 = chdecdvbt2;/* stub->chdecdvbt2;*/
    euinstalltc->plfres = stub->plfres;
    euinstalltc->mpldiv = stub->mpldiv;
    euinstalltc->mpldiv = stub->mpldiv;
    euinstalltc->vssm = ssm;
    euinstalltc->qssm = ssm;
    euinstalltc->assm = ssm;
    euinstalltc->chdec = chdec;
    euinstalltc->chdecT = chdecT;
    euinstalltc->chdecC = chdecC;
    euinstalltc->pgdatrtk = stub->pgdatrtk;      
//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);
    ins = euinstalltc->ins;
	acids = euinstalltc->acids;
    stub->ins = euinstalltc->ins;
	stub->tvcoresettings = tvMwCore->syset;
    pow = euinstalltc->pow;
    fetunN = euinstalltc->fetunN;
	srcstpN = euinstalltc->srcstpN; 
	//Demux
    tvMwCore->dmxsecfN = euinstalltc->dmxsecfN;
    tvMwCore->hsvdmxN = euinstalltc->hsvdmxN;   
    euinstalltc->dmxena = tvMwCore->ena;
    euinstalltc->secfltr = tvMwCore->secfltr;

    stub->plfApiTsDmx = tvMwCore->plfdmx;

//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);

	/*Analog requires*/
	euinstalltc->mem = stub->pool;
	euinstalltc->tmr = stub->tmr;
	euinstalltc->vip = stub->vip;
	euinstalltc->col = stub->col;
	euinstalltc->xcol = stub->col;
	
	
	
	
	euinstalltc->vps = stub->vps;
	euinstalltc->p830 = stub->p830;
	euinstalltc->txtpre = stub->txtpre;
	euinstalltc->chlname = stub->chlname;
	euinstalltc->cnv = stub->cnv;
	euinstalltc->pkt0 = stub->pkt0;
	euinstalltc->dsdrv = stub->dsdrv;
	euinstalltc->dsdrv3 = stub->dsdrv3;
	euinstalltc->req = stub->req;
	euinstalltc->acc = stub->acc;
	euinstalltc->dec = stub->dec;
	euinstalltc->dsenb = stub->dsenb;
	euinstalltc->gfxtxt = stub->gfxtxt;
	euinstalltc->txtpow = stub->txtpow;
	stub->rpen = tvMwCore->sundry;
//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);
	stub->SetMwCoreInstance (tvMwCore);
	/*Analog requires*/
	tvMwCore->Init();
//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);
	//tvMwCore->syset->InitDbNative();
	tvMwCore->syset->InitDbJni();
    euinstalltc->pow->Init();
    //euinstalltc->pow->TurnOn();
	euinstalltc->opins = opins;
	opinsN	= euinstalltc->opinsN;
	euinstalltc->plfvbi = tvMwCore->plfvbi;
	stub->plfvbi = tvMwCore->plfvbi;
	
	tvMwCore->plfvbintf = stub->plfvbintf;
	euinstalltc->dcu 	= stub->dcu;
//	__android_log_print(ANDROID_LOG_DEBUG,"Function = [%s], Line = [%d]", __FUNCTION__, __LINE__);
	stub->globalSettings = globalSettings;
	euinstalltc->plfproxy = tvMwCore->plfProxy;
	tvMwCore->plfProxyN = euinstalltc->plfProxyN;
	stub->plfav	= tvMwCore->plfav;


	tvMwCore->syssetN = this;
	
	
}

CTvInstallTC::~CTvInstallTC()
{
	delete GfxNative;
	delete tvMwCore;
    delete euinstalltc;
    delete stub;
}

void CTvInstallTC::SetSurface(ANativeWindow *pAnw)
{
//__android_log_print(ANDROID_LOG_DEBUG, "CTvInstallTC","SetSurface");
	stub->SetGfxhandle(GfxNative);
	GfxNative->IANWSetSurface(pAnw);
}

void CTvInstallTC::DestroySurface()
{
//	__android_log_print(ANDROID_LOG_DEBUG, "CTvInstallTC","DestroySurface");
}
void CTvInstallTC::setDemuxInterface(long demuxHandle)
{
//	__android_log_print(ANDROID_LOG_DEBUG, "CTvInstallTC","setDemuxInterface");
	tvMwCore->SetDemuxInterface(demuxHandle);
	
}
void CTvInstallTC::setVbiInterface(long vbiHandle)
{
//	__android_log_print(ANDROID_LOG_DEBUG, "CTvInstallTC","setVbiInterface");
	tvMwCore->setVbiInterface(vbiHandle);
}


void CTvInstallTC::OnEvent(int eventid, int value)
{
//	__android_log_print(ANDROID_LOG_DEBUG, "CTvInstallTC","OnEvent");
	stub->insN->OnEvent(eventid, value);
	insN->OnEvent(eventid, value);
}

void CTvInstallTC::Notify(int property,int value)
{
	 if(property == IHsvSystemSettings_InstalledCountry)
    {
        __android_log_print(ANDROID_LOG_DEBUG,"CTVInstallTC::Notify","Installed country changed to: [%d]",value);
        if (tvMwCore->syset->getValue(IHsvSystemSettings_VirginBitStatus) == TRUE)
        {
        	euinstalltc->ins->SetSystemCountry(value);
            euinstalltc->syssetExN->OnCountryChanged(value);
        }
    }
	 
	if(property == IHsvSystemSettings_MenuLanguage)
	{
	 __android_log_print(ANDROID_LOG_DEBUG,"CTVInstallTC::Notify","Menu Language changed to: [%d]",value);
	 euinstalltc->syssetExN->OnLanguageChanged(value);

	}
}
