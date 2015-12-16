#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include "SingletonTemplate.h"

#define GET_STRING(NAME, KEY, DEFAULT_VALUE) \
	QString get##NAME() const { \
		QSettings settings(m_filename, QSettings::IniFormat); \
		return settings.value(KEY, DEFAULT_VALUE).toString(); \
	}


class SettingsManager :
		public QObject,
		public SingletonTemplate<SettingsManager>
{
	Q_OBJECT

	QString m_filename;

public:
	explicit SettingsManager(QObject *parent = 0) :
		QObject(parent)
	{
		m_filename = "";
	}

	void setFile(QString filepath) {
		m_filename = filepath;
	}

	GET_STRING(OwnCloudHost, "Network/owncloudhost", "http://vaness0.ga:83/owncloud")
	GET_STRING(UserName, "Account/username", "degree")
	GET_STRING(UserPassword, "Account/password", "Fcnhjabpbrf95")
	GET_STRING(ApiMusicCollection, "OwnCloudAPI/musiccollection", "/index.php/apps/music/api/collection")
};

#endif // SETTINGSMANAGER_H
