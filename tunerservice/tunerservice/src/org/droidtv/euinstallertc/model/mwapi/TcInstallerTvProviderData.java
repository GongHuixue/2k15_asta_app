package org.droidtv.euinstallertc.model.mwapi;

import java.util.Arrays;

public class TcInstallerTvProviderData {

	public int UniqueId;
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
	public int 	StreamPriority;
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
	public int 	CniNi;
	public String 	ChannelName;
	public String	TxtPages;

	/*Private Data*/
	
	/*Service table data*/
	public int SignalStrength;
	public int SignalQuality;
	public int SDTVersion;
	public int NITVersion;
	public int DateStamp;
	public int DeltaVolume;
	public int PmtPid;
	public int SecAudioPid;
	public int LowPrioLCN;
	public int LowPrioVisibleService;
	public int FreeCiMode;
	public int VideoDescPresent;
	public int VisibleService;
	public int OUI;
	public int ServiceListVersion;
	public int UserInstalled;
	public int SecAudioStreamType;
	public int UserModifiedName;
	public int PreferredNicam; /*Analog and digital*/
	public int MatchBrandFlag;
	public int NumBrandIds;
	public int BrandIds[];
	public int SrcambledStatus;
	public int RegionDepth;
	public int PrimaryRegion;
	public int SecondaryRegion;
	public int TertiaryRegion;
	public int CountryCode;
	public int HDSimulcastRepOnId;
	public int HDSimulcastRepTsId;
	public int HDSimulcastRepSvcId;
	public int FavoriteNumber;
	public int MultipleLCN[];
	public int MultiplePreset[];
	public int MultipleFavorite[];

	
	/*Analog data*/	

	public int FineTuneFrequency;
	public int FineTuneOffset;
	public int ColourSystem;
	public int DataIndicator;
	public int Attenuator;
	public int Tuned;
	public int DeTuned;
	public int AgcInstalled;
	public int PreferredFavorite;

	/*TS Table data*/

	public int ASignalStrength;
	public int VSignalStrength;
	public int QSignalStrength;
	public int CDSDFrequency;
	public int CodeRate;
	public int HierarchyMode;
	public int GuardInterval;
	public int PtcListVersion;
	public int TSVersion;
	public int BarkerMux;
	public int LanguageCode;

	/*Preset table data*/
	public int AnalogTablePreset;
	public int Type;

	
	public TcInstallerTvProviderData(){}

