/*
 *  Copyright(C) 2003 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.
 *
 *          %name: svpat.h %
 *       %version: TVG_tv550r4dev_2 %
 * %date_modified: Thu Jan 08 15:22:44 2009 %
 *    %derived_by: nareshj %
 */


#ifndef _svpat_H
#define _svpat_H


typedef enum
{
  presetNameOther=0u,
  presetNameTelez,
  presetNameTelec,
  presetNameZueri,
  presetNameTeleb,
  presetNameM1,
  presetNameStar,
  presetNamePro7,
  presetNameTpo,
  presetNameKabe1,	/* PATS 8.5 */
  presetNameSmt,	/* PATS 8.5 */
  presetNameIntro,	/* PATS 8.5 */
  presetNameTell,	/* PATS 8.5 */
  presetNameTop,	/* PATS 8.5 */
  presetNameTso,	/* PATS 8.5 */
  presetNameTvo,	/* PATS 8.5 */
  presetNameTelti,	/* PATS 8.5 */
  presetNameShf,	/* PATS 8.5 */
  presetNameU1tv,	/* PATS 8.5 */
  presetNameMtvs,	/* PATS 8.5 */
  presetNameSf1,
  presetNameTsr1,
  presetNameTsi1,
  presetNameSf2,
  presetNameTsr2,
  presetNameU1,     /* PATS 8.4 */
  presetNameTsi2,
  presetNameSrgs,
  presetNameSfi,	/* PATS 8.5 */
  presetNameOrf1,
  presetNameOrf2,
  presetNameOrf3,
  presetNameOrfsp,  /* PATS 8.5 */
  presetNameTw1,	/* PATS 8.5 */
  presetNameNivi,	/* PATS 8.5 */
  presetNameMtva,	/* PATS 8.5 */
  presetNameOrf2Burgenland,
  presetNameOrf2Karnten,
  presetNameOrf2Niederosterreich,
  presetNameOrf2Oberosterreich,
  presetNameOrf2Salzburg,
  presetNameOrf2Steiermark,
  presetNameOrf2Tirol,
  presetNameOrf2Voraelberg,
  presetNameOrf2Wien,
  presetNameArd,
  presetNameZdf,
  presetName123Tv,          /* PATS 8.4 */
  presetNameRtls,			/* PATS 8.5 */
  presetName3sat,
  presetNameBr3,
  presetNameHess3,
  presetNameN3,
  presetNameRb3,
  presetNameSfb3,
  presetNameSw3,
  presetNameWdr3,
  presetNameWdrl,
  presetNameMdr3,
  presetNameArte,
  presetNameDsf,
  presetNameVox,
  presetNameRtl2,
  presetNameEurosport,
  presetNameEurosport2,		/* PATS 8.5 */
  presetNameEurosportNews,	/* PATS 8.5 */
  presetNameKabel,
  presetNameSat1,
  presetNameRtl,
  presetNamePremiere,
  presetNameDwtv,
  presetNameOffenerKanal,
  presetNameBerlin2,
  presetNameBerlin1,
  presetName1atv,		/* PATS 8.5 */
  presetNameViva,
  presetNameViva2,
  presetNameSrtl,
  presetNameRtlc,
  presetNameNtv,
  presetNameFest,
  presetNameMuxx,
  presetNameExtra,
  presetNameNick,		/* PATS 8.5 */
  presetNameKdgi,		/* PATS 8.5 */
  presetNameDas4,		/* PATS 8.5 */
  presetNameOnyx,
  presetNameQvc,
  presetNameNickde,
  presetNameRnn7,       /* PATS 8.4 */
  presetNameHse,
  presetNameOrb1,
  presetNameOrb3,
  presetNameTm3,
  presetNamePhoen,
  presetNameKika,
  presetNameBr1,
  presetNameHr1,
  presetNameNdr3,
  presetNameRb1,
  presetNameSfb1,
  presetNameSdr,
  presetNameSwf,
  presetNameSr1,
  presetNameSdr1,
  presetNameWdr1,
  presetNameSwf1,
  presetNameMdr1,
  presetNameMdre,
  presetNameTv1,
  presetNameKa2,
  presetNameTv2,
  presetNameVt4,
  presetNameVtm,
  presetNameEt1,
  presetNameEt2,
  presetNameEt3,
  presetNameEt,
  presetNameSat,
  presetNameYle1,
  presetNameYle2,
  presetNameOwl3,
  presetNameDr1,
  presetNameTv2danemark,
  presetNameDr2,
  presetNameTv2Charlie,     /* PATS 8.4 */
  presetNameTv2Film,        /* PATS 8.4 */
  presetNameKanal5,         /* PATS 8.4 */
  presetNameAngliatv,
  presetNameBbcprime,
  presetNameBbcworld,
  presetNameBbc1,
  presetNameBbc2,
  presetNameBordertv,
  presetNameCarltonselect,
  presetNameCarltontv,
  presetNameCentraltv,
  presetNameCh4,
  presetNameChannel5,
  presetNameChanneltv,
  presetNameGrampiantv,
  presetNameGranadatv,
  presetNameHtv,
  presetNameItvnetwork,
  presetNameLwt,
  presetNameMeridian,
  presetNameMoviechannel,
  presetNameMtv,
  presetNameMusbo,		/* PATS 8.5 */
  presetNameNbceurope,
  presetNameRacingch,
  presetNameS4c,
  presetNameScifich,
  presetNameScottishtv,
  presetNameSkygold,
  presetNameSkymovieplus,
  presetNameSkynews,
  presetNameSkyone,
  presetNameSkysoaps,
  presetNameSkysport,
  presetNameSkysport2,
  presetNameSky2,
  presetNameSsvc,
  presetNameTyneteestv,
  presetNameUkliving,
  presetNameUlstertv,
  presetNameVh1,
  presetNameWestcountrytv,
  presetNameWiretv,
  presetNameYorkshiretv,
  presetNameBbcn,
  presetNameHtvfutureuse,
  presetNameVh1gerlang,
  presetNameFr2,
  presetNameFr3,
  presetNameAbi,
  presetNameAqui,
  presetNameCanj,
  presetNameJimmy,
  presetNameCanp,
  presetNameMeteo,
  presetNameLci,
  presetNameM6,
  presetNameMcm,
  presetNameParis,
  presetNamePlnet,
  presetNameRfo1,
  presetNameRfo2,
  presetNameSerie,
  presetNameTtoon,
  presetNameTeva,
  presetNameTf1,
  presetNameTlm,
  presetNameTlt,
  presetNameTmc,
  presetNameTn7,			/* PATS 8.5 */
  presetNameTn8,			/* PATS 8.5 */
  presetNameCt1,
  presetNameCt2,
  presetNameCt4S,			/* PATS 8.5 */
  presetNameCt24,			/* PATS 8.5 */
  presetNameNovatv,
  presetNameRtlTelevizija,	/* PATS 8.5 */
  presetNameNetwork2,
  presetNameRte1,
  presetNameTeilifis,
  presetNameFilm,
  presetNameNed1,
  presetNameNed2,
  presetNameNed3,
  presetNameRtl4,
  presetNameRtl5,
  presetNameTalpaTv,        /* PATS 8.4 */
  /*presetNameVeronica,*/	/* PATS 8.5 */
  presetNameSvt1,
  presetNameSvt2,
  presetNameSvt,
  presetNameTv4,
  presetNameBravo,
  presetNameChildrenschannel,
  presetNameCnn,
  presetNameDiscovery,
  presetNameDisneyuk,
  presetNameFamilych,
  presetNameGmtv,
  presetNameGranadaplus,
  presetNameGranadatimeshare,
  presetNameHistorych,
  presetNameLearningch,
  presetNameLivetv,
  presetNameSkytravel,
  presetNameUkgold,
  presetNameRtbf1,
  presetNameRtbf2,
  presetNameMtv1,
  presetNameMtv2,
  presetNameRai1,
  presetNameRai2,
  presetNameRai3,
  presetNameRete4,
  presetNameRetea,
  presetNameCanale5,
/* PATS 8.4 Italy Start */
    presetName7Gold,
    presetNameA1,
    presetNameAlice,
    presetNameBassanoTv,
    presetNameBoing,
    presetNameBoomerang,
    presetNameCanaleItalia,
    presetNameCartoonNetwork,
    presetNameCartoonNetwork1,
    presetNameCnnInternational,
	presetNameCuatro,		/* PATS 8.5 */
    presetNameDisneyChannel,
    presetNameDisneyChannel1,
    presetNameEntertainmentTv,
	presetNameEspansioneTv,			/* PATS 8.5 */
    presetNameEspnClassicSport,
    presetNameFox,
    presetNameFoxKids,
    presetNameFoxKids1,
    presetNameFoxlife,
    presetNameGxt,
    presetNameHistoryChannel,
    presetNameHistoryChannel1,
    presetNameLeonardo,
    presetNameMarcopolo,
    presetNameMatchMusic,
    presetNameMediasetPremium1,
    presetNameMediasetPremium2,
    presetNameMediasetPremium3,
    presetNameMediasetPremium4,
	presetNameMediasetPremium5,	/* PATS 8.5 */
	presetNameMediashopping,	/* PATS 8.5 */
    presetNameNatGeoChl,
    presetNameNatGeoChl1,
    presetNameNuvolari,
    presetNameNuovarete,
    presetNamePeopleTvRete7,
    presetNamePlanet,
    presetNamePlayhouseDisney,
    presetNamePlaylistItalia,
    presetNamePrimaTv,
    presetNameRadioItaliaTv,
	presetNameRadioTeleEuropa,	/* PATS 8.5 */
    presetNameRete7,
    presetNameRete8Vga,
    presetNameSciFiChannel,
	presetNameSenato,			/* PATS 8.5 */
	presetNameSitcom1,			/* PATS 8.5 */
	presetNameSitcom2,			/* PATS 8.5 */
	presetNameSitcom3,			/* PATS 8.5 */
	presetNameSitcom4,			/* PATS 8.5 */
	presetNameSitcom5,			/* PATS 8.5 */
    presetNameSkyCalcio1,
    presetNameSkyCalcio2,
    presetNameSkyCalcio3,
    presetNameSkyCalcio4,
    presetNameSkyCalcio5,
    presetNameSkyCalcio6,
    presetNameSkyCalcio7,
    presetNameSkyCalcio8,
    presetNameSkyCalcio9,
    presetNameSkyCalcio10,
    presetNameSkyCalcio11,
    presetNameSkyCalcio12,
    presetNameSkyCalcio13,
    presetNameSkyCalcio14,
    presetNameSkyCanale224,
    presetNameSkyCinema2,
    presetNameSkyCinema3,
    presetNameSkyCinema16_9,
    presetNameSkyCinemaAutore,
    presetNameSkyCinemaClassic,
    presetNameSkyCinemaMax,
    presetNameSkyDirrettaGol,
    presetNameSkyMeteo24,
    presetNameSkySports2,
    presetNameSkySports3,
    presetNameSkyTG24,
    presetNameSkyTv,
    presetNameSportItalia,
    presetNameStudioUniversal,
    presetNameSuperpippaChannel,
    presetNameTelesanterno,
    presetNameTelecentro,
	presetNameTeleradiocity,			/* PATS 8.5 */
	presetNameTeleradiocityGenova,		/* PATS 8.5 */
	presetNameTeleradiocityLombardia,	/* PATS 8.5 */
	presetNameTelestarLiguria,			/* PATS 8.5 */
	presetNameTelestarPiemontia,		/* PATS 8.5 */
	presetNameTelestarLombardia,		/* PATS 8.5 */
    presetNameTelestense,
    presetNameTelenova,
	presetNameTelevisiviaSuper3,		/* PATS 8.5 */
	presetNameTgNorba,					/* PATS 8.5 */
    presetNameToonDisney,
	presetNameTp9Telepuglia,			/* PATS 8.5 */
    presetNameVideolina,
/* PATS 8.4 Italy End */
  presetNameItalia1,
  presetNameItalia8Piemonte,	/* PATS 8.5 */
  presetNameItalia8Lombardio,	/* PATS 8.5 */
  presetNameTrs,
  /*presetNameTeleplus1,*/      /* PATS 8.4*/
  presetNameSkyCinema1,         /* PATS 8.4*/
  /*presetNameTeleplus2,*/      /* PATS 8.4*/
  presetNameSkySports1,         /* PATS 8.4*/
  presetNameTeleplus3,
  presetNameNrk1,
  presetNameNrk2,
  presetNameTv2norway,
  presetNameTvn,
  presetNameTvpolonia,
  presetNameTvp1,
  presetNameTvp2,
  presetNameC33,
  presetNameCanal9,     /* PATS 8.4 */
  presetNameCcv,        /* PATS 8.4 */
  presetNameClanTVE,	/* PATS 8.5 */
  presetNameEtb1,
  presetNameEtb2,
  presetNameLaOtra,		/* PATS 8.5 */
  presetNameLaSexta,	/* PATS 8.5 */
  presetNameLaNeox,		/* PATS 8.5 */
  presetNameLaNova,		/* PATS 8.5 */
  presetNamePunt2,      /* PATS 8.4 */
  presetNameTv3,
  presetNameTve1,
  presetNameTve2,
  presetNameAtv,
  presetNameCine5,
  presetNameShowtv,
  presetNameShowEuro,	/* PATS 8.5 */
  presetNameSupersport,
  presetNameAvrasya,
  presetNameTrt1,
  presetNameTrt2,
  presetNameTrt3,
  presetNameTrt4,
  presetNameTrtint,
  presetNameBarvot,
  presetNameEko,
  presetNameEurod,
  presetNameFun,
  presetNameGalak,
  presetNameKand,
  presetNameTgrt,
  presetNameTempo,
  presetNameTnt,
  presetNameEuronews,
  presetNameTv5,
/*  presetNameHrt, */	/* PATS 8.5 */
  presetNameRikisutvarpid,
  presetNameHr3,
  presetNameRtp1,
  presetNameRtp2,
  presetNameRtpaf,
  presetNameRtpi,
  presetNameRtpaz,
  presetNameRtpm,
  presetNameRtv38,
  /*presetNameWot51,*/
  presetNameBialystok,
  presetNameBydgoszcz,
  presetNameGdansk,
  presetNameGdanskt,
  presetNameKatowice,
  presetNameKrakow,
  presetNameLubin,
  presetNameLodz,
  presetNameRzeszow,
  presetNamePoznan,
  presetNameSzczecin,
  presetNameWroclaw,
  presetNameTvnPoland,
  presetNameCanalpPoland,
  presetNameCanalpPolandt,
  presetNameLaCinquieme,
  presetNameSlo1,
  presetNameSlo2,
  presetNameKc,
  presetNameSlo3,
  presetNameNdr1,
  presetNameMdrd,
  presetNamePhoenix,
  presetNameZulu,
  presetNameTvDanmark,
  presetNameStv1,
  presetNameStv2,
  presetNameTvJoj,			/* PATS 8.5 */
  presetName40Latino,		/* PATS 8.5 */
  presetName24Horas,		/* PATS 8.5 */
  presetNameAntena3,		/* PATS 8.5 */
  presetNameDUNA,
  presetNameRTV,
  presetNameCENTV,
  presetNameHTV,
  presetNameMERID,
/*  presetNameNICKE,*/		/* PATS 8.5 */
  presetNamePARA,
  presetNameQVC,
  presetNameVH1,
  presetNameJimtv,          /* PATS 8.0 */
  presetNameRtbfs,          /* PATS 8.0 */
  presetNameBra,            /* PATS 8.0 */
  presetNameHr,             /* PATS 8.0 */
  presetNameBox,            /* PATS 8.0 */
  presetNameV8,             /* PATS 8.0 */
  presetNameAnpl,           /* PATS 8.0 */
  presetNameDish,           /* PATS 8.0 */
  presetNameNet5,           /* PATS 8.0 */
  presetNameSbs6,           /* PATS 8.0 */
  presetNameAb3,            /* PATS 8.1 */
  presetNameAb4,            /* PATS 8.4 */
  presetNameTvnSiedem,      /* PATS 8.1 */
  presetNameTele5,          /* PATS 8.1 */
  presetNameTeled,			/* PATS 8.5 */
  presetNameTelem,			/* PATS 8.5 */
  presetNameTmsat,			/* PATS 8.5 */
  presetNameCameraDeputati,
  presetNameGayTV,
  presetNameRAINotizie24,	/* PATS 8.5 */
  presetNameRAIMed,
  presetNameRAISportSat,	/* PATS 8.5 */
  presetNameRAIEdu1,		/* PATS 8.5 */
  presetNameRAIEdu2,		/* PATS 8.5 */
  presetNameRAINettunoSat1,	/* PATS 8.5 */
  presetNameRAINettunoSat2,	/* PATS 8.5 */
  presetNameRAIDocFutura,	/* PATS 8.5 */
  presetNameRAIMosaico,
  presetNameRaisatAlbum,
  presetNameRaisatArt,
  presetNameRaisatCinema,
  presetNameRaisatCinemaWorld,	/* PATS 8.5 */
  presetNameRaisatExtra,		/* PATS 8.5 */
  presetNameRaisatFiction,
  presetNameRaisatGamberoRossoChannel,
  presetNameRaisatPremium,				/* PATS 8.5 */
  presetNameRaisatRagazzi,
  /*presetNameRaisatShow,*/				/* PATS 8.5 */
  /*presetNameRaisatGRossoInterattivo,*//* PATS 8.5 */
  presetNameRAITest2,					/* PATS 8.5 */
  presetNameRAIUtile,					/* PATS 8.5 */
  presetNameVideoItalia,
  presetNameCNBCEurope,
  presetNameKindernet,
  presetNameUkraine1plus1,
  presetNameM1Music,
  presetNameKanal6,
  presetNameStar4,
  presetNameStar5,
  presetNameStar6,
  presetNameStar7,
  presetNameStar8,
  presetNameStarMax,
  presetNameN24,
  presetNameTmf,
  presetNameRtl7,				/* PATS 8.5 */
  presetNameLa7,
  presetNameSat2000,
  presetNameAntenneCentre,
  presetNameAVSe,
  presetNameCanalC,
  presetNameCanalZoom,
  /*presetNameCanalPlus,*/      /* PATS 8.4 */
  presetNameBe1ana,             /* PATS 8.4 */
  /*presetNameCanalplusN1,*/    /* PATS 8.4 */
  presetNameBe1num,             /* PATS 8.4 */
  /*presetNameCanalplusN2,*/    /* PATS 8.4 */
  presetNameBeCine1,            /* PATS 8.4 */
  /*presetNameCanalplusN3,*/    /* PATS 8.4 */
  presetNameBeSport1,           /* PATS 8.4 */
  presetNameBe1plus1h,          /* PATS 8.4 */
  presetNameBeCine2,            /* PATS 8.4 */
  presetNameBeSport2,
  /*presetNameCanalplusVL1,*/	/* PATS 8.5 */
  /*presetNameCanalplusVLN1,*/  /* PATS 8.4 */
  /*presetNameCanalplusBlauw,*/     /* PATS 8.4 */	/*PATS 8.5 */
  /*presetNameCanalplusVLN2,*/  /* PATS 8.4 */
  /*presetNameCanalplusRood,*/      /* PATS 8.4 */  /* PATS 8.5 */
  presetNameFocusTV,
  presetNameCanalInfo,
  presetNameKanaal2,
  presetNameKanaal3,
  presetNameMCMBelgique,
  presetNameNoTele,
  presetNamePlugTv,             /* PATS 8.4 */
  presetNamePrimeSport,			/* PATS 8.5 */
  presetNamePrimeSport2,		/* PATS 8.5 */
  presetNamePrimeAction,		/* PATS 8.5 */
  presetNamePrimeOne,			/* PATS 8.5 */
  presetNameRingTV,
  presetNameRobTV,
  presetNameRTVKempen,
  presetNameRTVMechelen,
  presetNameSporza,             /* PATS 8.4 */
  presetNameTeleBruxelles,
  presetNameTeleMB,
  presetNameTelesambre,
  presetNameTelevesdre,
  presetNameTVBrussel,
  presetNameTVCom,
  presetNameTVLimburg,
  presetNameTVLux,
  presetNameVideoscope,
  presetNameVijfTv,             /* PATS 8.4 */
  presetNameVitaya,
  presetNameRTCTeleLiege,
  presetNameTvn24,
  presetNameSailingChannel,
  presetNameWtv,
  presetNameHrt1,				/* PATS 8.5 */
  presetNameHrt2,				/* PATS 8.5 */
  presetNameHrtPlus,				/* PATS 8.5 */
  presetNameTvpWarszawa,
  presetNameCanalZFr,
  presetNameCartoonNetworkNl,
  presetNameCartoonNetworkFr,
  presetNameKanaalZNl,
  presetNameLibertyChannelNl,
  presetNameLibertyChannelFr,
  presetNameLifeTv,				/* PATS 8.5 */
  presetNameTCMNl,
  presetNameTCMFr,
  presetNameDiscoveryCivilisations,
  presetNameDiscoveryItaly,
  presetNameDiscoveryScience,
  presetNameDiscoveryTravelandAdventure,
  presetNameMTVBrandNew,
  presetNameMTVHits,
  presetNameICTV,
  presetNameNovyKanal,
  presetNameAnimalPlanetBenelux,
  presetNameMTVNL,
  presetNameTVEInternacionalEurope,
  presetNamePrimaTV,
  presetNameTVPraha,
  presetNameTVHK,
  presetNameTVPardubice,
  presetNameTVBrno,
  /** Start-- Pats 8.6 */
  presetNameDMax,
  presetNameParla,
  presetNameComed,
  presetNameRbb1,
  presetNameRbb,
  presetNameOkto,
  presetNameStv,
  presetNameTv2Ne,
  presetNameMondo,
  presetNamePlay,
  presetNameTcs,
  presetNameTvi,
  presetNameNicke,
  presetNameKan,
  presetNamePoptv,
  presetNameCan4,
  presetNameRtl8          /* PATS 8.6 - IPM-65689  */
  /** End-- Pats 8.6 */
} PresetName;

