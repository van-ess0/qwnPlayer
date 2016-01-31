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

	GET_SET_STRING(OwnCloudHost, "Network/owncloudhost", "")
	GET_SET_STRING(UserName, "Account/username", "")
	GET_SET_STRING(UserPassword, "Account/password", "")
	GET_SET_STRING(ApiMusicCollection, "OwnCloudAPI/musiccollection", "/owncloud/index.php/apps/music/api/collection")
	GET_SET_STRING(ApiCover, "OwnCloudAPI/cover", "/owncloud/index.php/apps/music/api/album/")

	GET_SET_STRING(HomeLocation, "App/homelocation", "./")

	GET_SET_STRING(GlobalAccentColor, "UI/globalAccentColor", "skyblue")
	GET_SET_STRING(GlobalBackgroundColor, "UI/globalBackgroundColor", "black")
	GET_SET_STRING(GlobalRectangleColor, "UI/globalRectangleColor", "#111111")
	GET_SET_STRING(GlobalRectangleBorderColor, "UI/globalRectangleBorderColor", "#171717")
	GET_SET_BOOL(MenuShowPermant, "UI/menuShowPermanent", true)
};

#endif // SETTINGSMANAGER_H
