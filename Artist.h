#ifndef ARTIST_H
#define ARTIST_H

#include <QList>
#include "Album.h"

class Artist : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QList<QObject*> albumList READ albumList WRITE setAlbumList NOTIFY albumListChanged)
	//Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)

private:
	QString m_name;
	QList<QObject*> m_albums;

public:
	explicit Artist(const QString& name,
					QObject *parent = 0);

	QString name() const {
		return m_name;
	}
	void setName(const QString& name) {
		if (name != m_name) {
			m_name = name;
			emit nameChanged();
		}
	}


	// You need to check on empty list
	QList<QObject*> albumList() const{
		return m_albums;
	}
	void setAlbumList(const QList<QObject*>& albums) {
		m_albums = albums;
		emit albumListChanged();
	}
	void addAlbum(Album* album) {
		m_albums.append(album);
		emit albumListChanged();
	}

signals:
	void nameChanged();
	void albumListChanged();
};

Q_DECLARE_METATYPE(QList<Artist*>)

#endif // ARTIST_H
