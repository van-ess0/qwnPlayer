#include "OwnCloudClient.h"
#include <QDebug>
#include "SettingsManager.h"

OwnCloudClient::OwnCloudClient(QObject *parent) : QObject(parent)
{
	connect(&m_networkManager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
			this, SLOT(slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
	connect(&m_networkManager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(slotReplyFinished(QNetworkReply*)));
    connect(&m_networkManager, SIGNAL(networkSessionConnected()),
                this, SLOT(slotConnected()));
//	connect(&m_networkManager, SIGNAL())
}

void OwnCloudClient::auth()
{
	m_username = SettingsManager::instance()->getUserName();
	m_password = SettingsManager::instance()->getUserPassword();

	QUrl url(SettingsManager::instance()->getOwnCloudHost());
	url.setPort(SettingsManager::instance()->getOwnCloudPort().toInt());

	QString path = SettingsManager::instance()->getOwnCloudPath() +
				   SettingsManager::instance()->getApiMusicCollection();
	url.setPath(path);

	url.setUserName(SettingsManager::instance()->getUserName());
	url.setPassword(SettingsManager::instance()->getUserPassword());

	qDebug() << url;

	QNetworkRequest request(url);
	addAuthHeader(&request);

	QNetworkReply* reply = m_networkManager.get(request);
	connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
			reply, SLOT(ignoreSslErrors()));
}

void OwnCloudClient::startProcess()
{
}

void OwnCloudClient::slotReplyFinished()
{
	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

	qDebug() << "reply finished" << reply->readAll();

	reply->deleteLater();
	reply = NULL;
}

void OwnCloudClient::readyRead()
{
	qDebug() << "ready read";
}

void OwnCloudClient::updateDataReadProgress(qint64,qint64)
{
	qDebug() << "update download progress";
}

void OwnCloudClient::slotAuthenticationRequired(QNetworkReply*, QAuthenticator*)
{
	qDebug() << "Auth required";
}

void OwnCloudClient::slotReplyFinished(QNetworkReply* reply)
{
	qDebug() << "Reply from " << reply->url().path();

	QByteArray rawData = reply->readAll();

	qDebug() << "reply finished" << rawData;

	emit signalCollectionData(rawData);

	reply->deleteLater();
    reply = NULL;
}

void OwnCloudClient::slotConnected()
{
    emit signalConnected();
}

void OwnCloudClient::addAuthHeader(QNetworkRequest* request)
{
	if (!request) {
		return;
	}

	QString concatenated = SettingsManager::instance()->getUserName()
						   + ":"
						   + SettingsManager::instance()->getUserPassword();

	QByteArray data = concatenated.toLocal8Bit().toBase64();
	QString headerData = "Basic " + data;

	request->setRawHeader("Authorization", headerData.toLocal8Bit());
}



