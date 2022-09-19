#ifndef PIDDEVICE_H
#define PIDDEVICE_H

#include "global.h"
#include "Device.h"

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

class PIDDevice : public Device
{
Q_OBJECT
public:
	PIDDevice(QString name, QObject *parent = nullptr);
private slots:
	bool step();
public slots:
	bool start();
	bool stop();
	bool reset();
	void loadSettings();
	bool saveSettings();
	//------------------
	bool setR(double);
	bool setDT(double);
	bool setKp(double);
	bool setKi(double);
	bool setKd(double);
	bool setY(double);
signals: 
	void control(float, float);
private:
	double r, dt, Kp, Ki, Kd;    //Установочные параметры
	double y;                    //Измеряемый параметр
	double u, U, P, I, D, e, de; //Вычисляемые параметры
	double t, Se, _e, k;         //Промежуточные параметры
};

#endif
