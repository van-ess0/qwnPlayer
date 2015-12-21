#ifndef ARTIST_H
#define ARTIST_H

#include <QList>
#include "Album.h"
#include "Models/SubListedListModel.h"

class Artist : public Models::SubListedListItem
{
	Q_OBJECT
	NEW_GLOBAL_INDEX(GlobalArtistIndex)

//	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
//	Q_PROPERTY(QList<QObject*> albumList READ albumList WRITE setAlbumList NOTIFY albumListChanged)
	//Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)

private:
	QString m_name;
//	QList<QObject*> m_albums;

	quint64 m_globalId;

	enum ArtistModelItemRoles {
		artistId = Qt::UserRole + 1,
		artistName,
		artistAlbums
//		albumYear,
//		albumTracks
	};

	QSharedPointer<Models::SubListedListModel> m_albumsModel;

public:
	explicit Artist(const QString& name,
					QObject *parent = 0)
		:
		  SubListedListItem(parent)
	{
		m_name		= name;
		m_globalId	= GlobalArtistIndex::instance()->getIndex();

		m_albumsModel = QSharedPointer<Models::SubListedListModel>(new Models::SubListedListModel(new Album("empty", 0, NULL)));
	}

	QString getName() const {
		return m_name;
	}
//	void setName(const QString& name) {
//		if (name != m_name) {
//			m_name = name;
//			emit nameChanged();
//		}
//	}

	QVariant getAlbums() const {

		return QVariant::fromValue< QSharedPointer<Models::SubListedListModel> >(m_albumsModel);
	}


	// You need to check on empty list
//	QList<QObject*> albumList() const{
//		return m_albums;
//	}
//	void setAlbumList(const QList<QObject*>& albums) {
//		m_albums = albums;
//		emit albumListChanged();
//	}
	void addAlbum(Album* album) {
//		m_albums.append(album);
//		emit albumListChanged();

		m_albumsModel->appendRow(album);
	}

signals:
	void nameChanged();
	void albumListChanged();

	// ListItem interface
public:
	virtual int id() const
	{
		return m_globalId;
	}
	virtual QVariant data(int role) const
	{
		switch (role) {
		case artistId:
			return this->id();
		case artistName:
			return this->getName();
		case artistAlbums:
			return this->getAlbums();
		default:
			return QVariant();
		}
	}
	virtual QHash<int, QByteArray> roleNames() const
	{
		QHash<int, QByteArray> roles;

		roles[artistId]		= "artistId";
		roles[artistName]	= "artistName";
		roles[artistAlbums] = "artistAlbums";
//		roles[albumYear]	= "albumYear";
//		roles[albumTracks]	= "albumTracks";

		return roles;
	}

	// SubListedListItem interface
public:
	virtual Models::ListModel* submodel() const
	{
		return m_albumsModel.data();
	}
};

Q_DECLARE_METATYPE(QList<Artist*>)
Q_DECLARE_METATYPE(Models::SubListedListModel*)

#endif // ARTIST_H
