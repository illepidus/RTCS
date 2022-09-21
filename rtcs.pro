TEMPLATE = app
INCLUDEPATH += src

DESTDIR = bin
OBJECTS_DIR = bin/.obj
MOC_DIR = bin/.moc
RCC_DIR = bin/.rcc
UI_DIR = bin/.ui

HEADERS += src/global.h
SOURCES += src/main.cpp

HEADERS += src/Modbus.h
SOURCES += src/Modbus.cpp

HEADERS += src/RTCS.h
SOURCES += src/RTCS.cpp

HEADERS += src/Device.h
SOURCES += src/Device.cpp

HEADERS += src/PIDDevice.h
SOURCES += src/PIDDevice.cpp

HEADERS += src/ThermometerDevice.h
SOURCES += src/ThermometerDevice.cpp

HEADERS += src/ModbusServerDevice.h
SOURCES += src/ModbusServerDevice.cpp

HEADERS += src/ModbusDevice.h
SOURCES += src/ModbusDevice.cpp

HEADERS += src/M7015Device.h
SOURCES += src/M7015Device.cpp

HEADERS += src/RTCSMainWindow.h
SOURCES += src/RTCSMainWindow.cpp

HEADERS += src/PIDSettingsWidget.h
SOURCES += src/PIDSettingsWidget.cpp

HEADERS += src/ProcessWidget.h
SOURCES += src/ProcessWidget.cpp

RC_ICONS = img/rtcs.ico
TARGET = rtcs
CONFIG += release
QT += gui network widgets svg xml serialport serialbus
