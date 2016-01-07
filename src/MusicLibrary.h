#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <QQmlContext>

#include "Artist.h"

class MusicLibrary : public QObject
{
	Q_OBJECT

private:
	Models::SubListedListModel* m_artistModel;

public:
	explicit MusicLibrary(QQmlContext *context, QObject *parent = 0);
	Models::SubListedListModel* getArtistModel() const;

	Track* getTrack(const quint64& artistId,
					const quint64& albumId,
					const quint64& trackId) const;

	Album* getAlbum(const quint64& albumId) const;

	Album* getAlbum(const quint64& artistId,
					const quint64& albumId) const;

	Artist* getArtist(const quint64& artistId) const;

public slots:
	void slotCollectionDataParsed(QList<Artist*> artists);
};

#endif // MUSICLIBRARY_H
