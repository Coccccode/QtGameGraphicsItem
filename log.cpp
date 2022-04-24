#include "log.h"

Log::Log()
{

}

template<typename T>
void Log::log(T &type)
{
    qDebug() << type;
}
