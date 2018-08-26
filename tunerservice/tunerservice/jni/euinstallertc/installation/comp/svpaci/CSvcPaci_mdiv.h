#ifndef  _CSVCPACI_MDIV_H
#define  _CSVCPACI_MDIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <ICesPaciDiv.h>
class CSvcPaci_mdiv_Priv;
class CSvcPaci_mdiv
{
public:
ProvidesInterface<ICesPaciDiv>	adiv;

//Required interfaces
public:
RequiresInterface<ICesPaciDiv>	div;
public:
CSvcPaci_mdiv();
virtual ~CSvcPaci_mdiv();
private:
CSvcPaci_mdiv_Priv	*m_priv;
};

#endif

