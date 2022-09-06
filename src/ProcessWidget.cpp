#include "ProcessWidget.h"

ProcessWidget::ProcessWidget(QWidget *parent) : QSvgWidget (parent)
{
	QFile file("/home/ivan/rtcs/img/process.svg");
	file.open(QFile::ReadOnly | QFile::Text);
	dom_doc.setContent(&file);
	file.close();

	cooler_element = elementById(SVG_COOLER_ID);
	heater_element = elementById(SVG_HEATER_ID);
	t1_element = elementById(SVG_T1_ID);
	t2_element = elementById(SVG_T2_ID);

	setHeater(true);
	setCooler(true);
	setT1(13.1);
	setT2(20.0);
}

bool ProcessWidget::update()
{
	load(dom_doc.toByteArray());
	return true;
}

QDomElement ProcessWidget::elementById(QString id)
{
	//Поскольку QDomDocument::elementById не реализован, используем костыли
	//Все изменяемые элементы должны быть прямыми потомками корневого
	//TODO: переделать
	QDomNode n = dom_doc.documentElement().firstChild();
	while(!n.isNull()) {
		QDomElement e = n.toElement();
		if(!e.isNull() && e.attribute("id") == id) {
			return e;
		}
		n = n.nextSibling();
	}
	return QDomElement();
}

bool ProcessWidget::setHeater(bool state)
{
	if (heater_element.attribute("class") == (state ? SVG_CLASS_POWER_ON : SVG_CLASS_POWER_OFF))
		return false;

	heater_element.setAttribute("class", state ? SVG_CLASS_POWER_ON : SVG_CLASS_POWER_OFF);
	return update();
}

bool ProcessWidget::setCooler(bool state)
{
	if (cooler_element.attribute("class") == (state ? SVG_CLASS_POWER_ON : SVG_CLASS_POWER_OFF))
		return false;

	cooler_element.setAttribute("class", state ? SVG_CLASS_POWER_ON : SVG_CLASS_POWER_OFF);
	return update();
}

bool ProcessWidget::setT1(double val)
{
	t1_element.firstChild().setNodeValue(QString("%1°C").arg(QString::number(val, 'f', 2)));
	return update();
}

bool ProcessWidget::setT2(double val)
{
	t2_element.firstChild().setNodeValue(QString("%1°C").arg(QString::number(val, 'f', 2)));
	return update();
}