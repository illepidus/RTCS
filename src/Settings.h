#ifndef SETTINGS_H
#define SETTINGS_H

#define SETTINGS_FORMAT QSettings::IniFormat
#define SETTINGS_PATH   "/opt/rtcs/conf/rtcs.conf"

class Settings : public QSettings
{
public:
	Settings():QSettings(SETTINGS_PATH, SETTINGS_FORMAT){};
};

#endif