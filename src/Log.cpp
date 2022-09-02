#include "Log.h"

Log::Log() : QObject()
{
	
}

Log::Log(const char *file, int line, const char *function) : QObject(), file(file), line(line), function(function)
{
	
}

//TODO: make logging

void Log::info(QString m)
{
	qDebug() << m;
}

void Log::debug(QString m)
{
	qDebug() << file << m;
}

void Log::warning(QString m)
{
	qDebug() << m;
}

void Log::error(QString m)
{
	qDebug() << m;
}

void Log::fatal(QString m)
{
	qDebug() << m;
}