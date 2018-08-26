/**********************************************************************
*
*   C Source:       cabletuner_attributes.h
*   Instance:       blr81mgr_2
*   Description:    
*   %created_by:    nareshj %
*   %date_created:  Tue Feb 28 22:14:00 2012 %
*
**********************************************************************/

#define MAX_SETS                3
#define MAX_SYMRATES_PER_SET    5
#define MAX_MOD_TYP             3   
#define MAX_MODULATION_VALS     5

static int mConstellation[14] =
{
/*HsvUnknownConstellation*/ tmFe_UnknownConstellation,
/*HsvAutoConstellation*/    tmFe_AutoConstellation,
/*HsvBpsk*/                 tmFe_Bpsk,
/*HsvQpsk*/                 tmFe_Qpsk,
/*Hsv8psk*/                 tmFe_8psk,
/*HsvQam4*/                 tmFe_Qam4,
/*HsvQam16*/                tmFe_Qam16,
/*HsvQam32*/                tmFe_Qam32,
/*HsvQam64*/                tmFe_Qam64,
/*HsvQam128*/               tmFe_Qam128,
/*HsvQam256*/               tmFe_Qam256,
/*HsvQam1024*/              tmFe_Qam1024,
/*HsvVsb8*/                 tmFe_Vsb8,
/*HsvVsb16*/                tmFe_Vsb16
};

static int ModulationVals[MAX_MODULATION_VALS]  = { 
                            HsvQam128, 
                            HsvQam64,
                            HsvQam256,
                            HsvQam32, 
                            HsvQam16 
                        };


int ModulationVals_Sweden   [MAX_MOD_TYP] = { HsvQam64, HsvQam128,HsvQam256 }; 
int ModulationVals_Norway   [MAX_MOD_TYP] = { HsvQam128,HsvQam256,HsvQam64 };
int ModulationVals_Denmark  [MAX_MOD_TYP] = { HsvQam128,HsvQam256,HsvQam64 };

int SearchRates_Sweden [MAX_SETS][MAX_SYMRATES_PER_SET] =   {   { 6875000, 6950000, 7000000, 6900000, INVALID_SYMBOLRATE },
                                                                { 5957000, 6000000, 6125000, 6900000, INVALID_SYMBOLRATE },
                                                                { 6950000, 6900000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE }    };

int SearchRates_Norway [MAX_SETS][MAX_SYMRATES_PER_SET] =   {   { 5957000, 6000000, 6125000, 6900000, 6875000 },
                                                                { 6950000, 6900000, 6875000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE },
                                                                { 6900000, 6875000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE }    };

int SearchRates_Denmark [MAX_SETS][MAX_SYMRATES_PER_SET] =  {   { 5957000, 6000000, 6125000, 6875000, 6900000 },
                                                                { 6950000, 6875000, 6900000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE },
                                                                { 6875000, 6900000, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE, INVALID_SYMBOLRATE }    };


