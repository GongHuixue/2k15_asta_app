package org.droidtv.euinstallersat.model.mwapi;

import java.util.Arrays;

public class SatInstallerTvProviderData {
    
	public int 	UniqueId;
	public int 	PresetNumber;
	public int 	OriginalNetworkId;
	public int 	Tsid;
	public int 	ServiceId;
	public int 	Frequency;
	public int 	TextSubTitlePage;
	public int 	LogoURL;
	public int 	DecoderType;
	public int 	ModulationType;
	public int 	UserModifiedLogo;
	public int 	SAP;
	public int 	PreferredStereo;
	public int 	Ptc;
	public int 	SymbolRate;
	public int 	AudioPid;
	public int 	VideoPid;
	public int 	PcrPid;
	public int 	NetworkId;
	public int 	LCN;
	public int 	ServiceType;
	public int 	SystemHidden;
	public int 	NumericSelect;
	public int 	Bandwidth;
	public int 	ScrambledStatus;
	public int 	IntHbbTvOption;
	public int 	UserHidden;
	public int 	NewPreset;
	public int 	VideoStreamType;
	public int 	AudioStreamType;
	public int 	LnbNumber;
	public int 	Polarization;
	public int 	DpTsid;
	public int 	DpServiceId;
	public int 	Tpid;
	public int 	PackageGroup;

	public int 	FavoriteNumber;
	public int 	VisibleService;
	public int 	LnbType;
	public int 	SatelliteId;
	public int 	OrbitalPosition;
	public int 	SignalStrength;
	public int 	SignalQuality;
	public int 	AppsCookie;
	public int 	SDTVersion;
	public int 	NITVersion;
	public int 	DateStamp;
	public int 	PmtPid;
	public int 	SecAudioPid;
	public int 	LowPrioLCN;
	public int 	LowPrioVisibleService;
	public int 	FreeCiMode;
	public int 	VideoDescPresent;
	public int 	ScramblingStatus;
	public int 	DuplicateSvc;
	public int 	ServiceListVersion;
	public int 	UserInstalled;
	public int 	SecAudioStreamType;
	public int 	UserModifiedName;
	public int 	ChannelLock;
	public int 	DvbType;
	public int 	MatchBrandFlag;
	public int 	NumBrandIds;
	public int 	InstalledSatelliteNumber;
	public int 	NewChannel;
	public int 	HbbTvOption;
	public int 	SDSDFrequency;
	public int 	CountryCode;
	public int 	HDSimulcastRepOnId;
	public int 	HDSimulcastRepTsId;
	public int 	HDSimulcastRepSvcId;
	public int 	ParentalRating;
	public int 	ServiceIdentifier;
	public int 	AdultGenere;
	public int 	FreesatServiceIdentifier;
	public int 	InteractiveServiceEnabled;
	public int 	ASignalStrength;
	public int 	VSignalStrength;
	public int 	QSignalStrength;
	public int 	ChannelInformation;
	public int 	CodeRate;
	public int 	PtcListVersion;
	public int 	TSVersion;
	public int 	PlpId;
	public int 	BarkerMux;
	public int 	FECInner;
	public int 	RollOff;
	

	public String 	ChannelName;

	public String 	SatelliteName;
	public int 	MultipleVisibleService[];
	public int 	MultipleNumericSelect[];
	public int 	BrandIds[];
	public int 	MultipleLCN[];
	public int 	MultiplePreset[];
	public int 	MultipleFavorite[];

	public SatInstallerTvProviderData(){}

