#include "QwnSettings.h"
#include "SettingsManager.h"

#include <QFile>
#include <QStandardPaths>
#include <QDebug>

QwnSettings::QwnSettings(QObject* parent) : QObject(parent)
{
	m_homeLocation =  QStandardPaths::locate(QStandardPaths::AppLocalDataLocation,
												   QString(),
												   QStandardPaths::LocateDirectory);
	qDebug() << m_homeLocation;
	m_filePath = m_homeLocation + "qwnsettings.conf";
	qDebug() << m_filePath;

	m_url = "OwnCloud URL";
	m_username = "username";
	m_password = "password";
	m_is_initialized = false;

	connect(this, SIGNAL(urlChanged()), SLOT(slotUrlChanged()));
	connect(this, SIGNAL(usernameChanged()), SLOT(slotUsernameChanged()));
	connect(this, SIGNAL(passwordChanged()), SLOT(slotPasswordChanged()));

}

void QwnSettings::slotUrlChanged() {
	qDebug() << "slot url";
	SettingsManager::instance()->setOwnCloudHost(m_url);
}

void QwnSettings::slotUsernameChanged() {
	qDebug() << "slot username";
	SettingsManager::instance()->setUserName(m_username);
}

void QwnSettings::slotPasswordChanged() {
	qDebug() << "slot password";
	SettingsManager::instance()->setUserPassword(m_password);
}

void QwnSettings::initialize() {
	if (m_is_initialized) {
		qDebug() << "already initialized";
		return;
	}

	SettingsManager::instance()->setFile(m_filePath);

	if (!QFile::exists(m_filePath)) {
		SettingsManager::instance()->setOwnCloudHost(m_url);
		SettingsManager::instance()->setUserName(m_username);
		SettingsManager::instance()->setUserPassword(m_password);
	} else {
		setUrl(SettingsManager::instance()->getOwnCloudHost());
		setUsername(SettingsManager::instance()->getUserName());
		setPassword(SettingsManager::instance()->getUserPassword());
	}
	SettingsManager::instance()->setApiMusicCollection("/owncloud/index.php/apps/music/api/collection");
	SettingsManager::instance()->setHomeLocation(m_homeLocation);

	m_is_initialized = true;
}
