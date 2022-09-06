#include "Log.h"

Log::Log() : QObject()
{

}

Log& Log::getInstance()
{
	static Log instance;
	return instance;
}

void Log::log(int level, QString message, const char * file, int line, const char * function)
{
	qDebug() << level << message;
	emit getInstance().logged(message);
	emit getInstance().logged(level, message);
	emit getInstance().logged(level, message, file, line, function);
}