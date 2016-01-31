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

	m_url = "OwnCloud URL";
	m_username = "username";
	m_password = "password";
	m_is_initialized = false;

	m_globalAccentColor				= "skyblue";
	m_globalBackgroundColor			= "black";
	m_globalRectangleColor			= "#111111";
	m_globalRectangleBorderColor	= "#171717";

	m_menuShowPermanent = true;

	connect(this, SIGNAL(urlChanged()), SLOT(slotUrlChanged()));
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
	qDebug() << "slot url";
	SettingsManager::instance()->setOwnCloudHost(m_url);
}

void QwnSettings::slotUsernameChanged()
{
	qDebug() << "slot username";
	SettingsManager::instance()->setUserName(m_username);
}

void QwnSettings::slotPasswordChanged()
{
	qDebug() << "slot password";
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
		SettingsManager::instance()->setUserName(m_username);
		SettingsManager::instance()->setUserPassword(m_password);

		SettingsManager::instance()->setGlobalAccentColor(m_globalAccentColor);
		SettingsManager::instance()->setGlobalBackgroundColor(m_globalBackgroundColor);
		SettingsManager::instance()->setGlobalRectangleColor(m_globalRectangleColor);
		SettingsManager::instance()->setGlobalRectangleBorderColor(m_globalRectangleBorderColor);

		SettingsManager::instance()->setMenuShowPermant(m_menuShowPermanent);

	} else {
		setUrl(SettingsManager::instance()->getOwnCloudHost());
		setUsername(SettingsManager::instance()->getUserName());
		setPassword(SettingsManager::instance()->getUserPassword());

		setGlobalAccentColor(SettingsManager::instance()->getGlobalAccentColor());
		setGlobalBackgroundColor(SettingsManager::instance()->getGlobalBackgroundColor());
		setGlobalRectangleColor(SettingsManager::instance()->getGlobalRectangleColor());
		setGlobalRectangleBorderColor(SettingsManager::instance()->getGlobalRectangleBorderColor());

		setMenuShowPermanent(SettingsManager::instance()->getMenuShowPermant());
		// WTF?!
//		emit signalSettingsFilled();
	}
	SettingsManager::instance()->setApiMusicCollection("/owncloud/index.php/apps/music/api/collection");
	SettingsManager::instance()->setApiCover("/owncloud/index.php/apps/music/api/album/");
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
