#ifndef TRACK_H
#define TRACK_H

#include "Models/ListItem.h"
#include "SingletonTemplate.h"

class GlobalTrackIndex : public SingletonTemplate<GlobalTrackIndex>
{
	quint64 m_index;

public:
	GlobalTrackIndex() {
		m_index = 0;
	}

	quint64 getTrackIndex() {
		return m_index++;
	}
};

class Track : public Models::ListItem
{
	Q_OBJECT
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
				   QObject *parent = 0)
		:
		  Models::ListItem(parent)
	{
		m_number		= number;
		m_title			= title;
		m_audioType		= type;
		m_serverPath	= path;
		m_globalId		= GlobalTrackIndex::instance()->getTrackIndex();
	}
	quint32 getNumber() const {
		return m_number;
	}
	QString getTitle() const {
		return m_title;
	}
	QString getType() const {
		return m_audioType;
	}
	QString getServerPath() const {
		return m_serverPath;
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
		case trackId:
			return this->id();
		case trackNumber:
			return this->getNumber();
		case trackTitle:
			return this->getTitle();
		case trackAudioType:
			return this->getType();
		case trackServerPath:
			return this->getServerPath();
		default:
			return QVariant();
		}
	}
	virtual QHash<int, QByteArray> roleNames() const
	{
		QHash<int, QByteArray> roles;

		roles[trackId]			= "trackId";
		roles[trackNumber]		= "trackNumber";
		roles[trackTitle]		= "trackTitle";
		roles[trackAudioType]	= "trackAudioType";
		roles[trackServerPath]	= "trackServerPath";

		return roles;
	}
};

#endif // TRACK_H
