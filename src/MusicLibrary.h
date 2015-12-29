#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include "Artist.h"

class MusicLibrary : public QObject
{
	Q_OBJECT

private:
	Models::SubListedListModel* m_artistModel;

public:
	explicit MusicLibrary(QObject *parent = 0);
	Models::SubListedListModel* getArtistModel() const;

	Models::ListItem* getAlbumById(const quint64& id);

public slots:
	void slotCollectionDataParsed(QList<Artist*> artists);
};

#endif // MUSICLIBRARY_H
