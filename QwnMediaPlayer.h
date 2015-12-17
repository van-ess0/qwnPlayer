#ifndef QWNMEDIAPLAYER_H
#define QWNMEDIAPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVariant>

#include "Artist.h"

class QwnMediaPlayer : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QVariant currentTrack READ currentTrack WRITE setCurrentTrack NOTIFY currentTrackChanged)

private:
	QMediaPlayer* m_player;
	QMediaPlaylist* m_playlist;

	QString m_username;
	QString m_password;

	bool m_isPlaying;

	QVariant m_currentTrack;

public:
	explicit QwnMediaPlayer(QObject *parent = 0);

	QVariant currentTrack() const {
		return m_currentTrack;
	}

	void setCurrentTrack(const QVariant& track) {
		qDebug() << "set current track";
		if (track != m_currentTrack) {
			m_currentTrack = track;
			emit currentTrackChanged();
		}
	}


	// Create 'onNameOfSignal' handler in qml for signal 'nameOfSignal'
	// if you want to handle it :)
signals:
//	void testSig();
//	void keyGenerated(bool success);
//public slots:
//	void qmlSlot(QString string);
//	void qmlSlotEmpty();

	void currentTrackChanged();
	void signalPositionChanged(qint64 progress);
	void signalDurationChanged(qint64 duration);

	// connections with qmediaplayer
private slots:
	void slotAudioAvailabilityChanged(bool);

	void slotMediaStatusChanged(QMediaPlayer::MediaStatus);
	void slotBufferStatusChanged(int percentFilled);
	void positionChanged(qint64 progress);
	void durationChanged(qint64 duration);
	void seek(int seconds);
	void stateChanged(QMediaPlayer::State);
	void error(QMediaPlayer::Error);

	// This methods will be called from qml file
public slots:
	void playToggle();
	void nextTrack();
	void prevTrack();
	void shuffleToggle();
	void cycleToggle();

	void currentTrackPath(QString path);

//	void setCurrentTrack(Track* track);
	void resetPlaylist() {
		QObject* trackModel = qvariant_cast<QObject*>(m_currentTrack);
		Models::ListModel* model = qobject_cast<Models::ListModel*>(trackModel);

		if (model != NULL) {
			qDebug() << "not null";

		}

		qDebug() << "reset playlist";
		m_playlist->clear();
	}
};

#endif // QWNMEDIAPLAYER_H
