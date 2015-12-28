#include "QwnMediaPlayer.h"
#include <QFile>
#include <QStandardPaths>


QwnMediaPlayer::QwnMediaPlayer(QObject *parent) : QObject(parent)
{
	m_player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
	m_playlist = new QMediaPlaylist;
	m_player->setPlaylist(m_playlist);
	m_isPlaying = false;

//	m_username = ;
//	m_password = ;

	connect(m_player, SIGNAL(audioAvailableChanged(bool)),
			this, SLOT(slotAudioAvailabilityChanged(bool)));
	connect(m_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
			this, SLOT(slotMediaStatusChanged(QMediaPlayer::MediaStatus)));
	connect(m_player, SIGNAL(bufferStatusChanged(int)),
			this, SLOT(slotBufferStatusChanged(int)));
	connect(m_player, SIGNAL(positionChanged(qint64)),
			this, SLOT(positionChanged(qint64)));
	connect(m_player, SIGNAL(durationChanged(qint64)),
			this, SLOT(durationChanged(qint64)));
//	connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)),
//			this, SLOT(seek(int)));
	connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
			this, SLOT(stateChanged(QMediaPlayer::State)));
	connect(m_player, SIGNAL(error(QMediaPlayer::Error)),
			this, SLOT(error(QMediaPlayer::Error)));


}

void QwnMediaPlayer::slotAudioAvailabilityChanged(bool value)
{
	qDebug() << "AA changed " << value;
}

void QwnMediaPlayer::slotMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
	qDebug() << "status" << status;
}

void QwnMediaPlayer::slotBufferStatusChanged(int percentFilled)
{
	qDebug() << "slotBufferStatusChanged" << percentFilled;
}

void QwnMediaPlayer::positionChanged(qint64 progress)
{
	qDebug() << "positionChanged" << progress;
	emit signalPositionChanged(progress);
//	if (!ui->horizontalSlider->isSliderDown()) {
//		ui->horizontalSlider->setValue(progress / 1000);
//	}
//	updateDurationInfo(progress / 1000);
}

void QwnMediaPlayer::durationChanged(qint64 duration)
{
	qDebug() << "durationChanged" << duration;
	emit signalDurationChanged(duration);
//	ui->horizontalSlider->setMaximum(duration / 1000);
}

void QwnMediaPlayer::seek(int seconds)
{
	m_player->setPosition(seconds * 1000);
}

void QwnMediaPlayer::stateChanged(QMediaPlayer::State state)
{
	qDebug() << "stateChanged" << state;
}

void QwnMediaPlayer::error(QMediaPlayer::Error error)
{
	qDebug() << "error" << error << m_player->errorString();
}

//void QwnMediaPlayer::qmlSlot(QString string)
//{
//	qDebug() << string;
//	emit keyGenerated(false);
//	emit testSig();
//}

//void QwnMediaPlayer::qmlSlotEmpty()
//{
//	qDebug() << "Empty slot from qml";
//	emit keyGenerated(true);
//	emit testSig();

//}

void QwnMediaPlayer::playToggle()
{
	qDebug() << "play toggled";

//	QString homeLocation =  QStandardPaths::locate(QStandardPaths::AppLocalDataLocation,
//												   QString(),
//												   QStandardPaths::LocateDirectory);
//	qDebug() << homeLocation;

//	QFile::copy(":/resources/sound_cut2.mp3" , homeLocation + "sound_cut2.mp3");

//	QUrl url("http://vaness0.ga:83/owncloud/remote.php/webdav/04. Narcissistic Cannibal.mp3");
//	url.setUserName("degree");
//	url.setPassword("Fcnhjabpbrf95");
//	player->setMedia(url);

//	m_player->setMedia(QUrl::fromLocalFile(homeLocation + "sound_cut2.mp3"));

    if (m_playlist->isEmpty())
		return;

	if (m_isPlaying) {
		m_player->pause();
	} else {
		m_player->play();
	}

	m_isPlaying = !m_isPlaying;
}

void QwnMediaPlayer::nextTrack()
{
	qDebug() << "next track";
	m_playlist->next();
}

void QwnMediaPlayer::prevTrack()
{
	qDebug() << "prev track";
	m_playlist->previous();
}

void QwnMediaPlayer::shuffleToggle()
{
	qDebug() << "shuffle toggled";
	/// TODO: make real shuffle
	m_playlist->shuffle();
}

void QwnMediaPlayer::cycleToggle()
{
	qDebug() << "cycle toggled";
//	m_playlist
}

void QwnMediaPlayer::currentTrackPath(QString path)
{
	qDebug() << path;
//	QUrl url(path);
//	url.setUserName(m_username);
//	url.setPassword(m_password);
////	m_playlist->clear();
//	m_playlist->addMedia(url);
}

void QwnMediaPlayer::setCurrentPosition(qint64 position)
{
    qDebug() << "Position set to " << position;
    m_player->setPosition(position);
}

void QwnMediaPlayer::stopPlaying()
{
    qDebug() << "stop";
    m_player->stop();
    m_playlist->clear();
    m_isPlaying = false;
}

void QwnMediaPlayer::startPlaying()
{
    qDebug() << "play";
    m_isPlaying = true;
    m_player->play();
}

void QwnMediaPlayer::settingCurrentTrackToPlaylist()
{
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

void QwnMediaPlayer::settingCurrentAlbumToPlaylist()
{
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

    foreach (Models::ListItem* track, tracks->toList())
    {

        Track* track_obj = qobject_cast<Track*>(track);

        QString serverPath = track_obj->getServerPath();
        qDebug() << serverPath;

        QUrl url(serverPath);
        url.setUserName(SettingsManager::instance()->getUserName());
        url.setPassword(SettingsManager::instance()->getUserPassword());

        m_playlist->addMedia(url);
    }
}

void QwnMediaPlayer::settingCurrentArtistToPlaylist()
{
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
void QwnMediaPlayer::resetPlaylist()
{
    qDebug() << "reset playlist";

//		QObject* trackModel = qvariant_cast<QObject*>(m_currentTrack);
//		qDebug() << QQmlProperty(trackModel, "trackTitle").read().toString();

    m_playlist->clear();
}
//void QwnMediaPlayer::setCurrentTrack(Track* track)
//{
//	qDebug() << "set current track";
//}

