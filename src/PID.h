#ifndef PID_H
#define PID_H

#include "global.h"
#include "Settings.h"

#include <QObject>

/**
r [Уставка]
y [Измеряемая температура]

u [Управляющий сигнал]
u = P + I + D

P, I, D [PID слогаемые]
P = Kp * e
I = Kp * Kip * Se
D = Kp * Kdp * de / dt

e [Ошибка]
e = r - y

Se [Накопленная ошибка]
Se = sum(e * dt)

de [Изменение ошбики]
de = e - _e

dt [Время дискретезации]
**/

class PID : public QObject
{
Q_OBJECT
public:
	PID();
private slots:
	void init();
	bool step();
public slots:
	bool start();
	void loadSettings();
	bool saveSettings();
signals: 
	void control(float, float);
private:
	double r, dt, Kp, Ki, Kd;    //Установочные параметры
	double y;                    //Измеряемый параметр
	double u, U, P, I, D, e, de; //Вычисляемые параметры
	double t, Se, _e, k;         //Промежуточные параметры
	bool is_running;
};

#endif
