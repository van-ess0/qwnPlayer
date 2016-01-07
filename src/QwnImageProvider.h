#ifndef QWNIMAGEPROVIDER_H
#define QWNIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "SettingsManager.h"

class QwnImageProvider : public QQuickImageProvider
{

private:
	QNetworkAccessManager manager;

public:
	QwnImageProvider(ImageType type, Flags flags = 0);

	~QwnImageProvider();

	QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);

	void addAuthHeader(QNetworkRequest* request);
};

#endif // QWNIMAGEPROVIDER_H
