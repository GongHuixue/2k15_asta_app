/*
 * Frontend_DVBT_params.h
 *
 *  Created on: 13-May-2013
 *      Author: mahesh.mathada
 */

#ifndef FRONTEND_DVBT_PARAMS_H_
#define FRONTEND_DVBT_PARAMS_H_

typedef enum _DvbTBandwidth
{
   DVBT_AUTO   /**< use this for auto detection */
  ,DVBT_MHZ_6  /**< 6 MHz Channel */
  ,DVBT_MHZ_7  /**< 7 MHz Channel */
  ,DVBT_MHZ_8  /**< 8 MHz Channel */

  /* note: 1.7, 5, 10 MHz for T2 not used*/
}DvbTBandwidth;

/** Constellations */
typedef enum _DvbTConstellations
{
	DVBT_UNKNOWN /**< Constellation could not be detected */
   ,DVBT_QPSK
   ,DVBT_QAM16
   ,DVBT_QAM64
   ,DVBT_QAM256
}DvbTConstellations;

/*******************************************************************/
/** Stream Priority Select for Hierarchical Modulation (HM) in DVB-T */
typedef enum _DvbTStreamPriority
{
	DVBT_HIGH /**< High Priority Stream */
   ,DVBT_LOW  /**< Low  Priority Stream */
}DvbTStreamPriority;

/*******************************************************************/
/** DvbT Channel Specific Parameters */
typedef struct _ParamsDvbTSpecific
{
	bool hiermode;                 /**< Hierarchical modulation detected or not */
	DvbTStreamPriority streamprio; /**< Enabled stream priority */
}ParamsDvbTSpecific;

/** DvbT2 Channel Specific Parameters */
typedef struct _ParamsDvbT2Specific
{
	unsigned char activeplp;       /**< Currently selected PLP */
	int plpcount;                  /**< Number of PLPs in the muxed stream */
	unsigned char plpids[256];     /**< PLP IDs */
}ParamsDvbT2Specific;


/** Aggregate Channel Parameters */
typedef struct _ParamsDvbTer
{
	/** Basic Channel Information */
	DvbTBandwidth bandwidth;
	DvbTConstellations constellation;

	/** Quality Indicators */
	int sqi;  /*< Signal Quality Indicator.  Scale : 0 to 100 */
	int ssi;  /*< Signal Strength Indicator. Scale : 0 to 100 */
	int ber;  /*< Bit Error Rate - div factor 10^6 */

	/** Standard Specific Information */
	ParamsDvbTSpecific  *paramdvbt;
	ParamsDvbT2Specific *paramdvbt2;
}ParamsDvbTer;


#endif /* FRONTEND_DVBT_PARAMS_H_ */
