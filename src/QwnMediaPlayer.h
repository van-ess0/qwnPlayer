#ifndef QWNMEDIAPLAYER_H
#define QWNMEDIAPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QQmlProperty>

#include "Artist.h"
#include "SettingsManager.h"

class QwnMediaPlayer : public QObject {
	Q_OBJECT

	QML_PROPERTY(QVariant, currentTrack, setCurrentTrack, currentTrackChanged)
	QML_PROPERTY(QVariant, currentAlbum, setCurrentAlbum, currentAlbumChanged)
	QML_PROPERTY(QVariant, currentArtist, setCurrentArtist, currentArtistChanged)

private:
	QMediaPlayer* m_player;
	QMediaPlaylist* m_playlist;

	bool m_isPlaying;

public:
	explicit QwnMediaPlayer(QObject *parent = 0);

	// Create 'onNameOfSignal' handler in qml for signal 'nameOfSignal'
	// if you want to handle it :)
signals:
//	void testSig();
//	void keyGenerated(bool success);
//public slots:
//	void qmlSlot(QString string);
//	void qmlSlotEmpty();

//	void currentTrackChanged();
//	void currentAlbumChanged();
//	void currentArtistChanged();

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
    void setCurrentPosition(qint64 position);
	void currentTrackPath(QString path);
    void stopPlaying();
    void startPlaying();
    void settingCurrentTrackToPlaylist();
    void settingCurrentAlbumToPlaylist();
    void settingCurrentArtistToPlaylist();
    void resetPlaylist();
};

#endif // QWNMEDIAPLAYER_H
