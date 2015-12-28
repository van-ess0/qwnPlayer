#include "OwnCloudClient.h"
#include <QDebug>
#include "SettingsManager.h"

OwnCloudClient::OwnCloudClient(QObject *parent) : QObject(parent)
{
	connect(&m_networkManager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
			this, SLOT(slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
	connect(&m_networkManager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(slotReplyFinished(QNetworkReply*)));
//	connect(&m_networkManager, SIGNAL())
}

void OwnCloudClient::auth()
{
	emit signalLog("HI!!!");
	m_username = SettingsManager::instance()->getUserName();
	m_password = SettingsManager::instance()->getUserPassword();

	QUrl url(SettingsManager::instance()->getOwnCloudHost());
//	url.setScheme("http");
//	url.setHost("vaness0.ga");
//	url.setPort(83);
	url.setPath(SettingsManager::instance()->getApiMusicCollection());
	url.setUserName(m_username);
	url.setPassword(m_password);

	qDebug() << url;
	emit signalLog(url.toString());

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
	emit signalLog("reply finished" + QString(reply->readAll()));

	reply->deleteLater();
	reply = NULL;
}

void OwnCloudClient::readyRead()
{
	qDebug() << "ready read";
	emit signalLog("ready read");
}

void OwnCloudClient::updateDataReadProgress(qint64,qint64)
{
	qDebug() << "update download progress";
	emit signalLog("update download progress");
}

void OwnCloudClient::slotAuthenticationRequired(QNetworkReply*, QAuthenticator*)
{
	qDebug() << "Auth required";
	emit signalLog("Auth required");

}

void OwnCloudClient::slotReplyFinished(QNetworkReply* reply)
{
	qDebug() << "Reply from " << reply->url().path();
	emit signalLog("Reply from " + reply->url().path());

	QByteArray rawData = reply->readAll();

	qDebug() << "reply finished" << rawData;
	emit signalLog("reply finished " + QString(rawData));

	emit signalCollectionData(rawData);

	reply->deleteLater();
	reply = NULL;
}

void OwnCloudClient::addAuthHeader(QNetworkRequest* request)
{
	if (!request) {
		return;
	}

	QString concatenated = m_username + ":" + m_password;
	QByteArray data = concatenated.toLocal8Bit().toBase64();
	QString headerData = "Basic " + data;
	request->setRawHeader("Authorization", headerData.toLocal8Bit());
}



