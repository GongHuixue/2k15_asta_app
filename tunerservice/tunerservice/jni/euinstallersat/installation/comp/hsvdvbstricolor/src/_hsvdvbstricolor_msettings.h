#ifndef HSVDVBSTRICOLOR_MSETTINGS
#define HSVDVBSTRICOLOR_MSETTINGS

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsTricolor_msettings.h"
#include "CHsvDvbsTricolor_msettings_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsTricolor_msettings_Priv::params__init(void)
{
}
CHsvDvbsTricolor_msettings_Priv::~CHsvDvbsTricolor_msettings_Priv()
{
}

//public class connections
CHsvDvbsTricolor_msettings::CHsvDvbsTricolor_msettings()
{
	m_priv = new CHsvDvbsTricolor_msettings_Priv();
	idvbset	= m_priv->idvbset;
	idvbsetpow	= m_priv->idvbsetpow;
	m_priv->err	=err;

}
CHsvDvbsTricolor_msettings::~CHsvDvbsTricolor_msettings()
{
 delete m_priv;
}
#endif
