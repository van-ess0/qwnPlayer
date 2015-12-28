#ifndef QWNMEDIAPLAYER_H
#define QWNMEDIAPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QQmlProperty>

#include "Artist.h"
#include "SettingsManager.h"

class QwnMediaPlayer : public QObject
{
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
    void setCurrentPosition(qint64 position) {
        m_player->setPosition(position);
    }

	void currentTrackPath(QString path);

	void stopPlaying() {
		qDebug() << "stop";
		m_player->stop();
		m_playlist->clear();
		m_isPlaying = false;
	}

	void startPlaying() {
		qDebug() << "play";
		m_isPlaying = true;
		m_player->play();
	}

	void settingCurrentTrackToPlaylist() {
		qDebug() << "setting current track to playlist";
		QObject* trackModel = qvariant_cast<QObject*>(m_currentTrack);

		if (!trackModel) {
			qDebug() << "cast track error";
			return;
		}

		qDebug() << QQmlProperty(trackModel, "trackTitle").read().toString();

		QString serverPath = QQmlProperty(trackModel, "trackServerPath").read().toString();
		qDebug() << serverPath;
		QUrl url(serverPath);
		url.setUserName(SettingsManager::instance()->getUserName());
		url.setPassword(SettingsManager::instance()->getUserPassword());

		m_playlist->addMedia(url);
	}

	void settingCurrentAlbumToPlaylist() {
		qDebug() << "setting current album to playlist";

		QObject* albumModel = qvariant_cast<QObject*>(m_currentAlbum);

		if (!albumModel) {
			qDebug() << "cast album error";
			return;
		}

		qDebug() << QQmlProperty(albumModel, "albumName").read().toString();

		QVariant var = QQmlProperty(albumModel, "albumTracks").read();
		QSharedPointer<Models::ListModel> tracks = var.value< QSharedPointer<Models::ListModel> >();

		if (tracks.isNull()) {
			qDebug() << "cast album tracks error";
			return;
		}

		foreach (Models::ListItem* track, tracks->toList()) {

			Track* track_obj = qobject_cast<Track*>(track);

			QString serverPath = track_obj->getServerPath();
			qDebug() << serverPath;

			QUrl url(serverPath);
			url.setUserName(SettingsManager::instance()->getUserName());
			url.setPassword(SettingsManager::instance()->getUserPassword());

			m_playlist->addMedia(url);
		}
	}

	void settingCurrentArtistToPlaylist() {
		qDebug() << "setting current artist to playlist";

		QObject* artistModel = qvariant_cast<QObject*>(m_currentArtist);

		if (!artistModel) {
			qDebug() << "cast album artist";
			return;
		}

		qDebug() << QQmlProperty(artistModel, "artistName").read().toString();

		QVariant var = QQmlProperty(artistModel, "artistAlbums").read();
		QSharedPointer<Models::SubListedListModel> albums = var.value< QSharedPointer<Models::SubListedListModel> >();

		if (albums.isNull()) {
			qDebug() << "cast album tracks error";
			return;
		}

		foreach (Models::ListItem* album, albums->toList()) {
			Album* album_obj = qobject_cast<Album*>(album);
			qDebug() << album_obj->getName();

			foreach (Models::ListItem* track, album_obj->submodel()->toList()) {
				Track* track_obj = qobject_cast<Track*>(track);

				QString serverPath = track_obj->getServerPath();
				qDebug() << track_obj->getTitle() << serverPath;

				QUrl url(serverPath);
				url.setUserName(SettingsManager::instance()->getUserName());
				url.setPassword(SettingsManager::instance()->getUserPassword());

				m_playlist->addMedia(url);
			}
		}
	}

//	void setCurrentTrack(Track* track);
	void resetPlaylist() {
		qDebug() << "reset playlist";

//		QObject* trackModel = qvariant_cast<QObject*>(m_currentTrack);
//		qDebug() << QQmlProperty(trackModel, "trackTitle").read().toString();

		m_playlist->clear();
	}
};

#endif // QWNMEDIAPLAYER_H