static  Nat8 ROM presetnames[] = {
  /*                                                                        */
  /* The order in this table MUST MATCH the order in the Enum PresetName    */
  /*                                                                        */
  ' ',' ',' ',' ',' ',    /* presetNameOther */
  'T','E','L','E','Z',	  /* presetNameTelez*/
  'T','E','L','E','C',	  /* presetNameTelec */
  'Z','U','E','R','I',	  /* presetNameZueri */
  'T','E','L','E','B',    /* presetNameTeleb*/
  'M','1',' ',' ',' ',    /* presetNameM1*/
  'S','T','A','R',' ',    /* presetNameStar,*/
  'P','R','O','7',' ',    /* presetNamePro7,*/
  'T','O','P',' ',' ',    /* presetNameTpo,	*/
  'K','A','B','E','1',    /* presetNameKabe1,*/		/* PATS 8.5 */
  'S','M','T',' ',' ',    /* presetNameSMT,	*/		/* PATS 8.5 */
  'I','N','T','R','O',    /* presetNameIntro,*/		/* PATS 8.5 */
  'T','E','L','L',' ',    /* presetNameTell,*/		/* PATS 8.5 */
  'T','O','P',' ',' ',    /* presetNameTop,*/		/* PATS 8.5 */
  'T','S','O',' ',' ',    /* presetNameTso,	*/		/* PATS 8.5 */
  'T','V','O',' ',' ',    /* presetNameTvo,	*/		/* PATS 8.5 */
  'T','E','L','T','I',    /* presetNameTelti,*/		/* PATS 8.5 */
  'S','H','F',' ',' ',    /* presetNameShf,	*/		/* PATS 8.5 */
  'U','1',' ','T','V',    /* presetNameU1tv,*/		/* PATS 8.5 */
  'M','T','V','-','S',    /* presetNameMtvs,*/		/* PATS 8.5 */
  'S','F','1',' ',' ',    /* presetNameSf1,	*/
  'T','S','R','1',' ',    /* presetNameTsr1,*/
  'T','S','I','1',' ',    /* presetNameTsi1,*/
  'S','F','2',' ',' ',    /* presetNameSf2,*/
  'T','S','R','2',' ',    /* presetNameTsr2,*/
  'U','1',' ',' ',' ',    /* presetNameU1 */        /* PATS 8.4 */
  'T','S','I','2',' ',    /* presetNameTsi2,*/
  'S','R','G','-','S',    /* presetNameSrgs,*/
  'S','F','I',' ',' ',    /* presetNameSfi,*/  		/* PATS 8.5 */
  'O','R','F','1',' ',    /* presetNameOrf1,*/
  'O','R','F','2',' ',    /* presetNameOrf2,*/
  'O','R','F','3',' ',    /* presetNameOrf3,*/
  'O','R','F','S','P',    /* presetNameOrfsp,*/		/* PATS 8.5 */
  'T','W','1',' ',' ',    /* presetNameTw1,  */		/* PATS 8.5 */
  'N','I','-','V','I',    /* presetNameNivi, */		/* PATS 8.5 */
  'M','T','V','-','A',    /* presetNameMtva, */		/* PATS 8.5 */
  'O','R','F','2','B',    /* presetNameOrf2Burgenland,*/
  'O','R','F','2','K',    /* presetNameOrf2Karnten,*/
  'O','R','F','2','N',    /* presetNameOrf2Niederosterreich,*/
  'O','R','F','2','O',    /* presetNameOrf2Oberosterreich,*/
  'O','R','F','2','S',    /* presetNameOrf2Salzburg,*/
  'O','R','F','2','S',    /* presetNameOrf2Steiermark,*/
  'O','R','F','2','T',    /* presetNameOrf2Tirol,*/
  'O','R','F','2','V',    /* presetNameOrf2Voraelberg,*/
  'O','R','F','2','W',    /* presetNameOrf2Wien,*/
  'A','R','D',' ',' ',    /* presetNameArd,*/
  'Z','D','F',' ',' ',    /* presetNameZdf, */
  '1','2','3','T','V',    /* presetName123Tv */      /* PATS 8.4 */
  'R','T','L','-','S',    /* presetNameRtls */      /* PATS 8.5 */
  '3','S','A','T',' ',    /* presetName3sat,*/
  'B','R','3',' ',' ',    /* presetNameBr3,*/
  'H','E','S','S','3',    /* presetNameHess3,*/
  'N','3',' ',' ',' ',    /* presetNameN3, */
  'R','B','3',' ',' ',    /* presetNameRb3, */
  'S','F','B','3',' ',    /* presetNameSfb3,*/
  'S','W','3',' ',' ',    /* presetNameSw3, */
  'W','D','R','3',' ',    /* presetNameWdr3, */
  'W','D','R','-','L',    /* presetNameWdrl, */
  'M','D','R','3',' ',    /* presetNameMdr3, */
  'A','R','T','E',' ',    /* presetNameArte,*/
  'D','S','F',' ',' ',    /* presetNameDsf, */
  'V','O','X',' ',' ',    /* presetNameVox, */
  'R','T','L','2',' ',    /* presetNameRtl2,*/
  'E','U','S','P',' ',    /* presetNameEurosport,*/		/* PATS 8.5 */
  'E','U','S','P','2',    /* presetNameEurosport2,*/	/* PATS 8.5 */
  'E','U','S','P','N',    /* presetNameEurosportNews,*/	/* PATS 8.5 */
  'K','A','B','E','L',    /* presetNameKabel, */
  'S','A','T','1',' ',    /* presetNameSat1,*/
  'R','T','L',' ',' ',    /* presetNameRtl,*/
  'P','R','E','M','I',    /* presetNamePremiere,*/
  'D','W','T','V',' ',    /* presetNameDwtv, */
  'O','F','F','K',' ',    /* presetNameOffenerKanal,*/
  'B','L','N','2',' ',    /* presetNameBerlin2,*/
  'B','L','N','1',' ',    /* presetNameBerlin1, */
  '1','A','-','T','V',    /* presetName1atv,	 */
  'V','I','V','A',' ',    /* presetNameViva,	   */
  'V','I','V','A','2',    /* presetNameViva2,*/
  'S','-','R','T','L',    /* presetNameSrtl, */
  'R','T','L','-','C',    /* presetNameRtlc, */
  'N','-','T','V',' ',    /* presetNameNtv,  */
  'F','E','S','T',' ',    /* presetNameFest, */
  'M','U','X','X',' ',    /* presetNameMuxx, */
  'E','X','T','R','A',    /* presetNameExtra, */
  'N','I','C','K',' ',    /* presetNameNick,	*/		/* PATS 8.5 */
  'K','D','G',' ','I',    /* presetNameKdgi,	*/		/* PATS 8.5 */
  'D','A','S','4',' ',    /* presetNameDas4	    */		/* PATS 8.5 */
  'O','N','Y','X',' ',    /* presetNameOnyx, */
  'Q','V','C',' ',' ',    /* presetNameQvc, */
  'N','I','C','K','E',    /* presetNameNickde,*/
  'R','N','N','7',' ',    /* presetNameRnn7,*/      /* PATS 8.4 */
  'H','S','E',' ',' ',    /* presetNameHse,  */
  'O','R','B','1',' ',    /* presetNameOrb1, */
  'O','R','B','3',' ',    /* presetNameOrb3, */
  'T','M','3',' ',' ',    /* presetNameTm3,  */
  'P','H','O','E','N',    /* presetNamePhoen,*/
  'K','I','K','A',' ',    /* presetNameKika, */
  'B','R','1',' ',' ',    /* presetNameBr1,  */
  'H','R','1',' ',' ',    /* presetNameHr1,  */
  'N','D','R','3',' ',    /* presetNameNdr3, */
  'R','B','1',' ',' ',    /* presetNameRb1,  */
  'S','F','B','1',' ',    /* presetNameSfb1, */
  'S','D','R',' ',' ',    /* presetNameSdr,  */
  'S','W','F',' ',' ',    /* presetNameSwf,  */
  'S','R','1',' ',' ',    /* presetNameSr1,   */
  'S','D','R','1',' ',    /* presetNameSdr1,  */
  'W','D','R','1',' ',    /* presetNameWdr1, */
  'S','W','F','1',' ',    /* presetNameSwf1, */
  'M','D','R','1',' ',    /* presetNameMdr1, */
  'M','D','R','-','E',    /* presetNameMdre  */
  'E','E','N',' ',' ',    /* presetNameTv1,*/       /* PATS 8.4 */
  'K','A','2',' ',' ',    /* presetNameKa2  */
  'C','A','N','V',' ',    /* presetNameTv2, */
  'V','T','4',' ',' ',    /* presetNameVt4,*/
  'V','T','M',' ',' ',    /* presetNameVtm,*/
  'E','T','1',' ',' ',    /* presetNameEt1,*/
  'N','E','T',' ',' ',    /* presetNameEt2,*/
  'E','T','3',' ',' ',    /* presetNameEt3,*/
  'E','T',' ',' ',' ',    /* presetNameEt, */
  'S','R','G','-','S',    /* presetNameSat,*/
  'Y','L','E','1',' ',    /* presetNameYle1,*/
  'Y','L','E','2',' ',    /* presetNameYle2,*/
  'O','W','L','3',' ',    /* presetNameOwl3, */
  'D','R','1',' ',' ',    /* presetNameDr1,  */
  'T','V','2',' ',' ',    /* presetNameTv2danemark,*/
  'D','R','2',' ',' ',    /* presetNameDr2,*/
  'C','H','A','R','L',    /* presetNameTv2Charlie *//* PATS 8.4 */
  'T','V','2',' ','F',    /* presetNameTv2Film */   /* PATS 8.4 */
  'K','A','N',' ','5',    /* presetNameKanal5 */    /* PATS 8.4 */
  'A','N','G','L','I',    /* presetNameAngliatv,*/
  'B','B','C','P',' ',    /* presetNameBbcprime,*/
  'B','B','C','W',' ',    /* presetNameBbcworld,	*/
  'B','B','C','1',' ',    /* presetNameBbc1,*/
  'B','B','C','2',' ',    /* presetNameBbc2, */
  'B','O','R','T','V',    /* presetNameBordertv,*/
  'C','A','R','S','E',    /* presetNameCarltonselect,*/
  'C','A','R','L','T',    /* presetNameCarltontv,*/
  'C','E','N','T','V',    /* presetNameCentraltv, */
  'C','H','4',' ',' ',    /* presetNameCh4,	   */
  'C','H','5',' ',' ',    /* presetNameChannel5,  */
  'C','H','T','V',' ',    /* presetNameChanneltv, */
  'G','R','A','M','P',    /* presetNameGrampiantv,*/
  'G','R','A','N','A',    /* presetNameGranadatv, */
  'H','T','V',' ',' ',    /* presetNameHtv,	    */
  'I','T','V',' ',' ',    /* presetNameItvnetwork,  */
  'L','W','T',' ',' ',    /* presetNameLwt,	    */
  'M','E','R','I','D',    /* presetNameMeridian,    */
  'S','K','Y','M','O',    /* presetNameMoviechannel,*/
  'M','T','V',' ',' ',    /* presetNameMtv,	    */
  'M','U','S','B','O',    /* presetNameMusbo,	*/		/* PATS 8.5 */
  'N','B','C','E','U',    /* presetNameNbceurope,   */
  'R','A','C','I','N',    /* presetNameRacingch,    */
  'C','H','4',' ',' ',    /* presetNameS4c,	    */
  'S','C','I','F','I',    /* presetNameScifich,	    */
  'S','C','O','T','V',    /* presetNameScottishtv,  */
  'S','K','Y','G',' ',    /* presetNameSkygold,	    */
  'M','O','V','I','E',    /* presetNameSkymovieplus,*/
  'S','K','Y','N','E',    /* presetNameSkynews,	    */
  'S','K','Y','O','N',    /* presetNameSkyone,	    */
  'S','K','Y','S','O',    /* presetNameSkysoaps,   */
  'S','K','Y','S','P',    /* presetNameSkysport,   */
  'S','K','Y','S','2',    /* presetNameSkysport2,   */
  'S','K','Y','T','W',    /* presetNameSky2,	    */
  'S','S','V','C',' ',    /* presetNameSsvc,	   */
  'T','T','T','V',' ',    /*  presetNameTyneteestv, */
  'L','I','V','N','G',    /*  presetNameUkliving,   */
  'U','L','S','T','E',    /*  presetNameUlstertv, */
  'V','H','1',' ',' ',    /*  presetNameVh1,	    */
  'W','E','S','T',' ',    /*  presetNameWestcountrytv,*/
  'W','I','R','E',' ',    /*  presetNameWiretv,       */
  'Y','O','R','K',' ',    /*  presetNameYorkshiretv,  */
  'B','B','C','N',' ',    /*  presetNameBbcn,	      */
  'H','T','V',' ',' ',    /*  presetNameHtvfutureuse,*/
  'V','H','1',' ',' ',    /*  presetNameVh1gerlang,  */
  'F','R','2',' ',' ',    /*  presetNameFr2,	      */
  'F','R','3',' ',' ',    /*  presetNameFr3,	      */
  'A','B','1',' ',' ',    /* presetNameAbi,	      */
  'A','Q','U','I',' ',    /*  presetNameAqui,	      */
  'C','A','N','J',' ',    /*  presetNameCanj,	      */
  'J','I','M','M','Y',    /*  presetNameJimmy,	      */
  'C','A','N','+',' ',    /*  presetNameCanp,	     */
  'M','E','T','E','O',    /*  presetNameMeteo,	     */
  'L','C','I',' ',' ',    /*  presetNameLci,	     */
  'M','6',' ',' ',' ',    /*  presetNameM6,	     */
  'M','C','M',' ',' ',    /*  presetNameMcm,	     */
  'P','A','R','I','S',    /*  presetNameParis,	     */
  'P','L','N','E','T',    /*  presetNamePlnet,	     */
  'R','F','O','1',' ',    /*  presetNameRfo1,	     */
  'R','F','O','2',' ',    /*  presetNameRfo2,	     */
  'S','E','R','I','E',    /*  presetNameSerie,	     */
  'T','T','O','O','N',    /*  presetNameTtoon,	     */
  'T','E','V','A',' ',    /*  presetNameTeva,	     */
  'T','F','1',' ',' ',    /*  presetNameTf1,	     */
  'T','L','M',' ',' ',    /*  presetNameTlm,	     */
  'T','L','T',' ',' ',	  /*  presetNameTlt,	     */
  'T','M','C',' ',' ',    /*  presetNameTmc,	     */
  'T','N','7',' ',' ',    /*  presetNameTn7,	     */
  'T','N','8',' ',' ',    /*  presetNameTn8,	     */		/* PATS 8.5 */
  'C','T','1',' ',' ',    /*  presetNameCt1,	     */
  'C','T','2',' ',' ',    /*  presetNameCt2,	     */
  'C','T','4',' ','S',    /*  presetNameCt4S,	     */		/* PATS 8.5 */
  'C','T','2','4',' ',    /*  presetNameCt24,	     */		/* PATS 8.5 */
  'N','O','V','A',' ',    /*  presetNameNovatv,     */
  'R','T','L',' ','T',    /*  presetNameRtlTelevizija,*/	/* PATS 8.5 */
  'N','E','T','W','2',    /*  presetNameNetwork2,   */
  'R','T','E','1',' ',    /*  presetNameRte1,	     */
  'T','E','I','L','I',    /*  presetNameTeilifis,   */
  'F','I','L','M',' ',    /* presetNameFilm,	     */
  'N','E','D','1',' ',    /*  presetNameNed1,	    */
  'N','E','D','2',' ',    /*  presetNameNed2,	    */
  'N','E','D','3',' ',    /*  presetNameNed3,	    */
  'R','T','L','4',' ',    /*  presetNameRtl4,	    */
  'R','T','L','5',' ',    /*  presetNameRtl5,	    */
  'T','A','L','P','A',    /*  presetNameTalpaTv,    */      /* PATS 8.4 */
  /*'Y','O','R','I','N',  */  /*  presetNameVeronica,  */	/* PATS 8.5 */
  'S','V','T','1',' ',    /*  presetNameSvt1,	    */
  'S','V','T','2',' ',    /*  presetNameSvt2,	    */
  'S','V','T',' ',' ',    /*  presetNameSvt,	    */
  'T','V','4',' ',' ',    /*  presetNameTv4,	    */
  'B','R','A','V','O',    /*  presetNameBravo,	    */
  'C','H','I','L','D',    /*  presetNameChildrenschannel, */
  'C','N','N',' ',' ',    /*  presetNameCnn,	    */
  'D','I','S','C','O',    /*  presetNameDiscovery, */
  'D','I','S','N','E',   /*   presetNameDisneyuk,  */
  'F','A','M','I','L',    /*  presetNameFamilych, */
  'G','M','T','V',' ',    /*  presetNameGmtv,	    */
  'G','R','A','P','L',    /*  presetNameGranadaplus,*/
  'G','R','A','T','I',    /*  presetNameGranadatimeshare,*/
  'H','I','S','T','O',    /*  presetNameHistorych,	*/
  'L','E','A','R','N',    /*  presetNameLearningch,	*/
  'L','I','V','E',' ',    /*  presetNameLivetv,       */
  'S','K','Y','T','R',    /*  presetNameSkytravel,   */
  'G','O','L','D',' ',    /*  presetNameUkgold	      */
  'R','T','B','F','1',   /* presetNameRtbf1, */
  'R','T','B','F','2',   /* presetNameRtbf2, */
  'M','T','V','1',' ',   /* presetNameMtv1,    */
  'M','T','V','2',' ',   /* presetNameMtv2,	 */
  'R','A','I','1',' ',   /* presetNameRai1,	 */ /*Space needed or not?? DOC inconsistent*/
  'R','A','I','2',' ',   /* presetNameRai2,	 */
  'R','A','I','3',' ',   /* presetNameRai3,	  */
  'R','E','T','E','4',   /* presetNameRete4,	 */
  'R','E','T','E','A',   /* presetNameRetea,	  */
  'C','A','N','A','L',   /* presetNameCanale5,	  */
/* PATS 8.4 Italy Start */
  '7','G','O','L','D',   /*   presetName7Gold,*/
  'A','1',' ',' ',' ',   /*   presetNameA1,*/
  'A','L','I','C','E',   /*   presetNameAlice,*/
  'B','A','S','S','A',   /*   presetNameBassanoTv,*/
  'B','O','I','N','G',   /*   presetNameBoing,*/
  'B','O','O','M',' ',   /*   presetNameBoomerang,*/
  'C','A','N',' ','I',   /*   presetNameCanaleItalia,*/
  'C','A','R','T','O',   /*   presetNameCartoonNetwork,*/
  'C','A','R','T','1',   /*   presetNameCartoonNetwork1,*/
  'C','N','N',' ',' ',   /*   presetNameCnnInternational,*/
  'C','U','A','T','R',   /*   presetNameCuatro,  */	/* PATS 8.5 */
  'D','I','S','N','E',   /*   presetNameDisneyChannel,*/
  'D','I','S','N','1',   /*   presetNameDisneyChannel1,*/
  'E',' ','E','N','T',   /*   presetNameEntertainmentTv,*/
  'E','S','P','A','N',   /*   presetNameEspansioneTv,*/			/* PATS 8.5 */
  'E','S','P','N',' ',   /*   presetNameEspnClassicSport,*/
  'F','O','X',' ',' ',   /*   presetNameFox, */
  'K','I','D','S',' ',   /*   presetNameFoxKids,*/
  'K','I','D','S','1',   /*   presetNameFoxKids1,*/
  'F','O','X','L','I',   /*   presetNameFoxlife,*/
  'G','X','T',' ',' ',   /*   presetNameGxt,*/
  'H','I','S','T','O',   /*   presetNameHistoryChannel,*/
  'H','I','S','T','1',   /*   presetNameHistoryChannel1,*/
  'L','E','O','N','A',   /*   presetNameLeonardo,*/
  'M','A','R','C','O',   /*   presetNameMarcopolo,*/
  'M','A','T','C','H',   /*   presetNameMatchMusic,*/
  'P','R','E','M','1',   /*   presetNameMediasetPremium1,*/
  'P','R','E','M','2',   /*   presetNameMediasetPremium2,*/
  'P','R','E','M','3',   /*   presetNameMediasetPremium3,*/
  'P','R','E','M','4',   /*   presetNameMediasetPremium4,*/
  'P','R','E','M','5',   /*   presetNameMediasetPremium5,*/	/* PATS 8.5 */
  'M','E','D','I','A',   /*   presetNameMediashopping,*/	/* PATS 8.5 */
  'N','G','C',' ',' ',   /*   presetNameNatGeoChl,*/
  'N','G','C','+','1',   /*   presetNameNatGeoChl1,*/
  'N','U','V','O',' ',   /*   presetNameNuvolari,*/
  'N','U','O','V','A',   /*   presetNameNuovarete,*/
  'R','E','T','E','7',   /*   presetNamePeopleTvRete7,*/
  'P','L','A','N','E',   /*   presetNamePlanet,*/
  'P','L','A','Y','D',   /*   presetNamePlayhouseDisney,*/
  'P','L','A','Y','L',   /*   presetNamePlaylistItalia,*/
  'P','R','I','M','A',   /*   presetNamePrimaTv,*/
  'R','A','D','I','O',   /*   presetNameRadioItaliaTv,*/
  'R','T','E',' ',' ',   /*   presetNameRadioTeleEuropa,*/	/* PATS 8.5 */
  'R','E','T','E','7',   /*   presetNameRete7,*/
  'R','E','T','E','8',   /*   presetNameRete8Vga,*/
  'S','C','I','F','I',   /*   presetNameSciFiChannel,*/
  'S','E','N','A','T',   /*   presetNameSenato,*/			/* PATS 8.5 */
  'S','I','T','C','1',   /*   presetNameSitcom1,*/			/* PATS 8.5 */
  'S','I','T','C','2',   /*   presetNameSitcom2,*/			/* PATS 8.5 */
  'S','I','T','C','3',   /*   presetNameSitcom3,*/			/* PATS 8.5 */
  'S','I','T','C','4',   /*   presetNameSitcom4,*/			/* PATS 8.5 */
  'S','I','T','C','5',   /*   presetNameSitcom5,*/			/* PATS 8.5 */
  'C','A','L','1',' ',   /*   presetNameSkyCalcio1,   */
  'C','A','L','2',' ',   /*   presetNameSkyCalcio2,*/
  'C','A','L','3',' ',   /*   presetNameSkyCalcio3,*/
  'C','A','L','4',' ',   /*   presetNameSkyCalcio4,*/
  'C','A','L','5',' ',   /*   presetNameSkyCalcio5,*/
  'C','A','L','6',' ',   /*   presetNameSkyCalcio6,*/
  'C','A','L','7',' ',   /*   presetNameSkyCalcio7,*/
  'C','A','L','8',' ',   /*   presetNameSkyCalcio8,*/
  'C','A','L','9',' ',   /*   presetNameSkyCalcio9,*/
  'C','A','L','1','0',   /*   presetNameSkyCalcio10,*/
  'C','A','L','1','1',   /*   presetNameSkyCalcio11,*/
  'C','A','L','1','2',   /*   presetNameSkyCalcio12,*/
  'C','A','L','1','3',   /*   presetNameSkyCalcio13,*/
  'C','A','L','1','4',   /*   presetNameSkyCalcio14,*/
  'C','A','2','2','4',   /*   presetNameSkyCanale224,*/
  'C','I','N','E','2',   /*   presetNameSkyCinema2,*/
  'C','I','N','E','3',   /*   presetNameSkyCinema3,*/
  'C','I','N','1','6',   /*   presetNameSkyCinema16_9,*/
  'C','I','N','E','A',   /*   presetNameSkyCinemaAutore,*/
  'C','I','N','E','C',   /*   presetNameSkyCinemaClassic,*/
  'C','I','N','E','M',   /*   presetNameSkyCinemaMax,*/
  'D','I','R','G','O',   /*   presetNameSkyDirrettaGol,*/
  'M','E','T','E','O',   /*   presetNameSkyMeteo24,*/
  'S','P','O','R','2',   /*   presetNameSkySports2,*/
  'S','P','O','R','3',   /*   presetNameSkySports3,*/
  'T','G','2','4',' ',   /*   presetNameSkyTG24,*/
  'S','K','Y',' ',' ',   /*   presetNameSkyTv,*/
  'S','P','O','R','T',   /*   presetNameSportItalia,*/
  'S','T','U','D','I',   /*   presetNameStudioUniversal,*/
  'S','U','P','E','R',   /*   presetNameSuperpippaChannel,*/
  'S','A','N','T','E',   /*   presetNameTelesanterno,*/
  'C','E','N','T','R',   /*   presetNameTelecentro,*/
  'T','R','C',' ',' ',   /*   presetNameTeleradiocity,*/			/* PATS 8.5 */
  'T','R','C',' ','G',   /*   presetNameTeleradiocityGenova,*/		/* PATS 8.5 */
  'T','R','C',' ','L',   /*   presetNameTeleradiocityLombardia,*/	/* PATS 8.5 */
  'T','S',' ','L','I',   /*   presetNameTelestarLiguria,*/			/* PATS 8.5 */
  'T','S',' ','P','I',   /*   presetNameTelestarPiemontia,*/		/* PATS 8.5 */
  'T','S',' ','L','O',   /*   presetNameTelestarLombardia,*/		/* PATS 8.5 */
  'S','T','E','N','S',   /*   presetNameTelestense,*/
  'T','E','L','E','N',   /*   presetNameTelenova,*/
  'S','U','P','E','3',   /*   presetNameTelevisiviaSuper3 */		/* PATS 8.5 */
  'T','G',' ','N','O',   /*   presetNameTgNorba */					/* PATS 8.5 */
  'T','O','O','N',' ',   /*   presetNameToonDisney,*/
  'T','P','9',' ',' ',   /*   presetNameTp9Telepuglia */			/* PATS 8.5 */
  'V','I','D','L','I',   /*   presetNameVideolina,*/
/* PATS 8.4 Italy End */
  'I','T','A','L','I',   /* presetNameItalia1,	  */
  'I','T','8','P','I',   /* presetNameItalia8Piemonte,*/	/* PATS 8.5 */
  'I','T','8','L','O',   /* presetNameItalia8Lombardio,*/	/* PATS 8.5 */
  'T','R','S',' ',' ',   /* presetNameTrs,	   */
  /*'T','E','L','E','1',*/   /* presetNameTeleplus1,  */    /* PATS 8.4*/
  'C','I','N','E','1',   /* presetNameSkyCinema1,  */       /* PATS 8.4*/
  /*'T','E','L','E','2',*/   /* presetNameTeleplus2,  */    /* PATS 8.4*/
  'S','P','O','R','1',   /*presetNameSkySports1*/           /* PATS 8.4*/
  'T','E','L','E','3',   /* presetNameTeleplus3,   */
  'N','R','K','1',' ',   /* presetNameNrk1,	   */
  'N','R','K','2',' ',   /* presetNameNrk2,	    */
  'T','V','2',' ',' ',   /* presetNameTv2norway,   */
  'T','V','N',' ',' ',   /* presetNameTvn,	    */
  'T','V','P','L','N',   /* presetNameTvpolonia,   */
  'T','V','P','1',' ',   /* presetNameTvp1,	     */
  'T','V','P','2',' ',   /* presetNameTvp2,   	     */
  'C','3','3',' ',' ',   /* presetNameC33,   */
  'C','A','N',' ','9',   /* presetNameCanal9 */     /* PATS 8.4 */
  'C','C','V',' ',' ',   /* presetNameCcv */        /* PATS 8.4 */
  'C','L','A','N',' ',   /* presetNameClanTVE,*/	/* PATS 8.5 */
  'E','T','B','1',' ',   /* presetNameEtb1,   */
  'E','T','B','2',' ',   /* presetNameEtb2,   */
  'O','T','R','A',' ',   /* presetNameLaOtra,  */	/* PATS 8.5 */
  'S','E','X','T','A',   /* presetNameLaSexta, */	/* PATS 8.5 */
  'N','E','O','X',' ',   /* presetNameLaNeox,  */	/* PATS 8.5 */
  'N','O','V','A',' ',   /* presetNameLaNova,  */	/* PATS 8.5 */
  'P','U','N','T','2',   /* presetNamePunt2 */      /* PATS 8.4 */
  'T','V','3',' ',' ',   /* presetNameTv3,     */
  'T','V','E','1',' ',   /* presetNameTve1,   */
  'T','V','E','2',' ',   /* presetNameTve2,    */
  'A','T','V',' ',' ',   /* presetNameAtv,     */
  'C','I','N','E','5',   /* presetNameCine5,   */
  'S','H','O','W',' ',   /* presetNameShowtv,	 */
  'S','H','O','W','E',   /* presetNameShowEuro,	 */	/* PATS 8.5 */
  'S','U','P','E','R',   /* presetNameSupersport, */
  'A','V','R','A','S',   /* presetNameAvrasya,	 */
  'T','R','T','1',' ',   /* presetNameTrt1,	 */
  'T','R','T','2',' ',   /* presetNameTrt2,	  */
  'T','R','T','3',' ',   /* presetNameTrt3,	  */
  'T','R','T','4',' ',   /* presetNameTrt4,	 */
  'T','R','T','I','N',   /* presetNameTrtint,	 */
  'B','R','A','V','O',   /* presetNameBarvot,	 */
  'E','K','O',' ',' ',   /* presetNameEko,	 */
  'E','U','R','O','D',   /* presetNameEurod,	 */
  'F','U','N',' ',' ',   /* presetNameFun,	 */
  'G','A','L','A','K',   /* presetNameGalak,	 */
  'K','A','N','D',' ',   /* presetNameKand,	  */
  'T','G','R','T',' ',   /* presetNameTgrt,	 */
  'T','E','M','P','O',   /* presetNameTempo,	 */
  'T','N','T',' ',' ',   /* presetNameTnt*/
  'E','U','-','N','E',   /* presetNameEuronews, */
  'T','V','5',' ',' ',   /*presetNameTv5,*/
/*  'H','R','T',' ',' ',  */ /*presetNameHrt, */		/* PATS 8.5 */
  'R','I','K','I',' ',   /*presetNameRikisutvarpid,*/
  'H','R','3',' ',' ',   /* presetNameHr3 */
  'R','T','P','1',' ',   /*,presetNameRtp1*/
  'R','T','P','2',' ',   /*,presetNameRtp2*/
  'R','T','P','A','F',   /*,presetNameRtpaf*/
  'R','T','P','I',' ',   /*,presetNameRtpi*/
  'R','T','P','A','Z',   /*,presetNameRtpaz*/
  'R','T','P','M',' ',   /*,presetNameRtpm*/
  'R','T','V','3','8',   /*presetNameRtv38,*/
  /*'W','O','T',' ',' ',*/   /*presetNameWot51,*/
  'B','I','A','L','Y',   /*presetNameBialystok,*/
  'B','Y','D','G',' ',   /*presetNameBydgoszcz,*/
  'T','V','G',' ',' ',   /*presetNameGdansk,*/
  'T','V','G',' ',' ',   /*presetNameGdanskt,*/
  'T','V','K','C','E',   /*presetNameKatowice,*/
  'K','R','A','K',' ',   /*presetNameKrakow,*/
  'T','V','L','U','B',   /*presetNameLubin,*/
  'L','O','D','Z',' ',   /*presetNameLodz,*/
  'R','Z','E','S','Z',   /*presetNameRzeszow,*/
  'T','V','P','Z','N',   /*presetNamePoznan,*/
  'S','Z','C','Z','E',   /*presetNameSzczecin,*/
  'W','R','O','C',' ',   /*presetNameWroclaw,*/
/*'P','L','S','A','T', */  /*presetNamePolsat,*/
/*'P','L','S','A','2', */  /*presetNamePoisat2,*/
  'T','V','N',' ',' ',   /*presetNameTvnPoland,*/
  'C','A','N','A','L',   /*presetNameCanalpPoland,*/
  'C','A','N','A','L',   /*presetNameCanalpPolandt*/
  'L','A','5',' ',' ',   /*presetNameLaCinquieme*/
  'S','L','O','1',' ',   /*presetNameSlo1,*/
  'S','L','O','2',' ',   /*presetNameSlo2,*/
  'K','C',' ',' ',' ',   /*presetNameKc,*/
  'S','L','O','3',' ',    /*presetNameSlo3*/
  'N','D','R','1',' ',    /* presetNameNdr1, */
  'M','D','R','-','D',    /* presetNameMdrd, */
  'P','H','O','E','N',    /* presetNamePhoenix,*/
  'Z','U','L','U',' ',    /*presetNameZulu*/
  'T','V','D','A','N',    /*presetNameTvDanmark*/       /* PATS 8.4 */
  'S','T','V','1',' ',    /*  presetNameStv1,	    */
  'S','T','V','2',' ',    /*  presetNameStv2,	    */
  'T','V','J','O','J',    /*  presetNameTvJoj,	    */	/* PATS 8.5 */
  '4','0',' ','L','A',   /*  presetName40Latino,   */	/* PATS 8.5 */
  '2','4',' ','H','O',    /*  presetName24Horas,    */	/* PATS 8.5 */
  'A','N','T','E','3',    /*  presetNameAntena3		*/	/* PATS 8.5 */
  'D','U','N','A',' ',    /*presetNameDUNA,*/
  'R','T','V',' ',' ',   /*presetNameRTV,*/
  'C','E','N','T','V',   /*presetNameCENTV,*/
  'H','T','V',' ',' ',   /*presetNameHtv,*/
  'M','E','R','I','D',   /*presetNameMERID,*/
  /*'N','I','C','K','E', */  /*presetNameNICKE,*/		/* PATS 8.5 */
  'P','A','R','A',' ',   /*presetNamePARA,*/
  'Q','V','C',' ',' ',   /*presetNameQvc,*/
  'V','H','1',' ',' ',   /*presetNameVH1*/
  'J','I','M','T','V',   /*presetNameJimtv*/            /* PATS 8.0 */
  'R','T','B','F','S',   /*presetNameRtbfs*/            /* PATS 8.0 */
  'B','R','-','A',' ',   /*presetNameBra*/              /* PATS 8.0 */
  'H','R',' ',' ',' ',   /*presetNameHr*/               /* PATS 8.0 */
  'B','O','X',' ',' ',   /*presetNameBox*/              /* PATS 8.0 */
  'V','8',' ',' ',' ',   /*presetNameV8*/               /* PATS 8.0 */
  'A','N','-','P','L',   /*presetNameAnpl*/             /* PATS 8.0 */
  'D','I','S','-','H',   /*presetNameDish*/             /* PATS 8.0 */
  'N','E','T','5',' ',   /*presetNameNet5*/             /* PATS 8.0 */
  'S','B','S','6',' ',   /*presetNamesbs6*/             /* PATS 8.0 */
  'A','B','3',' ',' ',   /*presetNameAb3*/              /* PATS 8.1 */
  'A','B','4',' ',' ',   /*presetNameAb4*/              /* PATS 8.4 */
  'T','V','N',' ','S',   /*presetNameTvnSiedem*/        /* PATS 8.1 */
  'T','E','L','E','5',   /*presetNameTele5*/            /* PATS 8.1 */
  'T','E','L','E','D',   /*presetNameTeled*/            /* PATS 8.5 */
  'T','E','L','E','M',   /*presetNameTelem*/            /* PATS 8.5 */
  'T','M','S','A','T',   /*presetNameTmsat*/            /* PATS 8.5 */
  'C','A','M','D','E',   /*presetNameCameraDeputati*/
  'G','A','Y','T','V',   /*presetNameGayTV*/
  'N','E','W','S',' ',   /*presetNameRAINotizie24*/		/* PATS 8.5 */
  'M','E','D',' ',' ',   /*presetNameRAIMed*/
  'S','P','O','R','T',   /*presetNameRAISportSat*/		/* PATS 8.5 */
  'E','D','U',' ','1',   /*presetNameRAIEdu1*/			/* PATS 8.5 */
  'E','D','U',' ','2',   /*presetNameRAIEdu2*/			/* PATS 8.5 */
  'N','E','T',' ','1',   /*presetNameRAINettunoSat1*/	/* PATS 8.5 */
  'N','E','T',' ','2',   /*presetNameRAINettunoSat2*/	/* PATS 8.5 */
  'R','A','I','D','F',   /*presetNameRAIDocFutura*/		/* PATS 8.5 */
  'M','O','S','A','I',   /*presetNameRAIMosaico*/
  'R','S',' ','A','L',   /*presetNameRaisatAlbum*/
  'R','S',' ','A','R',   /*presetNameRaisatArt*/
  'R','S',' ','C',' ',   /*presetNameRaisatCinema*/
  'R','S',' ','C','W',   /*presetNameRaisatCinemaWorld*//* PATS 8.5 */
  'R','S',' ','E','X',   /*presetNameRaisatExtra*/		/* PATS 8.5 */
  'R','S',' ','F',' ',   /*presetNameRaisatFiction*/
  'R','S',' ','G','R',   /*presetNameRaisatGamberoRossoChannel*/
  'R','S',' ','P','R',   /*presetNameRaisatPremium*/	/* PATS 8.5 */
  'R','S',' ','R',' ',   /*presetNameRaisatRagazzi*/
  /*'R','S',' ','S',' ', */  /*presetNameRaisatShow*/		/* PATS 8.5 */
  /*'R','S',' ','R','I', */  /*presetNameRaisatGRossoInterattivo*//* PATS 8.5 */
  'R','A','I','T','2',   /*presetNameRAITest2*/				/* PATS 8.5 */
  'R','A','I','U','T',   /*presetNameRAIUtile*/				/* PATS 8.5 */
  'V','I','D','E','O',   /*presetNameVideoItalia*/
  'C','N','B','C',' ',   /*presetNameCNBCEurope*/
  'V','E','R','O','N',   /*presetNameKindernet*/
  '1','+','1',' ',' ',   /*presetNameUkraine1plus1*/
  'M','1',' ',' ',' ',   /*presetNameM1Music*/
  'K','A','N',' ','6',   /*presetNameKanal6*/
  'S','T','A','R','4',   /*presetNameStar4*/
  'S','T','A','R','5',   /*presetNameStar5*/
  'S','T','A','R','6',   /*presetNameStar6*/
  'S','T','A','R','7',   /*presetNameStar7*/
  'S','T','A','R','8',   /*presetNameStar8*/
  'S','T','A','R','M',   /*presetNameStarMax*/
  'N','2','4',' ',' ',   /*presetNameN24*/
  'T','M','F',' ',' ',   /*presetNameTmf*/
  'R','T','L','7',' ',   /*presetNameRtl7*/					/* PATS 8.5 */
  'L','A','7',' ',' ',   /*presetNameLa7*/
  'S','2','0','0','0',   /*presetNameSat2000*/
  'C','E','N','T','R',   /*presetNameAntenneCentre,*/
  'A','V','S','E',' ',   /*presetNameAVSe*/
  'C','A','N',' ','C',   /*presetNameCanalC*/
  'Z','O','O','M',' ',   /*presetNameCanalZoom*/
  /*'C','A','N','+',' ',*/   /*presetNameCanalPlus*/        /* PATS 8.4 */
  'B','E','1',' ','A',   /*presetNameBe1ana*/               /* PATS 8.4 */
  /*'C','+',' ','N','1',*/   /*presetNameCanalplusN1*/      /* PATS 8.4 */
  'B','E','1',' ','N',   /*presetNameBe1num*/               /* PATS 8.4 */
  /*'C','+',' ','N','2',*/   /*presetNameCanalplusN2*/      /* PATS 8.4 */
  'C','I','N','E','1',   /*presetNameBeCine1*/              /* PATS 8.4 */
  /*'C','+',' ','N','3',*/   /*presetNameCanalplusN3*/      /* PATS 8.4 */
  'S','P','O','R','1',   /*presetNameBeSport1*/             /* PATS 8.4 */
  '1','+','1','H',' ',   /*presetNameBe1plus1h*/            /* PATS 8.4 */
  'C','I','N','E','2',   /*presetNameBeCine2*/              /* PATS 8.4 */
  'S','P','O','R','2',   /*presetNameBeSport2*/             /* PATS 8.4 */
  /*'V','L','1',' ',' ', */  /*presetNameCanalplusVL1*/		/* PATS 8.5 */
  /*'V','L','N','1',' ',*/   /*presetNameCanalplusVLN1*/    /* PATS 8.4 */
  /*'B','L','A','U','W',*/   /*presetNameCanalplusBlauw*/   /* PATS 8.4 */	/*PATS 8.5 */
  /*'V','L','N','2',' ',*/   /*presetNameCanalplusVLN2*/    /* PATS 8.4 */
  /*'R','O','O','D',' ',*/ /*presetNameCanalplusRood*/      /* PATS 8.4 */ /* PATS 8.5 */
  'F','O','C','U','S',   /*presetNameFocusTV*/
  'I','N','F','O',' ',   /*presetNameCanalInfo*/
  'K','A','2',' ',' ',   /*presetNameKanaal2*/
  'K','A','N',' ','3',   /*presetNameKanaal3*/
  'M','C','M',' ','B',   /*presetNameMCMBelgique*/
  'N','O',' ',' ',' ',   /*presetNameNoTele*/
  'P','L','U','G',' ',   /*presetNamePlugTv*/               /* PATS 8.4 */
  'P','R','S','P',' ',   /*presetNamePrimeSport*/           /* PATS 8.5 */
  'P','R','S','P','2',   /*presetNamePrimeSport2*/          /* PATS 8.5 */
  'P','R','A','C','T',   /*presetNamePrimeAction*/          /* PATS 8.5 */
  'P','R','O','N','E',   /*presetNamePrimeOne*/				/* PATS 8.5 */
  'R','I','N','G',' ',   /*presetNameRingTV*/
  'R','O','B',' ',' ',   /*presetNameRobTV*/
  'K','E','M','P',' ',   /*presetNameRTVKempen*/
  'M','E','C','H',' ',   /*presetNameRTVMechelen*/
  'S','P','O','R','Z',   /*presetNameSporza*/               /* PATS 8.4 */
  'B','R','U','X','E',   /*presetNameTeleBruxelles*/
  'M','B',' ',' ',' ',   /*presetNameTeleMB*/
  'S','A','M','B','R',   /*presetNameTelesambre*/
  'V','E','S','D','R',   /*presetNameTelevesdre*/
  'T','V',' ','B','R',   /*presetNameTVBrussel*/
  'C','O','M',' ',' ',   /*presetNameTVCom*/
  'T','V','L','I','M',   /*presetNameTVLimburg*/
  'L','U','X',' ',' ',   /*presetNameTVLux*/
  'V','I','D','E','O',   /*presetNameVideoscope*/
  'V','I','J','F',' ',   /*presetNameVijfTv*/               /* PATS 8.4 */
  'V','I','T','A','Y',   /*presetNameVitaya*/
  'L','I','E','G','E',   /*presetNameRTCTeleLiege*/
  'T','V','N','2','4',   /*presetNameTvn24*/
  'S','A','I','L',' ',   /*presetNameSailingChannel*/
  'W','T','V',' ',' ',   /*presetNameWtv*/
  'H','R','T','1',' ',	 /*presetNameHrt1*/					/* PATS 8.5 */
  'H','R','T','2',' ',	 /*presetNameHrt2*/					/* PATS 8.5 */
  'H','R','T','P','L',	 /*presetNameHrtPlus*/					/* PATS 8.5 */
  'W','A','R','S','Z',   /*presetNameTvpWarszawa*/
  'C','A','N',' ','Z',   /*presetNameCanalZFr*/
  'C','A','R','T','O',   /*presetNameCartoonNetworkNl*/
  'C','A','R','T','O',   /*presetNameCartoonNetworkFr*/
  'K','A','N',' ','Z',   /*presetNameKanaalZNl*/
  'L','I','B','E','R',   /*presetNameLibertyChannelNl*/
  'L','I','B','E','R',   /*presetNameLibertyChannelFr*/
  'L','I','F','E',' ',   /*presetNameLifeTv*/				/* PATS 8.5 */
  'T','C','M',' ',' ',   /*presetNameTCMNl*/
  'T','C','M',' ',' ',   /*presetNameTCMFr*/
  'D','I','S',' ','C',   /*presetNameDiscoveryCivilisations*/
  'D','I','S',' ','I',   /*presetNameDiscoveryItaly*/
  'D','I','S',' ','S',   /*presetNameDiscoveryScience*/
  'D','I','S',' ','T',   /*presetNameDiscoveryTravelandAdventure*/
  'M','T','V',' ','N',   /*presetNameMTVBrandNew*/
  'M','T','V',' ','H',   /*presetNameMTVHits*/
  'I','C','T','V',' ',   /*presetNameICTV*/
  'N','O','V','Y',' ',   /*presetNameNovyKanal*/
  'A','N','-','P','L',   /*presetNameAnimalPlanetBenelux*/
  'M','T','V',' ',' ',   /*presetNameMTVNL*/
  'T','V','E',' ',' ',   /*presetNameTVEInternacionalEurope*/
  'P','R','I','M','A',   /*presetNamePrimaTV*/
  'P','R','A','H','A',   /*presetNameTVPraha*/
  'T','V',' ','H','K',   /*presetNameTVHK*/
  'P','A','R','D','U',   /*presetNameTVPardubice*/
  'B','R','N','O',' ',    /*presetNameTVBrno*/

  'D','M','A','X',' ',    /*  presetNameDMax,*/
  'P','A','R','L','A',  	/*  presetNameParla,*/
  'C','O','M','E','D',  	/*  presetNameComed,*/
  'R','B','B','1',' ',      /*  presetNameRbb1,*/
  'R','B','B',' ',' ',  	/*  presetNameRbb,*/
  'O','K','T','O',' ',  	/*  presetNameOkto,*/
  'S','T','V',' ',' ',  	/*  presetNameStv,*/
  'T','V','2','N','E',  	/*  presetNameTv2Ne,*/
  'M','O','N','D','O',  	/*  presetNameMondo,*/
  'P','L','A','Y',' ',  	/*  presetNamePlay,*/
  'T','C','S',' ',' ',  	/*  presetNameTcs,*/
  'T','V','I',' ',' ',  	/*  presetNameTvi,*/
  'N','I','C','K','E',  	/*  presetNameNicke,*/
  'K','A','N',' ','A',  	/*  presetNameKan,*/
  'P','O','P','T','V',  	/*  presetNamePoptv,*/
  'C','A','N',' ','4',  	/*  presetNameCan4*/
  'R','T','L','8',' ',  	/*  presetNameRtl8*/
  };

