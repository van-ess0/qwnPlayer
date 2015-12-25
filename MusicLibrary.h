#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include "Artist.h"

class MusicLibrary : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QList<QObject*> artistList READ getArtistList WRITE setArtistList NOTIFY artistListChanged)

private:
	QList<QObject*> m_artists;

public:
	explicit MusicLibrary(QObject *parent = 0);

	QList<QObject*> getArtistList() const {
		return m_artists;
	}

	void setArtistList(const QList<QObject*>& artists) {
		m_artists = artists;
		emit artistListChanged();
	}

signals:
	void artistListChanged();

public slots:
	void slotCollectionDataParsed(QList<QObject*> artists) {
		setArtistList(artists);
	}
};

#endif // MUSICLIBRARY_H
