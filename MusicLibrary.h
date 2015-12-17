#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include "Artist.h"

class MusicLibrary : public QObject
{
	Q_OBJECT
//	Q_PROPERTY(QList<QObject*> artistList READ getArtistList WRITE setArtistList NOTIFY artistListChanged)

private:
//	QList<QObject*> m_artists;
	Models::SubListedListModel* m_artistModel;

public:
	explicit MusicLibrary(QObject *parent = 0) : QObject(parent)
	{
		m_artistModel = new Models::SubListedListModel(new Artist("empty", NULL));
	}

//	QList<QObject*> getArtistList() const {
//		return m_artists;
//	}

	Models::SubListedListModel* getArtistModel() const {
		return m_artistModel;
	}

//	void setArtistList(const QList<QObject*>& artists) {
//		m_artists = artists;
//		emit artistListChanged();
//	}

//signals:
//	void artistListChanged();

public slots:
	void slotCollectionDataParsed(QList<Artist*> artists) {
		foreach (Artist* value, artists) {
			m_artistModel->appendRow(value);
		}
//		setArtistList(artists);
	}
//	void slotCollectionDataParsed(Models::SubListedListModel* artistModel) {
//		m_artistModel = artistModel;
//		emit artistListChanged();
//		Track* track_one = new Track(1, "Number One", "audio/mp3", "./one.mp3");
//		Track* track_two = new Track(2, "Number Two", "audio/mp3", "./two.mp3");
//		Album* album_one = new Album("Album One", 2001);
//		album_one->addTrack(track_one);
//		album_one->addTrack(track_two);

//		Track* track_three = new Track(3, "Number 3", "audio/mp3", "./three.mp3");
//		Track* track_four = new Track(4, "Number 4", "audio/mp3", "./four.mp3");

//		Album* album_two = new Album("Album Two", 2002);
//		album_two->addTrack(track_three);
//		album_two->addTrack(track_four);

//		Artist* artist_one = new Artist("Artist One");
//		artist_one->addAlbum(album_one);
//		artist_one->setName("Artist One");

//		Artist* artist_two = new Artist("Artist Two");
//		artist_two->addAlbum(album_two);
//		artist_two->setName("Artist Two");

//		QList<QObject*> artists;
//		artists.append(artist_one);
//		artists.append(artist_two);

//		m_artistModel->appendRow(artist_one);
//		m_artistModel->appendRow(artist_two);

//	}
};

#endif // MUSICLIBRARY_H
