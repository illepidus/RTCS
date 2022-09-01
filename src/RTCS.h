#ifndef RTCS_H
#define RTCS_H

#include <QObject>
#include "global.h"
#include "RTCSMainWindow.h"

class RTCS : public QObject
{
Q_OBJECT
private:
	RTCSMainWindow *main_window;
public:
	RTCS();
public slots:
	void showMainWindow(bool = true);
	void hideMainWindow();
};

#endif
