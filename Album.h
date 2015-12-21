#ifndef ALBUM_H
#define ALBUM_H

#include <QList>
#include <QVariantList>
#include <QSharedPointer>
#include "Track.h"
#include "Models/SubListedListItem.h"
#include "Models/ListModel.h"

template <typename T>
QVariantList toVariantList( const QList<T> &list )
{
	QVariantList newList;
	foreach( const T &item, list ) {
		newList << QVariant::fromValue<T>(item);
	}
	return newList;
}

template <typename T>
QList<T> fromVariantList( const QVariantList &list )
{
	QList<T> newList;
	foreach( const QVariant &item, list ) {
		T value = item.value<T>();
		newList << value;
	}

	return newList;
}

class Album : public Models::SubListedListItem
{
	Q_OBJECT
	NEW_GLOBAL_INDEX(GlobalAlbumIndex)

private:
	QString m_name;
	quint32 m_year;
//	QList<Track*> m_tracks;
	/// TODO
	// QByteArray m_cover;

	quint64 m_globalId;

	enum AlbumModelItemRoles {
		albumId = Qt::UserRole + 1,
		albumName,
		albumYear,
		albumTracks
	};

	QSharedPointer<Models::ListModel> m_tracksModel;

public:
	explicit Album(const QString& name,
				   const quint32 year,
				   QObject *parent = NULL)
		:
		  SubListedListItem(parent)
	{
		m_name		= name;
		m_year		= year;
		m_globalId	= GlobalAlbumIndex::instance()->getIndex();

		m_tracksModel = QSharedPointer<Models::ListModel>(new Models::ListModel(new Track(0, "empty", "empty", "empty", NULL)));
	}

	QString getName() const {
		return m_name;
	}
	quint32 getYear() const {
		return m_year;
	}

	// You need to check on emppty list
//	QList<Track*> getTrackList() const {
//		return m_tracks;
//	}
	void addTrack(Track* track) {
//		m_tracks.append(track);

		m_tracksModel->appendRow(track);
	}

	QList< QSharedPointer<Models::ListItem> > getTracks() const {

		QList<Models::ListItem*> tracks = m_tracksModel->toList();
		QList< QSharedPointer<Models::ListItem> > tracks_sp;
		foreach (Models::ListItem* track, tracks) {
			QSharedPointer<Models::ListItem> pointer
					= QSharedPointer<Models::ListItem>(track);
			tracks_sp << pointer;

		}

		return tracks_sp;
	}



	// ListItem interface
public:
	virtual int id() const
	{
		return m_globalId;
	}
	virtual QVariant data(int role) const
	{
		switch (role) {
		case albumId:
			return this->id();
		case albumName:
			return this->getName();
		case albumYear:
			return this->getYear();
		case albumTracks:
			return QVariant::fromValue< QSharedPointer<Models::ListModel> >(this->m_tracksModel);
		default:
			return QVariant();
		}
	}
	virtual QHash<int, QByteArray> roleNames() const
	{
		QHash<int, QByteArray> roles;

		roles[albumId]		= "albumId";
		roles[albumName]	= "albumName";
		roles[albumYear]	= "albumYear";
		roles[albumTracks]	= "albumTracks";

		return roles;
	}

	// SubListedListItem interface
public:
	virtual Models::ListModel* submodel() const
	{
		return m_tracksModel.data();
	}
};

#endif // ALBUM_H
