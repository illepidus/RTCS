#ifndef MODBUSSERVERDEVICE_H
#define MODBUSSERVERDEVICE_H

#include "global.h"
#include "Device.h"

#include <QSerialPort>
#include <QModbusRtuSerialMaster>

#define MODBUS_BUFFER_OVERFLOW_SIZE      100
#define MODBUS_READ_BUFFER_SIZE          256

class ModbusServerDevice : public Device
{
Q_OBJECT

struct Request {
	Request(int a, QModbusRequest r, Device* d) : address(a), request(r), device(d) {};
	Request() {};
	int            address;
	QModbusRequest request;
	Device*        device;
};

public:
	ModbusServerDevice(QString name, QObject *parent = nullptr);
public slots:
	void loadSettings();
	bool start();
	bool stop();
	bool addRoutineRequest(int address, QModbusRequest request, Device* device);
	bool request(int address, QModbusRequest request, Device* device);
private slots:
	void onReplyFinished();
	void nextRequest();
private:
	QModbusRtuSerialMaster *m_rtu;

	QString               m_portName;
	QSerialPort::Parity   m_parity;
	QSerialPort::BaudRate m_baudRate;
	QSerialPort::DataBits m_dataBits;
	QSerialPort::StopBits m_stopBits;
	int                   m_retries;
	int                   m_timeout;

	QList<Request> m_routineRequests; //список циклических запросов
	QList<Request> m_requests;        //список одноразрвых запросов
	Request m_request;                //текущий запрос, на который придет ответ
};

#endif
