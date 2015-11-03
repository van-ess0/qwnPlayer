#include "ResponseDecoder.h"

#include "Artist.h"

ResponseDecoder::ResponseDecoder(QObject *parent) : QObject(parent)
{

}

void ResponseDecoder::decode(const QString& dataType, const QByteArray& data)
{
	decodeCollection(data);
}

void ResponseDecoder::decodeCollection(const QByteArray& data)
{
	QJsonDocument doc = QJsonDocument::fromBinaryData(data);

	QJsonArray artistArray = doc.array();
	QList<Artist*> listOfArtists;
	foreach (QJsonObject artistJson, artistArray) {

		Artist* artist = new Artist(artistJson["name"].toString());

		QJsonArray albumArray = artistJson["albums"].toArray();

		foreach (QJsonObject albumJson, albumArray) {
			Album* album = new Album(albumJson["name"].toString(),
					albumJson["year"].toInt(), artist];
		}
	}
}

