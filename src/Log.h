#ifndef LOG_H
#define LOG_H

#include "global.h"
#include <QObject>

#define  $i(X) Log(__FILE__, __LINE__, __PRETTY_FUNCTION__).info(X)
#define  $d(X) Log(__FILE__, __LINE__, __PRETTY_FUNCTION__).debug(X)
#define  $w(X) Log(__FILE__, __LINE__, __PRETTY_FUNCTION__).warning(X)
#define  $e(X) Log(__FILE__, __LINE__, __PRETTY_FUNCTION__).error(X)
#define  $f(X) Log(__FILE__, __LINE__, __PRETTY_FUNCTION__).fatal(X)

class Log : public QObject
{
public:
	Log();
	Log(const char *, int, const char *);
private:
	QString file;
	int line;
	QString function;
public:
	void info(QString);
	void debug(QString);
	void warning(QString);
	void error(QString);
	void fatal(QString);
};

#endif
