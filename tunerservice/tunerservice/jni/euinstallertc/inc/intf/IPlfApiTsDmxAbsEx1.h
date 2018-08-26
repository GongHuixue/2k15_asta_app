#ifndef _IPLFAPITSDMXABSEX1_H_
#define _IPLFAPITSDMXABSEX1_H_

class IPlfApiTsDmxAbsEx1
{
public:
	virtual ~IPlfApiTsDmxAbsEx1() {};
	virtual Nat32 GetSections (Nat32 subscrid, int *cookie, Nat32 *dataCookie, int *nSections, tmTsDmx_Section_t **sections) = 0;
	virtual Nat32 GetPes (Nat32 subscrid, int *cookie, Nat32 *listCookie, int *nPackets, tmTsDmx_Pes_t **packets) = 0;
};

#endif /* _IPLFAPITSDMXABSEX1_H_ */