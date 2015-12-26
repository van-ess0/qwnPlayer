#include "QwnSettings.h"
#include "SettingsManager.h"

#include <QFile>
#include <QStandardPaths>
#include <QDebug>

QwnSettings::QwnSettings(QObject* parent) : QObject(parent)
{
	QString homeLocation =  QStandardPaths::locate(QStandardPaths::AppLocalDataLocation,
												   QString(),
												   QStandardPaths::LocateDirectory);
	qDebug() << homeLocation;
	m_filePath = homeLocation + "qwnsettings.conf";
	qDebug() << m_filePath;

	m_url = "OwnCloud URL";
	m_username = "username";
	m_password = "password";
	m_is_initialized = false;

	connect(this, SIGNAL(urlChanged()), SLOT(slotUrlChanged()));
	connect(this, SIGNAL(usernameChanged()), SLOT(slotUsernameChanged()));
	connect(this, SIGNAL(passwordChanged()), SLOT(slotPasswordChanged()));


}

QString QwnSettings::url() const {
	return m_url;
}

QString QwnSettings::username() const {
	return m_username;
}

QString QwnSettings::password() const {
	return m_password;
}

bool QwnSettings::is_initialized() const {
	return m_is_initialized;
}

void QwnSettings::setUrl(const QString& url) {
	qDebug() << "set url";
	if (url != m_url) {
		m_url = url;
		emit urlChanged();
	}
}

void QwnSettings::setUsername(const QString& username) {
	qDebug() << "set username";
	if (username != m_username) {
		m_username = username;
		emit usernameChanged();
	}
}

void QwnSettings::setPassword(const QString& password) {
	qDebug() << "set username";
	if (password != m_password) {
		m_password = password;
		emit passwordChanged();
	}
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

	m_is_initialized = true;
}
