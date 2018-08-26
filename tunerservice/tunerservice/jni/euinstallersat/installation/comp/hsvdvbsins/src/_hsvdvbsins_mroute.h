#ifndef HSVDVBSINS_MROUTE
#define HSVDVBSINS_MROUTE

#define GENERATE__LEGACY__DEFINES

#include "../CHsvDvbsInstallation_mroute.h"
#include "CHsvDvbsInstallation_mroute_Priv.h"


#undef GENERATE__LEGACY__DEFINES
void CHsvDvbsInstallation_mroute_Priv::params__init(void)
{
}
CHsvDvbsInstallation_mroute_Priv::~CHsvDvbsInstallation_mroute_Priv()
{
}
//public class connections
CHsvDvbsInstallation_mroute::CHsvDvbsInstallation_mroute()
{
 m_priv = new CHsvDvbsInstallation_mroute_Priv();
ibckInstall	= m_priv->ibckInstall;
ibckctrlN	= m_priv->ibckctrlN;
ipackagectrlN	= m_priv->ipackagectrlN;
ipackageins	= m_priv->ipackageins;
ipackageplfApidvbsN	= m_priv->ipackageplfApidvbsN;
ipackagepow	= m_priv->ipackagepow;
ipackageroute	= m_priv->ipackageroute;
ipackagesort	= m_priv->ipackagesort;
istrapiN	= m_priv->istrapiN;
ipackageopinsN	= m_priv->ipackageopinsN;
m_priv->err	=err;
m_priv->hsvdvbscanal_ctrlN	=hsvdvbscanal_ctrlN;
m_priv->hsvdvbscanal_ins	=hsvdvbscanal_ins;
m_priv->hsvdvbscanal_plfApidvbsN	=hsvdvbscanal_plfApidvbsN;
m_priv->hsvdvbscanal_pow	=hsvdvbscanal_pow;
m_priv->hsvdvbscanal_sort	=hsvdvbscanal_sort;
m_priv->hsvdvbsopprofile_ctrlN	=hsvdvbsopprofile_ctrlN;
m_priv->hsvdvbsopprofile_ins	=hsvdvbsopprofile_ins;
m_priv->hsvdvbsopprofile_plfApidvbsN	=hsvdvbsopprofile_plfApidvbsN;
m_priv->hsvdvbsopprofile_pow	=hsvdvbsopprofile_pow;
m_priv->hsvdvbsopprofile_sort	=hsvdvbsopprofile_sort;
m_priv->hsvdvbsopprofile_strapiN = hsvdvbsopprofile_strapiN;
m_priv->hsvdvbsopprofile_opinsN = hsvdvbsopprofile_opinsN;
m_priv->hsvdvbsdigiturk_ctrlN	=hsvdvbsdigiturk_ctrlN;
m_priv->hsvdvbsdigiturk_ins	=hsvdvbsdigiturk_ins;
m_priv->hsvdvbsdigiturk_plfApidvbsN	=hsvdvbsdigiturk_plfApidvbsN;
m_priv->hsvdvbsdigiturk_pow	=hsvdvbsdigiturk_pow;
m_priv->hsvdvbsdigiturk_sort	=hsvdvbsdigiturk_sort;
m_priv->hsvdvbsfransat_bckInstall	=hsvdvbsfransat_bckInstall;
m_priv->hsvdvbsfransat_bckctrlN	=hsvdvbsfransat_bckctrlN;
m_priv->hsvdvbsfransat_ctrlN	=hsvdvbsfransat_ctrlN;
m_priv->hsvdvbsfransat_ins	=hsvdvbsfransat_ins;
m_priv->hsvdvbsfransat_plfApidvbsN	=hsvdvbsfransat_plfApidvbsN;
m_priv->hsvdvbsfransat_pow	=hsvdvbsfransat_pow;
m_priv->hsvdvbsfransat_sort	=hsvdvbsfransat_sort;
m_priv->hsvdvbsfransat_strapiN	=hsvdvbsfransat_strapiN;
m_priv->hsvdvbsgeneric_bckInstall	=hsvdvbsgeneric_bckInstall;
m_priv->hsvdvbsgeneric_bckctrlN	=hsvdvbsgeneric_bckctrlN;
m_priv->hsvdvbsgeneric_ctrlN	=hsvdvbsgeneric_ctrlN;
m_priv->hsvdvbsgeneric_ins	=hsvdvbsgeneric_ins;
m_priv->hsvdvbsgeneric_plfApidvbsN	=hsvdvbsgeneric_plfApidvbsN;
m_priv->hsvdvbsgeneric_pow	=hsvdvbsgeneric_pow;
m_priv->hsvdvbsgeneric_sort	=hsvdvbsgeneric_sort;
m_priv->hsvdvbsgeneric_strapiN	=hsvdvbsgeneric_strapiN;
m_priv->hsvdvbsm7_ctrlN	=hsvdvbsm7_ctrlN;
m_priv->hsvdvbsm7_ins	=hsvdvbsm7_ins;
m_priv->hsvdvbsm7_plfApidvbsN	=hsvdvbsm7_plfApidvbsN;
m_priv->hsvdvbsm7_pow	=hsvdvbsm7_pow;
m_priv->hsvdvbsm7_sort	=hsvdvbsm7_sort;
m_priv->hsvdvbsn_ctrlN	=hsvdvbsn_ctrlN;
m_priv->hsvdvbsn_ins	=hsvdvbsn_ins;
m_priv->hsvdvbsn_plfApidvbsN	=hsvdvbsn_plfApidvbsN;
m_priv->hsvdvbsn_pow	=hsvdvbsn_pow;
m_priv->hsvdvbsn_sort	=hsvdvbsn_sort;
m_priv->hsvdvbspol_ctrlN	=hsvdvbspol_ctrlN;
m_priv->hsvdvbspol_ins	=hsvdvbspol_ins;
m_priv->hsvdvbspol_plfApidvbsN	=hsvdvbspol_plfApidvbsN;
m_priv->hsvdvbspol_pow	=hsvdvbspol_pow;
m_priv->hsvdvbspol_sort	=hsvdvbspol_sort;
m_priv->hsvdvbsrussia_ctrlN	=hsvdvbsrussia_ctrlN;
m_priv->hsvdvbsrussia_ins	=hsvdvbsrussia_ins;
m_priv->hsvdvbsrussia_plfApidvbsN	=hsvdvbsrussia_plfApidvbsN;
m_priv->hsvdvbsrussia_pow	=hsvdvbsrussia_pow;
m_priv->hsvdvbsrussia_sort	=hsvdvbsrussia_sort;
m_priv->hsvdvbsfreesat_ctrlN	=hsvdvbsfreesat_ctrlN;
m_priv->hsvdvbsfreesat_ins	=hsvdvbsfreesat_ins;
m_priv->hsvdvbsfreesat_plfApidvbsN	=hsvdvbsfreesat_plfApidvbsN;
m_priv->hsvdvbsfreesat_pow	=hsvdvbsfreesat_pow;
m_priv->hsvdvbsfreesat_sort	=hsvdvbsfreesat_sort;
m_priv->hsvdvbsfreesat_settings	=hsvdvbsfreesat_settings;
m_priv->hsvdvbsfreesat_strapiN =hsvdvbsfreesat_strapiN;
m_priv->hsvdvbsfreesat_ibckInstall=hsvdvbsfreesat_ibckInstall;
m_priv->hsvdvbstricolor_ctrlN	=hsvdvbstricolor_ctrlN;
m_priv->hsvdvbstricolor_ins	=hsvdvbstricolor_ins;
m_priv->hsvdvbstricolor_plfApidvbsN	=hsvdvbstricolor_plfApidvbsN;
m_priv->hsvdvbstricolor_pow	=hsvdvbstricolor_pow;
m_priv->hsvdvbstricolor_sort	=hsvdvbstricolor_sort;
m_priv->hsvdvbstricolor_strapiN	=	hsvdvbstricolor_strapiN;
m_priv->ipackage	=ipackage;
m_priv->pins	=pins;
m_priv->hsvdvbsastra_ctrlN	=hsvdvbsastra_ctrlN;
m_priv->hsvdvbsastra_ins	=hsvdvbsastra_ins;
m_priv->hsvdvbsastra_plfApidvbsN	=hsvdvbsastra_plfApidvbsN;
m_priv->hsvdvbsastra_pow	=hsvdvbsastra_pow;
m_priv->hsvdvbsastra_sort	=hsvdvbsastra_sort;
m_priv->hsvdvbsastra_bckInstall	=	hsvdvbsastra_bckInstall;
m_priv->hsvdvbsastra_strapiN	=	hsvdvbsastra_strapiN;

}
CHsvDvbsInstallation_mroute::~CHsvDvbsInstallation_mroute()
{
 delete m_priv;
}
#endif
