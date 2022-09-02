#ifndef SETTINGS_H
#define SETTINGS_H

#define SETTINGS_FORMAT QSettings::NativeFormat
#define SETTINGS_PATH   "/etc/rtcs/rtcs.conf"

class Settings : public QSettings
{
public:
	//TODO: make the following constructor working
	//Settings():QSettings(SETTINGS_PATH, SETTINGS_FORMAT){};
	Settings():QSettings(){};
};

#endif