	public TcInstallerTvProviderData(int UniqueId, int PresetNumber, 	int OriginalNetworkId, int Tsid, int  ServiceId,  int Frequency, 
					int TextSubTitlePage, 	int LogoURL, int DecoderType, int ModulationType, int UserModifiedLogo,
					int SAP, int PreferredStereo, int Ptc, int SymbolRate, int StreamPriority,  
					int AudioPid, int VideoPid, int PcrPid, int NetworkId, int LCN, 
					int ServiceType, int SystemHidden, int NumericSelect, int Bandwidth, int ScrambledStatus, 
					int IntHbbTvOption, int UserHidden, int NewPreset, int VideoStreamType, int AudioStreamType, 
					int CniNi, int SignalStrength, int SignalQuality, int SDTVersion, int NITVersion, 
					int DateStamp,int DeltaVolume, int PmtPid, int SecAudioPid, int LowPrioLCN,	int LowPrioVisibleService,
					int FreeCiMode,	int VideoDescPresent, int VisibleService, int OUI, int ServiceListVersion, int UserInstalled,
					int SecAudioStreamType, int UserModifiedName, int PreferredNicam, int MatchBrandFlag, int NumBrandIds,
					int SrcambledStatus, int RegionDepth, int PrimaryRegion, int SecondaryRegion, int TertiaryRegion,
					int CountryCode, int HDSimulcastRepOnId, int HDSimulcastRepTsId, int HDSimulcastRepSvcId, int FavoriteNumber,
					int FineTuneFrequency, int FineTuneOffset, int ColourSystem, int DataIndicator,
					int Attenuator, int Tuned, int DeTuned, int AgcInstalled, int PreferredFavorite, int ASignalStrength,
					int VSignalStrength, int QSignalStrength, int CDSDFrequency, int CodeRate, int HierarchyMode,
					int GuardInterval, int PtcListVersion, int TSVersion, int BarkerMux, int AnalogTablePreset, int Type, int LanguageCode,
					java.lang.String param2, java.lang.String param3, int BrandIds[], int MultipleLCN[],
					int MultiplePreset[], int MultipleFavorite[]) {
		this.UniqueId = UniqueId;
		this.PresetNumber = PresetNumber;
		this.OriginalNetworkId = OriginalNetworkId;
		this.Tsid = Tsid;
		this.ServiceId = ServiceId;
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
		this.StreamPriority = StreamPriority;
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
		this.CniNi = CniNi;
		this.ChannelName = param2;
		this.TxtPages = param3;

		this.SignalStrength = SignalStrength;
		this.SignalQuality = SignalQuality;
		this.SDTVersion = SDTVersion;
		this.NITVersion = NITVersion;
		this.DateStamp = DateStamp;
		this.DeltaVolume = DeltaVolume;
		this.PmtPid = PmtPid;
		this.SecAudioPid = SecAudioPid;
		this.LowPrioLCN = LowPrioLCN;
		this.LowPrioVisibleService = LowPrioVisibleService;
		this.FreeCiMode = FreeCiMode;
		this.VideoDescPresent = VideoDescPresent;
		this.VisibleService = VisibleService;
		this.OUI = OUI;
		this.ServiceListVersion = ServiceListVersion;
		this.UserInstalled = UserInstalled;
		this.SecAudioStreamType = SecAudioStreamType;
		this.UserModifiedName = UserModifiedName;
		this.PreferredNicam = PreferredNicam; 
		this.MatchBrandFlag = MatchBrandFlag;
		this.NumBrandIds = NumBrandIds;
		this.BrandIds = Arrays.copyOf(BrandIds,BrandIds.length);
		this.SrcambledStatus = SrcambledStatus;
		this.RegionDepth = RegionDepth;
		this.PrimaryRegion = PrimaryRegion;
		this.SecondaryRegion = SecondaryRegion;
		this.TertiaryRegion = TertiaryRegion;
		this.CountryCode = CountryCode;
		this.HDSimulcastRepOnId = HDSimulcastRepOnId;
		this.HDSimulcastRepTsId = HDSimulcastRepTsId;
		this.HDSimulcastRepSvcId = HDSimulcastRepSvcId;
		this.FavoriteNumber = FavoriteNumber;
		this.MultipleLCN = Arrays.copyOf(MultipleLCN,MultipleLCN.length);
		this.MultiplePreset = Arrays.copyOf(MultiplePreset,MultiplePreset.length);
		this.MultipleFavorite = Arrays.copyOf(MultipleFavorite,MultipleFavorite.length);
		this.FineTuneFrequency = FineTuneFrequency;
		this.FineTuneOffset = FineTuneOffset;
		this.ColourSystem = ColourSystem;
		this.DataIndicator = DataIndicator;
		this.Attenuator = Attenuator;
		this.Tuned = Tuned;
		this.DeTuned = DeTuned;
		this.AgcInstalled = AgcInstalled;
		this.PreferredFavorite = PreferredFavorite;
		this.ASignalStrength = ASignalStrength;
		this.VSignalStrength = VSignalStrength;
		this.QSignalStrength = QSignalStrength;
		this.CDSDFrequency = CDSDFrequency;
		this.CodeRate = CodeRate;
		this.HierarchyMode = HierarchyMode;
		this.GuardInterval = GuardInterval;
		this.PtcListVersion = PtcListVersion;
		this.TSVersion = TSVersion;
		this.BarkerMux = BarkerMux;
		this.AnalogTablePreset = AnalogTablePreset;
		this.Type = Type;
		this.LanguageCode = LanguageCode;
		
	}
}
