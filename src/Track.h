#ifndef TRACK_H
#define TRACK_H

#include "Models/ListItem.h"
#include "GlobalIndex.h"

class Track : public Models::ListItem
{
	Q_OBJECT
	NEW_GLOBAL_INDEX(GlobalTrackIndex)

private:
	quint32 m_number;
	QString m_title;
	QString m_audioType;
	QString m_serverPath;

	quint64 m_globalId; // track
	quint64 m_albumId;
	
	enum TrackModelItemRoles {
		trackId = Qt::UserRole + 1,
		trackNumber,
		trackTitle,
		trackAudioType,
		trackServerPath,
		trackAlbumId
	};


public:
	explicit Track(const quint32 number,
				   const QString& title,
				   const QString& type,
				   const QString& path,
				   const quint64& trackAlbumId,
				   QObject *parent = 0);
	quint32 getNumber() const;
	QString getTitle() const;
	QString getAudioType() const;
	QString getServerPath() const;
	quint64 getAlbumId() const;

	// ListItem interface
public:
	virtual int id() const;
	virtual QVariant data(int role) const;
	virtual QHash<int, QByteArray> roleNames() const;
	virtual bool operator <(const ListItem& nextElem);
};

#endif // TRACK_H
