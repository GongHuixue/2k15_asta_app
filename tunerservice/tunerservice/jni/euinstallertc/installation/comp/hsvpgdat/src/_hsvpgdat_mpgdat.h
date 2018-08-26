#ifndef HSVPGDAT_MPGDAT
#define HSVPGDAT_MPGDAT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvProgramData_mpgdat.h"
#include "CHsvProgramData_mpgdat_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvProgramData_mpgdat_Priv::params__init(void)
{
}
CHsvProgramData_mpgdat_Priv::~CHsvProgramData_mpgdat_Priv()
{
}
//public class connections
CHsvProgramData_mpgdat::CHsvProgramData_mpgdat()
{
 m_priv = new CHsvProgramData_mpgdat_Priv();
ipgdatpow	= m_priv->ipgdatpow;
pgdat	= m_priv->pgdat;
pgdat3	= m_priv->pgdat3;
m_priv->chmapop	=chmapop;
m_priv->div	=div;
m_priv->err	=err;
m_priv->ipgdb	=ipgdb;
m_priv->ipgdbconst	=ipgdbconst;
m_priv->nvmids	=nvmids;
m_priv->nvmpa	=nvmpa;
m_priv->pgdatN	=pgdatN;
m_priv->pgdatNxx	=pgdatNxx;
m_priv->pgdatNxxx	=pgdatNxxx;
m_priv->subid	=subid;
m_priv->sync	=sync;
}
CHsvProgramData_mpgdat::~CHsvProgramData_mpgdat()
{
 delete m_priv;
}
#endif
