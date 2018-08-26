#ifndef _CTCMWBASE_H
#define _CTCMWBASE_H

#include <InfraGlobals.h>
#include <stdarg.h>
#include "CTCLogger.h"

#undef TRACESYMBOL
#undef TraceErr
#undef TraceWarn
#undef TraceNotice
#undef TraceInfo
#undef TraceDebug

#define TRACESYMBOL(x, T) static const char *x = T;
#define TraceErr(m,...) _android_log_base(ANDROID_LOG_ERROR, m ,__VA_ARGS__)
#define TraceWarn(m,...) _android_log_base(ANDROID_LOG_WARN, m ,__VA_ARGS__ )
#define TraceNotice(m,...) _android_log_base(ANDROID_LOG_DEBUG, m ,__VA_ARGS__ )
#define TraceInfo(m,...) _android_log_base(ANDROID_LOG_VERBOSE, m ,__VA_ARGS__ )
#define TraceDebug(m,...) _android_log_base(ANDROID_LOG_DEBUG, m ,__VA_ARGS__)


class CTCMwBase
{
private:
  TCAbstractLogger  *logger;

public:
  CTCMwBase(){
    //__android_log_print(ANDROID_LOG_DEBUG, "CTCMwBase", "Constructor called");
    logger = TCAbstractLogger::getAbstractLogger();
  }

  void _android_log_base(int level, const char *name ,const char *format, ...) { 
    va_list arglist; 
    
    va_start(arglist, format); 
    
    switch(level) {
        case ANDROID_LOG_ERROR:
            (*logger)->error(name, format, arglist);
            break;
        case ANDROID_LOG_WARN:
            (*logger)->warning(name, format, arglist);
            break;
        case ANDROID_LOG_DEBUG:
            (*logger)->debug(name, format, arglist);
            break;
        case ANDROID_LOG_VERBOSE:
            (*logger)->verbose(name, format, arglist);
            break;
        default:
            break;
    }
    va_end(arglist);
   }         
};

#endif

