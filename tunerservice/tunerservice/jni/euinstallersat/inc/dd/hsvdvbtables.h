TABLEITEM( nit         ,HsvNITHeader     ,HsvNITSection)
TABLEITEM( sdt         ,HsvSDTHeader     ,HsvSDTSection)
TABLEITEM( bat         ,HsvBATTHeader    ,HsvBATSection)
TABLEITEM( fnt         ,HsvFNTTHeader    ,HsvFNTSection)
TABLEITEM( fst         ,HsvFSTTHeader    ,HsvFSTSection)
TABLEITEM( postcode    ,HsvPostcodeTHeader    ,HsvPostcodeSection)
TABLEITEM( sgt	  	   ,HsvSGTHeader 	 ,HsvSGTSection)
TABLEITEM( tot		   ,HsvTOTHeader	 ,HsvTOTSection)
#ifdef DESCRIPTORTABLE /*This means we are including this file for the
                         descriptor functionality. PMT is not intialised
                         from this module. The same is true for any mpeg table 
                       */
TABLEITEM( pmt         ,HsvPMTHeader     ,HsvPMTSection)
#endif
#undef TABLEITEM
