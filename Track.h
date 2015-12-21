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

	quint64 m_globalId;
	
	enum TrackModelItemRoles {
		trackId = Qt::UserRole + 1,
		trackNumber,
		trackTitle,
		trackAudioType,
		trackServerPath
//		trackObject
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
		m_globalId		= GlobalTrackIndex::instance()->getIndex();
	}
	quint32 getNumber() const {
		return m_number;
	}
	QString getTitle() const {
		return m_title;
	}
	QString getAudioType() const {
		return m_audioType;
	}
	QString getServerPath() const {
		return m_serverPath;
	}
//	const Track* getObject() const {
//		return this;
//	}

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
			return this->getAudioType();
		case trackServerPath:
			return this->getServerPath();
//		case trackObject:
//			return this->getObject();
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
//		roles[trackObject]		= "trackObject";

		return roles;
	}
};

Q_DECLARE_METATYPE(Models::ListItem*)

#endif // TRACK_H
