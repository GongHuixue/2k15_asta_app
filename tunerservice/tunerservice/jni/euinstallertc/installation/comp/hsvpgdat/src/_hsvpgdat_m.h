#ifndef HSVPGDAT_M
#define HSVPGDAT_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvProgramData_m.h"
#include "CHsvProgramData_m_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvProgramData_m_Priv::params__init(void)
{
}
CHsvProgramData_m_Priv::~CHsvProgramData_m_Priv()
{
}
//public class connections
CHsvProgramData_m::CHsvProgramData_m()
{
 m_priv = new CHsvProgramData_m_Priv();
pow	= m_priv->pow;
m_priv->ipgdatpow	=ipgdatpow;
m_priv->ipgdbpow	=ipgdbpow;
}
CHsvProgramData_m::~CHsvProgramData_m()
{
 delete m_priv;
}
#endif
