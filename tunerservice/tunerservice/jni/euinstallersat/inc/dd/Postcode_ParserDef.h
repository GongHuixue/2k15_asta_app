/*Characters allowed in postcode are A-Z, 0-9 and space
**So max child per node will be 37
*/
#define FREESAT_MAX_CHILD_PER_NODE			(37)
//define FREESAT_MAX_NODE					(12000)
//define FREESAT_MAX_REGION_KEY_PER_SECTION	(1000)
#define FREESAT_MAX_POSTCODE_TREE_SECTIONS 	(20)
#define FREESAT_MAX_REGION_KEY_SECTIONS 	(5)
#define FREESAT_MAX_POSTCODE_LENGHT			(4096)
#define FREESAT_MAX_REGIONKEY_LENGHT		(4096)
#define INVALID_LOOKUP_TABLETYPE			(3)


typedef struct _TsFreesatPostcodeKeyMapping
{
	Nat16 RegionKey;
	Nat16 NextWordOffset;
	Nat8 PostcodeChar;
	Bool IsLeafNode;
}TsFreesatPostcodeKeyMapping;

typedef struct _TsFreesatPostcodeMapping{
	Nat16 ChildCount;
	TsFreesatPostcodeKeyMapping PostcodeKey[FREESAT_MAX_CHILD_PER_NODE];
}TsFreesatPostcodeMapping;


typedef struct _TsFreesatRegionKeyMapping{
	Nat16  RegionKey;
	Nat16  SDBouquetId;
	Nat16  SDRegionId;
	Nat16  HDBouquetId;
	Nat16  HDRegionId;
}TsFreesatRegionKeyMapping;

/*pedef struct _Postcode_Parser
{
	Nat8     TableId;
	Nat16    SectionLen;
	Nat16    LookupTableType;
	Nat8     VersionNo;
	Nat8	 SectionNumber;
	Nat16 PostcodeMapping_num;
	TsFreesatPostcodeMapping PostcodeMapping[FREESAT_MAX_NODE];
	Nat16 RegionKeyMapping_num;
	TsFreesatRegionKeyMapping	RegionKeyMapping[FREESAT_MAX_REGION_KEY_PER_SECTION];
}TypePostcode_Parser;*/
	

typedef struct _postCodeTree_Dump
{
	Nat8    TableId;
	Nat16 	PostCodeTreeLen;
	Nat16   SectionLen;
	Nat8 	SectionNumberIndex;
	Nat8 	LastSectionNumber;
	Nat8 	VersionNo;
	Nat8 	PostCodeTreeDump[FREESAT_MAX_POSTCODE_LENGHT];
}PostCodeTree_Dump;

typedef struct _regionKeyMap_Dump
{
	Nat8    TableId;
	Nat16 	RegionKeyMapLen;
	Nat16   SectionLen;
	Nat8 	SectionNumberIndex;
	Nat8 	LastSectionNumber;
	Nat8 	VersionNo;
	Nat8 	regionKeyMapDump[FREESAT_MAX_REGIONKEY_LENGHT];
}RegionKeyMap_Dump;