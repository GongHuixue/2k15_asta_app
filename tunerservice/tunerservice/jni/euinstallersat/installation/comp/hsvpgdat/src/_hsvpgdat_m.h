#ifndef HSVPGDAT_M
#define HSVPGDAT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvSatProgramData_m.h"
#include "CHsvSatProgramData_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvSatProgramData_m_Priv::params__init(void)
{
}
CHsvSatProgramData_m_Priv::~CHsvSatProgramData_m_Priv()
{
}
//public class connections
CHsvSatProgramData_m::CHsvSatProgramData_m()
{
 m_priv = new CHsvSatProgramData_m_Priv();
pow	= m_priv->pow;
m_priv->ipgdatpow	=ipgdatpow;
m_priv->ipgdbpow	=ipgdbpow;
}
CHsvSatProgramData_m::~CHsvSatProgramData_m()
{
 delete m_priv;
}
#endif
