#ifndef PID_H
#define PID_H

#include "global.h"

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
de = e - e_prev

dt [Время дискретезации]
**/

class PID : public QObject
{
Q_OBJECT
public:
	PID();
private:
	double r, dt, Kp, Kip, Kdp;   //Установочные параметры
	double y;                     //Измеряемый параметр
	double u, P, I, D, e, de, Se; //Вычисляемые параметры
	double e_prev;                //Промежуточные параметры
};

#endif
