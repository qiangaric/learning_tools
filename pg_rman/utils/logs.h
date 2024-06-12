
#ifndef LOGS_H
#define LOGS_H
#include <glib.h>
 
void _torctlmain_log(GLogLevelFlags level, const gchar* fileName,
    const gchar* functionName, gint line, const gchar* format, ...);
 
#define mylogerror(...) _torctlmain_log(G_LOG_LEVEL_ERROR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define mylogcritical(...) _torctlmain_log(G_LOG_LEVEL_CRITICAL, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define mylogwarning(...) _torctlmain_log(G_LOG_LEVEL_WARNING, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define mylogmessage(...) _torctlmain_log(G_LOG_LEVEL_MESSAGE, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define myloginfo(...) _torctlmain_log(G_LOG_LEVEL_INFO, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define mylogdebug(...) _torctlmain_log(G_LOG_LEVEL_DEBUG, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
 
#define MYLOG_FUNCALL mylogdebug("enter %s()", __FUNCTION__)
 
#endif // LOGS_H
