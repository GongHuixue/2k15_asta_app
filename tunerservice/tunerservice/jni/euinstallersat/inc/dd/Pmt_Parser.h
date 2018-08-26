#define MAX_ES_PER_SERVICE		(30)


struct _PmtTsStreamIdentifierDescriptor{
	Nat8 DescriptorTag;
    	Nat8 DescriptorLen;
	Nat16 ServiceId;
	Nat8 StreamType;
	Nat16      BasicPID;
	Nat8 ComponentTag;
};

struct _PmtTsFreesatAltTunnelledData_Descriptor{
	Nat32 PrivateDataSpecifier;
	Nat8 DescriptorTag;
    	Nat8 DescriptorLen;
	Nat8 TunnelledDataType;
	Nat16 ServiceId;
	Nat8 StreamType;
	Nat16 BasicPID;
};
struct _PmtTsLoopData
{
	Nat8     StreamType;
	Nat16      BasicPID;
	Nat16     TsDescLoopLen;
	struct _PmtTsStreamIdentifierDescriptor StreamIdentifierDescriptor[5];
	Nat8 StreamIdentifierDescNum;
	struct _PmtTsFreesatAltTunnelledData_Descriptor FreesatAltTunnelledData_Descriptor[25];
	Nat8 FreesatAltTunnelledDataDescNum;
};
struct _PmtFreesatTunnelledData_Descriptor{
	Nat32 PrivateDataSpecifier;
	Nat8 DescriptorTag;
    	Nat8 DescriptorLen;
	Nat8 TunnelledDataType;
	Nat8 ComponentTag;
	Nat16 ServiceId;
};

typedef struct _Pmt_Parser
{
    Nat8     TableId;
    Nat16    SectionLength;
    Nat16    ProgramNumber;
    Nat8     VersionNumber;
    Nat16    PCR_PID;
    Nat16    ProgramInfoLen;
    
	struct _PmtFreesatTunnelledData_Descriptor FreesatTunnelledData_Descriptor[130];
	Nat8	FreesatTunnelledDataDescNum;
    Nat8     TsLoopDataNum;
	struct _PmtTsLoopData TsLoopData[MAX_ES_PER_SERVICE]; 

}TypePmt_Parser;
