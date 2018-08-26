#include <InfraGlobals.h>
#include "CTCLogger.h"

TCAbstractLogger * TCAbstractLogger::s_inst = NULL;

TCAbstractLogger* TCAbstractLogger::getAbstractLogger()
{	
    /* Race conditions */
    if (s_inst == NULL) {
		s_inst = new TCAbstractLogger();
    }
    return s_inst;
}

CTCLogger* TCAbstractLogger::operator -> ()
{
	//ToDo:Always return debug logger
    return /*m_state*/ m_debug;
}

void TCAbstractLogger::setLevel(int level)
{
    /* No mutex as assignment is atomic */
    /* Some level */
    if (level == 1) {
        m_state = m_debug;
    }
    else {
        m_state = this;
    }
}

void TCAbstractLogger::enableFeature(int tag)
{
}

void TCAbstractLogger::disableFeature(int tag)
{
}

int TCAbstractLogger::error (const char * tag, const char *string, va_list args)
{
    char tempBuf[LOGGER_BUF_SIZE];
    vsnprintf(tempBuf, LOGGER_BUF_SIZE, string, args);
    __android_log_print(ANDROID_LOG_ERROR, tag, " %s ", tempBuf);
    return 0;
}

int TCAbstractLogger::warning (const char * tag, const char *string, va_list args)
{
    return 0;
}

int TCAbstractLogger::debug (const char * tag, const char *string, va_list args)
{
    return 0;
}

int TCAbstractLogger::verbose (const char * tag, const char *string, va_list args)
{
    return 0;
}

