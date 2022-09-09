#include "ModbusServerDevice.h"

ModbusServerDevice::ModbusServerDevice(QString n, QObject *p) : Device(n, p)
{
	loadSettings();
	serial_port = new QSerialPort();
	response_timer = new QTimer(this);
	response_timer->setSingleShot(true);

	init();

	QByteArray data_unit;
	//data_unit.append(encodeUInt8(0));
	//data_unit = dataUnit(0x70, 0x46, data_unit);
	data_unit.append(encodeUInt8(0x00));
	data_unit.append(encodeUInt8(0x00));
	data_unit.append(encodeUInt8(0x00));
	data_unit.append(encodeUInt8(0x06));
	data_unit = dataUnit(0x70, 0x04, data_unit);
	send(data_unit);

	QObject::connect(serial_port, SIGNAL(readyRead()), this, SLOT(readData()), Qt::UniqueConnection);
}

void ModbusServerDevice::send(QByteArray du)
{
	qDebug() << toHumanReadable(du);
	serial_port->write(du);

}

void ModbusServerDevice::readData() 
{
	QByteArray data_unit = serial_port->readAll();
	qDebug() << toHumanReadable(data_unit);
	qDebug() << toHumanReadable(data_unit.mid(3, 2)) << ":" << decodeInt16(data_unit.mid(3, 2));
	qDebug() << toHumanReadable(data_unit.mid(5, 2)) << ":" << decodeInt16(data_unit.mid(5, 2));
	qDebug() << toHumanReadable(data_unit.mid(7, 2)) << ":" << decodeInt16(data_unit.mid(7, 2));
}

void ModbusServerDevice::loadSettings()
{
	QSettings s;
	setDeviceFile(s.value(settingsKey("device_file"), "/dev/ttyUSB0").toString());
	setBaudRate(s.value(settingsKey("baud_rate"), 115200).toInt());
	setResponseTimeout(s.value(settingsKey("response_timeout"), 300).toInt());
}

bool ModbusServerDevice::setDeviceFile(QString p)
{
	device_file = p;
	return true;
}

bool ModbusServerDevice::setBaudRate(int b)
{
	baud_rate = b;
	return true;
}

bool ModbusServerDevice::setResponseTimeout(int t)
{
	response_timeout = t;
	return true;
}

bool ModbusServerDevice::init()
{
	if (getStateFlag(Device::Disabled)) {
		qWarning() << name << "Cannot init ModbusServer while it is disabled";
		return false;
	}

	if (getStateFlag(Device::Running)) {
		qWarning() << name << "Cannot init ModbusServer while it is running";
		return false;
	}

	serial_port->setPortName(device_file);
	serial_port->setBaudRate(baud_rate);
	serial_port->setReadBufferSize(MODBUS_READ_BUFFER_SIZE);

	if (serial_port->open(QIODevice::ReadWrite)) {
		setStateFlag(Device::Running, true);
		setStateFlag(Device::Initialized, true);
		return true;
	}
	return false;

}


//++++++++++++++++++STATIC FUNCTIONS+++++++++++++++++

quint16 ModbusServerDevice::crc16(QByteArray du) {
	quint8 nTemp;
	quint16 wCRCWord = 0xFFFF;
	foreach(nTemp, du) {
		nTemp = nTemp ^ wCRCWord;
		wCRCWord >>= 8;
		wCRCWord ^= wCRCTable[nTemp];
	}

	return wCRCWord;
}

QString ModbusServerDevice::toString(QByteArray du) 
{
	QString echo;
	QString byte;
	quint8 c;
	foreach(c, du) {
		if (c > 0x0F)
			echo += byte.setNum(c, 16).toUpper() + " ";
		else
			echo += "0" + byte.setNum(c, 16).toUpper() + " ";
	}
	echo.chop(1);
	return echo;
}

bool ModbusServerDevice::checkDataUnit(QByteArray du) 
{
	if (crc16(du) == 0)
		return true;
	return false;
}

quint8 ModbusServerDevice::getID(QByteArray du)
{
	return du.at(0);
}

uint8_t ModbusServerDevice::getFnCode(QByteArray du)
{
	return du.at(1);
}

QByteArray ModbusServerDevice::getData(QByteArray du)
{
	return du.mid(2, du.size()-4);
}

qint32 ModbusServerDevice::decodeInt32(QByteArray data)
{
	if (data.size() != sizeof(qint32))
		return 0;

	data = swapByteOrder(data);

	qint32 r;
	quint8 i[sizeof(r)];
	for (uint j=0; j<sizeof(r); j++) {
		i[j] = data.at(j);
	}
	memcpy (&r, &i, sizeof(i));
	return r;
}


quint32 ModbusServerDevice::decodeUInt32(QByteArray data)
{
	if (data.size() != sizeof(quint32))
		return 0;

	data = swapByteOrder(data);

	quint32 r;
	quint8 i[sizeof(r)];
	for (uint j=0; j<sizeof(r); j++) {
		i[j] = data.at(j);
	}
	memcpy (&r, &i, sizeof(i));
	return r;
}


qint16 ModbusServerDevice::decodeInt16(QByteArray data)
{
	if (data.size() != sizeof(qint16))
		return 0;

	data = swapByteOrder(data);

	qint16 r = 0;
	quint8 i[sizeof(r)];

	for (uint j=0; j < sizeof(r); j++) {
		i[j] = data.at(j);
	}
	memcpy (&r, &i, sizeof(i));	
	return r;
}

