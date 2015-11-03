#ifndef ARTIST_H
#define ARTIST_H

#include <QList>
#include "Album.h"

class Artist : public QObject
{
	Q_OBJECT

private:
	QString m_name;
	QList<Album*> m_albums;

public:
	explicit Artist(const QString& name,
					QObject *parent = 0);
	QString getName() const {
		return m_name;
	}
	// You need to check on empty list
	QList<Album*> getAlbumList() const{
		return m_albums;
	}
	void addAlbum(Album* album) {
		m_albums.append(album);
	}
};

Q_DECLARE_METATYPE(QList<Artist*>)

#endif // ARTIST_H
