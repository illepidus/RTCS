#ifndef RTCSMAINWINDOW_H
#define RTCSMAINWINDOW_H

#include "global.h"
#include "PIDSettingsWidget.h"
#include "ProcessWidget.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>

class RTCSMainWindow : public QMainWindow
{
Q_OBJECT
public:
	RTCSMainWindow(QWidget *parent = nullptr);
public:
	PIDSettingsWidget *pid_settings_widget;
	ProcessWidget *process_widget;
};

#endif
