#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QDebug>
class Log
{
public:
    Log();
    template<typename T>
    static void log(T &var);
};

#endif // LOG_H
