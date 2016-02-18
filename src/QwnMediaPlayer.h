#ifndef QWNMEDIAPLAYER_H
#define QWNMEDIAPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QQmlProperty>

#include "SettingsManager.h"
#include "MusicLibrary.h"

class QwnMediaPlayer : public QObject
{
	Q_OBJECT

	QML_PROPERTY(QVariant, currentTrack, setCurrentTrack, currentTrackChanged)
	QML_PROPERTY(QVariant, currentAlbum, setCurrentAlbum, currentAlbumChanged)
	QML_PROPERTY(QVariant, currentArtist, setCurrentArtist, currentArtistChanged)
	QML_PROPERTY(QVariant, currentTrackIndex, setCurrentTrackIndex, currentTrackIndexChanged)

private:
	QMediaPlayer* m_player;
	QMediaPlaylist* m_playlist;

	bool m_isPlaying;

	MusicLibrary* m_musicLibrary;

	Models::ListModel* m_currentPlaylist;

public:
	explicit QwnMediaPlayer(QObject *parent = 0);

	void setMusicLibrary(MusicLibrary* library);
	void setContext(QQmlContext* context);

	// Create 'onNameOfSignal' handler in qml for signal 'nameOfSignal'
	// if you want to handle it :)
signals:
	void signalPositionChanged(qint64 progress);
	void signalDurationChanged(qint64 duration);
	void signalPlayingTrackChanged(QString title, QString artist, QString album);
	void signalPlayingStateChanged(QMediaPlayer::State state);
	void signalCoverChanged(QString coverPath);
	void signalCurrentTrackIndexChanged(qint32 index);

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
	void slotMediaChanged(QMediaContent);

	void slotCurrentIndexChanged(int);

	// This methods will be called from qml file
public slots:
	void playToggle();
	void nextTrack();
	void prevTrack();
	void shuffleToggle();
	void cycleToggle();
	void setCurrentPosition(qint64 position);
	void stopPlaying();
	void startPlaying();
	void settingCurrentTrackToPlaylist();
	void settingCurrentAlbumToPlaylist();
	void settingCurrentArtistToPlaylist();
	void changeCurrentTrackIndex(int index);

private:
	void addTrackToCurrentPlaylist(Track* track);
};

#endif // QWNMEDIAPLAYER_H
