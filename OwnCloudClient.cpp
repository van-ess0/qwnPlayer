#include "OwnCloudClient.h"
#include <QDebug>

OwnCloudClient::OwnCloudClient(QObject *parent) : QObject(parent)
{
	connect(&m_networkManager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
			this, SLOT(slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
	connect(&m_networkManager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(slotReplyFinished(QNetworkReply*)));
}

void OwnCloudClient::auth()
{
	m_username = "degree";
	m_password = "Fcnhjabpbrf95";

	QUrl url;
	url.setScheme("http");
	url.setHost("192.168.237.129");
	url.setPort(8080);
	url.setPath("/index.php/apps/music/api/collection");
	url.setUserName(m_username);
	url.setPassword(m_password);

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
	qDebug() << "reply finished" << reply->readAll();

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



