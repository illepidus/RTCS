#include "ModbusServerDevice.h"

ModbusServerDevice::ModbusServerDevice(QString n, QObject *p) : Device(n, p)
{
	loadSettings();
	serial_master = new QModbusRtuSerialMaster(this);

	start();
	request();
}

void ModbusServerDevice::loadSettings()
{
	/*
	QSettings s;
	setPortName(s.value(settingsKey("port_name"), "/dev/ttyUSB0").toString());
	setBaudRate(s.value(settingsKey("baud_rate"), 115200).toInt());
	setResponseTimeout(s.value(settingsKey("response_timeout"), 300).toInt());
	*/
}

void ModbusServerDevice::request()
{
	QModbusReply *reply = serial_master->sendReadRequest(QModbusDataUnit(QModbusDataUnit::InputRegisters, 0, 6), 112);
	if (!reply->isFinished())
		QObject::connect(reply, &QModbusReply::finished, this, &ModbusServerDevice::onReadReady);
	else
			delete reply;
}

void ModbusServerDevice::onReadReady()
{
	auto reply = qobject_cast<QModbusReply *>(QObject::sender());
	if (!reply)
		return;

	if (reply->error() == QModbusDevice::NoError) {
		const QModbusDataUnit unit = reply->result();
		qDebug() << unit.values();
	}

	reply->deleteLater();
	request();
}

bool ModbusServerDevice::start()
{
	if (getStateFlag(Device::Disabled)) {
		qWarning() << name << "Cannot start while disabled";
		return false;
	}

	if (getStateFlag(Device::Running)) {
		qWarning() << name << "Cannot start while running";
		return false;
	}

	serial_master->setConnectionParameter(QModbusDevice::SerialParityParameter,   QSerialPort::NoParity);
	serial_master->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
	serial_master->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
	serial_master->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
	serial_master->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "/dev/ttyUSB0");
	serial_master->setTimeout(300);
	serial_master->setNumberOfRetries(3);

	if (serial_master->connectDevice()) {
		setStateFlag(Device::Running, true);
		qInfo() << name << "Connected to serial port";
		return true;
	}
	qCritical() << name << "Was not able to connect to serial port";
	return false;
}

bool ModbusServerDevice::stop()
{
	if (getStateFlag(Device::Disabled)) {
		qWarning() << name << "Cannot stop while disabled";
		return false;
	}
	if (!getStateFlag(Device::Running)) {
		qWarning() << name << "Cannot stop while running";
		return false;
	}

	setStateFlag(Device::Running, false);
	serial_master->disconnectDevice();
	return true;
}