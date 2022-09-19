TEMPLATE = app
INCLUDEPATH += src

DESTDIR = bin
OBJECTS_DIR = bin/.obj
MOC_DIR = bin/.moc
RCC_DIR = bin/.rcc
UI_DIR = bin/.ui

HEADERS += src/global.h
HEADERS += src/RTCS.h
HEADERS += src/Device.h
HEADERS += src/PIDDevice.h
HEADERS += src/ModbusServerDevice.h
HEADERS += src/RTCSMainWindow.h
HEADERS += src/PIDSettingsWidget.h
HEADERS += src/ProcessWidget.h

SOURCES += src/main.cpp
SOURCES += src/RTCS.cpp
SOURCES += src/Device.cpp
SOURCES += src/PIDDevice.cpp
SOURCES += src/ModbusServerDevice.cpp
SOURCES += src/RTCSMainWindow.cpp
SOURCES += src/PIDSettingsWidget.cpp
SOURCES += src/ProcessWidget.cpp

RC_ICONS = img/rtcs.ico
TARGET = rtcs
CONFIG += release
QT += gui network widgets svg xml serialport serialbus
