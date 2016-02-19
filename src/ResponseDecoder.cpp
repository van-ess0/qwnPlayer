#include "ResponseDecoder.h"

#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>


ResponseDecoder::ResponseDecoder(QObject *parent) : QObject(parent)
{

}

void ResponseDecoder::decode(const QString& dataType, const QByteArray& data)
{
	Q_UNUSED(dataType)
	decodeCollection(data);
}

void ResponseDecoder::decodeCollection(const QByteArray& data)
{

	// Looking for artists in json
	QJsonDocument doc = QJsonDocument::fromJson(data);
	QList<Artist*> library = assembleLibrary(doc.array());

	// TODO: need to move forward the artist list
	emit signalCollectionDataParsed(library);
}

Track* ResponseDecoder::createTrack(const QJsonObject& jsonObject, Album* albumParent)
{
	// Parsing audio type, because
	// json key is string description of type
	QJsonObject file = jsonObject["files"].toObject();
	QString type = file.keys().first();

	// Creating new track object
	Track* track = new Track(
							// Track number
							jsonObject["number"].toInt(),
							// Title
							jsonObject["title"].toString(),
							// Audio type (flac, mpeg)
							type,
							// Server path to file
							jsonObject["files"].toObject()[type].toString(),
							// Album ID
							albumParent->id(),
							// parent object
							albumParent
						);

	return track;
}

Album* ResponseDecoder::createAlbum(const QJsonObject& jsonObject, Artist* artistParent)
{
	// Creating new album object
	Album* album = new Album(
							// Album name
							jsonObject["name"].toString(),
							// Year
							jsonObject["year"].toInt(),
							// Owncloud ID (for cover)
							jsonObject["id"].toInt(),
							// Cover
							jsonObject["cover"].toString(),
							// Artist ID
							artistParent->id(),
							// parent object
							artistParent
						);

	return album;
}

Artist* ResponseDecoder::createArtist(const QJsonObject& jsonObject, QObject* parent)
{
	// Creating new artist object
	Artist* artist = new Artist(jsonObject["name"].toString(), parent);

	return artist;
}

Album* ResponseDecoder::assembleAlbum(const QJsonObject& albumJson, Artist* artist)
{
	// Creating album from json
	Album* album = createAlbum(albumJson, artist);

	// Looking for tracks in json
	QJsonArray trackArray = albumJson["tracks"].toArray();

	foreach (const QJsonValue& trackJsonValue, trackArray) {

		// Creating track from json
		Track* track = createTrack(trackJsonValue.toObject(), album);

		// Adding track to album
		album->addTrack(track);
	}

	return album;
}

Artist* ResponseDecoder::assembleArtist(const QJsonObject& artistJson)
{
	// Creating artist from json
	Artist* artist = createArtist(artistJson);

	// Looking for albums in json
	QJsonArray albumArray = artistJson["albums"].toArray();

	foreach (const QJsonValue& albumJsonValue, albumArray) {
		// Adding album with tracks to artist
		artist->addAlbum(assembleAlbum(albumJsonValue.toObject(), artist));

	}

	return artist;
}

QList<Artist*> ResponseDecoder::assembleLibrary(const QJsonArray& artistArray)
{
	QList<Artist*> artists;
	foreach (const QJsonValue& artistJsonValue, artistArray) {
		// Adding artist to list
		artists.append(assembleArtist(artistJsonValue.toObject()));
	}
	return artists;
}

void ResponseDecoder::slotCollectionData(QByteArray rawData)
{
	decode("EMPTY", rawData);
}

