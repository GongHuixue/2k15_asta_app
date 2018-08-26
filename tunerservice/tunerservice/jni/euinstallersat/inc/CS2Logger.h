#ifndef _S2LOGGER__H_
#define _S2LOGGER__H_

#include <stdarg.h>
#include <android/log.h>
#include <cutils/properties.h>

class CS2Logger {
    public:
        CS2Logger() {}
        virtual ~CS2Logger() {}
        virtual int error (const char * tag, const char *string, va_list args) = 0;
        virtual int warning (const char * tag, const char *string, va_list args) = 0;
        virtual int debug (const char * tag, const char *string, va_list args) = 0;
        virtual int verbose (const char * tag, const char *string, va_list args) = 0;
};


#define LOGGER_BUF_SIZE    512

class S2DebugLogger: public CS2Logger {
    private:
       char tempBuf[LOGGER_BUF_SIZE];

    public:
        S2DebugLogger() {}
        virtual ~S2DebugLogger() {}

        virtual int error (const char * tag, const char *string, va_list args) {
            vsnprintf(tempBuf, LOGGER_BUF_SIZE, string, args);
            __android_log_print(ANDROID_LOG_ERROR, tag, " %s ", tempBuf);
            return 0;
        }
        virtual int warning (const char * tag, const char *string, va_list args) {
            vsnprintf(tempBuf, LOGGER_BUF_SIZE, string, args);
            __android_log_print(ANDROID_LOG_WARN, tag, " %s ", tempBuf);
            return 0;
        }
        virtual int debug (const char * tag, const char *string, va_list args) {
            vsnprintf(tempBuf, LOGGER_BUF_SIZE, string, args);
            __android_log_print(ANDROID_LOG_DEBUG, tag, " %s ", tempBuf);
            return 0;
        }
        virtual int verbose (const char * tag, const char *string, va_list args) {
            vsnprintf(tempBuf, LOGGER_BUF_SIZE, string, args);
            __android_log_print(ANDROID_LOG_VERBOSE, tag, " %s ", tempBuf);
            return 0;
        }
};

class S2AbstractLogger: public CS2Logger {
    private:
        CS2Logger      *m_debug;
        CS2Logger      *m_state;
        static S2AbstractLogger   *s_inst;

    private:
        S2AbstractLogger() {
            char value[PROPERTY_VALUE_MAX];

            m_debug = new S2DebugLogger();
            int len = property_get("persist.tpvlog.s2installer", value, NULL);
            if(len == 1 && value[0] == '1') {
                __android_log_print(ANDROID_LOG_ERROR, "CS2Logger","sys.droidtv.s2installer.log is set so enable logging");  
                m_state = m_debug;
            }
            else {
                __android_log_print(ANDROID_LOG_ERROR, "CS2Logger","sys.droidtv.s2installer.log is not set so disable logging");     
                m_state = this;
            }
         }

    public:

        virtual ~S2AbstractLogger()  {
            delete(m_debug);
        }

        static S2AbstractLogger* getAbstractLogger();
        CS2Logger* operator -> ();
        void setLevel(int level);
        void enableFeature(int tag);
        void disableFeature(int tag);
        virtual int error (const char * tag, const char *string, va_list args);
        virtual int warning (const char * tag, const char *string, va_list args);
        virtual int debug (const char * tag, const char *string, va_list args);
        virtual int verbose (const char * tag, const char *string, va_list args);

};

#endif

