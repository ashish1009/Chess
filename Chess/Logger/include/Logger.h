#pragma once
#include <iostream>
#include <stdarg.h>

enum LogLevel_e : unsigned char
{
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

class Logger
{
private:
    static Logger *m_LoggerInstance;
    
private:
    LogLevel_e m_LogLevel;
    unsigned int m_LogBitMask;
    
private:
    Logger();
    ~Logger();

public:
    static Logger *GetLoggerInstance();
    
public:
    void SetLogLevel(LogLevel_e level);
    void SetLogBitMask(const unsigned int mask);

    void LOG(LogLevel_e level, const unsigned int mask, const char* fmt, ...);
};

char *GetLogLevelString(LogLevel_e level);
