#include "QwnSettings.h"
#include "SettingsManager.h"

#include <QFile>
#include <QStandardPaths>
#include <QDebug>

QwnSettings::QwnSettings(QObject* parent) : QObject(parent)
{
	m_homeLocation = QStandardPaths::locate(QStandardPaths::DataLocation,
											QString(),
											QStandardPaths::LocateDirectory);
	qDebug() << m_homeLocation;
	m_filePath = m_homeLocation + "qwnsettings.conf";
	qDebug() << m_filePath;

	m_url = "";
	m_url_port = "";
	m_url_path = "";

	m_username = "";
	m_password = "";

	m_is_initialized = false;

	m_globalAccentColor				= "skyblue";
	m_globalBackgroundColor			= "black";
	m_globalRectangleColor			= "#111111";
	m_globalRectangleBorderColor	= "#171717";

	m_menuShowPermanent = false;

	m_isFirstLaunch = true;

	connect(this, SIGNAL(urlChanged()), SLOT(slotUrlChanged()));
	connect(this, SIGNAL(urlPortChanged()), SLOT(slotUrlPortChanged()));
	connect(this, SIGNAL(urlPathChanged()), SLOT(slotUrlPathChanged()));

	connect(this, SIGNAL(usernameChanged()), SLOT(slotUsernameChanged()));
	connect(this, SIGNAL(passwordChanged()), SLOT(slotPasswordChanged()));

	connect(this, SIGNAL(globalAccentColorChanged()), SLOT(slotGlobalAccentColorChanged()));
	connect(this, SIGNAL(globalBackgroundColorChanged()), SLOT(slotGlobalBackgroundColorChanged()));
	connect(this, SIGNAL(globalRectangleColorChanged()), SLOT(slotGlobalRectangleColorChanged()));
	connect(this, SIGNAL(globalRectangleBorderColorChanged()), SLOT(slotGlobalRectangleBorderColorChanged()));
	connect(this, SIGNAL(menuShowPermanentChanged()), SLOT(slotMenuShowPermanentChanged()));
}

void QwnSettings::slotUrlChanged()
{
	SettingsManager::instance()->setOwnCloudHost(m_url);
}

void QwnSettings::slotUrlPortChanged()
{
	SettingsManager::instance()->setOwnCloudPort(m_url_port);
}

void QwnSettings::slotUrlPathChanged()
{
	SettingsManager::instance()->setOwnCloudPath(m_url_path);
}

void QwnSettings::slotUsernameChanged()
{
	SettingsManager::instance()->setUserName(m_username);
}

void QwnSettings::slotPasswordChanged()
{
	SettingsManager::instance()->setUserPassword(m_password);
}

void QwnSettings::slotGlobalAccentColorChanged()
{
	SettingsManager::instance()->setGlobalAccentColor(m_globalAccentColor);
}

void QwnSettings::slotGlobalBackgroundColorChanged()
{
	SettingsManager::instance()->setGlobalBackgroundColor(m_globalBackgroundColor);
}

void QwnSettings::slotGlobalRectangleColorChanged()
{
	SettingsManager::instance()->setGlobalRectangleColor(m_globalRectangleColor);
}

void QwnSettings::slotGlobalRectangleBorderColorChanged()
{
	SettingsManager::instance()->setGlobalRectangleBorderColor(m_globalRectangleBorderColor);
}

void QwnSettings::slotMenuShowPermanentChanged()
{
	SettingsManager::instance()->setMenuShowPermant(m_menuShowPermanent);
}

void QwnSettings::initialize()
{
	if (m_is_initialized) {
		qDebug() << "already initialized";
		return;
	}

	SettingsManager::instance()->setFile(m_filePath);

	if (!QFile::exists(m_filePath)) {
		SettingsManager::instance()->setOwnCloudHost(m_url);
		SettingsManager::instance()->setOwnCloudPort(m_url_port);
		SettingsManager::instance()->setOwnCloudPath(m_url_path);

		SettingsManager::instance()->setUserName(m_username);
		SettingsManager::instance()->setUserPassword(m_password);

		SettingsManager::instance()->setGlobalAccentColor(m_globalAccentColor);
		SettingsManager::instance()->setGlobalBackgroundColor(m_globalBackgroundColor);
		SettingsManager::instance()->setGlobalRectangleColor(m_globalRectangleColor);
		SettingsManager::instance()->setGlobalRectangleBorderColor(m_globalRectangleBorderColor);

		SettingsManager::instance()->setMenuShowPermant(m_menuShowPermanent);

	} else {
		setUrl(SettingsManager::instance()->getOwnCloudHost());
		setUrlPort(SettingsManager::instance()->getOwnCloudPort());
		setUrlPath(SettingsManager::instance()->getOwnCloudPath());

		setUsername(SettingsManager::instance()->getUserName());
		setPassword(SettingsManager::instance()->getUserPassword());

		setGlobalAccentColor(SettingsManager::instance()->getGlobalAccentColor());
		setGlobalBackgroundColor(SettingsManager::instance()->getGlobalBackgroundColor());
		setGlobalRectangleColor(SettingsManager::instance()->getGlobalRectangleColor());
		setGlobalRectangleBorderColor(SettingsManager::instance()->getGlobalRectangleBorderColor());

		setMenuShowPermanent(SettingsManager::instance()->getMenuShowPermant());
		// WTF?!
//		emit signalSettingsFilled();
		m_isFirstLaunch = false;
	}

	SettingsManager::instance()->setApiMusicCollection("/apps/music/api/collection");
	SettingsManager::instance()->setApiCover("/apps/music/api/album/");
	SettingsManager::instance()->setHomeLocation(m_homeLocation);



	m_is_initialized = true;
}

void QwnSettings::saveAllSettings()
{
	SettingsManager::instance()->setOwnCloudHost(m_url);
	SettingsManager::instance()->setUserName(m_username);
	SettingsManager::instance()->setUserPassword(m_password);

	SettingsManager::instance()->setApiMusicCollection("/owncloud/index.php/apps/music/api/collection");
	SettingsManager::instance()->setApiCover("/owncloud/index.php/apps/music/api/album/");
	SettingsManager::instance()->setHomeLocation(m_homeLocation);

	SettingsManager::instance()->setGlobalAccentColor(m_globalAccentColor);
	SettingsManager::instance()->setGlobalBackgroundColor(m_globalBackgroundColor);
	SettingsManager::instance()->setGlobalRectangleColor(m_globalRectangleColor);
	SettingsManager::instance()->setGlobalRectangleBorderColor(m_globalRectangleBorderColor);

	SettingsManager::instance()->setMenuShowPermant(m_menuShowPermanent);
}
