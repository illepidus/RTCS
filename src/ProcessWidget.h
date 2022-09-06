#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#define SVG_T1_ID "t1"
#define SVG_T2_ID "t2"
#define SVG_HEATER_ID "heater"
#define SVG_COOLER_ID "cooler"
#define SVG_CLASS_POWER_ON  "power_on"
#define SVG_CLASS_POWER_OFF "power_off"


#include "global.h"

#include <QMainWindow>
#include <QSvgWidget>
#include <QDomDocument>
#include <QString>

class ProcessWidget : public QSvgWidget 
{
Q_OBJECT
public:
	ProcessWidget(QWidget *parent = nullptr);
public slots:
	bool setHeater(bool);
	bool setCooler(bool);
	bool setT1(double);
	bool setT2(double);
	bool update();
private slots:
	QDomElement elementById(QString id);
private:
	QDomDocument dom_doc;
	QDomElement t1_element;
	QDomElement t2_element;
	QDomElement heater_element;
	QDomElement cooler_element;
};

#endif
