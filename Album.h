#ifndef ALBUM_H
#define ALBUM_H

#include <QList>
#include <Track.h>

class Album : public QObject
{
	Q_OBJECT

private:
	QString m_name;
	quint32 m_year;
	QList<Track*> m_tracks;
	/// TODO
	// QByteArray m_cover;
public:
	explicit Album(const QString& name,
				   const quint32 year,
				   QObject *parent = NULL);

	QString getName() const {
		return m_name;
	}
	quint32 getYear() const {
		return m_year;
	}

	// You need to check on emppty list
	QList<Track*> getTrackList() const {
		return m_tracks;
	}
	void addTrack(Track* track) {
		m_tracks.append(track);
	}
};

#endif // ALBUM_H