	public SatInstallerTvProviderData(int UniqueId, int PresetNumber, 	int OriginalNetworkId, int Tsid, int  ServiceId,  int Frequency, 
					int TextSubTitlePage, 	int LogoURL, int DecoderType, int ModulationType, int UserModifiedLogo,
					int SAP, int PreferredStereo, int Ptc, int SymbolRate, int AudioPid,
					int VideoPid, int PcrPid, int NetworkId, int LCN, int ServiceType,
					int SystemHidden, int NumericSelect, int Bandwidth, int ScrambledStatus, int IntHbbTvOption,
					int UserHidden, int NewPreset, int VideoStreamType, int AudioStreamType, int LnbNumber,
					int Polarization, int DpTsid, int DpServiceId, int Tpid, int PackageGroup,
					int FavoriteNumber, int VisibleService, int LnbType, int SatelliteId, int OrbitalPosition, int SignalStrength, int SignalQuality, int AppsCookie, 
					int SDTVersion, int NITVersion, int DateStamp, int PmtPid, int SecAudioPid, int LowPrioLCN, 
					int LowPrioVisibleService, int FreeCiMode, int VideoDescPresent, int ScramblingStatus, int DuplicateSvc, int ServiceListVersion, 
					int UserInstalled, int SecAudioStreamType, int UserModifiedName, int ChannelLock,
					int DvbType, int MatchBrandFlag, 
					int NumBrandIds, int SrcambledStatus, int InstalledSatelliteNumber,
					int NewChannel, int HbbTvOption,
					int CountryCode, int HDSimulcastRepOnId, int HDSimulcastRepTsId, int HDSimulcastRepSvcId, int ParentalRating, int ServiceIdentifier, 
					int AdultGenere, int FreesatServiceIdentifier, int InteractiveServiceEnabled, int ASignalStrength, int VSignalStrength, int QSignalStrength, 
					int ChannelInformation, int CodeRate, int PtcListVersion, int TSVersion, int SDSDFrequency, int PlpId, int BarkerMux, int FECInner, int RollOff,
					java.lang.String param2, java.lang.String SatelliteName,int MultipleVisibleService[], int MultipleNumericSelect[],
					int BrandIds[],int MultipleLCN[],
					int MultiplePreset[], int MultipleFavorite[]) {
		this.UniqueId = UniqueId;
		this.PresetNumber = PresetNumber;
		this.OriginalNetworkId = OriginalNetworkId;
		this.Tsid = Tsid;
		this.ServiceId = ServiceId;
		this.ChannelLock = ChannelLock;
		this.Frequency = Frequency;
		this.TextSubTitlePage = TextSubTitlePage;
		this.LogoURL = LogoURL;
		this.DecoderType = DecoderType;
		this.ModulationType = ModulationType;
		this.UserModifiedLogo = UserModifiedLogo;
		this.SAP = SAP;
		this.PreferredStereo = PreferredStereo;
		this.Ptc = Ptc;
		this.SymbolRate = SymbolRate;
		this.AudioPid = AudioPid;
		this.VideoPid = VideoPid;
		this.PcrPid = PcrPid;
		this.NetworkId = NetworkId;
		this.LCN = LCN;
		this.ServiceType = ServiceType;
		this.SystemHidden = SystemHidden;
		this.NumericSelect = NumericSelect;
		this.Bandwidth = Bandwidth;
		this.ScrambledStatus = ScrambledStatus;
		this.IntHbbTvOption = IntHbbTvOption;
		this.UserHidden = UserHidden;
		this.NewPreset = NewPreset;
		this.VideoStreamType = VideoStreamType;
		this.AudioStreamType = AudioStreamType;
		this.LnbNumber = LnbNumber;
		this.Polarization = Polarization;
		this.DpTsid = DpTsid;
		this.DpServiceId = DpServiceId;
		this.Tpid = Tpid;
		this.PackageGroup = PackageGroup;

		this.DateStamp = DateStamp;
		this.PmtPid = PmtPid;
		this.SecAudioPid = SecAudioPid;
		this.FreeCiMode = FreeCiMode;
		this.ScramblingStatus = ScramblingStatus;
		this.SecAudioStreamType = SecAudioStreamType;
		this.UserModifiedName = UserModifiedName;
		this.MatchBrandFlag = MatchBrandFlag;
		this.NumBrandIds = NumBrandIds;
		this.HbbTvOption = HbbTvOption;
		this.ParentalRating = ParentalRating;
		this.ServiceIdentifier = ServiceIdentifier;
		

		this.FavoriteNumber = FavoriteNumber;
		this.VisibleService = VisibleService;
		this.LnbType = LnbType;
		this.SatelliteId = SatelliteId;
		this.OrbitalPosition = OrbitalPosition;
		this.SignalStrength = SignalStrength;
		this.SignalQuality = SignalQuality;
		this.AppsCookie = AppsCookie;
		this.SDTVersion = SDTVersion;
		this.NITVersion = NITVersion;
		this.LowPrioLCN = LowPrioLCN;
		this.LowPrioVisibleService = LowPrioVisibleService;
		this.VideoDescPresent = VideoDescPresent;
		this.DuplicateSvc = DuplicateSvc;
		this.ServiceListVersion = ServiceListVersion;
		this.UserInstalled = UserInstalled;

		this.DvbType = DvbType;
		this.InstalledSatelliteNumber = InstalledSatelliteNumber;
		this.NewChannel = NewChannel;
		this.SDSDFrequency = SDSDFrequency;
		this.CountryCode = CountryCode;
		this.HDSimulcastRepOnId = HDSimulcastRepOnId;
		this.HDSimulcastRepTsId = HDSimulcastRepTsId;
		this.HDSimulcastRepSvcId = HDSimulcastRepSvcId;
		this.AdultGenere = AdultGenere;
		this.FreesatServiceIdentifier = FreesatServiceIdentifier;
		this.InteractiveServiceEnabled = InteractiveServiceEnabled;
		this.ASignalStrength = ASignalStrength;
		this.VSignalStrength = VSignalStrength;
		this.QSignalStrength = QSignalStrength;
		this.ChannelInformation = ChannelInformation;
		this.CodeRate = CodeRate;
		this.PtcListVersion = PtcListVersion;
		this.TSVersion = TSVersion;
		this.PlpId = PlpId;
		this.BarkerMux = BarkerMux;
		this.FECInner = FECInner;
		this.RollOff = RollOff;
		

		this.ChannelName = param2;		
		this.SatelliteName = SatelliteName;


		this.MultipleVisibleService = Arrays.copyOf(MultipleVisibleService,MultipleVisibleService.length);
		this.MultipleNumericSelect = Arrays.copyOf(MultipleNumericSelect,MultipleNumericSelect.length);
		this.BrandIds = Arrays.copyOf(BrandIds,BrandIds.length);
		this.MultipleLCN = Arrays.copyOf(MultipleLCN,MultipleLCN.length);
		this.MultiplePreset = Arrays.copyOf(MultiplePreset,MultiplePreset.length);
		this.MultipleFavorite = Arrays.copyOf(MultipleFavorite,MultipleFavorite.length);
		
	}
}
