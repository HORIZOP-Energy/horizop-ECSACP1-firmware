#ifndef _LOGGER_H
#define _LOGGER_H
#define LOG_BUFFER_SIZE 1024

#include "C:\Users\Elyes\esp-idf-v4.4.5\components\arduino\cores\esp32\Arduino.h"
#include "config.h"

class Logger
{
private:
public:
    char logBuffer[LOG_BUFFER_SIZE];
    unsigned long bytesLogged = 0;

    Logger();
    void log(const char *msg);
};

extern Logger Log;

#endif
