#ifndef HSVMPEG_M
#define HSVMPEG_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvMpegDataManager.h"
#include "CHsvMpegDataManager_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvMpegDataManager_Priv::params__init(void)
{

	basicpidinfoconfmain_MaxElements    = 1;        /* One per channel */
	
	basicpidinfoconfmain_ElementSize    = sizeof(HsvPMTBasicPidInfo);
	basicpidinfoconfmain_SortCriteria   = basicpidinfoconfmain_Primary;
	
	audioinfoconfmain_MaxElements       =  10; /* 10 is because the structure used to read in descriptor data has an array of 10 elements into which information is read */

	audioinfoconfmain_ElementSize       = sizeof(HsvPMTAudioInfo);
	audioinfoconfmain_SortCriteria      = audioinfoconfmain_Primary | audioinfoconfmain_Secondary | audioinfoconfmain_Teritiary;

	subtitleconfmain_MaxElements        =  10;

	subtitleconfmain_ElementSize        = sizeof(HsvPMTSubtitlingInfo);
	subtitleconfmain_SortCriteria       = subtitleconfmain_Primary | subtitleconfmain_Secondary | subtitleconfmain_Teritiary;
	teletextconfmain_MaxElements        =  10;

	teletextconfmain_ElementSize        =  sizeof(HsvPMTTeletextInfo);
	teletextconfmain_SortCriteria       = teletextconfmain_Primary | teletextconfmain_Secondary | teletextconfmain_Teritiary;

	componenttaginfomain_MaxElements    =  10;

	componenttaginfomain_ElementSize    =  sizeof(HsvPMTComponentTagInfo);
	componenttaginfomain_SortCriteria   = componenttaginfomain_Primary | componenttaginfomain_Secondary; 
	databroadcastinfomain_MaxElements    =  10;

	databroadcastinfomain_ElementSize    =  sizeof(HsvPMTDatabroadcastInfo);
	databroadcastinfomain_SortCriteria   = databroadcastinfomain_Primary | databroadcastinfomain_Secondary; 

}
CHsvMpegDataManager_Priv::~CHsvMpegDataManager_Priv()
{
}
//public class connections
CHsvMpegDataManager::CHsvMpegDataManager()
{
 m_priv = new CHsvMpegDataManager_Priv();
audioinfoconfaux	= m_priv->audioinfoconfaux;
audioinfoconfmain	= m_priv->audioinfoconfmain;
basicpidinfoconfaux	= m_priv->basicpidinfoconfaux;
basicpidinfoconfmain	= m_priv->basicpidinfoconfmain;
componenttaginfoaux	= m_priv->componenttaginfoaux;
componenttaginfomain	= m_priv->componenttaginfomain;
databroadcastinfoaux	= m_priv->databroadcastinfoaux;
databroadcastinfomain	= m_priv->databroadcastinfomain;
enable	= m_priv->enable;
init	= m_priv->init;
langids	= m_priv->langids;
mpegsecn	= m_priv->mpegsecn;
mpegserv	= m_priv->mpegserv;
patstrapi	= m_priv->patstrapi;
pmtstrapi	= m_priv->pmtstrapi;
pow	= m_priv->pow;
subtitleconfaux	= m_priv->subtitleconfaux;
subtitleconfmain	= m_priv->subtitleconfmain;
teletextconfaux	= m_priv->teletextconfaux;
teletextconfmain	= m_priv->teletextconfmain;
m_priv->eurdiv	=eurdiv;
m_priv->mpegN	=mpegN;
m_priv->mpegsecnN	=mpegsecnN;
m_priv->pen	=pen;
m_priv->pgdat	=pgdat;
m_priv->pgsel	=pgsel;
m_priv->pmp	=pmp;
m_priv->rtk	=rtk;
m_priv->sdmdiv	=sdmdiv;
m_priv->sec	=sec;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
}
CHsvMpegDataManager::~CHsvMpegDataManager()
{
 delete m_priv;
}
#endif
