#ifndef MODBUS_H
#define MODBUS_H

#include "global.h"

/*
ADU: [APPLICATION DATA UNIT]
******************
**ADDR**PDU**CRC**
******************
PDU: [PROTOCOL DATA UNIT]
***************
**FC**PAYLOAD**
***************
*/

class Modbus
{
public slots:
	static quint16 crc16(QByteArray data);
	static bool    check(QByteArray adu);

	static quint8 getId(QByteArray adu);
	static quint8 getFc(QByteArray adu);
	static QByteArray getPayload(QByteArray adu);

	static qint32  decodeInt32 (QByteArray data);
	static quint32 decodeUInt32(QByteArray data);
	static qint16  decodeInt16 (QByteArray data);
	static quint16 decodeUInt16(QByteArray data);
	static float   decodeFloat (QByteArray data);
	static QString decodeString(QByteArray data);

	static QByteArray encodeInt32 (qint32);
	static QByteArray encodeUInt32(quint32);
	static QByteArray encodeInt16 (qint16);
	static QByteArray encodeUInt16(quint16);
	static QByteArray encodeInt8  (qint8);
	static QByteArray encodeUInt8 (quint8);
	static QByteArray encodeFloat (float);
	static QByteArray encodeString(QString);
	static QByteArray encodeByteArray(QByteArray);

	static QByteArray adu(quint8 id, quint8 fc, QByteArray payload);

	static QByteArray reverseBytes(QByteArray);
	static QByteArray reverseByteOrder(QByteArray);
	static QByteArray swapByteOrder(QByteArray);

	static QString toHumanReadable(QByteArray);

private:
	Modbus() = delete;
	static const quint16 wCRCTable[304];
};

#endif