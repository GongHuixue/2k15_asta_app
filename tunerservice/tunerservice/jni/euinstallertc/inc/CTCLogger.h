#ifndef _TCLOGGER__H_
#define _TCLOGGER__H_

#include <stdarg.h>
#include <android/log.h>
#include <cutils/properties.h>

class CTCLogger {
    public:
        CTCLogger() {}
        virtual ~CTCLogger() {}
        virtual int error (const char * tag, const char *string, va_list args) = 0;
        virtual int warning (const char * tag, const char *string, va_list args) = 0;
        virtual int debug (const char * tag, const char *string, va_list args) = 0;
        virtual int verbose (const char * tag, const char *string, va_list args) = 0;
};


#define LOGGER_BUF_SIZE    512

class TCDebugLogger: public CTCLogger {
    private:
       char tempBuf[LOGGER_BUF_SIZE];

    public:
        TCDebugLogger() {}
        virtual ~TCDebugLogger() {}

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

class TCAbstractLogger: public CTCLogger {
    private:
        CTCLogger      *m_debug;
        CTCLogger      *m_state;
        static TCAbstractLogger   *s_inst;

    private:
        TCAbstractLogger() {
            char value[PROPERTY_VALUE_MAX];

            m_debug = new TCDebugLogger();
            int len = property_get("persist.tpvlog.tcinstaller", value, NULL);
            if(len == 1 && value[0] == '1') {
                __android_log_print(ANDROID_LOG_ERROR, "CTCLogger","persist.tpvlog.tcinstaller is set so enable logging");  
                m_state = m_debug;
            }
            else {
                __android_log_print(ANDROID_LOG_ERROR, "CTCLogger","persist.tpvlog.tcinstaller is not set so disable logging");     
                m_state = this;
            }
         }

    public:

        virtual ~TCAbstractLogger()  {
            delete(m_debug);
        }

        static TCAbstractLogger* getAbstractLogger();
        CTCLogger* operator -> ();
        void setLevel(int level);
        void enableFeature(int tag);
        void disableFeature(int tag);
        virtual int error (const char * tag, const char *string, va_list args);
        virtual int warning (const char * tag, const char *string, va_list args);
        virtual int debug (const char * tag, const char *string, va_list args);
        virtual int verbose (const char * tag, const char *string, va_list args);

};

#endif

