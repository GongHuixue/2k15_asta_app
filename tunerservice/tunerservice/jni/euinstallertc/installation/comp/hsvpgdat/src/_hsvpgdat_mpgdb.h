#ifndef HSVPGDAT_MPGDB
#define HSVPGDAT_MPGDB

#define GENERATE__LEGACY__DEFINES

#include "../CHsvProgramData_mpgdb.h"
#include "CHsvProgramData_mpgdb_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvProgramData_mpgdb_Priv::params__init(void)
{

			freqmaptableconf_MaxElements    = 140;
			freqmaptableconf_ElementSize    = sizeof(HsvPgdatDigFreqMapData);   
            freqmaptableconf_SortCriteria   = freqmaptableconf_Primary | freqmaptableconf_Secondary;

			tstableconf_MaxElements    = 140;     
			tstableconf_ElementSize    = sizeof(HsvPgdatDigTSData);   
            tstableconf_SortCriteria   = tstableconf_Primary | tstableconf_Secondary ;

			digsrvtableconf_MaxElements    = 1000;     
			digsrvtableconf_ElementSize    = sizeof(HsvPgdatDigServiceData);   
            digsrvtableconf_SortCriteria   = digsrvtableconf_Primary | digsrvtableconf_Secondary | digsrvtableconf_Teritiary | digsrvtableconf_Quaternary;

			analogtableconf_MaxElements    = 200;     
			analogtableconf_ElementSize    = sizeof(HsvPgdatAnalogData);   
            analogtableconf_SortCriteria   = analogtableconf_Primary;

			presettableconf_MaxElements    = 1000;     
			presettableconf_ElementSize    = sizeof(HsvPgdatPresetData);   
            presettableconf_SortCriteria   = presettableconf_Primary;

			tempfreqmaptableconf_MaxElements    = 140;
			tempfreqmaptableconf_ElementSize    = sizeof(HsvPgdatDigFreqMapData);   
            tempfreqmaptableconf_SortCriteria   = tempfreqmaptableconf_Primary | tempfreqmaptableconf_Secondary;

			temptstableconf_MaxElements    = 140;     
			temptstableconf_ElementSize    = sizeof(HsvPgdatDigTSData);   
            temptstableconf_SortCriteria   = temptstableconf_Primary | temptstableconf_Secondary ;

			tempdigsrvtableconf_MaxElements    = 1000;     
			tempdigsrvtableconf_ElementSize    = sizeof(HsvPgdatDigServiceData);   
            tempdigsrvtableconf_SortCriteria   = tempdigsrvtableconf_Primary | tempdigsrvtableconf_Secondary | tempdigsrvtableconf_Teritiary | tempdigsrvtableconf_Quaternary;

			tempanalogtableconf_MaxElements    = 200;
			tempanalogtableconf_ElementSize    = sizeof(HsvPgdatAnalogData);   
            tempanalogtableconf_SortCriteria   = tempanalogtableconf_Primary;

			temppresettableconf_MaxElements    = 1000; 
			temppresettableconf_ElementSize    = sizeof(HsvPgdatPresetData);   
            temppresettableconf_SortCriteria   = temppresettableconf_Primary;

			backupfreqmaptableconf_MaxElements    = 140;
			backupfreqmaptableconf_ElementSize    = sizeof(HsvPgdatDigFreqMapData);   
            backupfreqmaptableconf_SortCriteria   = backupfreqmaptableconf_Primary | backupfreqmaptableconf_Secondary;

			backuptstableconf_MaxElements    = 140;     
			backuptstableconf_ElementSize    = sizeof(HsvPgdatDigTSData);   
            backuptstableconf_SortCriteria   = backuptstableconf_Primary | backuptstableconf_Secondary ;

			backupdigsrvtableconf_MaxElements    = 1000;     
			backupdigsrvtableconf_ElementSize    = sizeof(HsvPgdatDigServiceData);   
            backupdigsrvtableconf_SortCriteria   = backupdigsrvtableconf_Primary | backupdigsrvtableconf_Secondary | backupdigsrvtableconf_Teritiary | backupdigsrvtableconf_Quaternary;

			backupanalogtableconf_MaxElements    = 200;
			backupanalogtableconf_ElementSize    = sizeof(HsvPgdatAnalogData);   
            backupanalogtableconf_SortCriteria   = backupanalogtableconf_Primary;

			backuppresettableconf_MaxElements    = 1000; 
			backuppresettableconf_ElementSize    = sizeof(HsvPgdatPresetData);   
            backuppresettableconf_SortCriteria   = backuppresettableconf_Primary;


}
CHsvProgramData_mpgdb_Priv::~CHsvProgramData_mpgdb_Priv()
{
}
//public class connections
CHsvProgramData_mpgdb::CHsvProgramData_mpgdb()
{
 m_priv = new CHsvProgramData_mpgdb_Priv();
chmapop	= m_priv->chmapop;
ffsres	= m_priv->ffsres;
ipgdb	= m_priv->ipgdb;
ipgdbconst	= m_priv->ipgdbconst;
ipgdbpow	= m_priv->ipgdbpow;
m_priv->div	=div;
m_priv->err	=err;
m_priv->ffsdir	=ffsdir;
m_priv->pgctl	=pgctl;
m_priv->pgctl3	=pgctl3;
m_priv->pgdatN	=pgdatN;
m_priv->rtk	=rtk;
m_priv->sync	=sync;
m_priv->corertk = corertk;
m_priv->insN = insN;
m_priv->srtdb2 = srtdb2;
m_priv->srtdbids = srtdbids;
m_priv->sysset = sysset;
freqmaptableconf = m_priv->freqmaptableconf;
tstableconf = m_priv->tstableconf;
digsrvtableconf = m_priv->digsrvtableconf;
analogtableconf = m_priv->analogtableconf;
presettableconf = m_priv->presettableconf;
tempfreqmaptableconf = m_priv->tempfreqmaptableconf;
temptstableconf = m_priv->temptstableconf;
tempdigsrvtableconf = m_priv->tempdigsrvtableconf;
tempanalogtableconf = m_priv->tempanalogtableconf;
temppresettableconf = m_priv->temppresettableconf;
backupfreqmaptableconf = m_priv->backupfreqmaptableconf;
backuptstableconf = m_priv->backuptstableconf;
backupdigsrvtableconf = m_priv->backupdigsrvtableconf;
backupanalogtableconf = m_priv->backupanalogtableconf;
backuppresettableconf = m_priv->backuppresettableconf;

}
CHsvProgramData_mpgdb::~CHsvProgramData_mpgdb()
{
 delete m_priv;
}
#endif
