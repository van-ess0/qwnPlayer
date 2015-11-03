#include "ResponseDecoder.h"

#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

ResponseDecoder::ResponseDecoder(QObject *parent) : QObject(parent)
{

}

void ResponseDecoder::decode(const QString& dataType, const QByteArray& data)
{
	decodeCollection(data);
}

void ResponseDecoder::decodeCollection(const QByteArray& data)
{
	QList<Artist*> artists;

	// Looking for artists in json
	QJsonDocument doc = QJsonDocument::fromJson(data);
	QJsonArray artistArray = doc.array();

	foreach (const QJsonValue& artistJsonValue, artistArray) {

		// Strange casting.. whatever
		QJsonObject artistJson = artistJsonValue.toObject();

		// Creating new artist object
		Artist* artist = new Artist(artistJson["name"].toString());

		// Looking for albums in json
		QJsonArray albumArray = artistJson["albums"].toArray();

		foreach (const QJsonValue& albumJsonValue, albumArray) {

			// Strange casting.. whatever
			QJsonObject albumJson = albumJsonValue.toObject();

			// Creating new album object
			Album* album = new Album(
								// Album name
								albumJson["name"].toString(),
								// Year
								albumJson["year"].toInt(),
								// parent object
								artist);


			// Looking for tracks in json
			QJsonArray trackArray = albumJson["tracks"].toArray();

			foreach (const QJsonValue& trackJsonValue, trackArray) {

				// Strange casting.. whatever
				QJsonObject trackJson = trackJsonValue.toObject();

				// Parsing audio type, because
				// json key is string description of type
				QJsonObject file = trackJson["files"].toObject();
				QString type = file.keys().first();

				// Creating new track object
				Track* track = new Track(
									// Track number
									trackJson["number"].toInt(),
									// Title
									trackJson["title"].toString(),
									// Audio type (flac, mpeg)
									type,
									// Server path to file
									trackJson["files"].toObject()[type].toString(),
									// parent object
									album);

				// Adding track to album
				album->addTrack(track);
			}

			// Adding album with tracks to artist
			artist->addAlbum(album);

		}

		// Adding artist to list
		artists.append(artist);
	}

	// TODO: need to move forward the artist list
	emit signalCollectionDataParsed(artists);
}

void ResponseDecoder::slotCollectionData(QByteArray rawData)
{
	decode("EMPTY", rawData);
}

