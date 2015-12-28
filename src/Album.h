#ifndef ALBUM_H
#define ALBUM_H

#include <QSharedPointer>

#include "Models/SubListedListItem.h"
#include "Models/ListModel.h"
#include "Track.h"

class Album : public Models::SubListedListItem {
	Q_OBJECT
	NEW_GLOBAL_INDEX(GlobalAlbumIndex)

private:
	QString m_name;
	quint32 m_year;

	// path on server (in case OwnCloud music app will work fine)
	QString m_cover;

	quint64 m_globalId;

	enum AlbumModelItemRoles {
		albumId = Qt::UserRole + 1,
		albumName,
		albumYear,
		albumTracks,
		albumCover
	};

	QSharedPointer<Models::ListModel> m_tracksModel;

public:
	explicit Album(const QString& name,
				   const quint32 year,
				   const QString& cover,
				   QObject *parent = NULL);

	QString getName() const;
	quint32 getYear() const;
	QVariant getTracks() const;
	QString getCover() const;

	void addTrack(Track* track);

	// ListItem interface
public:
	virtual int id() const;
	virtual QVariant data(int role) const;
	virtual QHash<int, QByteArray> roleNames() const;
	virtual bool operator <(const ListItem& nextElem);

	// SubListedListItem interface
public:
	virtual Models::ListModel* submodel() const;
};

#endif // ALBUM_H