static Nat16 ROM VpsCniTable[] = {
/*  network#, CountryNetwork(s),               presetname */
        1,       0x0481,                        presetNameTelez,
        1,       0x0482,                        presetNameTelec,
        /*1,       0x0483,                        presetNameZueri,*/
        1,       0x0484,                        presetNameTeleb,
        1,       0x0485,                        presetNameM1,
        1,       0x0486,                        presetNameStar,
        1,       0x0487,                        presetNamePro7,
        1,       0x0488,						presetNameTpo,			/* PATS 8.5 */
		1,       0x048A,                        presetNameKabe1,		/* PATS 8.5 */
		1,       0x048D,                        presetNameSmt,			/* PATS 8.5 */
		1,       0x048E,                        presetNameIntro,		/* PATS 8.5 */
		1,       0x048F,                        presetNameTell,			/* PATS 8.5 */
		1,       0x0490,                        presetNameTop,			/* PATS 8.5 */
		1,       0x0491,                        presetNameTso,			/* PATS 8.5 */
		1,       0x0492,                        presetNameTvo,			/* PATS 8.5 */
		1,       0x0493,                        presetNameTelti,		/* PATS 8.5 */
		1,       0x0494,                        presetNameShf,			/* PATS 8.5 */
		1,       0x0495,                        presetNameU1tv,			/* PATS 8.5 */
		1,       0x0496,                        presetNameMtvs,			/* PATS 8.5 */
        1,       0x04C1,                 		presetNameSf1,
        1,       0x04C2,                        presetNameTsr1,
        1,       0x04C3,                        presetNameTsi1,
        1,       0x04C7,                        presetNameSf2,
        1,       0x04C8,                        presetNameTsr2,
        1,       0x04C9,                        presetNameTsi2,
        1,       0x04CA,                        presetNameSrgs,
        1,       0x04CC,                        presetNameSfi,			/* PATS 8.5 */
		1,       0x0AC1,                        presetNameOrf1,
        1,       0x0AC2,                        presetNameOrf2,
        1,       0x0AC3,                        presetNameOrf3,
		1,		 0x0AC4,						presetNameOrfsp,	/* PATS 8.5 */
		1,		 0x0AC7,						presetNameTw1,		/* PATS 8.5 */
		1,		 0x0AC8,						presetNameNivi,		/* PATS 8.5 */
		1,		 0x0AC9,						presetNameMtva,		/* PATS 8.5 */
        1,       0x0ACA,                        presetNameAtv,      /* PATS 8.1 */
        1,       0x0ACB,                        presetNameOrf2Burgenland,
        1,       0x0ACC,                        presetNameOrf2Karnten,
        1,       0x0ACD,                        presetNameOrf2Niederosterreich,
        1,       0x0ACE,                        presetNameOrf2Oberosterreich,
        1,       0x0ACF,                        presetNameOrf2Salzburg,
        1,       0x0AD0,                        presetNameOrf2Steiermark,
        1,       0x0AD1,                        presetNameOrf2Tirol,
        1,       0x0AD2,                        presetNameOrf2Voraelberg,
        1,       0x0AD3,                        presetNameOrf2Wien,
        4,       0x0DC1,0x0DC3,0x0DC4,0x0DC5,   presetNameArd,
        2,       0x0DC2, 0x0DC3,                presetNameZdf,
        1,       0x0DC7,                        presetName3sat,
        3,       0x0DCB, 0x0DCC, 0x0DCD,        presetNameBr3,
        1,       0x0DCF,                        presetNameHess3,
        1,       0x0DD4,                        presetNameN3,
        5,       0x0DD5,0x0DD6,0x0DD7,0x0DD8,
                 0x0DF2,                        presetNameNdr3,
        1,       0x0DDA,                        presetNameRb3,
        1,       0x0DDC,                        presetNameRbb,      /* PATS 8.6 */
        7,       0x0DE0,0x0DE1,0x0DE2,0x0DE3,0x0DE4,
                 0x0DED, 0x0DEE,                presetNameSw3,
        6,       0x0DE6,0x0DE7,0x0DE8,0x0DE9,0x0DEA,
                 0x0DEB,                         presetNameWdr3,
        1,       0x0DF7,                           presetNameWdrl,
        5,       0x0DF4,0x0DF8,0x0DF9,0x0DFB,0x0DFE,presetNameMdr3,
        1,       0x0D85,                           presetNameArte,
        1,       0x0D8D,                           presetNameDsf,
        1,       0x0D8E,                           presetNameVox,
        2,       0x0D8F, 0x0D90,                   presetNameRtl2,
        1,       0x0D91,                           presetNameEurosport,
        1,       0x0D92,                           presetNameKabel,
        1,       0x0D94,                           presetNamePro7,
        18,      0x0D95,0x0D96,0x0D97,0x0D98,0x0D99,
                 0x0DAD,0x0DAE,0x0DAF,0x0DB0,0x0DB1,
                 0x0DB2,0x0DB3,0x0DB4,0x0DB5,0x0DB6,
                 0x0DB7,0x0DB8,0x0DB9,             presetNameSat1,
        18,      0x0D9A,0x0D9B,0x0D9C,0x0D9D,0x0D9E,
                 0x0D9F,0x0DA0,0x0DA1,0x0DA2,0x0DA3,
                 0x0DA4,0x0DA5,0x0DA6,0x0DA7,0x0DA8,
                 0x0DA9,0x0DAA,0x0DAB,             presetNameRtl,
        1,       0x0DAC,                           presetNamePremiere,
        1,       0x0DBB,                           presetNameDwtv,
        1,       0x0DBD,                           presetNameOffenerKanal,
        1,       0x0DBE,                           presetNameBerlin2,
        1,       0x0DBF,                           presetNameBerlin1,
        1,       0x0D87,                           presetName1atv,		/* PATS 8.5 */
        1,       0x0D88,                           presetNameViva,
        1,       0x0D89,                           presetNameComed,    /* PATS 8.6 */
        1,       0x0D8A,                           presetNameSrtl,
        1,       0x0D8B,                           presetNameRtlc,
        1,       0x0D8C,                           presetNameNtv,
        1,       0x0D41,                           presetNameFest,
        1,       0x0D42,                           presetNameMuxx,
        1,       0x0D43,                           presetNameExtra,
		1,		 0x0D72,						   presetNameDMax,		/* PATS 8.6 */
		1,		 0x0D73,						   presetNameMtv,		/* PATS 8.5 */
		1,		 0x0D74,						   presetNameNick,		/* PATS 8.5 */
		1,		 0x0D75,						   presetNameKdgi,		/* PATS 8.5 */
		1,		 0x0D76,						   presetNameDas4,		/* PATS 8.5 */
        1,       0x0D77,                           presetName123Tv,    /* PATS 8.4 */
		1,       0x0D79,                           presetNameRtls,		/* PATS 8.5 */
        1,       0x0D7C,                           presetNameOnyx,
        1,       0x0D7D,                           presetNameQvc,
        /*1,       0x0D7E,                           presetNameNickde,*//* PATS 8.5 */
        1,       0x0D7F,                           presetNameHse,
        1,       0x0D81,                           presetNameOrb1,
        1,       0x0D82,                           presetNameOrb3,
		1,       0x0D83,                           presetNameParla,     /* PATS 8.6 */
		1,       0x0DBA,                           presetNameTm3,
        1,       0x0DC8,                           presetNamePhoen,
        1,       0x0DC9,                           presetNameKika,
        1,       0x0DCA,                           presetNameBr1,
        1,       0x0DCE,                           presetNameHr1,
        5,       0x0DD0,0x0DD1,0x0DD2,0x0DD3,0x0Df1,presetNameNdr1,
        1,       0x0DD9,                           presetNameRb1,
        1,       0x0DDB,                           presetNameRbb1,       /* PATS 8.6 */
        1,       0x0DDD,                           presetNameSdr,
        1,       0x0DDE,                           presetNameSwf,
        1,       0x0DDF,                           presetNameSr1,
        2,       0x0DEC,0x0DEF,                    presetNameSdr1,
        1,       0x0DE5,                           presetNameWdr1,
        1,       0x0DF0,                           presetNameSwf1,
        4,       0x0DF6,0x0DFA,0x0DFD,0x0DF3,      presetNameMdr1,
        1,       0x0DFC,                           presetNameMdre,
        1,       0x0DF5,                           presetNameMdrd,
        2,       0x0D78,0x0D7B,                    presetNameTele5,    /* PATS 8.1 */
        1,       0x0D7A,                           presetNameN24,
        1,       0x07C8,                           presetNameNovyKanal,
        1,       0x07C0,                           presetNameUkraine1plus1,
        1,       0x07C5,                           presetNameM1Music,    /* PATS 8.4 */
		1,       0x0791,                           presetNameRtl    /* PATS 8.6 */
};

