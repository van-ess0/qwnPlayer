#include "Track.h"

Track::Track(const quint32 number, const QString& title, const QString& type, const QString& path, QObject* parent)
	:
	  Models::ListItem(parent)
{
	m_number		= number;
	m_title			= title;
	m_audioType		= type;
	m_serverPath	= path;
	m_globalId		= GlobalTrackIndex::instance()->getIndex();
}

quint32 Track::getNumber() const {
	return m_number;
}

QString Track::getTitle() const {
	return m_title;
}

QString Track::getAudioType() const {
	return m_audioType;
}

QString Track::getServerPath() const {
	return m_serverPath;
}

int Track::id() const {
	return m_globalId;
}

QVariant Track::data(int role) const {
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
		default:
			return QVariant();
	}
}

QHash<int, QByteArray> Track::roleNames() const {
	QHash<int, QByteArray> roles;

	roles[trackId]			= "trackId";
	roles[trackNumber]		= "trackNumber";
	roles[trackTitle]		= "trackTitle";
	roles[trackAudioType]	= "trackAudioType";
	roles[trackServerPath]	= "trackServerPath";

	return roles;
}

bool Track::operator <(const Models::ListItem& nextElem) {
	return m_number < nextElem.data(TrackModelItemRoles::trackNumber).toUInt();
}
