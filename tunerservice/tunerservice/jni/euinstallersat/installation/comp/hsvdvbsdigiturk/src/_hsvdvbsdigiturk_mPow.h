#ifndef HSVDVBSDIGITURK_MPOW
#define HSVDVBSDIGITURK_MPOW

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsDigiTurk_mPow.h"
#include "CHsvDvbsDigiTurk_mPow_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsDigiTurk_mPow_Priv::params__init(void)
{
}
CHsvDvbsDigiTurk_mPow_Priv::~CHsvDvbsDigiTurk_mPow_Priv()
{
}
//public class connections
CHsvDvbsDigiTurk_mPow::CHsvDvbsDigiTurk_mPow()
{
 m_priv = new CHsvDvbsDigiTurk_mPow_Priv();
pow	= m_priv->pow;
m_priv->iacqpow	=iacqpow;
m_priv->iscanpow	=iscanpow;
m_priv->isortpow	=isortpow;
}
CHsvDvbsDigiTurk_mPow::~CHsvDvbsDigiTurk_mPow()
{
 delete m_priv;
}
#endif
