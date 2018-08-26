#ifndef HSVDVBFST_M
#define HSVDVBFST_M

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbFST.h"
#include "CHsvDvbFST_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbFST_Priv::params__init(void)
{
	fstconf_MaxElements    = 3000;     
	fstconf_ElementSize    = sizeof(HsvfstSection);   
	fstconf_SortCriteria   = fstconf_Primary | fstconf_Secondary | fstconf_Teritiary;

}
CHsvDvbFST_Priv::~CHsvDvbFST_Priv()
{
}
//public class connections
CHsvDvbFST::CHsvDvbFST()
{
 m_priv = new CHsvDvbFST_Priv();
dmxsecfN	= m_priv->dmxsecfN;
ena	= m_priv->ena;
fstconf	= m_priv->fstconf;
pow	= m_priv->pow;
strapi	= m_priv->strapi;
strmfltr	= m_priv->strmfltr;
m_priv->charsetutil	=charsetutil;
m_priv->conf	=conf;
m_priv->ctrlN	=ctrlN;
m_priv->eurdiv	=eurdiv;
m_priv->pakgins	=pakgins;
m_priv->sec	=sec;
m_priv->srtdb	=srtdb;
m_priv->srtdbids	=srtdbids;
m_priv->strapiN	=strapiN;
}
CHsvDvbFST::~CHsvDvbFST()
{
 delete m_priv;
}
#endif
