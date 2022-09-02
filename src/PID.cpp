#include "PID.h"

PID::PID() : QObject()
{
	init();
	loadSettings();
}

void PID::init()
{
	is_running = false;

	u  = 0;
	P  = 0;
	I  = 0;
	D  = 0;
	e  = 0;
	de = 0;
	t  = 0;
	Se = 0;
	_e = 0;
	k  = 0;
}

void PID::loadSettings()
{
	Settings s;
	r  = s.value("PID/r",  80.0).toDouble();
	dt = s.value("PID/dt", 1.0 ).toDouble();
	Kp = s.value("PID/Kp", 0.05).toDouble();
	Ki = s.value("PID/Ki", 0.01).toDouble();
	Kd = s.value("PID/Kd", 10  ).toDouble();

	y  = 0;
	r  = 80.0;
	dt = 0.2;
	Kp = 0.05;
	Ki = 0.01;
	Kd = 10;
}

bool PID::saveSettings()
{
	Settings s;
	if (!s.isWritable()) {
		$e("Settings not writable");
		return false;
	}
	
	s.setValue("PID/r",  r);
	s.setValue("PID/dt", dt);
	s.setValue("PID/Kp", Kp);
	s.setValue("PID/Ki", Ki);
	s.setValue("PID/Kd", Kd);
	return true;
}

bool PID::start()
{
	if (is_running) {
		$w("Невозможно запустить ПИД, пока тот не остановлен.");
		return false;
	}
	init();
	return step();
}

bool PID::step()
{
	t += dt;
	e = r - y;

	Se += e * dt;
	de = (k == 0) ? 0 : e - _e;

	P = Kp * e;
	I = Kp * Ki * Se;
	D = Kp * Kd * de / dt;

	u = P + I + D;
	U = (u < 0) ? 0 : (u > 1) ? 1 : u;


	$d(QString("Шаг [%1] [%2s]: U = %3; P = %4; I = %5; D = %6").arg(k).arg(t).arg(U).arg(P).arg(I).arg(D));

	_e = e;
	k++;

	QTimer::singleShot(dt * 1000, this, SLOT(step()));
	return true;
}