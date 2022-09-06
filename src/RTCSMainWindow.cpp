#include "RTCSMainWindow.h"

RTCSMainWindow::RTCSMainWindow(QWidget *parent) : QMainWindow(parent)
{
	pid_settings_widget = new PIDSettingsWidget(this);
	process_widget = new ProcessWidget();
	QWidget *central_widget = new QWidget(this);
	QGridLayout *layout = new QGridLayout(central_widget);

	layout->setSizeConstraint(QLayout::SetMinimumSize);
	layout->addWidget(new QLabel("1"), 0, 0);
	layout->addWidget(process_widget, 0, 1);
	layout->addWidget(pid_settings_widget, 1, 0);
	layout->addWidget(new QLabel("4"), 1, 1);

	central_widget->setLayout(layout);
	setCentralWidget(central_widget);
}
