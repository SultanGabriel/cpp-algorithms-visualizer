
#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogType;

void Log(LogType type, const char* message);

#endif // LOGGER_H