quint16 ModbusServerDevice::decodeUInt16(QByteArray data)
{
	if (data.size() != sizeof(quint16))
		return 0;

	data = swapByteOrder(data);

	quint16 r = 0;
	quint8 i[sizeof(r)];

	for (uint j=0; j < sizeof(r); j++) {
		i[j] = data.at(j);
	}
	memcpy (&r, &i, sizeof(i));	
	return r;
}

float ModbusServerDevice::decodeFloat(QByteArray data) 
{
	if (data.size() != sizeof(float))
		return 0;

	data = swapByteOrder(data);

	float r = 0;
	quint8 i[sizeof(r)];

	for (uint j=0; j<sizeof(r); j++)
		i[j] = data.at(j);

	memcpy (&r, &i, sizeof(r));
	if (r != r) //is NaN??
		return 0;

	return r;
}


QString ModbusServerDevice::decodeString(QByteArray data) 
{
	data = swapByteOrder(data);

	QString r = QString::fromLatin1(data);
	return r;
}

QByteArray ModbusServerDevice::encodeInt32(qint32 n)
{
	QByteArray res;
	quint8 i[sizeof(n)];
	memcpy (&i, &n, sizeof(n));
	for (uint j=0; j<sizeof(n); j++) {
		res += i[j];
	}
	res = swapByteOrder(res);
	return res;
}


QByteArray ModbusServerDevice::encodeUInt32(quint32 n)
{
	QByteArray res;
	quint8 i[sizeof(n)];
	memcpy (&i, &n, sizeof(n));
	for (uint j=0; j<sizeof(n); j++) {
		res += i[j];
	}
	res = swapByteOrder(res);
	return res;
}

QByteArray ModbusServerDevice::encodeInt16(qint16 n)
{
	QByteArray res;
	quint8 i[sizeof(n)];
	memcpy (&i, &n, sizeof(n));
	for (uint j=0; j<sizeof(n); j++) {
		res += i[j];
	}
	res = swapByteOrder(res);
	return res;
}

QByteArray ModbusServerDevice::encodeUInt16(quint16 n)
{
	QByteArray res;
	quint8 i[sizeof(n)];
	memcpy (&i, &n, sizeof(n));
	for (uint j=0; j<sizeof(n); j++) {
		res += i[j];
	}
	res = swapByteOrder(res);
	return res;
}

QByteArray ModbusServerDevice::encodeInt8(qint8 n)
{
	QByteArray res;
	quint8 i[sizeof(n)];
	memcpy (&i, &n, sizeof(n));
	for (uint j=0; j<sizeof(n); j++) {
		res += i[j];
	}
	return res;
}

QByteArray ModbusServerDevice::encodeUInt8(quint8 n)
{
	QByteArray res;
	quint8 i[sizeof(n)];
	memcpy (&i, &n, sizeof(n));
	for (uint j=0; j<sizeof(n); j++) {
		res += i[j];
	}
	return res;
}

QByteArray ModbusServerDevice::encodeFloat(float n)
{
	QByteArray res;
	quint8 i[sizeof(n)];
	memcpy (&i, &n, sizeof(n));
	for (uint j=0; j<sizeof(n); j++) {
		res += i[j];
	}
	res = swapByteOrder(res);
	return res;
}

QByteArray ModbusServerDevice::encodeString(QString s)
{
	QByteArray res = s.toLatin1();
	res = swapByteOrder(res);
	return res;
}

QByteArray ModbusServerDevice::encodeByteArray(QByteArray a)
{
	return swapByteOrder(a);
}


QByteArray ModbusServerDevice::dataUnit(quint8 id, quint8 fn, QByteArray data)
{
	QByteArray du;
	du += id;
	du += fn;
	du += data;

	quint32 crc = crc16(du);
	du+=crc & 0xFF;
	du+=crc >> 8 & 0xFF;

	return du;
}

QByteArray ModbusServerDevice::dataUnit(quint8 id, quint8 fn)
{
	QByteArray du;
	du += id;
	du += fn;

	quint32 crc = crc16(du);
	du+=crc & 0xFF;
	du+=crc >> 8 & 0xFF;

	return du;
}

QByteArray ModbusServerDevice::reverseBytes(QByteArray data)
{
	QByteArray buf = data;
	for (int i=0; i<data.size(); i++) {
		quint8 low = data[i] >> 4 & 0xF;
		quint8 hig = data[i] & 0xF;
		buf[i] = (hig << 4) + low;
	}
	return buf;
}

QByteArray ModbusServerDevice::reverseByteOrder(QByteArray data)
{
	QByteArray buf = data;
	for (int i=0; i<data.size(); i++) {
		buf[i] = data[data.size()-i-1];
	}
	return buf;
}

QByteArray ModbusServerDevice::swapByteOrder(QByteArray data)
{
	if (data.size() % 2 != 0) {
		return data;
	}

	QByteArray buf = data;
	for (int i=0; i < data.size(); i+=2) {
		buf[i] = data[i+1];
		buf[i+1] = data[i];
	}
	return buf;
}

QString ModbusServerDevice::toHumanReadable(QByteArray data)
{
	QString r;
	quint8 c;
	foreach(c, data) {
		if (c < 0x10)
			r += QString("0");
		r += QString::number(c, 16).toUpper();
		r += QString(" ");
	}
	r.chop(1);
	return r;
}