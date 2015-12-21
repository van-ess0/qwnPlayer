#ifndef ALBUM_H
#define ALBUM_H

#include <QSharedPointer>

#include "Models/SubListedListItem.h"
#include "Models/ListModel.h"
#include "Track.h"

class Album : public Models::SubListedListItem
{
	Q_OBJECT
	NEW_GLOBAL_INDEX(GlobalAlbumIndex)

private:
	QString m_name;
	quint32 m_year;

	/// TODO: add covers
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
				   QObject *parent = NULL);

	QString getName() const;
	quint32 getYear() const;
	QVariant getTracks() const;

	void addTrack(Track* track);

	// ListItem interface
public:
	virtual int id() const;
	virtual QVariant data(int role) const;
	virtual QHash<int, QByteArray> roleNames() const;

	// SubListedListItem interface
public:
	virtual Models::ListModel* submodel() const;
};

#endif // ALBUM_H