static Nat16 ROM PdcCniTable[] = {
/*  network#,  CountryNetwork(s), presetname */
        /* PATS 8.4 Italy Start */
        1,     0x15b3,                               presetName7Gold,
        1,     0x1580,                               presetNameA1,
        1,     0x1592,                               presetNameAlice,
        1,     0x15c7,                               presetNameBassanoTv,
        1,     0x15d6,                               presetNameBoing,
        1,     0x1545,                               presetNameBoomerang,
        1,     0x1505,                               presetNameCanaleItalia,
        1,     0x1544,                               presetNameCartoonNetwork,
        1,     0x1547,                               presetNameCartoonNetwork1,
        2,     0x1546,0x3e28,                        presetNameCnnInternational,/* PATS 8.5 */
		1,	   0x3E27,								 presetNameCuatro,			/* PATS 8.5 */
		1,	   0x3e21,								 presetNameLaOtra,			/* PATS 8.5 */
		1,	   0x3e23,								 presetNameLaSexta,			/* PATS 8.5 */
		1,     0x3e25,								 presetNameLaNeox,			/* PATS 8.5 */
		1,     0x3e26,								 presetNameLaNova,			/* PATS 8.5 */
		1,     0x1fe5,                               presetNameTele5,			/* PATS 8.5 */
		1,     0x3e2c,								 presetNameTeled,			/* PATS 8.5 */
		1,	   0x3e20,								 presetNameTelem,			/* PATS 8.5 */
		1,	   0x3e22,								 presetNameTmsat,			/* PATS 8.5 */
        1,     0x15b2,                               presetNameDisneyChannel,
        1,     0x15b0,                               presetNameDisneyChannel1,
        1,     0x15b8,                               presetNameEntertainmentTv,
        1,     0x15c8,                               presetNameEspnClassicSport,
        1,     0x1577,                               presetNameFox,
        1,     0x1578,                               presetNameFoxlife,
        1,     0x15e4,                               presetNameGxt,
        1,     0x1581,                               presetNameHistoryChannel,
        1,     0x15e2,                               presetNameHistoryChannel1,
        1,     0x1594,                               presetNameLeonardo,
        1,     0x1591,                               presetNameMarcopolo,
        1,     0x15d8,                               presetNameMatchMusic,
        1,     0x15d2,                               presetNameMediasetPremium1,
        1,     0x15d3,                               presetNameMediasetPremium2,
        1,     0x15d4,                               presetNameMediasetPremium3,
        1,     0x15d5,                               presetNameMediasetPremium4,
		1,     0x15D1,                               presetNameMediasetPremium5,	/* PATS 8.5*/
        1,     0x1579,                               presetNameNatGeoChl,
        1,     0x15e1,                               presetNameNatGeoChl1,
        1,     0x1593,                               presetNameNuvolari,
        1,     0x15b5,                               presetNameNuovarete,
        1,     0x1543,                               presetNamePlanet,
        1,     0x15e5,                               presetNamePlayhouseDisney,
        1,     0x15d7,                               presetNamePlaylistItalia,
        1,     0x15b6,                               presetNameRadioItaliaTv,
        1,     0x15b7,                               presetNameRete7,
        1,     0x15b4,                               presetNameRete8Vga,
        1,     0x1560,                               presetNameSciFiChannel,
        1,     0x150A,                               presetNameSitcom1,				/* PATS 8.5*/
        1,     0x150B,                               presetNameSitcom2,				/* PATS 8.5*/
        1,     0x150C,                               presetNameSitcom3,				/* PATS 8.5*/
        1,     0x150D,                               presetNameSitcom4,				/* PATS 8.5*/
        1,     0x150E,                               presetNameSitcom5,				/* PATS 8.5*/
        1,     0x1513,                               presetNameSkyCalcio1,
        1,     0x1514,                               presetNameSkyCalcio2,
        1,     0x1515,                               presetNameSkyCalcio3,
        1,     0x1516,                               presetNameSkyCalcio4,
        1,     0x1517,                               presetNameSkyCalcio5,
        1,     0x1518,                               presetNameSkyCalcio6,
        1,     0x1519,                               presetNameSkyCalcio7,
        1,     0x15a0,                               presetNameSkyCalcio8,
        1,     0x15a1,                               presetNameSkyCalcio9,
        1,     0x15a2,                               presetNameSkyCalcio10,
        1,     0x15a3,                               presetNameSkyCalcio11,
        1,     0x15a4,                               presetNameSkyCalcio12,
        1,     0x15a5,                               presetNameSkyCalcio13,
        1,     0x15a6,                               presetNameSkyCalcio14,
        1,     0x15e6,                               presetNameSkyCanale224,
        1,     0x1511,                               presetNameSkyCinemaClassic,
        1,     0x1549,                               presetNameSkyDirrettaGol,
        1,     0x1568,                               presetNameSkyMeteo24,
        1,     0x1548,                               presetNameSkySports3,
        1,     0x15e3,                               presetNameSkyTv,
        1,     0x1590,                               presetNameStudioUniversal,
        1,     0x1596,                               presetNameSuperpippaChannel,
        1,     0x15a7,                               presetNameTelesanterno,
        1,     0x15a8,                               presetNameTelecentro,
        1,     0x15a9,                               presetNameTelestense,
        1,     0x15b9,                               presetNameToonDisney,
        /* PATS 8.4 Italy End */
        1,       0x1601,                           presetNameTv1,
        1,       0x1606,                           presetNameKa2,
        1,       0x1602,                           presetNameTv2,
        1,       0x1604,                           presetNameVt4,
        1,       0x1605,                           presetNameVtm,
        1,       0x2101,                           presetNameEt1,
        1,       0x2102,                           presetNameEt2,
        1,       0x2103,                           presetNameEt3,
        1,       0x2104,                           presetNameEt,
        1,       0x2105,                           presetNameEt,
        1,       0x2106,                           presetNameEt,
        1,       0x2107,                           presetNameEt,
        1,       0x2108,                           presetNameEt,
        1,       0x2109,                           presetNameEt,
        1,       0x210A,                           presetNameEt,
        1,       0x210B,                           presetNameEt,
        1,       0x210C,                           presetNameEt,
        1,       0x210D,                           presetNameEt,
        1,       0x210E,                           presetNameEt,
        1,       0x210F,                           presetNameEt,
        1,       0x24c7,                           presetNameSf2,
		1,		 0x2422,                           presetNameTelez,		/* PATS 8.5 */
        1,       0x24c8,                           presetNameTsr2,
        1,       0x2421,                           presetNameU1,        /* PATS 8.4 */
        1,       0x24c9,                           presetNameTsi2,
        1,       0x24CA,                           presetNameSat,
        1,       0x24c1,                           presetNameSf1,
        1,       0x24c3,                           presetNameTsi1,
        1,       0x24c2,                           presetNameTsr1,
        1,       0x2601,                           presetNameYle1,
        1,       0x2602,                           presetNameYle2,
        1,       0x260F,                           presetNameOwl3,
        1,       0x2901,                           presetNameDr1,
        1,       0x2902,                           presetNameTv2danemark,
        1,       0x2903,                           presetNameDr2,
        1,       0x2905,                           presetNameTv2Charlie,        /* PATS 8.4 */
        1,       0x2907,                           presetNameKanal5,            /* PATS 8.4 */
        1,       0x2908,                           presetNameTv2Film,           /* PATS 8.4 */
        1,       0x2c1c,                           presetNameAngliatv,
        1,       0x2c68,                           presetNameBbcprime,
        1,       0x2c57,                           presetNameBbcworld,
        7,       0x2c2F,0x2c41,0x2c7b,0x2c7d,0x2c7f,0x2c04
                 ,0x2c43,                          presetNameBbc1,
        7,       0x2c3E,0x2c40,0x2c42,0x2c44,0x2c7e,0x2c0A
                 ,0x2c7C,                          presetNameBbc2,
        1,       0x2c27,                           presetNameBordertv,
        1,       0x2c05,                           presetNameCarltonselect,
        1,       0x2c1d,                           presetNameCarltontv,
        1,       0x2c37,                           presetNameCentraltv,
        1,       0x2c11,                           presetNameCh4,
        4,       0x2c02,0x2c09,0x2c2b,0x2c3b,      presetNameChannel5,
        1,       0x2c24,                           presetNameChanneltv,
        1,       0x2c3a,                           presetNameGrampiantv,
        1,       0x2c18,                           presetNameGranadatv,
        1,       0x2c3f,                           presetNameHtv,
        1,       0x2c1e,                           presetNameItvnetwork,
        1,       0x2c0b,                           presetNameLwt,
        1,       0x2c34,                           presetNameMeridian,
        1,       0x2c1b,                           presetNameMoviechannel,
        1,       0x2c14,                           presetNameMtv,
        1,       0x2c31,                           presetNameNbceurope,
        1,       0x2c13,                           presetNameRacingch,
        1,       0x2c07,                           presetNameCh4,
        1,       0x2c15,                           presetNameScifich,
        1,       0x2c12,                           presetNameScottishtv,
        1,       0x2c19,                           presetNameSkygold,
        1,       0x2c0c,                           presetNameSkymovieplus,
        1,       0x2c0d,                           presetNameSkynews,
        1,       0x2c0e,                           presetNameSkyone,
        1,       0x2c17,                           presetNameSkysoaps,
        1,       0x2c1a,                           presetNameSkysport,
        1,       0x2c08,                           presetNameSkysport2,
        1,       0x2c0f,                           presetNameSky2,
        1,       0x2c25,                           presetNameSsvc,
        1,       0x2c2c,                           presetNameTyneteestv,
        1,       0x2c01,                           presetNameUkliving,
        1,       0x2c3d,                           presetNameUlstertv,
        1,       0x2c20,                           presetNameVh1,
        1,       0x2c30,                           presetNameWestcountrytv,
        1,       0x2c3c,                           presetNameWiretv,
        1,       0x2c2d,                           presetNameYorkshiretv,
        1,       0x2c69,                           presetNameBbcn,
        1,       0x2c38,                           presetNameHtvfutureuse,
        1,       0x2c21,                           presetNameVh1gerlang,
        1,       0x2f02,                           presetNameFr2,
        1,       0x2f03,                           presetNameFr3,
        1,       0x2fc1,                           presetNameAbi,
        1,       0x2f20,                           presetNameAqui,
        1,       0x2f0a,                           presetNameArte,
        1,       0x2fc2,                           presetNameCanj,
        2,       0x2fc3,0x1542,                    presetNameJimmy,
        1,       0x2f04,                           presetNameCanp,
		1,		 0x2fe1,						   presetNameEuronews,				/* PATS 8.4 */
		1,		 0x2fe2,						   presetNameEurosport,				/* PATS 8.4 */
		1,       0x2fe3,                           presetNameEurosport2,			/* PATS 8.5 */
		1,       0x2fe4,                           presetNameEurosportNews,			/* PATS 8.5 */
        1,       0x2f05,                           presetNameLaCinquieme,
        1,       0x2fc5,                           presetNameMeteo,
        1,       0x2fc4,                           presetNameLci,
        1,       0x2f06,                           presetNameM6,
        1,       0x2fc6,                           presetNameMcm,
        1,       0x2fc8,                           presetNameParis,
        1,       0x2fc9,                           presetNamePlnet,
        1,       0x2f11,                           presetNameRfo1,
        1,       0x2f12,                           presetNameRfo2,
        1,       0x2fca,                           presetNameSerie,
        1,       0x2fcb,                           presetNameTtoon,
        1,       0x2fcc,                           presetNameTeva,
        1,       0x2f01,                           presetNameTf1,
        1,       0x2f21,                           presetNameTlm,
        1,       0x2f22,                           presetNameTlt,
        1,       0x2fc7,                           presetNameTmc,
        4,       0x32c1,0x32d1,0x32e1,0x32f1,      presetNameCt1,
        4,       0x32c2,0x32d2,0x32e2,0x32f2,      presetNameCt2,
		1,       0x32CB,						   presetNameCt4S,			/* PATS 8.5 */
		1,       0x32CA,						   presetNameCt24,			/* PATS 8.5 */
        1,       0x32c3,                           presetNameNovatv,
        1,       0x32c4,                           presetNamePrimaTV,       /* PATS 8.4 */
        1,       0x4202,                           presetNameNetwork2,
        1,       0x4201,                           presetNameRte1,
        1,       0x4203,                           presetNameTeilifis,
        1,       0x42f4,                           presetNameFilm,
        1,       0x4306,                           presetNameAvrasya,
        1,       0x4301,                           presetNameTrt1,
        1,       0x4302,                           presetNameTrt2,
        1,       0x4303,                           presetNameTrt3,
        1,       0x4304,                           presetNameTrt4,
        1,       0x4305,                           presetNameTrtint,
        1,       0x4801,                           presetNameNed1,
        1,       0x4802,                           presetNameNed2,
        1,       0x4803,                           presetNameNed3,
        1,       0x4804,                           presetNameRtl4,
        1,       0x4805,                           presetNameRtl5,
        /*1,       0x4806,                           presetNameVeronica,*/	/* PATS 8.5 */
		1,       0x4847,                           presetNameRtl7,			/* PATS 8.5 */
		1,       0x4848,                           presetNameRtl8,			/* PATS 8.6 - IPM-65689  */
        1,       0x4e01,                           presetNameSvt1,
        1,       0x4e02,                           presetNameSvt2,
        1,       0x4e00,                           presetNameSvt,
        1,       0x4e40,                           presetNameTv4,
        1,       0x5bef,                           presetNameBravo,
        1,       0x5bf0,                           presetNameChildrenschannel,
        1,       0x5bf1,                           presetNameCnn,
        1,       0x5bf2,                           presetNameDiscovery,
        1,       0x5bcc,                           presetNameDisneyuk,
        1,       0x5bf3,                           presetNameFamilych,
        1,       0x5bd2,                           presetNameGmtv,
        1,       0x5bf4,                           presetNameGranadaplus,
        1,       0x5bf5,                           presetNameGranadatimeshare,
        1,       0x5bf6,                           presetNameHistorych,
        1,       0x5bf7,                           presetNameLearningch,
        1,       0x5bf8,                           presetNameLivetv,
        1,       0x5bf9,                           presetNameSkytravel,
        1,       0x5bfa,                           presetNameUkgold,
        1,       0x2904,                           presetNameZulu,
        1,       0x2906,                           presetNameTvDanmark,     /* PATS 8.4 */
        3,       0x35a1,0x35a3,0x35a5,             presetNameStv1,
        3,       0x35a2,0x35a4,0x35a6,             presetNameStv2,
		1,		 0x35b1,						   presetNameTvJoj,			/* PATS 8.5 */
		1,		 0x3e29,						   presetName40Latino,		/* PATS 8.5 */
		1,		 0x3e2a,						   presetName24Horas,		/* PATS 8.5 */
		1,		 0x3e24,						   presetNameAntena3,		/* PATS 8.5 */
		1,		 0x3e2b,						   presetNameClanTVE,		/* PATS 8.5 */
        1,       0x2C16,                           presetNameCentraltv,
        1,       0x2C10,                           presetNameMeridian,
        1,       0x2C35,                           presetNameCNBCEurope,
        1,       0x4822,                           presetNameNickde,
        1,       0x1606,                           presetNameKanaal2,
		1,       0x2909,                           presetNameTv2Ne,          /* PATS 8.6 */
		1,       0x150F,                           presetNameMondo           /* PATS 8.6 */
};


