#include <InfraGlobals.h>
#include "CS2Logger.h"

S2AbstractLogger * S2AbstractLogger::s_inst = NULL;

S2AbstractLogger* S2AbstractLogger::getAbstractLogger()
{	
    /* Race conditions */
    if (s_inst == NULL) {
		s_inst = new S2AbstractLogger();
    }
    return s_inst;
}

CS2Logger* S2AbstractLogger::operator -> ()
{
	//ToDo:Always return debug logger
    return /*m_state*/ m_debug;
}

void S2AbstractLogger::setLevel(int level)
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

void S2AbstractLogger::enableFeature(int tag)
{
}

void S2AbstractLogger::disableFeature(int tag)
{
}

int S2AbstractLogger::error (const char * tag, const char *string, va_list args)
{
    char tempBuf[LOGGER_BUF_SIZE];
    vsnprintf(tempBuf, LOGGER_BUF_SIZE, string, args);
    __android_log_print(ANDROID_LOG_ERROR, tag, " %s ", tempBuf);
    return 0;
}

int S2AbstractLogger::warning (const char * tag, const char *string, va_list args)
{
    return 0;
}

int S2AbstractLogger::debug (const char * tag, const char *string, va_list args)
{
    return 0;
}

int S2AbstractLogger::verbose (const char * tag, const char *string, va_list args)
{
    return 0;
}

