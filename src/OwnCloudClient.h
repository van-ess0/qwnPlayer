#ifndef OWNCLOUDCLIENT_H
#define OWNCLOUDCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

class OwnCloudClient : public QObject
{
	Q_OBJECT

private:
	QNetworkAccessManager m_networkManager;

	QString m_username;
	QString m_password;

public:
	explicit OwnCloudClient(QObject *parent = 0);
	void startProcess();

signals:
	void signalCollectionData(QByteArray);
	void signalConnected();

public slots:
	void auth();

private slots:
	void slotReplyFinished();
	void readyRead();
	void updateDataReadProgress(qint64,qint64);
	void slotAuthenticationRequired(QNetworkReply*,QAuthenticator*);
	void slotReplyFinished(QNetworkReply* reply);
    void slotConnected();

private:
	void addAuthHeader(QNetworkRequest* request);
};

#endif // OWNCLOUDCLIENT_H
