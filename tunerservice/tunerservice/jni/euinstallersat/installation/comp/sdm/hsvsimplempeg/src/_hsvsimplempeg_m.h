#ifndef HSVSIMPLEMPEG_M
#define HSVSIMPLEMPEG_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvSimpleMpegDataManager.h"
#include "CHsvSimpleMpegDataManager_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvSimpleMpegDataManager_Priv::params__init(void)
{
			simplepmtinfomain_MaxElements    = 100;
            simplepmtinfomain_ElementSize    = sizeof(HsvSimplePMTPidInfo);
            simplepmtinfomain_SortCriteria   = simplepmtinfomain_Primary;

			simplepmtinfoaux_MaxElements    = 100;
            simplepmtinfoaux_ElementSize    = sizeof(HsvSimplePMTPidInfo);
            simplepmtinfoaux_SortCriteria   = simplepmtinfoaux_Primary;

	simplepmtFreesatTunnelledInfo_MaxElements    = 100;
	simplepmtFreesatTunnelledInfo_ElementSize    = sizeof(HsvFreesatTunnelledDataInfo);
	simplepmtFreesatTunnelledInfo_SortCriteria   = simplepmtFreesatTunnelledInfo_Primary;
}
CHsvSimpleMpegDataManager_Priv::~CHsvSimpleMpegDataManager_Priv()
{
}
//public class connections
CHsvSimpleMpegDataManager::CHsvSimpleMpegDataManager()
{
 m_priv = new CHsvSimpleMpegDataManager_Priv();
enable	= m_priv->enable;
pow	= m_priv->pow;
simplepatstrapi	= m_priv->simplepatstrapi;
simplepmtinfoaux	= m_priv->simplepmtinfoaux;
simplepmtinfomain	= m_priv->simplepmtinfomain;
simplepmtstrapi	= m_priv->simplepmtstrapi;
m_priv->ctrlN	=ctrlN;
m_priv->pen	=pen;
m_priv->pmp	=pmp;
m_priv->sdmdiv	=sdmdiv;
m_priv->sec	=sec;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
m_priv->ins	=ins;
}
CHsvSimpleMpegDataManager::~CHsvSimpleMpegDataManager()
{
 delete m_priv;
}
#endif
