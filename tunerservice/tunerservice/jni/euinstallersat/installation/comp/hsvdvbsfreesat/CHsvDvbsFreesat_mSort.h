#ifndef  _CHSVDVBSFREESAT_MSORT_H
#define  _CHSVDVBSFREESAT_MSORT_H

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvSorting.h>
#include <IHsvPower.h>
#include <IHsvSatelliteInstallationNotify.h>
#include <IHsvSatelliteInstallation.h>
#include <IPumpEngine.h>
#include <IHsvProgramDatabase.h>
#include <IHsvProgramDatabaseConstants.h>
#include <IPumpExSub.h>
#include <IHsvSatellitePackageInstallation.h>
#include <CS2MwBase.h>

class CHsvDvbsFreesat_mSort:public IHsvSorting,public IHsvPower, public CS2MwBase
{
private:

Pumpdefines(CHsvDvbsFreesat_mSort);

int mCurrentPresetIndex;
//static int s__mCurrentRadioIndex,s__mCurrentPresetIndex;
Pump Sortingpmp;
//static Pump s__Sortingpmp;
void SortingHandler( int event, Nat32 startindex );
void mSortServices(int startindex);
void mUpdateServiceTable(int startindex);
void mAddEntryToPresetTable(HsvPgdatDigServiceData *svcdat, int PresetNo, int LCNIndex);
int mGetPreExistingLcnIndex(int presetNo);
void mDigitalPresetEntryforValidLCN(int dbindex, int LCNIndex);

//IHsvPower

void Init(void);
void TurnOn(void);
void TurnOff(void);

//IHsvSorting

void Sort(Nat32 PackageIndex);

public:

ProvidesInterface<IHsvSorting>	ifreesatsort;
ProvidesInterface<IHsvPower>	isortpow;

//Required interfaces
public:
RequiresInterface<IHsvSatelliteInstallationNotify>	iinsN;
RequiresInterface<IHsvSatelliteInstallation>	insstate;
RequiresInterface<IPumpEngine>	pen;
RequiresInterface<IHsvProgramDatabase>	pgdb;
RequiresInterface<IHsvProgramDatabaseConstants>	pgdbconst;
RequiresInterface<IPumpExSub>	pmp;
RequiresInterface<IHsvSatellitePackageInstallation>	rins;
public:
CHsvDvbsFreesat_mSort()
{
	ifreesatsort = this;
	isortpow = this;
}
//virtual ~CHsvDvbsFreesat_mSort();

};

#endif

