#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include "SingletonTemplate.h"

#define GET_STRING(NAME, KEY, DEFAULT_VALUE) \
	virtual QString get##NAME() const { \
		QSettings settings(m_filename, QSettings::IniFormat); \
		return settings.value(KEY, DEFAULT_VALUE).toString(); \
	}

#define SET_STRING(NAME, KEY) \
	virtual void set##NAME(const QString& value)  { \
		QSettings settings(m_filename, QSettings::IniFormat); \
		settings.setValue(KEY, value); \
		settings.sync(); \
	}

#define GET_SET_STRING(NAME, KEY, DEFAULT_VALUE) \
	GET_STRING(NAME, KEY, DEFAULT_VALUE) \
	SET_STRING(NAME, KEY)

class SettingsManager :
		public QObject,
		public SingletonTemplate<SettingsManager>
{
	QString m_filename;

public:
	explicit SettingsManager(QObject *parent = 0);

	void setFile(QString filepath);

	GET_SET_STRING(OwnCloudHost, "Network/owncloudhost", "http://vaness0.ga:83/owncloud")
	GET_SET_STRING(UserName, "Account/username", "")
	GET_SET_STRING(UserPassword, "Account/password", "")
	GET_SET_STRING(ApiMusicCollection, "OwnCloudAPI/musiccollection", "/owncloud/index.php/apps/music/api/collection")
};

#endif // SETTINGSMANAGER_H
