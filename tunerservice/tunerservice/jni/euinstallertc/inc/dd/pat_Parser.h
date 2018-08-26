#ifndef _PAT_PARSER_H_
#define _PAT_PARSER_H_

typedef struct _pat_Parser{
    Nat8     TableId;
    Nat16     section_length;
    Nat16     ts_id;
    Nat8     version_no;
    Nat8     TsLoopDataNum;
    struct _programList{
    Nat16     program_number;
    Nat16     PID;
    }programList[50];
}Typepat_Parser;

#endif