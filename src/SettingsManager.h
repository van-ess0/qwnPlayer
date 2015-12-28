#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include "SingletonTemplate.h"
#include "Macros.h"

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

	GET_SET_STRING(HomeLocation, "App/homelocation", "./")
};

#endif // SETTINGSMANAGER_H