static Nat16 ROM NiTable[] = {
/* ni#,        ni(s),                               presetname */
        1,     0x4301,                               presetNameOrf1,
        1,     0x4302,                               presetNameOrf2,
        1,     0x320c,                               presetNameAb3,
        1,     0x320d,                               presetNameAb4,     /* PATS 8.4 */
        1,     0x320f,                               presetNameJimtv,
        1,     0x3201,                               presetNameTv1,
        1,     0x3206,                               presetNameKa2,
        1,     0x3203,                               presetNameRtbf1,
        1,     0x3204,                               presetNameRtbf2,
        1,     0x3207,                               presetNameRtbfs,
        1,     0x3209,                               presetNameRtl,
        1,     0x320a,                               presetNameRtlc,
        1,     0x3202,                               presetNameTv2,
        1,     0x0404,                               presetNameVt4,
        1,     0x3205,                               presetNameVtm,
        /*1,     0x0385,                               presetNameHrt,*/ /* PATS 8.5 */
        4,     0x4201,
               0x4231,
               0x4211,
               0x4221,                               presetNameCt1,
        4,     0x4202,
               0x4232,
               0x4212,
               0x4222,                               presetNameCt2,
		1,	   0x420B,								 presetNameCt4S,			/* PATS 8.5 */
		1,	   0x420A,								 presetNameCt24,			/* PATS 8.5 */
        2,     0x4203,0x0386,                        presetNameNovatv,			/* PATS 8.5 */
		1,     0x0400,                               presetNameRtlTelevizija,	/* PATS 8.5 */
        1,     0x7392,                               presetNameDr1,
        1,     0x49cf,                               presetNameDr2,
        1,     0x4507,                               presetNameKanal5,          /* PATS 8.4 */
        1,     0x358f,                               presetNameOwl3,
        1,     0x3581,                               presetNameYle1,
        1,     0x3582,                               presetNameYle2,
        4,     0x330a,
               0x490a,
               0x390a,
               0x340a,                               presetNameArte,
        1,     0xfe01,                               presetNameEuronews,
        1,     0xf101,                               presetNameEurosport,
		1,     0xf102,                               presetNameEurosport2,		/* PATS 8.5 */
		1,     0xf103,                               presetNameEurosportNews,	/* PATS 8.5 */
        1,     0x33f2,                               presetNameFr2,
        1,     0x33f3,                               presetNameFr3,
        1,     0x33f1,                               presetNameTf1,
        1,     0xf500,                               presetNameTv5,
        1,     0x33c1,                               presetNameAbi,
        1,     0x3320,                               presetNameAqui,
        1,     0x33c2,                               presetNameCanj,
        2,     0x33c3,0x3942,                        presetNameJimmy,
        1,     0x33f4,                               presetNameCanp,
        1,     0x33c5,                               presetNameMeteo,
        1,     0x33c4,                               presetNameLci,
        1,     0x33f6,                               presetNameM6,
        1,     0x33c6,                               presetNameMcm,
        1,     0x33c8,                               presetNameParis,
        1,     0x33c9,                               presetNamePlnet,
        1,     0x3311,                               presetNameRfo1,
        1,     0x3312,                               presetNameRfo2,
        1,     0x33ca,                               presetNameSerie,
        1,     0x33cb,                               presetNameTtoon,
        1,     0x33cc,                               presetNameTeva,
        2,     0x3321,0xaae4,                        presetNameTlm,
        1,     0x3322,                               presetNameTlt,
        1,     0x33c7,                               presetNameTmc,
        1,     0x3001,                               presetNameEt1,
        1,     0x3002,                               presetNameEt2,
        1,     0x3003,                               presetNameEt3,
        7,     0x3601,
               0x3611,
               0x3651,
               0x3661,
               0x3621,
               0x3631,
               0x3641,                               presetNameMtv1,
        1,     0x3602,                               presetNameMtv2,
        1,     0x3622,                               presetNameTv2norway,
        1,     0x3541,                               presetNameRikisutvarpid,
        1,     0x3532,                               presetNameNetwork2,
        1,     0x3531,                               presetNameRte1,
        1,     0x3533,                               presetNameTeilifis,
        1,     0x3333,                               presetNameTv3,
		3,     0xfa05,0x4833,0x3030,                 presetNameCanale5,
        /* PATS 8.4 Italy Start */
        2,     0x3906,0x39b3,                        presetName7Gold,		/* PATS 8.5 */
        1,     0x3980,                               presetNameA1,
        1,     0x3992,                               presetNameAlice,
        1,     0x39c7,                               presetNameBassanoTv,
        1,     0x39d6,                               presetNameBoing,
        1,     0x3945,                               presetNameBoomerang,
        1,     0x3905,                               presetNameCanaleItalia,
        1,     0x3944,                               presetNameCartoonNetwork,
        1,     0x3947,                               presetNameCartoonNetwork1,
        2,     0x3946,0x3428,                        presetNameCnnInternational,/* PATS 8.5 */
		1,	   0x3427,								 presetNameCuatro,			/* PATS 8.5 */
        1,     0x39b2,                               presetNameDisneyChannel,
        1,     0x39b0,                               presetNameDisneyChannel1,
        1,     0x39b8,                               presetNameEntertainmentTv,
		1,     0x398F,                               presetNameEspansioneTv,	/* PATS 8.5 */
        1,     0x39c8,                               presetNameEspnClassicSport,
        1,     0x3977,                               presetNameFox,
        1,     0x3985,                               presetNameFoxKids,
        1,     0x3987,                               presetNameFoxKids1,
        1,     0x3978,                               presetNameFoxlife,
        1,     0x39e4,                               presetNameGxt,
        1,     0x3981,                               presetNameHistoryChannel,
        1,     0x39e2,                               presetNameHistoryChannel1,
        1,     0x3994,                               presetNameLeonardo,
        1,     0x3991,                               presetNameMarcopolo,
        1,     0x39d8,                               presetNameMatchMusic,
        1,     0x39d2,                               presetNameMediasetPremium1,
        1,     0x39d3,                               presetNameMediasetPremium2,
        1,     0x39d4,                               presetNameMediasetPremium3,
        1,     0x39d5,                               presetNameMediasetPremium4,
		1,     0x39d1,                               presetNameMediasetPremium5,/* PATS 8.5*/
		1,     0x39da,                               presetNameMediashopping,/* PATS 8.5*/
        1,     0x3979,                               presetNameNatGeoChl,
        1,     0x39e1,                               presetNameNatGeoChl1,
        1,     0x3993,                               presetNameNuvolari,
        1,     0x39b5,                               presetNameNuovarete,
        1,     0x3986,                               presetNamePeopleTvRete7,
        1,     0x3943,                               presetNamePlanet,
        1,     0x39e5,                               presetNamePlayhouseDisney,
        1,     0x39d7,                               presetNamePlaylistItalia,
        1,     0x3989,                               presetNamePrimaTv,
        1,     0x39b6,                               presetNameRadioItaliaTv,
		1,	   0x39f9,								 presetNameRadioTeleEuropa,	/* PATS 8.5 */
        1,     0x39b7,                               presetNameRete7,
        1,     0x39b4,                               presetNameRete8Vga,
        1,     0x3960,                               presetNameSciFiChannel,
        1,     0x3928,                               presetNameSenato,			/* PATS 8.5 */
		1,     0x399A,                               presetNameSitcom1,			/* PATS 8.5 */
		1,     0x399B,                               presetNameSitcom2,			/* PATS 8.5 */
		1,     0x399C,                               presetNameSitcom3,			/* PATS 8.5 */
		1,     0x399D,                               presetNameSitcom4,			/* PATS 8.5 */
		1,     0x399E,                               presetNameSitcom5,			/* PATS 8.5 */
        1,     0x3913,                               presetNameSkyCalcio1,
        1,     0x3914,                               presetNameSkyCalcio2,
        1,     0x3915,                               presetNameSkyCalcio3,
        1,     0x3916,                               presetNameSkyCalcio4,
        1,     0x3917,                               presetNameSkyCalcio5,
        1,     0x3918,                               presetNameSkyCalcio6,
        1,     0x3919,                               presetNameSkyCalcio7,
        1,     0x39a0,                               presetNameSkyCalcio8,
        1,     0x39a1,                               presetNameSkyCalcio9,
        1,     0x39a2,                               presetNameSkyCalcio10,
        1,     0x39a3,                               presetNameSkyCalcio11,
        1,     0x39a4,                               presetNameSkyCalcio12,
        1,     0x39a5,                               presetNameSkyCalcio13,
        1,     0x39a6,                               presetNameSkyCalcio14,
        1,     0x39e6,                               presetNameSkyCanale224,
        1,     0x3970,                               presetNameSkyCinema2,
        1,     0x3971,                               presetNameSkyCinema3,
        1,     0x3974,                               presetNameSkyCinema16_9,
        1,     0x3972,                               presetNameSkyCinemaAutore,
        1,     0x3911,                               presetNameSkyCinemaClassic,
        1,     0x3973,                               presetNameSkyCinemaMax,
        1,     0x3949,                               presetNameSkyDirrettaGol,
        1,     0x3968,                               presetNameSkyMeteo24,
        1,     0x3975,                               presetNameSkySports2,
        1,     0x3948,                               presetNameSkySports3,
        1,     0x3976,                               presetNameSkyTG24,
        1,     0x39e3,                               presetNameSkyTv,
        1,     0x398a,                               presetNameSportItalia,
        1,     0x3990,                               presetNameStudioUniversal,
        1,     0x3996,                               presetNameSuperpippaChannel,
        1,     0x39a7,                               presetNameTelesanterno,
        1,     0x39a8,                               presetNameTelecentro,
		1,     0x39f1,                               presetNameTeleradiocity,			/* PATS 8.5 */
		1,     0x39f2,                               presetNameTeleradiocityGenova,		/* PATS 8.5 */
		1,     0x39f3,                               presetNameTeleradiocityLombardia,	/* PATS 8.5 */
		1,     0x39f4,                               presetNameTelestarLiguria,			/* PATS 8.5 */
		1,     0x39f5,                               presetNameTelestarPiemontia,		/* PATS 8.5 */
		1,     0x39f6,                               presetNameTelestarLombardia,		/* PATS 8.5 */
        1,     0x39a9,                               presetNameTelestense,
        1,     0x3909,                               presetNameTelenova,
		1,     0x39D9,                               presetNameTelevisiviaSuper3,		/* PATS 8.5 */
		1,     0x394A,                               presetNameTgNorba,					/* PATS 8.5 */

        1,     0x39b9,                               presetNameToonDisney,
		1,     0x393a,                               presetNameTp9Telepuglia,			/* PATS 8.5 */
        1,     0x39ca,                               presetNameVideolina,
        /* PATS 8.4 Italy End */
        1,     0xfa06,                               presetNameItalia1,
		1,     0x39f7,                               presetNameItalia8Piemonte,/* PATS 8.5*/
		1,     0x39f8,                               presetNameItalia8Lombardio,/* PATS 8.5*/
        1,     0x3901,                               presetNameRai1,
        1,     0x3902,                               presetNameRai2,
        1,     0x3903,                               presetNameRai3,
        1,     0xfa04,                               presetNameRete4,
        1,     0x3904,                               presetNameRetea,
      /*1,     0x3997,                               presetNameTeleplus1,*/     /* PATS 8.4*/
        1,     0x3997,                               presetNameSkyCinema1,      /* PATS 8.4*/
      /*1,     0x3998,                               presetNameTeleplus2,*/     /* PATS 8.4*/
        1,     0x3998,                               presetNameSkySports1,      /* PATS 8.4*/
        1,     0x3999,                               presetNameTeleplus3,
        1,     0xfa08,                               presetNameTmc,
		1,	   0x39e9,								 presetNameTn7,				/* PATS 8.5 */
		1,	   0x391a,								 presetNameTn8,				/* PATS 8.5 */
        1,     0x3910,                               presetNameTrs,
        2,     0x3121,0x4504,                        presetNameDiscovery,
        1,     0x3101,                               presetNameNed1,
        1,     0x3102,                               presetNameNed2,
        1,     0x3103,                               presetNameNed3,
        1,     0x3125,                               presetNameNet5,
        1,     0x3104,                               presetNameRtl4,
        1,     0x3105,                               presetNameRtl5,
        1,     0x3124,                               presetNameTalpaTv,     /* PATS 8.4 */
        1,     0x3120,                               presetNameBox,
        1,     0x3126,                               presetNameSbs6,
        1,     0x3128,                               presetNameV8,
        /*1,     0x3106,                               presetNameVeronica,*/ /* PATS 8.5 */
        1,     0x4720,                               presetNameDiscovery,
        1,     0x4701,                               presetNameNrk1,
        1,     0x4703,                               presetNameNrk2,
        1,     0x4702,                               presetNameTv2norway,
        2,     0x4704,0x4820,                        presetNameTvn,
        1,     0x4810,                               presetNameTvpolonia,
        1,     0x4801,                               presetNameTvp1,
        1,     0x4802,                               presetNameTvp2,
        1,     0xCA33,                               presetNameC33,
        1,     0x3403,                               presetNameCanal9,      /* PATS 8.4 */
        1,     0x3405,                               presetNameCcv,         /* PATS 8.4 */
		1,     0x342B,                               presetNameClanTVE,		/* PATS 8.5 */
        1,     0xBA01,                               presetNameEtb1,
        1,     0x3402,                               presetNameEtb2,
		1,     0x3421,                               presetNameLaOtra,		/* PATS 8.5 */
		1,     0x3423,                               presetNameLaSexta,		/* PATS 8.5 */
		1,     0x3425,                               presetNameLaNeox,		/* PATS 8.5 */
		1,     0x3426,                               presetNameLaNova,		/* PATS 8.5 */
        1,     0x3404,                               presetNamePunt2,       /* PATS 8.4 */
		1,     0xE500,                               presetNameTele5,		/* PATS 8.5 */
		1,     0x342c,                               presetNameTeled,		/* PATS 8.5 */
		1,     0x3420,                               presetNameTelem,		/* PATS 8.5 */
		1,     0x3422,                               presetNameTmsat,		/* PATS 8.5 */
        1,     0xCA03,                               presetNameTv3,
        1,     0x3E00,                               presetNameTve1,
        1,     0xE100,                               presetNameTve2,
        1,     0x4601,                               presetNameSvt1,
        1,     0x4602,                               presetNameSvt2,
        1,     0x4600,                               presetNameSvt,
        1,     0x4640,                               presetNameTv4,
        1,     0x410a,                               presetNameSat,
        1,     0x4109,                               presetNameTsi2,
        1,     0x4108,                               presetNameTsr2,
        1,     0x4121,                               presetNameU1,      /* PATS 8.4 */
        1,     0x4107,                               presetNameSf2,
		1,     0x4122,                               presetNameTelez,	/* PATS 8.5 */
        1,     0x4101,                               presetNameSf1,
        1,     0x4103,                               presetNameTsi1,
        1,     0x4102,                               presetNameTsr1,
        3,     0x900a,0x430c,0x3223,                 presetNameAtv,
        1,     0x9008,                               presetNameCine5,
        1,     0x9007,                               presetNameShowtv,
		1,     0x9017,                               presetNameShowEuro,/* PATS 8.5 */
        1,     0x9009,                               presetNameSupersport,
        1,     0x9006,                               presetNameAvrasya,
        1,     0x9001,                               presetNameTrt1,
        1,     0x9002,                               presetNameTrt2,
        1,     0x9003,                               presetNameTrt3,
        1,     0x9004,                               presetNameTrt4,
        1,     0x9005,                               presetNameTrtint,
        1,     0x900E,                               presetNameBarvot,
        1,     0x900d,                               presetNameEko,
        1,     0x900c,                               presetNameEurod,
        1,     0x9010,                               presetNameFun,
        1,     0x900f,                               presetNameGalak,
        1,     0x900b,                               presetNameKand,
        1,     0x9014,                               presetNameTgrt,
        1,     0x9011,                               presetNameTempo,
        1,     0xfb9c,                               presetNameAngliatv,
        2,     0x4421,0x4831,                        presetNameAnpl,
        1,     0x4468,                               presetNameBbcprime,
        1,     0x4469,                               presetNameBbcn,
        1,     0x4457,                               presetNameBbcworld,
        7,     0x4441,
               0xfa6f,
               0x1984,
               0x4443,
               0x447b,
               0x447d,
               0x447f,                               presetNameBbc1,
        7,     0x4440,
               0xa2fe,
               0x200a,
               0x447c,
               0x4442,
               0x4444,
               0x447e,                               presetNameBbc2,
        1,     0xb7f7,                               presetNameBordertv,
        1,     0x4405,                               presetNameBravo,
        1,     0x82e1,                               presetNameCarltonselect,
        1,     0x82dd,                               presetNameCarltontv,
        1,     0x2f27,                               presetNameCentraltv,
        1,     0xfcd1,                               presetNameCh4,
        4,     0x9602,
               0x1609,
               0x28eb,
               0xc47b,                               presetNameChannel5,
        1,     0xfce4,                               presetNameChanneltv,
        1,     0x4404,                               presetNameChildrenschannel,
        1,     0x01f2,                               presetNameCnn,
        1,     0x4420,                               presetNameDish,
        1,     0x4407,                               presetNameDiscovery,
        1,     0x44d1,                               presetNameDisneyuk,
        1,     0x4408,                               presetNameFamilych,
        1,     0xc4f4,                               presetNameFilm,
        1,     0xaddc,                               presetNameGmtv,
        1,     0xf33a,                               presetNameGrampiantv,
        1,     0x4d5a,                               presetNameGranadaplus,
        1,     0x4d5b,                               presetNameGranadatimeshare,
        1,     0xadd8,                               presetNameGranadatv,
        1,     0xfcf4,                               presetNameHistorych,
        1,     0x5aaf,                               presetNameHtv,
        1,     0xc8de,                               presetNameItvnetwork,
        1,     0x4406,                               presetNameLearningch,
        1,     0x4409,                               presetNameLivetv,
        1,     0x884b,                               presetNameLwt,
        1,     0x10e4,                               presetNameMeridian,
        1,     0xfcfb,                               presetNameMoviechannel,
        3,     0x4d54,0x3933,0x3229,                  presetNameMtv,				/* PATS 8.5 */
		1,	   0x39e7,							     presetNameMusbo,			/* PATS 8.5 */
        1,     0x8e71,                               presetNameNbceurope,
        1,     0xfcf3,                               presetNameRacingch,
        1,     0xb4c7,                               presetNameCh4,
        1,     0xfcf5,                               presetNameScifich,
        1,     0xf9d2,                               presetNameScottishtv,
        1,     0xfcf9,                               presetNameSkygold,
        1,     0xfcfc,                               presetNameSkymovieplus,
        1,     0xfcfd,                               presetNameSkynews,
        1,     0xfcfe,                               presetNameSkyone,
        1,     0xfcf7,                               presetNameSkysoaps,
        1,     0xfcfa,                               presetNameSkysport,
        1,     0xfcf8,                               presetNameSkysport2,
        1,     0xfcf6,                               presetNameSkytravel,
        1,     0xfcff,                               presetNameSky2,
        1,     0x37e5,                               presetNameSsvc,
        1,     0xa82c,                               presetNameTyneteestv,
        1,     0x4401,                               presetNameUkgold,
        1,     0x4402,                               presetNameUkliving,
        1,     0x833b,                               presetNameUlstertv,
        1,     0x4d58,                               presetNameVh1,
        1,     0x25d0,                               presetNameWestcountrytv,
        1,     0x4403,                               presetNameWiretv,
        1,     0xfa2c,                               presetNameYorkshiretv,
        1,     0x44c1,                               presetNameTnt,
        1,     0x3510,                               presetNameRtp1,
        1,     0x3511,                               presetNameRtp2,
        1,     0x3512,                               presetNameRtpaf,
        1,     0x3513,                               presetNameRtpi,
        1,     0x3514,                               presetNameRtpaz,
        1,     0x3515,                               presetNameRtpm,
        1,     0x3938,                               presetNameRtv38,
        1,     0x4880,                               presetNameTvpWarszawa,
        1,     0x4881,                               presetNameBialystok,
        1,     0x4882,                               presetNameBydgoszcz,
        1,     0x4883,                               presetNameGdansk,
        1,     0x4804,                               presetNameGdanskt,
        1,     0x4884,                               presetNameKatowice,
        1,     0x4886,                               presetNameKrakow,
        1,     0x4887,                               presetNameLubin,
        1,     0x4888,                               presetNameLodz,
        1,     0x4890,                               presetNameRzeszow,
        1,     0x4891,                               presetNamePoznan,
        1,     0x4892,                               presetNameSzczecin,
        1,     0x4893,                               presetNameWroclaw,
        1,     0x4834,                               presetNameTvnPoland,
        1,     0x4833,                               presetNameCanalpPoland,
        1,     0x3030,                               presetNameCanalpPolandt,
        1,     0xAAE1,                               presetNameSlo1,
        1,     0xAAE2,                               presetNameSlo2,
        1,     0xAAE3,                               presetNameKc,
        1,     0xAAF1,                               presetNameSlo3,
		1,     0x3429,                               presetName40Latino,		/* PATS 8.5 */
		1,     0x342A,                               presetName24Horas,			/* PATS 8.5 */
		1,     0x3424,                               presetNameAntena3,			/* PATS 8.5 */
        1,     0x4908,                               presetNamePhoenix,
        1,     0x4502,                               presetNameTv2danemark,
        1,     0x4505,                               presetNameTv2Charlie,      /* PATS 8.4 */
        1,     0x4508,                               presetNameTv2Film,         /* PATS 8.4 */
        1,     0x4000,                               presetNameRtl,
        1,     0x4503,                               presetNameZulu,
        1,     0x4506,                               presetNameTvDanmark,       /* PATS 8.4 */
        1,     0x5C49,                               presetNameQvc,
        1,     0x490C,                               presetNameVox,
        1,     0x4902,                               presetNameZdf,
        1,     0x49bd,                               presetName123Tv,           /* PATS 8.4 */
        1,     0x49c7,                               presetName3sat,
        1,     0x4901,                               presetNameArd,
        1,     0x49cb,                               presetNameBr3,
        1,     0x4944,                               presetNameBra,
        1,     0x4943,                               presetNameExtra,
        1,     0x4941,                               presetNameFest,
        1,     0x49bf,                               presetNameHse,
        1,     0x49bf,                               presetNameHse,
        1,     0x49ff,                               presetNameHr,
        1,     0x49c9,                               presetNameKika,
        1,     0x49fe,                               presetNameMdr3,
        1,     0x4942,                               presetNameMuxx,
        1,     0x49d4,                               presetNameN3,
        1,     0x4982,                               presetNameOrb3,
        1,     0x49d9,                               presetNameRb1,
        1,     0x49dc,                               presetNameSfb3,
        1,     0x49df,                               presetNameSr1,
        2,     0x49e1,0x49e4,                        presetNameSw3,
        1,     0x49e6,                               presetNameWdr3,
        3,     0x42a1,0x42a3,0x42a5,                 presetNameStv1,
        3,     0x42a2,0x42a4,0x42a6,                 presetNameStv2,
		1,	   0x42b1,								 presetNameTvJoj,		/* PATS 8.5 */
        1,     0x3636,                               presetNameDUNA,
        1,     0x3781,                               presetNameRTV,
        1,     0x5699,                               presetNameCentraltv,
        1,     0xF258,                               presetNameHtv,
        1,     0xDD50,                               presetNameMeridian,
        1,     0xA460,                               presetNameNickde,
        1,     0xA465,                               presetNamePARA,
        1,     0x5C44,                               presetNameQvc,
        1,     0x4D59,                               presetNameVh1,
        1,     0x49be,                               presetNameTele5,
        1,     0x3927,                               presetNameCameraDeputati,
        1,     0x3939,                               presetNameGayTV,
        1,     0x3920,                               presetNameRAINotizie24,    /* PATS 8.5 */
        1,     0x3921,                               presetNameRAIMed,
        1,     0x3922,                               presetNameRAISportSat,		/* PATS 8.5 */
        1,     0x3923,                               presetNameRAIEdu1,			/* PATS 8.5 */
        1,     0x3924,                               presetNameRAIEdu2,			/* PATS 8.5 */
        1,     0x3925,                               presetNameRAINettunoSat1,	/* PATS 8.5 */
        1,     0x3926,                               presetNameRAINettunoSat2,	/* PATS 8.5 */
		1,     0x3926,                               presetNameRAINettunoSat2,	/* PATS 8.5 */
		1,	   0x392A,								 presetNameRAIDocFutura,	/* PATS 8.5 */
        2,     0x3928,0x3298,                        presetNameRAIMosaico,
        1,     0x3950,                               presetNameRaisatAlbum,
        1,     0x3951,                               presetNameRaisatArt,
        1,     0x3952,                               presetNameRaisatCinema,
		1,     0x3958,                               presetNameRaisatCinemaWorld,/* PATS 8.5 */
		1,     0x3959,                               presetNameRaisatExtra,		 /* PATS 8.5 */
        1,     0x3953,                               presetNameRaisatFiction,
        1,     0x3954,                               presetNameRaisatGamberoRossoChannel,
		1,	   0x395A,								 presetNameRaisatPremium,	/* PATS 8.5 */
        1,     0x3955,                               presetNameRaisatRagazzi,
        /*1,     0x3956,                               presetNameRaisatShow,*/	/* PATS 8.5 */
        /*1,     0x3957,                               presetNameRaisatGRossoInterattivo,*//* PATS 8.5 */
		1,     0x392b,                               presetNameRAITest2,		/* PATS 8.5 */
		1,     0x3929,                               presetNameRAIUtile,		/* PATS 8.5 */
        2,     0x3940,0x3234,                        presetNameVideoItalia,
        1,     0x8e72,                               presetNameCNBCEurope,
        1,     0x7700,                               presetNameUkraine1plus1,
        1,     0x3122,                               presetNameNickde,
        1,     0x3137,                               presetNameRnn7,          /* PATS 8.4 */
        1,     0x9022,                               presetNameKanal6,
        1,     0x9023,                               presetNameStar4,
        1,     0x9024,                               presetNameStar5,
        1,     0x9025,                               presetNameStar6,
        1,     0x9026,                               presetNameStar7,
        1,     0x9027,                               presetNameStar8,
        1,     0x9021,                               presetNameStarMax,
        1,     0x9020,                               presetNameStar,
        2,     0x3130,0x3131,                        presetNameTmf,
		1,	   0x3147,								 presetNameRtl7,			/* PATS 8.5 */
		1,	   0x3148,								 presetNameRtl8,			/* PATS 8.6 - IPM-65689  */
        1,     0x3988,                               presetNameLa7,
        1,     0x3941,                               presetNameSat2000,
        1,     0x3237,                               presetNameAntenneCentre,
        1,     0x321f,                               presetNameAVSe,
        1,     0x3235,                               presetNameCanalC,
        1,     0x3233,                               presetNameCanalZoom,
      /*1,     0x3216,                               presetNameCanalPlus,*/     /* PATS 8.4 */
        1,     0x3216,                               presetNameBe1ana,          /* PATS 8.4 */
      /*1,     0x3217,                               presetNameCanalplusN1,*/   /* PATS 8.4 */
        1,     0x3217,                               presetNameBe1num,          /* PATS 8.4 */
      /*1,     0x3218,                               presetNameCanalplusN2,*/   /* PATS 8.4 */
        1,     0x3218,                               presetNameBeCine1,         /* PATS 8.4 */
      /*1,     0x3219,                               presetNameCanalplusN3,*/   /* PATS 8.4 */
        1,     0x3219,                               presetNameBeSport1,        /* PATS 8.4 */
        1,     0x32a7,                               presetNameBe1plus1h,       /* PATS 8.4 */
        1,     0x32a8,                               presetNameBeCine2,         /* PATS 8.4 */
        1,     0x32a9,                               presetNameBeSport2,        /* PATS 8.4 */
        /*2,     0x321a,0x321b,                        presetNameCanalplusVL1,*//* PATS 8.5 */
      /*1,     0x321c,                               presetNameCanalplusVLN1,*/ /* PATS 8.4 */
      /* 1,     0x321c,                              presetNameCanalplusBlauw, */ /* PATS 8.4 */ /*PATS 8.5 */
      /*1,     0x321d,                               presetNameCanalplusVLN2,*/ /* PATS 8.4 */
      /*1,     0x321d,                               presetNameCanalplusRood,*/   /* PATS 8.4 *//* PATS 8.5 */
        1,     0x3215,                               presetNameFocusTV,
        1,     0x3299,                               presetNameCanalInfo,
        1,     0x3206,                               presetNameKanaal2,
        1,     0x3222,                               presetNameKanaal3,
        1,     0x3212,                               presetNameMCMBelgique,
        1,     0x3240,                               presetNameNoTele,
        1,     0x3225,                               presetNamePlugTv,          /* PATS 8.4 */
		1,     0x321A,                               presetNamePrimeSport,      /* PATS 8.5 */
		1,     0x321B,                               presetNamePrimeSport2,     /* PATS 8.5 */
		1,     0x321C,                               presetNamePrimeAction,     /* PATS 8.5 */
		1,     0x321D,                               presetNamePrimeOne,	    /* PATS 8.5 */
        1,     0x320e,                               presetNameRingTV,
        1,     0x3224,                               presetNameRobTV,
        1,     0x3210,                               presetNameRTVKempen,
        1,     0x3211,                               presetNameRTVMechelen,
        1,     0x3226,                               presetNameSporza,          /* PATS 8.4 */
        1,     0x3230,                               presetNameTeleBruxelles,
        1,     0x3236,                               presetNameTeleMB,
        1,     0x3231,                               presetNameTelesambre,
        1,     0x3238,                               presetNameTelevesdre,
        1,     0x321e,                               presetNameTVBrussel,
        1,     0x3232,                               presetNameTVCom,
        1,     0x3221,                               presetNameTVLimburg,
        1,     0x3241,                               presetNameTVLux,
        1,     0x3234,                               presetNameVideoscope,
        1,     0x3227,                               presetNameVijfTv,          /* PATS 8.4 */
        1,     0x3213,                               presetNameVitaya,
        1,     0x4821,                               presetNameTvnSiedem,
        1,     0x3239,                               presetNameRTCTeleLiege,
        1,     0x4822,                               presetNameTvn24,
        2,     0x39b1,0x33b2,                        presetNameSailingChannel,
        1,     0x3214,                               presetNameWtv,
		1,     0x0385,                               presetNameHrt1,			/* PATS 8.5 */
		1,     0x0387,                               presetNameHrt2,			/* PATS 8.5 */
		1,     0x0388,                               presetNameHrtPlus,			/* PATS 8.5 */
        1,     0x325B,                               presetNameCanalZFr,
        1,     0x326A,                               presetNameCartoonNetworkNl,
        1,     0x326B,                               presetNameCartoonNetworkFr,
        1,     0x325A,                               presetNameKanaalZNl,
        1,     0x327A,                               presetNameLibertyChannelNl,
        1,     0x327B,                               presetNameLibertyChannelFr,
		1,     0x3228,                               presetNameLifeTv,			/* PATS 8.5 */
        1,     0x328A,                               presetNameTCMNl,
        1,     0x328B,                               presetNameTCMFr,
        1,     0x3961,                               presetNameDiscoveryCivilisations,
        1,     0x3930,                               presetNameDiscoveryItaly,
        1,     0x3963,                               presetNameDiscoveryScience,
        1,     0x3962,                               presetNameDiscoveryTravelandAdventure,
        1,     0x3934,                               presetNameMTVBrandNew,
        1,     0x3935,                               presetNameMTVHits,
        1,     0x7707,                               presetNameICTV,
        1,     0x3123,                               presetNameAnimalPlanetBenelux,
        1,     0x7705,                               presetNameM1,
        1,     0x7708,                               presetNameNovyKanal,
        1,     0x3132,                               presetNameMTVNL,
        1,     0xE200,                               presetNameTVEInternacionalEurope,
        1,     0x4204,                               presetNamePrimaTV,
        1,     0x4205,                               presetNameTVPraha,
        1,     0x4206,                               presetNameTVHK,
        1,     0x4207,                               presetNameTVPardubice,
        1,     0x4208,                               presetNameTVBrno,
		1,     0x8888,                               presetNameOkto,              /* PATS 8.6 */
		1,     0x3220,                               presetNameStv,
		1,     0x4509,                               presetNameTv2Ne,
		1,     0x399F,                               presetNameMondo,
		1,     0x39BA,                               presetNamePlay,
		1,     0x39AB,                               presetNameTcs,
		1,     0x4020,                               presetNameTvi,
		1,     0x3133,                               presetNameNicke,
		1,     0x3134,                               presetNameBox,
		1,     0xAAE6,                               presetNameKan,
		1,     0xAAE5,                               presetNamePoptv,
		1,     0x342D,                               presetNameCan4
};

