#ifndef  _CHSVEUROPEINSTALLATION_MROUTE_PRIV_H
#define  _CHSVEUROPEINSTALLATION_MROUTE_PRIV_H 

#include <InfraGlobals.h>
#include <provreq.h>
#include <IHsvHybridPresetSort.h>
#include <IHsvSortRoute.h>
#include <CTCMwBase.h>
class CHsvEuropeInstallation_mroute_Priv;
#define CLASSSCOPE CHsvEuropeInstallation_mroute_Priv::
#include "locals_mroute.h"

class CHsvEuropeInstallation_mroute_Priv : public CTCMwBase
{
public:
virtual ~CHsvEuropeInstallation_mroute_Priv();

private:
void params__init(void);
private:
#define MEMBERVARS
#include "locals_mroute.h"
#undef MEMBERVARS
//Provided interfaces
private:
IHsvHybridPresetSortImpl(CHsvEuropeInstallation_mroute_Priv,isort);
public:
ProvidesInterface<IHsvHybridPresetSort>	isort;

//Required interfaces
public:
RequiresInterface<IHsvHybridPresetSort>	idbooksort;
RequiresInterface<IHsvHybridPresetSort>	idvbclitesort;
RequiresInterface<IHsvHybridPresetSort>	idvbcsort;
RequiresInterface<IHsvHybridPresetSort>	idvbtlitesort;
RequiresInterface<IHsvHybridPresetSort>	iblizoosort;
RequiresInterface<IHsvHybridPresetSort>	idvbtsort;
RequiresInterface<IHsvHybridPresetSort>	ifinsort;
RequiresInterface<IHsvHybridPresetSort>	inorsort;
RequiresInterface<IHsvSortRoute>	isortroute;
RequiresInterface<IHsvHybridPresetSort>	istubsort;
RequiresInterface<IHsvHybridPresetSort>	itasort;
RequiresInterface<IHsvHybridPresetSort>	idvbtapmeasort;
RequiresInterface<IHsvHybridPresetSort>	idvbthungarysort;

public:
CHsvEuropeInstallation_mroute_Priv():i__isort(this)
{
isort	=	&i__isort;
module__init();
params__init();
}

};

