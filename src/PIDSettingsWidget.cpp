#include "PIDSettingsWidget.h"

PIDSettingsWidget::PIDSettingsWidget(QWidget *parent) : QTableWidget (parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setRowCount(2);
	setColumnCount(5);
	setHorizontalHeaderLabels(QStringList({"r", "dt", "Kp", "Ki", "Kd"}));
	setVerticalHeaderLabels(QStringList({"Нагрев", "Охлажение", "Kp", "Ki", "Kd"}));
	horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}