/* PRIORITY TABLE */

static PresetName ROM austriaSortTable[44] =
   { presetNameOrf1
   , presetNameOrf2
   , presetNameOrf2Burgenland
   , presetNameOrf2Karnten
   , presetNameOrf2Niederosterreich
   , presetNameOrf2Oberosterreich
   , presetNameOrf2Salzburg
   , presetNameOrf2Steiermark
   , presetNameOrf2Tirol
   , presetNameOrf2Voraelberg
   , presetNameOrf2Wien
   , presetNameOrf3
   , presetNameAtv
   , presetNameArd
   , presetNameZdf
   , presetNameSat1
   , presetNameRtl
   , presetNameRtl2
   , presetNamePro7
   , presetNameBr3
   , presetName3sat
   , presetNameVox
   , presetNameKabel
   , presetNameSf1
   , presetNamePremiere
   , presetNameViva
   , presetNameViva2
   , presetNameArte
   , presetNameSrtl
   , presetNameSw3
   , presetNameWdr3
   , presetNameSw3
   , presetNameMdr3
   , presetNameHess3
   , presetNameBerlin1
   , presetNameBerlin2
   , presetNameRb3
   , presetNameOrb3
   , presetNameSfb3
   , presetNameOffenerKanal
   , presetNameDsf
   , presetNameEurosport
   , presetNameNtv
   , presetNameOther
   };

