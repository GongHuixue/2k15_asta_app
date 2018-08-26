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
 *          %name: hsvtableparser.h %
 *       %version: TVG_tv550r4dev %
 * %date_modified: Wed Jun  8 15:11:20 2005 %
 *    %derived_by: lakshminb %
 */
 

/** koala group HsvTableParser **/

/** koala using infraglobals **/
/* Common syntax for a tables */


#ifndef HSVSHORTTABLE
#define HSVSHORTTABLE HSVLONGTABLE
#endif

#ifndef HSVLONGTABLE
#define HSVLONGTABLE(field, typ, declfunc, parfunc, secfunc, bits, name) 
#endif


HSVSHORTTABLE(	TableId,		Nat8,	Linear,	NA,	GetBits,	8,   table_id )
HSVSHORTTABLE(	SyntaxId,		Bool,	Linear,	NA,	GetBits,	1,   section_syntax_indicator )
HSVSHORTTABLE(	NA,				NA,		NA,		NA,	SkipBits,	1,   private_syntax )
HSVSHORTTABLE(	NA,				NA,		NA,		NA,	SkipBits,	2,   reserved )
HSVSHORTTABLE(	SectionLength,	Nat16,	Linear,	NA,	GetBits,	12,  section_length )

HSVLONGTABLE(	Attrib,			Nat16,	Linear,	NA,	GetBits,	16, attrib )
HSVLONGTABLE(	NA,				NA,		NA,		NA,	SkipBits,	2,   reserved )
HSVLONGTABLE(	VersionNumber,	Nat8,	Linear,	NA,	GetBits,	5,   version_number )
HSVLONGTABLE(	CurrentNextId,	Bool,	Linear,	NA,	GetBits,	1,   current_next_indicator )
HSVLONGTABLE(	SectionNumber,	Nat8,	Linear,	NA,	GetBits,	8,   section_number )
HSVLONGTABLE(	LastSectionNumber,	Nat8, Linear,   NA,	GetBits,	8,   last_section_number )
 
/* We dont undef these macros since we dont include these dd files directly */
