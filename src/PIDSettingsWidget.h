#ifndef PIDSETTINGSWIDGET_H
#define PIDSETTINGSWIDGET_H

#include "global.h"

#include <QMainWindow>
#include <QTableWidget>
#include <QHeaderView>

class PIDSettingsWidget : public QTableWidget 
{
Q_OBJECT
public:
	PIDSettingsWidget(QWidget *parent = nullptr);
};

#endif