/* Belgium : Dutch language */
static PresetName ROM belgiumSortTableDutch[34] =
   { presetNameTv1  /* EEN */
   , presetNameTv2  /* CANV */
   , presetNameVtm
   , presetNameKa2
   , presetNameVt4
   , presetNameVijfTv
   , presetNameNed1
   , presetNameNed2
   , presetNameNed3
   , presetNameRtbf1
   , presetNameRtbf2
   , presetNameArte
   , presetNameRtl
   , presetNameTf1
   , presetNameFr2
   , presetNameFr3
   , presetNameArd
   , presetNameZdf
   , presetNameBbc1
   , presetNameBbc2
   , presetNameRai1
   , presetNameTve1
   , presetNameRtpi
   , presetNameTrtint
   , presetNameTv5
   , presetNameEuronews
   , presetNameCnn
   , presetNameMtv
   , presetNameEurosport
   , presetNameCanp
   , presetNameNbceurope
   , presetNameTVBrussel
   , presetNameTnt
   , presetNameOther
   };

/* Belgium : French language */
static PresetName ROM belgiumSortTableFrench[33] =
   { presetNameRtbf1
   , presetNameRtbf2
   , presetNameArte
   , presetNameRtl
   , presetNameTf1
   , presetNameFr2
   , presetNameFr3
   , presetNameTv5
   , presetNameCanp
   , presetNameTv1   /* EEN */
   , presetNameTv2   /* CANV */
   , presetNameVtm
   , presetNameKa2
   , presetNameVt4
   , presetNameVijfTv
   , presetNameNed1
   , presetNameNed2
   , presetNameNed3
   , presetNameRai1
   , presetNameArd
   , presetNameZdf
   , presetNameBbc1
   , presetNameBbc2
   , presetNameEuronews
   , presetNameCnn
   , presetNameMtv
   , presetNameEurosport
   , presetNameTve1
   , presetNameRtpi
   , presetNameTrtint
   , presetNameTeleBruxelles
   , presetNameTnt
   , presetNameOther
   };

