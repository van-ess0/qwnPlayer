#ifndef RESPONSEDECODER_H
#define RESPONSEDECODER_H

#include <QJsonObject>
#include "Artist.h"

class ResponseDecoder : public QObject
{
	Q_OBJECT
public:
	explicit ResponseDecoder(QObject *parent = 0);


	void decode(const QString& dataType, const QByteArray& data);

private:
	void decodeCollection(const QByteArray& data);

	Track* createTrack(const QJsonObject& jsonObject, Album* albumParent);
	Album* createAlbum(const QJsonObject& jsonObject, Artist* artistParent);
	Artist* createArtist(const QJsonObject& jsonObject, QObject* parent = NULL);

	Album* assembleAlbum(const QJsonObject& albumJson, Artist* artist);
	Artist* assembleArtist(const QJsonObject& artistJson);
	QList<Artist*> assembleLibrary(const QJsonArray& artistArray);

public slots:
	void slotCollectionData(QByteArray);

signals:
	void signalCollectionDataParsed(QList<Artist*>);
};

#endif // RESPONSEDECODER_H
