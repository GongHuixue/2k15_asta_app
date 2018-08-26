#ifndef _CS2MWBASE_H
#define _CS2MWBASE_H

#include <InfraGlobals.h>
#include <stdarg.h>
#include "CS2Logger.h"

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


class CS2MwBase
{
private:
  S2AbstractLogger  *logger;

public:
  CS2MwBase(){
    //__android_log_print(ANDROID_LOG_DEBUG, "CS2MwBase", "Constructor called");
    logger = S2AbstractLogger::getAbstractLogger();
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

