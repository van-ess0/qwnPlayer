#ifndef TRACK_H
#define TRACK_H

#include "Models/ListItem.h"
#include "GlobalIndex.h"

class Track : public Models::ListItem {
	Q_OBJECT
	NEW_GLOBAL_INDEX(GlobalTrackIndex)

private:
	quint32 m_number;
	QString m_title;
	QString m_audioType;
	QString m_serverPath;

	quint64 m_globalId;
	
	enum TrackModelItemRoles {
		trackId = Qt::UserRole + 1,
		trackNumber,
		trackTitle,
		trackAudioType,
		trackServerPath
	};

public:
	explicit Track(const quint32 number,
				   const QString& title,
				   const QString& type,
				   const QString& path,
				   QObject *parent = 0);
	quint32 getNumber() const;
	QString getTitle() const;
	QString getAudioType() const;
	QString getServerPath() const;

	// ListItem interface
public:
	virtual int id() const;
	virtual QVariant data(int role) const;
	virtual QHash<int, QByteArray> roleNames() const;
	virtual bool operator <(const ListItem& nextElem);
};

#endif // TRACK_H
