#ifndef ARTIST_H
#define ARTIST_H

#include "Models/SubListedListModel.h"
#include "Album.h"

class Artist : public Models::SubListedListItem
{
	Q_OBJECT
	NEW_GLOBAL_INDEX(GlobalArtistIndex)

private:
	QString m_name;

	quint64 m_globalId;

	enum ArtistModelItemRoles {
		artistId = Qt::UserRole + 1,
		artistName,
		artistAlbums
	};

	QSharedPointer<Models::SubListedListModel> m_albumsModel;

public:
	explicit Artist(const QString& name,
					QObject *parent = 0);

	QString getName() const;
	QVariant getAlbums() const;

	void addAlbum(Album* album);

signals:
	void nameChanged();
	void albumListChanged();

	// ListItem interface
public:
	virtual int id() const;
	virtual QVariant data(int role) const;
	virtual QHash<int, QByteArray> roleNames() const;
	bool operator <(const ListItem &nextElem);

	// SubListedListItem interface
public:
	virtual Models::ListModel* submodel() const;
};

#endif // ARTIST_H
