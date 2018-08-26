TABLEITEM( nit         ,HsvNITHeader     ,HsvNITSection)
TABLEITEM( sdt         ,HsvSDTHeader     ,HsvSDTSection)

#ifdef DESCRIPTORTABLE /*This means we are including this file for the
                         descriptor functionality. PMT is not intialised
                         from this module. The same is true for any mpeg table 
                       */
TABLEITEM( pmt         ,HsvPMTHeader     ,HsvPMTSection)
#endif
#undef TABLEITEM
