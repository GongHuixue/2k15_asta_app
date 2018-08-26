#ifndef HSVPGDAT_MPGDAT
#define HSVPGDAT_MPGDAT

#define GENERATE__LEGACY__DEFINES

#include "../CHsvSatProgramData_mpgdat.h"
#include "CHsvSatProgramData_mpgdat_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvSatProgramData_mpgdat_Priv::params__init(void)
{
}
CHsvSatProgramData_mpgdat_Priv::~CHsvSatProgramData_mpgdat_Priv()
{
}
//public class connections
CHsvSatProgramData_mpgdat::CHsvSatProgramData_mpgdat()
{
 m_priv = new CHsvSatProgramData_mpgdat_Priv();
ipgdatpow	= m_priv->ipgdatpow;
pgdat	= m_priv->pgdat;
pgdat3	= m_priv->pgdat3;
m_priv->chmapop	=chmapop;
m_priv->err	=err;
m_priv->ipgdb	=ipgdb;
m_priv->ipgdbconst	=ipgdbconst;
m_priv->pgdatN	=pgdatN;
m_priv->pgdatNxx	=pgdatNxx;
m_priv->pgdatNxxx	=pgdatNxxx;
m_priv->sync	=sync;
}
CHsvSatProgramData_mpgdat::~CHsvSatProgramData_mpgdat()
{
 delete m_priv;
}
#endif
