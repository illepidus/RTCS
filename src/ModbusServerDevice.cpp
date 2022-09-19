#include "ModbusServerDevice.h"

ModbusServerDevice::ModbusServerDevice(QString n, QObject *p) : Device(n, p)
{
	m_rtu = new QModbusRtuSerialMaster(this);
	loadSettings();

	start();

	addRoutineRequest(112, QModbusRequest(QModbusPdu::FunctionCode(0x04), quint16(0x00), quint16(0x06)), this);
}

void ModbusServerDevice::loadSettings()
{
	QSettings s;
	m_portName = s.value(settingsKey("port_name"), "/dev/ttyUSB0").toString();
	m_parity   = static_cast<QSerialPort::Parity>   (s.value(settingsKey("parity"),    0     ).toInt());
	m_baudRate = static_cast<QSerialPort::BaudRate> (s.value(settingsKey("baud_rate"), 115200).toInt());
	m_dataBits = static_cast<QSerialPort::DataBits> (s.value(settingsKey("data_bits"), 8     ).toInt());
	m_stopBits = static_cast<QSerialPort::StopBits> (s.value(settingsKey("stop_bits"), 1     ).toInt());
	m_retries = (s.value(settingsKey("retries"), 3).toInt());
	m_timeout = (s.value(settingsKey("timeout"), 300).toInt());
}

void ModbusServerDevice::nextRequest()
{
	if (m_routineRequests.empty() && m_requests.empty()) {
		qDebug() << name() << "waiting...";
		QTimer::singleShot(300, this, SLOT(nextRequest()));
		return;
	}

	m_request = m_routineRequests.at(0);
	QModbusReply *reply = m_rtu->sendRawRequest(m_request.request, m_request.address);

	if (!reply->isFinished()) {
		QObject::connect(reply, &QModbusReply::finished,      this, &ModbusServerDevice::onReplyFinished);
	}
	else {
		delete reply;
		QTimer::singleShot(300, this, SLOT(nextRequest()));
	}
}

void ModbusServerDevice::onReplyFinished()
{
	auto reply = qobject_cast<QModbusReply *>(QObject::sender());
	if (!reply)
		return;

	if (reply->error() == QModbusDevice::NoError) {
		const QModbusResponse response = reply->rawResult();
		qInfo() << name() << "request: " << m_request.request.functionCode() << m_request.request.data() << "response: "<< response.data();
	}
	else {
		qCritical() << name() << "QModbusRtuSerialMaster" << reply->error();
	}

	reply->deleteLater();
	nextRequest();
}

bool ModbusServerDevice::addRoutineRequest(int address, QModbusRequest request, Device* device = nullptr) {
	m_routineRequests += Request(address, request, device);
	return true;
}

bool ModbusServerDevice::request(int address, QModbusRequest request, Device* device = nullptr) {
	m_requests += Request(address, request, device);
	return true;
}

bool ModbusServerDevice::start()
{
	if (stateFlag(Device::Disabled)) {
		qWarning() << name() << "Cannot start while disabled";
		return false;
	}

	if (stateFlag(Device::Running)) {
		qWarning() << name() << "Cannot start while running";
		return false;
	}

	m_rtu->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m_portName);
	m_rtu->setConnectionParameter(QModbusDevice::SerialParityParameter,   m_parity);
	m_rtu->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m_baudRate);
	m_rtu->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, m_dataBits);
	m_rtu->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, m_stopBits);
	m_rtu->setTimeout(m_timeout);
	m_rtu->setNumberOfRetries(m_retries);

	if (m_rtu->connectDevice()) {
		setStateFlag(Device::Running, true);
		qInfo() << name() << "Connected to serial port";
		nextRequest();
		return true;
	}
	qCritical() << name() << "Was not able to connect to serial port";
	return false;
}

bool ModbusServerDevice::stop()
{
	if (stateFlag(Device::Disabled)) {
		qWarning() << name() << "Cannot stop while disabled";
		return false;
	}
	if (!stateFlag(Device::Running)) {
		qWarning() << name() << "Cannot stop while running";
		return false;
	}

	setStateFlag(Device::Running, false);
	m_rtu->disconnectDevice();
	return true;
}
