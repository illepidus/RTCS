#ifndef LOG_H
#define LOG_H

#include "global.h"
#include <QObject>

#define  $i(X) Log::log(0, X, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define  $d(X) Log::log(1, X, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define  $w(X) Log::log(2, X, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define  $e(X) Log::log(3, X, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define  $f(X) Log::log(4, X, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define  $a(X) Log::log(5, X, __FILE__, __LINE__, __PRETTY_FUNCTION__)

class Log : public QObject
{
Q_OBJECT
private:
	Log();
public:
	/**********************************/
	Log(Log const&) = delete;
	void operator=(Log const&) = delete;
	/**********************************/
	static const int INFO = 0;
	static const int DEBUG = 1;
	static const int WARNING = 2;
	static const int ERROR = 3;
	static const int FATAL = 4;
	static const int ADMIN = 5;
	/**********************************/
	static Log& getInstance();
	static void log(int, QString, const char *, int, const char *);
signals:
	void logged(QString);
	void logged(int, QString);
	void logged(int, QString, QString, int, QString);
};

#endif
