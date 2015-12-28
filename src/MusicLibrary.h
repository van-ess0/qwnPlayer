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
		m_artistModel->setSorting(true);
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
    void slotCollectionDataParsed(QList<Artist*> artists);
};

#endif // MUSICLIBRARY_H
