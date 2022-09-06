#ifndef RTCS_H
#define RTCS_H

#include "global.h"
#include "RTCSMainWindow.h"
#include "PID.h"

#include <QObject>

class RTCS : public QObject
{
Q_OBJECT
private:
	RTCSMainWindow *main_window;
	PID *pid_heater;
	PID *pid_cooler;
public:
	RTCS();
public slots:
	void showMainWindow(bool = true);
	void hideMainWindow();
};

#endif
