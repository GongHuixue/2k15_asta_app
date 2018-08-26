/*
 *  Copyright(C) 2002 Koninklijke Philips Electronics N.V.,
 *  All Rights Reserved.
 *  This  source code and any compilation or derivative thereof is the
 *  proprietary information of Koninklijke Philips Electronics N.V.
 *  and is confidential in nature.
 *  Under no circumstances is this software to be exposed to or placed
 *  under an Open Source License of any type without the expressed
 *  written permission of Koninklijke Philips Electronics N.V.      
 *     
*	 %name:		PrescanTable.h %
*             %version: 1 %
*	%created_by:	Aneesh Chandran %
*	%date_created:	 %
*             %date_modified:  %
*             %derived_by: Aneesh Chandran %                  
 *############################################################
 */
/* SatId	BouquetId	NetworkId	NetworkId1	PrescanFreq		Polarization;						TsId;	Region	ModlnSystem	ModlnType	FECInner	RollOff	SymbolRate */
{	1,		0xFFFF, 	0x0001, 	0xFFFF,		12551000, 		satfeapi_PolarisationVertical, 		0xFFFF,	0xFFFF, 0,			1,			12,			35,		0	},		/* Astra 19.2*/
{	3,		0xFFFF, 	0x0003, 	0xFFFF,		12168000, 		satfeapi_PolarisationVertical, 		0xFFFF,	0xFFFF, 0,			1,			12,			35,		0	},		/* Astra 23.5 */
{	2,		0xFFFF, 	0x013F, 	0xFFFF,		11681000, 		satfeapi_PolarisationHorizontal,	0x3E1C,	0xFFFF, 0,			1,			12,			35,		0	},		/* Hotbird 13.0 */
{	4,		0xFFFF, 	0x0002, 	0x0020,		11778000, 		satfeapi_PolarisationVertical, 		0xFFFF,	6, 		0,			1,			12,			35,		0	},		/* Astra 28.2 */
{	14,		0xFFFF,		0x055F,		0xFFFF,		11554000,		satfeapi_PolarisationVertical,		0xFFFF,	2,		0,			1,			12,			35,		0	},		/* Eutelsat 5.0 */
{	7,		0xFFFF, 	0x0046, 	0xFFFF,		11247000, 		satfeapi_PolarisationVertical, 		0xFFFF,	5, 		0,			1,			12,			35,		0	},		/* Eutelsat 10 */
{	6,		0x10FC, 	0xFFFF, 	0xFFFF,		11575000, 		satfeapi_PolarisationVertical, 		0xC5A8,	1, 		0,			1,			12,			35,		0	},		/* Eutelsat 7 */
{	5,		0x0097, 	0xFFFF, 	0xFFFF,		11729000, 		satfeapi_PolarisationVertical, 		0xFFFF,	1, 		0,			1,			12,			35,		0	},		/* Turksat 42.0 */
{	15,		0xFFFF,		0x009E,		0xFFFF,		12073000,		satfeapi_PolarisationVertical,		0x1A90,	7,		0,			1,			12,			35,		0	},		/* Eutelst 9.0 */
{	13,		0xFFFF,		0x0070,		0xFFFF,		12073000,		satfeapi_PolarisationHorizontal,	0xFFFF,	3,		0,			1,			12,			35,		0	},		/* Eutelsat 36.0 */
{	1,		0xFFFF, 	0x0001, 	0xFFFF,		12603000, 		satfeapi_PolarisationHorizontal,	0xFFFF,	0xFFFF, 0,			1,			56,			35,		22000000},	/* Astra 19.2*/
{	3,		0xFFFF, 	0x0003, 	0xFFFF,		12525000, 		satfeapi_PolarisationVertical, 		0xFFFF,	0xFFFF,	0,			1,			12,			35,		0	},		/* Astra 23.5 */
{	2,		0xFFFF, 	0x0071, 	0xFFFF,		11158000, 		satfeapi_PolarisationVertical, 		0xFFFF,	4,		0,			1,			12,			35,		0	},		/* Hotbird 13.0 */
{	4,		0xFFFF, 	0x0002, 	0x0020,		10773000, 		satfeapi_PolarisationHorizontal,	0xFFFF,	6,		0,			1,			12,			35,		0	},		/* Astra 28.2 */
{	5,		0x0097, 	0xFFFF, 	0xFFFF,		11675000, 		satfeapi_PolarisationVertical, 		0xFFFF,	1,		0,			1,			12,			35,		0	},		/* Turksat 42.0 */
{	5,		0x6090, 	0xFFFF, 	0xFFFF,		11804000, 		satfeapi_PolarisationVertical, 		0xFFFF,	1,		0,			1,			12,			35,		0	},		/* Turksat 42.0 */
{	7,		0xFFFF, 	0x0046, 	0xFFFF,		10872000, 		satfeapi_PolarisationVertical, 		0xFFFF,	5,		0,			1,			12,			35,		0	},		/* Eutelsat 10 */
{	13,		0xFFFF,		0x0024,		0xFFFF,		12226000,		satfeapi_PolarisationHorizontal,	0xFFFF,	3,		0,			1,			12,			35,		0	},		/* Eutelsat 36.0 */
{	8,		0x10FC, 	0xFFFF, 	0xFFFF,		11575000, 		satfeapi_PolarisationVertical, 		0xC5A8,	1,		0,			1,			12,			35,		0	},		/* Eutelsat 7 MDU4 */
{	1,		0xFFFF, 	0x0035, 	0xFFFF,		12515000, 		satfeapi_PolarisationHorizontal,	0x0451,	0xFFFF,	0,			1,			12,			35,		0	},		/* Astra 19.2*/
{	3,		0xFFFF, 	0x0003, 	0xFFFF,		12070000, 		satfeapi_PolarisationHorizontal,	0xFFFF,	0xFFFF, 0,			1,			12,			35,		0	},		/* Astra 23.5 */
{	2,		0xC024, 	0xFFFF, 	0xFFFF,		10719000, 		satfeapi_PolarisationVertical, 		0xFFFF,	4,		0,			1,			12,			35,		0	},		/* Hotbird 13.0 */
{	2,		0xFFFF, 	0x013E, 	0xFFFF,		11393000, 		satfeapi_PolarisationVertical, 		0xFFFF,	4,		0,			1,			12,			35,		0	},		/* Hotbird 13.0 */
{	2,		0xFFFF, 	0x013E, 	0xFFFF,		11449000, 		satfeapi_PolarisationHorizontal,	0xFFFF,	4,		0,			1,			12,			35,		0	},		/* Hotbird 13.0 */
{	14,		0xFFFF,		0x055F,		0xFFFF,		11096000,		satfeapi_PolarisationVertical,		0xFFFF,	2,		0,			1,			12,			35,		0	},		/* Eutelsat 5.0 */
{	9,		0x10FC, 	0xFFFF, 	0xFFFF,		11575000, 		satfeapi_PolarisationVertical, 		0xC5A8,	1,		0,			1,			12,			35,		0	},		/* Eutelsat 7 MDU5 */
{	10,		0x10FC, 	0xFFFF, 	0xFFFF,		11575000, 		satfeapi_PolarisationVertical, 		0xC5A8,	1,		0,			1,			12,			35,		0	},		/* Eutelsat 7 MDU3 */
{	11,		0x10FC, 	0xFFFF, 	0xFFFF,		11575000, 		satfeapi_PolarisationVertical, 		0xC5A8,	1,		0,			1,			12,			35,		0	},		/* Eutelsat 7 MDU2 */
{	12,		0x10FC, 	0xFFFF, 	0xFFFF,		11575000, 		satfeapi_PolarisationVertical, 		0xC5A8,	1,		0,			1,			12,			35,		0	},		/* Eutelsat 7 MDU1 */
{	1,		0xFFFF, 	0x0001, 	0xFFFF,		12551000, 		satfeapi_PolarisationVertical, 		0xFFFF,	0xFFFF,	0,			1,			56,			35,		22000000},	/* Astra 19.2*/
{	14,		0xFFFF,		0x055F,		0xFFFF,		10971000,		satfeapi_PolarisationVertical,		0xFFFF,	2,		0,			1,			12,			35,		0	},		/* Eutelsat 5.0 */
{	4,		0xFFFF, 	0x003B, 	0xFFFF,		11428000, 		satfeapi_PolarisationHorizontal,	0xFFFF,	6,		0,			1,			12,			35,		0	}		/* Astra 28.2 */