#ifdef GENERATE__LEGACY__DEFINES
#define idbooksort_iPresent() (idbooksort.Present())
#define idbooksort_Initialise()	idbooksort->Initialise()
#define idbooksort_AddAnalogPreset(adata)	idbooksort->AddAnalogPreset(adata)
#define idbooksort_AnalogPresetEntry()	idbooksort->AnalogPresetEntry()
#define idbooksort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	idbooksort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define idbooksort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	idbooksort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define idbooksort_AssignPresetsOfOtherCountries()	idbooksort->AssignPresetsOfOtherCountries()
#define idbooksort_AddDigitalPreset(svcdat)	idbooksort->AddDigitalPreset(svcdat)
#define idbooksort_AutoStoreManualInstallationValues()	idbooksort->AutoStoreManualInstallationValues()
#define idbooksort_RemoveDigitalPresets()	idbooksort->RemoveDigitalPresets()
#define idbooksort_GetNumberOfAnalogChannelsFound()	idbooksort->GetNumberOfAnalogChannelsFound()
#define idbooksort_UpdateDigitalPreset(svcdat)	idbooksort->UpdateDigitalPreset(svcdat)
#define idbooksort_DeleteAllDigitalChannels()	idbooksort->DeleteAllDigitalChannels()
#define idbooksort_UpdatingLCNDuringUpdateInstallation()	idbooksort->UpdatingLCNDuringUpdateInstallation()
#define idbooksort_DeleteInvalidPTCTable()	idbooksort->DeleteInvalidPTCTable()
#define idbooksort_GetOriginalNetworkId(CurrentCountry)	idbooksort->GetOriginalNetworkId(CurrentCountry)
#define idbooksort_IsPresetInstalled(frequency)	idbooksort->IsPresetInstalled(frequency)
#define idbooksort_AssignPresetsForCountry(ONID)	idbooksort->AssignPresetsForCountry(ONID)
#define idbooksort_SortAll()	idbooksort->SortAll()
#define idbooksort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	idbooksort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define idbooksort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	idbooksort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define idbooksort_GetInstalledWeakSignalChannel()	idbooksort->GetInstalledWeakSignalChannel()
#define idvbclitesort_iPresent() (idvbclitesort.Present())
#define idvbclitesort_Initialise()	idvbclitesort->Initialise()
#define idvbclitesort_AddAnalogPreset(adata)	idvbclitesort->AddAnalogPreset(adata)
#define idvbclitesort_AnalogPresetEntry()	idvbclitesort->AnalogPresetEntry()
#define idvbclitesort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	idvbclitesort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define idvbclitesort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	idvbclitesort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define idvbclitesort_AssignPresetsOfOtherCountries()	idvbclitesort->AssignPresetsOfOtherCountries()
#define idvbclitesort_AddDigitalPreset(svcdat)	idvbclitesort->AddDigitalPreset(svcdat)
#define idvbclitesort_AutoStoreManualInstallationValues()	idvbclitesort->AutoStoreManualInstallationValues()
#define idvbclitesort_RemoveDigitalPresets()	idvbclitesort->RemoveDigitalPresets()
#define idvbclitesort_GetNumberOfAnalogChannelsFound()	idvbclitesort->GetNumberOfAnalogChannelsFound()
#define idvbclitesort_UpdateDigitalPreset(svcdat)	idvbclitesort->UpdateDigitalPreset(svcdat)
#define idvbclitesort_DeleteAllDigitalChannels()	idvbclitesort->DeleteAllDigitalChannels()
#define idvbclitesort_UpdatingLCNDuringUpdateInstallation()	idvbclitesort->UpdatingLCNDuringUpdateInstallation()
#define idvbclitesort_DeleteInvalidPTCTable()	idvbclitesort->DeleteInvalidPTCTable()
#define idvbclitesort_GetOriginalNetworkId(CurrentCountry)	idvbclitesort->GetOriginalNetworkId(CurrentCountry)
#define idvbclitesort_IsPresetInstalled(frequency)	idvbclitesort->IsPresetInstalled(frequency)
#define idvbclitesort_AssignPresetsForCountry(ONID)	idvbclitesort->AssignPresetsForCountry(ONID)
#define idvbclitesort_SortAll()	idvbclitesort->SortAll()
#define idvbclitesort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	idvbclitesort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define idvbclitesort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	idvbclitesort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define idvbclitesort_GetInstalledWeakSignalChannel()	idvbclitesort->GetInstalledWeakSignalChannel()
#define idvbcsort_iPresent() (idvbcsort.Present())
#define idvbcsort_Initialise()	idvbcsort->Initialise()
#define idvbcsort_AddAnalogPreset(adata)	idvbcsort->AddAnalogPreset(adata)
#define idvbcsort_AnalogPresetEntry()	idvbcsort->AnalogPresetEntry()
#define idvbcsort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	idvbcsort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define idvbcsort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	idvbcsort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define idvbcsort_AssignPresetsOfOtherCountries()	idvbcsort->AssignPresetsOfOtherCountries()
#define idvbcsort_AddDigitalPreset(svcdat)	idvbcsort->AddDigitalPreset(svcdat)
#define idvbcsort_AutoStoreManualInstallationValues()	idvbcsort->AutoStoreManualInstallationValues()
#define idvbcsort_RemoveDigitalPresets()	idvbcsort->RemoveDigitalPresets()
#define idvbcsort_GetNumberOfAnalogChannelsFound()	idvbcsort->GetNumberOfAnalogChannelsFound()
#define idvbcsort_UpdateDigitalPreset(svcdat)	idvbcsort->UpdateDigitalPreset(svcdat)
#define idvbcsort_DeleteAllDigitalChannels()	idvbcsort->DeleteAllDigitalChannels()
#define idvbcsort_UpdatingLCNDuringUpdateInstallation()	idvbcsort->UpdatingLCNDuringUpdateInstallation()
#define idvbcsort_DeleteInvalidPTCTable()	idvbcsort->DeleteInvalidPTCTable()
#define idvbcsort_GetOriginalNetworkId(CurrentCountry)	idvbcsort->GetOriginalNetworkId(CurrentCountry)
#define idvbcsort_IsPresetInstalled(frequency)	idvbcsort->IsPresetInstalled(frequency)
#define idvbcsort_AssignPresetsForCountry(ONID)	idvbcsort->AssignPresetsForCountry(ONID)
#define idvbcsort_SortAll()	idvbcsort->SortAll()
#define idvbcsort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	idvbcsort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define idvbcsort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	idvbcsort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define idvbcsort_GetInstalledWeakSignalChannel()	idvbcsort->GetInstalledWeakSignalChannel()
#define iblizoosort_iPresent() (iblizoosort.Present())
#define iblizoosort_Initialise()	iblizoosort->Initialise()
#define iblizoosort_AddAnalogPreset(adata)	iblizoosort->AddAnalogPreset(adata)
#define iblizoosort_AnalogPresetEntry()	iblizoosort->AnalogPresetEntry()
#define iblizoosort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	iblizoosort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define iblizoosort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	iblizoosort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define iblizoosort_AssignPresetsOfOtherCountries()	iblizoosort->AssignPresetsOfOtherCountries()
#define iblizoosort_AddDigitalPreset(svcdat)	iblizoosort->AddDigitalPreset(svcdat)
#define iblizoosort_AutoStoreManualInstallationValues()	iblizoosort->AutoStoreManualInstallationValues()
#define iblizoosort_RemoveDigitalPresets()	iblizoosort->RemoveDigitalPresets()
#define iblizoosort_GetNumberOfAnalogChannelsFound()	iblizoosort->GetNumberOfAnalogChannelsFound()
#define iblizoosort_UpdateDigitalPreset(svcdat)	iblizoosort->UpdateDigitalPreset(svcdat)
#define iblizoosort_DeleteAllDigitalChannels()	iblizoosort->DeleteAllDigitalChannels()
#define iblizoosort_UpdatingLCNDuringUpdateInstallation()	iblizoosort->UpdatingLCNDuringUpdateInstallation()
#define iblizoosort_DeleteInvalidPTCTable()	iblizoosort->DeleteInvalidPTCTable()
#define iblizoosort_GetOriginalNetworkId(CurrentCountry)	iblizoosort->GetOriginalNetworkId(CurrentCountry)
#define iblizoosort_IsPresetInstalled(frequency)	iblizoosort->IsPresetInstalled(frequency)
#define iblizoosort_AssignPresetsForCountry(ONID)	iblizoosort->AssignPresetsForCountry(ONID)
#define iblizoosort_SortAll()	iblizoosort->SortAll()
#define iblizoosort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	iblizoosort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define iblizoosort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	iblizoosort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define iblizoosort_GetInstalledWeakSignalChannel()	iblizoosort->GetInstalledWeakSignalChannel()
#define idvbtlitesort_iPresent() (idvbtlitesort.Present())
#define idvbtlitesort_Initialise()	idvbtlitesort->Initialise()
#define idvbtlitesort_AddAnalogPreset(adata)	idvbtlitesort->AddAnalogPreset(adata)
#define idvbtlitesort_AnalogPresetEntry()	idvbtlitesort->AnalogPresetEntry()
#define idvbtlitesort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	idvbtlitesort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define idvbtlitesort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	idvbtlitesort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define idvbtlitesort_AssignPresetsOfOtherCountries()	idvbtlitesort->AssignPresetsOfOtherCountries()
#define idvbtlitesort_AddDigitalPreset(svcdat)	idvbtlitesort->AddDigitalPreset(svcdat)
#define idvbtlitesort_AutoStoreManualInstallationValues()	idvbtlitesort->AutoStoreManualInstallationValues()
#define idvbtlitesort_RemoveDigitalPresets()	idvbtlitesort->RemoveDigitalPresets()
#define idvbtlitesort_GetNumberOfAnalogChannelsFound()	idvbtlitesort->GetNumberOfAnalogChannelsFound()
#define idvbtlitesort_UpdateDigitalPreset(svcdat)	idvbtlitesort->UpdateDigitalPreset(svcdat)
#define idvbtlitesort_DeleteAllDigitalChannels()	idvbtlitesort->DeleteAllDigitalChannels()
#define idvbtlitesort_UpdatingLCNDuringUpdateInstallation()	idvbtlitesort->UpdatingLCNDuringUpdateInstallation()
#define idvbtlitesort_DeleteInvalidPTCTable()	idvbtlitesort->DeleteInvalidPTCTable()
#define idvbtlitesort_GetOriginalNetworkId(CurrentCountry)	idvbtlitesort->GetOriginalNetworkId(CurrentCountry)
#define idvbtlitesort_IsPresetInstalled(frequency)	idvbtlitesort->IsPresetInstalled(frequency)
#define idvbtlitesort_AssignPresetsForCountry(ONID)	idvbtlitesort->AssignPresetsForCountry(ONID)
#define idvbtlitesort_SortAll()	idvbtlitesort->SortAll()
#define idvbtlitesort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	idvbtlitesort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define idvbtlitesort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	idvbtlitesort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define idvbtlitesort_GetInstalledWeakSignalChannel()	idvbtlitesort->GetInstalledWeakSignalChannel()