static PresetName ROM czechSortTable[4]=
{
   presetNameCt1
  ,presetNameCt2
  ,presetNameNovatv
  ,presetNameOther
};
static PresetName ROM denmarkSortTable[23] =
   { presetNameDr1
   , presetNameDr2
   , presetNameTv2danemark
    /*           nordic */
   /*           local_tv */
   , presetNameCnn
   , presetNameEurosport
   , presetNameDsf
   , presetNameDiscovery
   /*        info */
   , presetNameSvt1
   , presetNameSvt2
   , presetNameNrk1
   , presetNameTv5
   , presetNameEuronews
   , presetNameRai1
   , presetNameMtv
   , presetNameTve1
   , presetNameTve2
   , presetNameRtl
   , presetNameArd
   , presetNameZdf
   , presetNameN3
   , presetNameSat1
   , presetNameBbc1
   , presetNameOther
   };

static PresetName ROM finlandSortTable[8] =
   { presetNameYle1
   , presetNameYle2
   , presetNameOwl3
   /*           ptv */
   , presetNameEurosport
   , presetNameMtv
   , presetNameSvt1
   , presetNameSvt2
   , presetNameOther
   };

static PresetName ROM franceSortTable[8]=
   {
     presetNameTf1
    ,presetNameFr2
    ,presetNameFr3
    ,presetNameCanp
    ,presetNameArte
    ,presetNameM6
    ,presetNameLaCinquieme
    ,presetNameOther
   } ;


static PresetName ROM germanSortTable[29] =
   { presetNameArd
   , presetNameZdf
   , presetNameSat1
   , presetNameRtl
   , presetNameRtl2
   , presetNamePro7
   , presetNameKabel
   , presetNameVox
   , presetNamePremiere
   , presetName3sat
   , presetNameViva
   , presetNameViva2
   , presetNameSrtl
   , presetNameArte
   , presetNameNtv
   , presetNameDsf
   , presetName1atv   /* PATS 8.5 */
   , presetNameEurosport
   , presetNameDwtv
   , presetNameOffenerKanal
   , presetNameBerlin1
   , presetNameBerlin2
   , presetNameSf1
   , presetNameTsr1
   , presetNameTsi1
   , presetNameOrf1
   , presetNameOrf2
   , presetNameOrf3
   , presetNameOther
   };

static PresetName ROM germanThirdSortTable[10] =
   { presetNameWdr3
   , presetNameBr3
   , presetNameHess3
   , presetNameN3
   , presetNameSw3
   , presetNameRb3
   , presetNameMdr3
   , presetNameSfb3
   , presetNameOrb3
   , presetNameOther
   };
static PresetName ROM greeceSortTable[4]=
{
  presetNameEt1
 ,presetNameEt2
 ,presetNameEt3
 ,presetNameOther
};


static PresetName ROM hungarySortTable[4]=
{
  presetNameMtv1
 ,presetNameMtv2
 ,presetNameTv2norway
 ,presetNameOther
};
static PresetName ROM irelandSortTable[5]=/* PATS 8.5 */
{
  presetNameRte1
 ,presetNameNetwork2
 ,presetNameTv3
 ,presetNameTeilifis		/* PATS 8.5 */
 ,presetNameOther
 };

static PresetName ROM italySortTable[7] =
   { presetNameRai1
   , presetNameRai2
   , presetNameRai3
   , presetNameRete4
   , presetNameCanale5
   , presetNameItalia1
   , presetNameOther
   };

static PresetName ROM luxemburgSortTable[22] =
   { presetNameArd
   , presetNameZdf
   , presetNameSw3
   , presetNameSat1
   , presetNamePro7
   , presetNameRtl
   /*           tvi */
   , presetNameRtl2
   , presetNameRtl4
   , presetNameRtbf1
   , presetNameRtbf2
   , presetNameTf1
   , presetNameFr2
   , presetNameFr3
   , presetNameCanp
   , presetNameTv5
   , presetNameArte
   , presetNameCnn
   , presetNameEuronews
   , presetNameMtv
   , presetNameRai1
   , presetNameRtpi
   , presetNameOther
   };

static PresetName ROM netherlandSortTable[] =
   { presetNameNed1
   , presetNameNed2
   , presetNameNed3
   , presetNameRtl4
   , presetNameRtl5
   , presetNameSbs6
   , presetNameRtl7    /* PATS 8.6 - IPM-65689  */
   , presetNameV8
   , presetNameNet5
   , presetNameRtl8    /* PATS 8.6 - IPM-65689  */
   , presetNameTv1
   , presetNameTv2
   , presetNameBbc1
   , presetNameBbc2
   , presetNameArd
   , presetNameZdf
   , presetNameWdr3
   , presetNameN3
   , presetNameSw3
   , presetNameRtl
   , presetNameEurosport
   , presetNameMtv
   , presetNameCanp
   , presetNameCnn
   , presetNameDiscovery
   , presetNameRtbf1
   , presetNameTv5
   , presetNameTrtint
   , presetNameOther
   };

static PresetName ROM norwaySortTable[18] =
   { presetNameNrk1
    ,presetNameNrk2
    , presetNameTv2norway
    ,presetNameTvn
   , presetNameSvt1
   , presetNameMtv
   , presetNameEuronews
   , presetNameTv5
   , presetNameMcm
   , presetNameEurosport
   , presetNameTv4
   /*           tv5-s */
   , presetNameCanp
   /*           tv1000 */
   , presetNameSat1
   , presetNameChildrenschannel
   , presetNameBbc1
   , presetNameCnn
   , presetNameSkynews
   , presetNameOther
   };
static PresetName ROM polandSortTable[6]=
{
  presetNameTvp1
 ,presetNameTvp2
/*,presetNamePolsat
 ,presetNamePoisat2*/
 ,presetNameTvnPoland
 ,presetNameCanalpPoland
 ,presetNameTvpolonia
 ,presetNameOther
};

static PresetName ROM polandThirdSortTable[12]=
{

  /*presetNameWot51,*/
  presetNameBialystok,
  presetNameBydgoszcz,
  presetNameGdansk,
  presetNameKatowice,
  presetNameKrakow,
  presetNameLubin,
  presetNameLodz,
  presetNameRzeszow,
  presetNamePoznan,
  presetNameSzczecin,
  presetNameWroclaw,
  presetNameOther
};

static PresetName ROM portugalSortTable[7] =
   {
    presetNameRtp1
   ,presetNameRtp2
   ,presetNameRtpaf
   ,presetNameRtpaz
   ,presetNameRtpi
   ,presetNameRtpm
   , presetNameOther
   };

static PresetName ROM slovakiaSortTable[3]=
{
  presetNameStv1
 ,presetNameStv2
 ,presetNameOther
 };

static PresetName ROM sloveniaSortTable[6]=
{
  presetNameSlo1
 ,presetNameSlo2
 ,presetNameSlo3
 ,presetNameKc
 ,presetNameTlm
 ,presetNameOther
 };

static PresetName ROM spainSortTable[5] =
   { presetNameTve1
   , presetNameTve2
   /*   a 3 */
   , presetNameCanp
   , presetNameTv5
   , presetNameOther
   };

static PresetName ROM swedenSortTable[7] =
   { presetNameSvt1
   , presetNameSvt2
   , presetNameTv4
   /*, presetNameTv3*/
   /*           tv1000 */
   , presetNameNrk1
   , presetNameMtv
   , presetNameCnn
   , presetNameOther
   };

static PresetName ROM switzerlandSortTable[23] =
   { presetNameSf1
   , presetNameTsr1
   , presetNameTsi1
   , presetNameArd
   , presetNameZdf
   , presetNameRtl
   , presetNameRtl2
   , presetNameSat1
   , presetNamePro7
   , presetNameOrf1
   , presetNameOrf2
   , presetNameSw3
   , presetNameBr3
   , presetName3sat
   , presetNameTf1
   , presetNameFr2
   , presetNameFr3
    ,presetNameM6
   , presetNameRai1
   , presetNameRai2
   , presetNameRai3
   , presetNameTelez
   , presetNameOther
   };
static PresetName ROM turkeySortTable[6]=
{
   presetNameTrt1
  ,presetNameTrt2
  ,presetNameTrt3
  ,presetNameTrt4
  ,presetNameTrtint
  ,presetNameOther
};

static PresetName ROM ukSortTable[5] =
{
     presetNameBbc1
   , presetNameBbc2
   , presetNameCh4
   , presetNameChannel5
   , presetNameOther
};
static PresetName ROM ukThirdSortTable[19]=
{
     presetNameAngliatv
   , presetNameBordertv
   , presetNameCarltontv
   , presetNameCentraltv
   , presetNameChanneltv
   , presetNameGmtv
   , presetNameGrampiantv
   , presetNameGranadaplus
   , presetNameGranadatv
   , presetNameHtv
   , presetNameItvnetwork
   , presetNameLwt
   , presetNameMeridian
   , presetNameScottishtv
   , presetNameTyneteestv
   , presetNameUlstertv
   , presetNameWestcountrytv
   , presetNameYorkshiretv
   , presetNameOther
};


#endif

