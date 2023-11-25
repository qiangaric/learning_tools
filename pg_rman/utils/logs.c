
#include <glib.h>
#include <unistd.h>
#include <inttypes.h>
#include <dirent.h>
#include <regex.h>
/**
 * ÈÕÖ¾ÉèÖÃ
 */



typedef enum {
    NOTIME = 0, // display no time
    HourTime,   // display hour and so
    ALLTime     // all time include year
} LogTimeLength;
 
GLogLevelFlags torctlLogFilterLevel = G_LOG_LEVEL_DEBUG;
LogTimeLength defaultLogTime = HourTime;
 
static const gchar* _torctlmain_logLevelToString(GLogLevelFlags logLevel)
{
    switch (logLevel) {
    case G_LOG_LEVEL_ERROR:
        return "error   ";
    case G_LOG_LEVEL_CRITICAL:
        return "critical";
    case G_LOG_LEVEL_WARNING:
        return "warning ";
    case G_LOG_LEVEL_MESSAGE:
        return "message ";
    case G_LOG_LEVEL_INFO:
        return "info    ";
    case G_LOG_LEVEL_DEBUG:
        return "debug   ";
    default:
        return "default";
    }
}
 
void _torctlmain_log(GLogLevelFlags level, const gchar* fileName, const gchar* functionName, gint line, const gchar* format, ...)
{
    if (level > torctlLogFilterLevel) {
        return;
    }
 
    va_list vargs;
    va_start(vargs, format);
 
    GDateTime* dt = g_date_time_new_now_local();
    GString* newformat = g_string_new(NULL);
 
    switch (defaultLogTime) {
    case NOTIME:
        g_string_append_printf(newformat, "[%s] [%s:%d] [%s] %s",
            _torctlmain_logLevelToString(level), fileName, line, functionName, format);
        break;
    case ALLTime:
        g_string_append_printf(newformat, "%04i-%02i-%02i %02i:%02i:%02i %" G_GINT64_FORMAT ".%06i [%s] [%s:%d] [%s] %s",
            g_date_time_get_year(dt), g_date_time_get_month(dt), g_date_time_get_day_of_month(dt),
            g_date_time_get_hour(dt), g_date_time_get_minute(dt), g_date_time_get_second(dt),
            g_date_time_to_unix(dt), g_date_time_get_microsecond(dt),
            _torctlmain_logLevelToString(level), fileName, line, functionName, format);
        break;
    case HourTime:
    default:
        g_string_append_printf(newformat, "%02i:%02i:%02i .%06i  [%s] [%s:%d] [%s] %s",
            g_date_time_get_hour(dt), g_date_time_get_minute(dt), g_date_time_get_second(dt),
            g_date_time_get_microsecond(dt),
            _torctlmain_logLevelToString(level), fileName, line, functionName, format);
        break;
    }
 
    gchar* message = g_strdup_vprintf(newformat->str, vargs);
    g_print("%s\n", message);
    g_free(message);
 
    g_string_free(newformat, TRUE);
    g_date_time_unref(dt);
 
    va_end(vargs);
}


void _torctlmain_log(GLogLevelFlags level, const gchar* fileName,
    const gchar* functionName, gint line, const gchar* format, ...);
 