#define idvbtapmeasort_iPresent() (idvbtapmeasort.Present())
#define idvbtapmeasort_Initialise()	idvbtapmeasort->Initialise()
#define idvbtapmeasort_AddAnalogPreset(adata)	idvbtapmeasort->AddAnalogPreset(adata)
#define idvbtapmeasort_AnalogPresetEntry()	idvbtapmeasort->AnalogPresetEntry()
#define idvbtapmeasort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	idvbtapmeasort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define idvbtapmeasort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	idvbtapmeasort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define idvbtapmeasort_AssignPresetsOfOtherCountries()	idvbtapmeasort->AssignPresetsOfOtherCountries()
#define idvbtapmeasort_AddDigitalPreset(svcdat)	idvbtapmeasort->AddDigitalPreset(svcdat)
#define idvbtapmeasort_AutoStoreManualInstallationValues()	idvbtapmeasort->AutoStoreManualInstallationValues()
#define idvbtapmeasort_RemoveDigitalPresets()	idvbtapmeasort->RemoveDigitalPresets()
#define idvbtapmeasort_GetNumberOfAnalogChannelsFound()	idvbtapmeasort->GetNumberOfAnalogChannelsFound()
#define idvbtapmeasort_UpdateDigitalPreset(svcdat)	idvbtapmeasort->UpdateDigitalPreset(svcdat)
#define idvbtapmeasort_DeleteAllDigitalChannels()	idvbtapmeasort->DeleteAllDigitalChannels()
#define idvbtapmeasort_UpdatingLCNDuringUpdateInstallation()	idvbtapmeasort->UpdatingLCNDuringUpdateInstallation()
#define idvbtapmeasort_DeleteInvalidPTCTable()	idvbtapmeasort->DeleteInvalidPTCTable()
#define idvbtapmeasort_GetOriginalNetworkId(CurrentCountry)	idvbtapmeasort->GetOriginalNetworkId(CurrentCountry)
#define idvbtapmeasort_IsPresetInstalled(frequency)	idvbtapmeasort->IsPresetInstalled(frequency)
#define idvbtapmeasort_AssignPresetsForCountry(ONID)	idvbtapmeasort->AssignPresetsForCountry(ONID)
#define idvbtapmeasort_SortAll()	idvbtapmeasort->SortAll()
#define idvbtapmeasort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	idvbtapmeasort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define idvbtapmeasort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	idvbtapmeasort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define idvbtapmeasort_GetInstalledWeakSignalChannel()	idvbtapmeasort->GetInstalledWeakSignalChannel()
#define idvbthungarysort_iPresent() (idvbthungarysort.Present())
#define idvbthungarysort_Initialise()	idvbthungarysort->Initialise()
#define idvbthungarysort_AddAnalogPreset(adata)	idvbthungarysort->AddAnalogPreset(adata)
#define idvbthungarysort_AnalogPresetEntry()	idvbthungarysort->AnalogPresetEntry()
#define idvbthungarysort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	idvbthungarysort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define idvbthungarysort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	idvbthungarysort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define idvbthungarysort_AssignPresetsOfOtherCountries()	idvbthungarysort->AssignPresetsOfOtherCountries()
#define idvbthungarysort_AddDigitalPreset(svcdat)	idvbthungarysort->AddDigitalPreset(svcdat)
#define idvbthungarysort_AutoStoreManualInstallationValues()	idvbthungarysort->AutoStoreManualInstallationValues()
#define idvbthungarysort_RemoveDigitalPresets()	idvbthungarysort->RemoveDigitalPresets()
#define idvbthungarysort_GetNumberOfAnalogChannelsFound()	idvbthungarysort->GetNumberOfAnalogChannelsFound()
#define idvbthungarysort_UpdateDigitalPreset(svcdat)	idvbthungarysort->UpdateDigitalPreset(svcdat)
#define idvbthungarysort_DeleteAllDigitalChannels()	idvbthungarysort->DeleteAllDigitalChannels()
#define idvbthungarysort_UpdatingLCNDuringUpdateInstallation()	idvbthungarysort->UpdatingLCNDuringUpdateInstallation()
#define idvbthungarysort_DeleteInvalidPTCTable()	idvbthungarysort->DeleteInvalidPTCTable()
#define idvbthungarysort_GetOriginalNetworkId(CurrentCountry)	idvbthungarysort->GetOriginalNetworkId(CurrentCountry)
#define idvbthungarysort_IsPresetInstalled(frequency)	idvbthungarysort->IsPresetInstalled(frequency)
#define idvbthungarysort_AssignPresetsForCountry(ONID)	idvbthungarysort->AssignPresetsForCountry(ONID)
#define idvbthungarysort_SortAll()	idvbthungarysort->SortAll()
#define idvbthungarysort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	idvbthungarysort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define idvbthungarysort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	idvbthungarysort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define idvbthungarysort_GetInstalledWeakSignalChannel()	idvbthungarysort->GetInstalledWeakSignalChannel()
#define idvbtsort_iPresent() (idvbtsort.Present())
#define idvbtsort_Initialise()	idvbtsort->Initialise()
#define idvbtsort_AddAnalogPreset(adata)	idvbtsort->AddAnalogPreset(adata)
#define idvbtsort_AnalogPresetEntry()	idvbtsort->AnalogPresetEntry()
#define idvbtsort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	idvbtsort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define idvbtsort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	idvbtsort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define idvbtsort_AssignPresetsOfOtherCountries()	idvbtsort->AssignPresetsOfOtherCountries()
#define idvbtsort_AddDigitalPreset(svcdat)	idvbtsort->AddDigitalPreset(svcdat)
#define idvbtsort_AutoStoreManualInstallationValues()	idvbtsort->AutoStoreManualInstallationValues()
#define idvbtsort_RemoveDigitalPresets()	idvbtsort->RemoveDigitalPresets()
#define idvbtsort_GetNumberOfAnalogChannelsFound()	idvbtsort->GetNumberOfAnalogChannelsFound()
#define idvbtsort_UpdateDigitalPreset(svcdat)	idvbtsort->UpdateDigitalPreset(svcdat)
#define idvbtsort_DeleteAllDigitalChannels()	idvbtsort->DeleteAllDigitalChannels()
#define idvbtsort_UpdatingLCNDuringUpdateInstallation()	idvbtsort->UpdatingLCNDuringUpdateInstallation()
#define idvbtsort_DeleteInvalidPTCTable()	idvbtsort->DeleteInvalidPTCTable()
#define idvbtsort_GetOriginalNetworkId(CurrentCountry)	idvbtsort->GetOriginalNetworkId(CurrentCountry)
#define idvbtsort_IsPresetInstalled(frequency)	idvbtsort->IsPresetInstalled(frequency)
#define idvbtsort_AssignPresetsForCountry(ONID)	idvbtsort->AssignPresetsForCountry(ONID)
#define idvbtsort_SortAll()	idvbtsort->SortAll()
#define idvbtsort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	idvbtsort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define idvbtsort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	idvbtsort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define idvbtsort_GetInstalledWeakSignalChannel()	idvbtsort->GetInstalledWeakSignalChannel()
#define ifinsort_iPresent() (ifinsort.Present())
#define ifinsort_Initialise()	ifinsort->Initialise()
#define ifinsort_AddAnalogPreset(adata)	ifinsort->AddAnalogPreset(adata)
#define ifinsort_AnalogPresetEntry()	ifinsort->AnalogPresetEntry()
#define ifinsort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	ifinsort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define ifinsort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	ifinsort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define ifinsort_AssignPresetsOfOtherCountries()	ifinsort->AssignPresetsOfOtherCountries()
#define ifinsort_AddDigitalPreset(svcdat)	ifinsort->AddDigitalPreset(svcdat)
#define ifinsort_AutoStoreManualInstallationValues()	ifinsort->AutoStoreManualInstallationValues()
#define ifinsort_RemoveDigitalPresets()	ifinsort->RemoveDigitalPresets()
#define ifinsort_GetNumberOfAnalogChannelsFound()	ifinsort->GetNumberOfAnalogChannelsFound()
#define ifinsort_UpdateDigitalPreset(svcdat)	ifinsort->UpdateDigitalPreset(svcdat)
#define ifinsort_DeleteAllDigitalChannels()	ifinsort->DeleteAllDigitalChannels()
#define ifinsort_UpdatingLCNDuringUpdateInstallation()	ifinsort->UpdatingLCNDuringUpdateInstallation()
#define ifinsort_DeleteInvalidPTCTable()	ifinsort->DeleteInvalidPTCTable()
#define ifinsort_GetOriginalNetworkId(CurrentCountry)	ifinsort->GetOriginalNetworkId(CurrentCountry)
#define ifinsort_IsPresetInstalled(frequency)	ifinsort->IsPresetInstalled(frequency)
#define ifinsort_AssignPresetsForCountry(ONID)	ifinsort->AssignPresetsForCountry(ONID)
#define ifinsort_SortAll()	ifinsort->SortAll()
#define ifinsort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	ifinsort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define ifinsort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	ifinsort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define ifinsort_GetInstalledWeakSignalChannel()	ifinsort->GetInstalledWeakSignalChannel()
#define inorsort_iPresent() (inorsort.Present())
#define inorsort_Initialise()	inorsort->Initialise()
#define inorsort_AddAnalogPreset(adata)	inorsort->AddAnalogPreset(adata)
#define inorsort_AnalogPresetEntry()	inorsort->AnalogPresetEntry()
#define inorsort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	inorsort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define inorsort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	inorsort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define inorsort_AssignPresetsOfOtherCountries()	inorsort->AssignPresetsOfOtherCountries()
#define inorsort_AddDigitalPreset(svcdat)	inorsort->AddDigitalPreset(svcdat)
#define inorsort_AutoStoreManualInstallationValues()	inorsort->AutoStoreManualInstallationValues()
#define inorsort_RemoveDigitalPresets()	inorsort->RemoveDigitalPresets()
#define inorsort_GetNumberOfAnalogChannelsFound()	inorsort->GetNumberOfAnalogChannelsFound()
#define inorsort_UpdateDigitalPreset(svcdat)	inorsort->UpdateDigitalPreset(svcdat)
#define inorsort_DeleteAllDigitalChannels()	inorsort->DeleteAllDigitalChannels()
#define inorsort_UpdatingLCNDuringUpdateInstallation()	inorsort->UpdatingLCNDuringUpdateInstallation()
#define inorsort_DeleteInvalidPTCTable()	inorsort->DeleteInvalidPTCTable()
#define inorsort_GetOriginalNetworkId(CurrentCountry)	inorsort->GetOriginalNetworkId(CurrentCountry)
#define inorsort_IsPresetInstalled(frequency)	inorsort->IsPresetInstalled(frequency)
#define inorsort_AssignPresetsForCountry(ONID)	inorsort->AssignPresetsForCountry(ONID)
#define inorsort_SortAll()	inorsort->SortAll()
#define inorsort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	inorsort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define inorsort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	inorsort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define inorsort_GetInstalledWeakSignalChannel()	inorsort->GetInstalledWeakSignalChannel()
#define isortroute_iPresent() (isortroute.Present())
#define isortroute_stubsort	IHsvSortRoute_stubsort
#define isortroute_dvbtsort	IHsvSortRoute_dvbtsort
#define isortroute_dvbcsort	IHsvSortRoute_dvbcsort
#define isortroute_blizoosort	IHsvSortRoute_blizoosort
#define isortroute_norsort	IHsvSortRoute_norsort
#define isortroute_dvbclitesort	IHsvSortRoute_dvbclitesort
#define isortroute_dvbtlitesort	IHsvSortRoute_dvbtlitesort
#define isortroute_italysort	IHsvSortRoute_italysort
#define isortroute_dvbt2sort	IHsvSortRoute_dvbt2sort
#define isortroute_finsort	IHsvSortRoute_finsort
#define isortroute_apmeasort	IHsvSortRoute_apmeasort
#define isortroute_Enable()	isortroute->Enable()
#define isortroute_GetCurrentActiveSortInterface()	isortroute->GetCurrentActiveSortInterface()
#define isortroute_hungarysort	IHsvSortRoute_hungarysort
#define istubsort_iPresent() (istubsort.Present())
#define istubsort_Initialise()	istubsort->Initialise()
#define istubsort_AddAnalogPreset(adata)	istubsort->AddAnalogPreset(adata)
#define istubsort_AnalogPresetEntry()	istubsort->AnalogPresetEntry()
#define istubsort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	istubsort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define istubsort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	istubsort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define istubsort_AssignPresetsOfOtherCountries()	istubsort->AssignPresetsOfOtherCountries()
#define istubsort_AddDigitalPreset(svcdat)	istubsort->AddDigitalPreset(svcdat)
#define istubsort_AutoStoreManualInstallationValues()	istubsort->AutoStoreManualInstallationValues()
#define istubsort_RemoveDigitalPresets()	istubsort->RemoveDigitalPresets()
#define istubsort_GetNumberOfAnalogChannelsFound()	istubsort->GetNumberOfAnalogChannelsFound()
#define istubsort_UpdateDigitalPreset(svcdat)	istubsort->UpdateDigitalPreset(svcdat)
#define istubsort_DeleteAllDigitalChannels()	istubsort->DeleteAllDigitalChannels()
#define istubsort_UpdatingLCNDuringUpdateInstallation()	istubsort->UpdatingLCNDuringUpdateInstallation()
#define istubsort_DeleteInvalidPTCTable()	istubsort->DeleteInvalidPTCTable()
#define istubsort_GetOriginalNetworkId(CurrentCountry)	istubsort->GetOriginalNetworkId(CurrentCountry)
#define istubsort_IsPresetInstalled(frequency)	istubsort->IsPresetInstalled(frequency)
#define istubsort_AssignPresetsForCountry(ONID)	istubsort->AssignPresetsForCountry(ONID)
#define istubsort_SortAll()	istubsort->SortAll()
#define istubsort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	istubsort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define istubsort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	istubsort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define istubsort_GetInstalledWeakSignalChannel()	istubsort->GetInstalledWeakSignalChannel()
#define itasort_iPresent() (itasort.Present())
#define itasort_Initialise()	itasort->Initialise()
#define itasort_AddAnalogPreset(adata)	itasort->AddAnalogPreset(adata)
#define itasort_AnalogPresetEntry()	itasort->AnalogPresetEntry()
#define itasort_AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)	itasort->AssignPresetsForCurrentCountry(CurrentOnwid,CheckLCN)
#define itasort_AssignPresetsWithStaticTable(CurrentOnwid,Country)	itasort->AssignPresetsWithStaticTable(CurrentOnwid,Country)
#define itasort_AssignPresetsOfOtherCountries()	itasort->AssignPresetsOfOtherCountries()
#define itasort_AddDigitalPreset(svcdat)	itasort->AddDigitalPreset(svcdat)
#define itasort_AutoStoreManualInstallationValues()	itasort->AutoStoreManualInstallationValues()
#define itasort_RemoveDigitalPresets()	itasort->RemoveDigitalPresets()
#define itasort_GetNumberOfAnalogChannelsFound()	itasort->GetNumberOfAnalogChannelsFound()
#define itasort_UpdateDigitalPreset(svcdat)	itasort->UpdateDigitalPreset(svcdat)
#define itasort_DeleteAllDigitalChannels()	itasort->DeleteAllDigitalChannels()
#define itasort_UpdatingLCNDuringUpdateInstallation()	itasort->UpdatingLCNDuringUpdateInstallation()
#define itasort_DeleteInvalidPTCTable()	itasort->DeleteInvalidPTCTable()
#define itasort_GetOriginalNetworkId(CurrentCountry)	itasort->GetOriginalNetworkId(CurrentCountry)
#define itasort_IsPresetInstalled(frequency)	itasort->IsPresetInstalled(frequency)
#define itasort_AssignPresetsForCountry(ONID)	itasort->AssignPresetsForCountry(ONID)
#define itasort_SortAll()	itasort->SortAll()
#define itasort_AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)	itasort->AssignPresetsForCurrentCountryNonLCNs(CurrentOnwid,FillHoles)
#define itasort_AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)	itasort->AssignPresetsForCurrentCountryLowPrioLCN(CurrentOnwid)
#define itasort_GetInstalledWeakSignalChannel()	itasort->GetInstalledWeakSignalChannel()
#else //GENERATE__LEGACY__DEFINES
#ifdef CLASSSCOPE
#undef CLASSSCOPE
#endif
#ifdef FPCALL
#undef FPCALL
#endif
#ifdef NOCLASS
#undef NOCLASS
#endif
#define LOCAL_UNDEFINES
#include "locals_mroute.h"
#undef LOCAL_UNDEFINES
#endif //GENERATE__LEGACY__DEFINES
#endif

