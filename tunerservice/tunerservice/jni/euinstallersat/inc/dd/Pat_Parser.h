
struct _PatTsLoopData
{
	Nat16     ProgramNumber;
	Nat16     PID;
};

typedef struct _Pat_Parser
{
    Nat8     TableId;
    Nat16     SectionLength;
    Nat16     TSID;
    Nat8     version_number;
    Nat8     TsLoopDataNum;
    struct _PatTsLoopData	TsLoopData[94];
}TypePat_Parser;
