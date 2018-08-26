/*
 * Frontend_DVBC_params.h
 *
 *  Created on: 13-May-2013
 *      Author: mahesh.mathada
 */

#ifndef FRONTEND_DVBC_PARAMS_H_
#define FRONTEND_DVBC_PARAMS_H_



/* Error codes */
enum {
        DVBC_ERR_NONE             =  0, /**< no error / success */
        DVBC_ERR_BAD_PARAMETER    =  1, /**< parameters passed to function are not valid */
        DVBC_ERR_NOT_IMPLEMENTED  =  2, /**< unavailable method/implementation pending */
        DVBC_ERR_EXEC_FAILURE     =  3 /**< Function Failed to execute it's task */
};

/******************************************************************/
/** Constellations Detectable */
typedef enum _DvbCConstellations
{
     DVBC_UNKNOWN /**< Constellation could not be detected */
    ,DVBC_QAM16
    ,DVBC_QAM32
    ,DVBC_QAM64
    ,DVBC_QAM128
    ,DVBC_QAM256
    //,DVBC_QAM512
    //,DVBC_QAM1024
    //,DVBC_QAM2048
    //,DVBC_QAM4096
}DvbCConstellations;
/******************************************************************/
/** Frequency Band  */
typedef enum _DvbCTuningFreqRange
{
    DVBC_START_FREQUENCY  =  44000 //in kHz
   ,DVBC_END_FREQUENCY    = 870000

}DvbCTuningFreqRange;
/******************************************************************/
/** Symbol Rate Range */
typedef enum _DvbCSymbolRateRange
{
    DVBC_SYMBOLRATE_MIN = 2000000  //in baud
   ,DVBC_SYMBOLRATE_MAX = 7200000
}DvbCSymbolRateRange;
/******************************************************************/
/** Symbol Rate Detection Modes */
typedef enum _DvbCSymbolRateDetectionMode
{
    DVBC_SYMBOLRATE_AUTODETECT
   ,DVBC_SYMBOLRATE_KNOWN
}DvbCSymbolRateDetectionMode;
/******************************************************************/
/** Detected Channel Information */
typedef struct _DvbCParams
{
    DvbCConstellations constel;/**< Detected Constellation */
    int symbolrate;            /**< Detected Symbol Rate */

    int sqi;   /**< Signal Quality Indicator Scale: 0 to 100 */
    int ssi;   /**< Signal Strength Indicator Scale: 0 to 100  */
    int ber;   /**< Bit Error Rate. Div factor 10^6 */
}DvbCParams;
/******************************************************************/
/** Symbol Rate and Constellation Pair for detection */
typedef struct _DvbCSearchRateList
{
    DvbCConstellations constellation;
    int symbolrate;
}DvbCSearchRateList;
/******************************************************************/



#endif /* FRONTEND_DVBC_PARAMS_H_ */
