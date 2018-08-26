#ifndef HSVPGDAT_MPGDB
#define HSVPGDAT_MPGDB

#define GENERATE__LEGACY__DEFINES

#include "../CHsvSatProgramData_mpgdb.h"
#include "CHsvSatProgramData_mpgdb_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvSatProgramData_mpgdb_Priv::params__init(void)
{

			presettableconf_MaxElements    = 5000;     
			presettableconf_ElementSize    = sizeof(HsvPgdatPresetData);   
            presettableconf_SortCriteria   = presettableconf_Primary;

			digsrvctableconf_MaxElements    = 5000;     
			digsrvctableconf_ElementSize    = sizeof(HsvPgdatDigServiceData);   
            digsrvctableconf_SortCriteria   = digsrvctableconf_Primary | digsrvctableconf_Secondary ;

			satinfotableconf_MaxElements    = 4;     
			satinfotableconf_ElementSize    = sizeof(HsvPgdatDigSatInfoData);   
            satinfotableconf_SortCriteria   = satinfotableconf_Primary;

			digtstableconf_MaxElements    = 500;     
			digtstableconf_ElementSize    = sizeof(HsvPgdatDigTSData);   
            digtstableconf_SortCriteria   = digtstableconf_Primary | digtstableconf_Secondary | digtstableconf_Teritiary;

			homingsvctableconf_MaxElements    = 20;     
			homingsvctableconf_ElementSize    = sizeof(HsvPgdatHomServiceData);   
            homingsvctableconf_SortCriteria   = homingsvctableconf_Primary | homingsvctableconf_Secondary | homingsvctableconf_Teritiary;

			interactivesvctableconf_MaxElements    = 20;     
			interactivesvctableconf_ElementSize    = sizeof(HsvPgdatIntrServiceData);   
            interactivesvctableconf_SortCriteria   = interactivesvctableconf_Primary | interactivesvctableconf_Secondary;

			temppresettableconf_MaxElements    = 5000;     
			temppresettableconf_ElementSize    = sizeof(HsvPgdatPresetData);   
            temppresettableconf_SortCriteria   = temppresettableconf_Primary;

			tempdigsrvctableconf_MaxElements    = 5000;     
			tempdigsrvctableconf_ElementSize    = sizeof(HsvPgdatDigServiceData);   
            tempdigsrvctableconf_SortCriteria   = tempdigsrvctableconf_Primary | tempdigsrvctableconf_Secondary ;

			tempsatinfotableconf_MaxElements    = 4;     
			tempsatinfotableconf_ElementSize    = sizeof(HsvPgdatDigSatInfoData);   
            tempsatinfotableconf_SortCriteria   = tempsatinfotableconf_Primary;

			tempdigtstableconf_MaxElements    = 500;     
			tempdigtstableconf_ElementSize    = sizeof(HsvPgdatDigTSData);   
            tempdigtstableconf_SortCriteria   = tempdigtstableconf_Primary | tempdigtstableconf_Secondary | tempdigtstableconf_Teritiary;



}
CHsvSatProgramData_mpgdb_Priv::~CHsvSatProgramData_mpgdb_Priv()
{
}
//public class connections
CHsvSatProgramData_mpgdb::CHsvSatProgramData_mpgdb()
{
 m_priv = new CHsvSatProgramData_mpgdb_Priv();
chmapop	= m_priv->chmapop;
ffsres	= m_priv->ffsres;
ipgdb	= m_priv->ipgdb;
ipgdbconst	= m_priv->ipgdbconst;
ipgdbpow	= m_priv->ipgdbpow;
m_priv->err	=err;
m_priv->pgdatN	=pgdatN;
m_priv->rtk	=rtk;
m_priv->sync	=sync;
m_priv->insN = insN;
presettableconf = m_priv->presettableconf;
digsrvctableconf = m_priv->digsrvctableconf;
satinfotableconf = m_priv->satinfotableconf;
digtstableconf = m_priv->digtstableconf;
homingsvctableconf = m_priv->homingsvctableconf;
interactivesvctableconf = m_priv->interactivesvctableconf;
m_priv->srtdb2	=srtdb2;
m_priv->srtdbids	=srtdbids;
}
CHsvSatProgramData_mpgdb::~CHsvSatProgramData_mpgdb()
{
 delete m_priv;
}
#endif
