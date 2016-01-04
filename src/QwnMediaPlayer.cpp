#include "QwnMediaPlayer.h"
#include <QFile>
#include <QStandardPaths>
#include <QStringList>

QSharedPointer<QwnMediaPlayer::NowPlaying> QwnMediaPlayer::getMeta(const QString &title, const QString &album, const QString &artist, const QString &cover, const QString &url)
{
    QSharedPointer<NowPlaying> nowplaying = QSharedPointer<NowPlaying>(new NowPlaying());

    nowplaying->title	= title;
    nowplaying->album	= album;
    nowplaying->artist	= artist;

    if (!cover.isNull()) {
        QStringList stringList = cover.split("/");
        QString strTemp = stringList.at(7);
        nowplaying->albumId	= strTemp.toInt();
    }
    else {
        nowplaying->albumId = -1;
    }

    nowplaying->url = QUrl(url);
    nowplaying->url.setUserName(SettingsManager::instance()->getUserName());
    nowplaying->url.setPassword(SettingsManager::instance()->getUserPassword());

    return nowplaying;
}

QwnMediaPlayer::QwnMediaPlayer(QObject *parent) : QObject(parent)
{
	m_player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
	m_playlist = new QMediaPlaylist;
	m_player->setPlaylist(m_playlist);
	m_isPlaying = false;

	m_musicLibrary = NULL;

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
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SIGNAL(signalPlayingStateChanged(QMediaPlayer::State)));
	connect(m_player, SIGNAL(error(QMediaPlayer::Error)),
			this, SLOT(error(QMediaPlayer::Error)));

	connect(m_player, SIGNAL(mediaChanged(QMediaContent)),
			this, SLOT(slotMediaChanged(QMediaContent)));

	connect(m_playlist, SIGNAL(currentIndexChanged(int)),
			this, SLOT(slotCurrentIndexChanged(int)));
}

void QwnMediaPlayer::setMusicLibrary(MusicLibrary* library)
{
	m_musicLibrary = library;
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

void QwnMediaPlayer::slotMediaChanged(QMediaContent content)
{
	Q_UNUSED(content)
	qDebug() << "media changed";

//	QObject* trackModel = qvariant_cast<QObject*>(m_currentTrack);

//	if (!trackModel) {
//		qDebug() << "cast track error";
//		return;
//	}

//	QString trackTitle = QQmlProperty(trackModel, "trackTitle").read().toString();

//	quint64 albumId = QQmlProperty(trackModel, "trackAlbumId").read().toLongLong();
//	Album* album = qobject_cast<Album*>(m_musicLibrary->getAlbumById(albumId));
//	QString albumName = album->getName();

//	quint64 artistId = album->getArtistId();
//	Artist* artist = qobject_cast<Artist*>(m_musicLibrary->getArtistModel()->find(artistId));
//	QString artistName = artist->getName();

//	emit signalPlayingTrackChanged(trackTitle, artistName, albumName);
}

void QwnMediaPlayer::slotCurrentIndexChanged(int index)
{
	qDebug() << "current index changed: " << index;
	if (index < 0) {
		return;
	}
	if (index >= m_nowplayingPlaylist.size()) {
		return;
	}

	m_nowPlaying = m_nowplayingPlaylist.at(index);
	emit signalPlayingTrackChanged(m_nowPlaying->title, m_nowPlaying->artist, m_nowPlaying->album);
	emit signalCoverChanged(m_nowPlaying->albumId);
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

	if (m_nowplayingPlaylist.isEmpty()) {
		return;
	}
	qDebug() << "shuffle toggled";

	m_player->stop();
	m_playlist->clear();
	m_nowPlaying.clear();

	QList< QSharedPointer<NowPlaying> > newNowPlaylist;

	while (!m_nowplayingPlaylist.isEmpty()) {
		QSharedPointer<NowPlaying> nowplaying = m_nowplayingPlaylist.takeAt(qrand() % m_nowplayingPlaylist.size());
		newNowPlaylist.append(nowplaying);
		m_playlist->addMedia(nowplaying->url);
	}

	m_nowplayingPlaylist = newNowPlaylist;

	m_player->play();

	/// TODO: make real shuffle
//	m_playlist->shuffle();
}

void QwnMediaPlayer::cycleToggle()
{
	qint32 mode = m_playlist->playbackMode();
	switch(mode) {
		case QMediaPlaylist::Sequential:
			qDebug() << "cycle toggled to item loop";
			m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
			break;
		case QMediaPlaylist::CurrentItemInLoop:
			qDebug() << "cycle toggled to all loop";
			m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
			break;
		case QMediaPlaylist::Loop:
			qDebug() << "cycle toggled to sequential";
			m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);
			break;
		default:
			qDebug() << "cycle isn't toggled";
			break;
	}
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

	m_nowplayingPlaylist.clear();
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

	QObject* albumModel = qvariant_cast<QObject*>(m_currentAlbum);
	if (!albumModel) {
		qDebug() << "cast album error";
		return;
	}

	QObject* artistModel = qvariant_cast<QObject*>(m_currentArtist);
	if (!artistModel) {
		qDebug() << "cast album artist";
		return;
	}

//	qDebug() << QQmlProperty(artistModel, "artistName").read().toString();
//	qDebug() << QQmlProperty(artistModel, "artistName").read().toString();
//	qDebug() << QQmlProperty(trackModel, "trackTitle").read().toString();


    QSharedPointer<NowPlaying> nowplaying =
            getMeta(QQmlProperty(trackModel, "trackTitle").read().toString(),
                    QQmlProperty(albumModel, "albumName").read().toString(),
                    QQmlProperty(artistModel, "artistName").read().toString(),
                    QQmlProperty(albumModel, "albumCover").read().toString(),
                    QQmlProperty(trackModel, "trackServerPath").read().toString());
	m_nowplayingPlaylist.append(nowplaying);
	m_playlist->addMedia(nowplaying->url);
}

void QwnMediaPlayer::settingCurrentAlbumToPlaylist()
{
	qDebug() << "setting current album to playlist";

	QObject* albumModel = qvariant_cast<QObject*>(m_currentAlbum);
	if (!albumModel) {
		qDebug() << "cast album error";
		return;
	}

	QObject* artistModel = qvariant_cast<QObject*>(m_currentArtist);
	if (!artistModel) {
		qDebug() << "cast album artist";
		return;
	}

//    qDebug() << QQmlProperty(albumModel, "albumName").read().toString();

	QVariant var = QQmlProperty(albumModel, "albumTracks").read();
	QSharedPointer<Models::ListModel> tracks = var.value< QSharedPointer<Models::ListModel> >();

	if (tracks.isNull()) {
		qDebug() << "cast album tracks error";
		return;
	}

	foreach (Models::ListItem* track, tracks->toList())
	{

		Track* track_obj = qobject_cast<Track*>(track);

//		QSharedPointer<NowPlaying> nowplaying = QSharedPointer<NowPlaying>(new NowPlaying());

//		nowplaying->title	= track_obj->getTitle();
//		nowplaying->album	= QQmlProperty(albumModel, "albumName").read().toString();
//		nowplaying->artist	= QQmlProperty(artistModel, "artistName").read().toString();

//		QStringList stringList = QQmlProperty(albumModel, "albumCover").read().toString().split("/");
//		QString strTemp = stringList.at(7);
//		nowplaying->albumId	= strTemp.toInt();

        QSharedPointer<NowPlaying> nowplaying =
                getMeta(track_obj->getTitle(),
                        QQmlProperty(albumModel, "albumName").read().toString(),
                        QQmlProperty(artistModel, "artistName").read().toString(),
                        QQmlProperty(albumModel, "albumCover").read().toString(),
                        track_obj->getServerPath());

//		nowplaying->url = QUrl(track_obj->getServerPath());
//		nowplaying->url.setUserName(SettingsManager::instance()->getUserName());
//		nowplaying->url.setPassword(SettingsManager::instance()->getUserPassword());

		m_nowplayingPlaylist.append(nowplaying);
		m_playlist->addMedia(nowplaying->url);
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

//    qDebug() << QQmlProperty(artistModel, "artistName").read().toString();

	QVariant var = QQmlProperty(artistModel, "artistAlbums").read();
	QSharedPointer<Models::SubListedListModel> albums = var.value< QSharedPointer<Models::SubListedListModel> >();

	if (albums.isNull()) {
		qDebug() << "cast album tracks error";
		return;
	}

	foreach (Models::ListItem* album, albums->toList()) {
		Album* album_obj = qobject_cast<Album*>(album);
//        qDebug() << album_obj->getName();

		foreach (Models::ListItem* track, album_obj->submodel()->toList()) {
			Track* track_obj = qobject_cast<Track*>(track);

//			QSharedPointer<NowPlaying> nowplaying = QSharedPointer<NowPlaying>(new NowPlaying());

//			nowplaying->title	= track_obj->getTitle();
//			nowplaying->album	= album_obj->getName();
//			nowplaying->artist	= QQmlProperty(artistModel, "artistName").read().toString();

//			QStringList stringList = album_obj->getCover().split("/");
//			QString strTemp = stringList.at(7);
//			nowplaying->albumId	= strTemp.toInt();

//			nowplaying->url = QUrl(track_obj->getServerPath());

            QSharedPointer<NowPlaying> nowplaying =
                    getMeta(track_obj->getTitle(),
                            album_obj->getName(),
                            QQmlProperty(artistModel, "artistName").read().toString(),
                            album_obj->getCover(),
                            track_obj->getServerPath());

//			nowplaying->url.setUserName(SettingsManager::instance()->getUserName());
//			nowplaying->url.setPassword(SettingsManager::instance()->getUserPassword());

			m_nowplayingPlaylist.append(nowplaying);
			m_playlist->addMedia(nowplaying->url);
		}
	}
}

//	void setCurrentTrack(Track* track);
//void QwnMediaPlayer::resetPlaylist()
//{
//    qDebug() << "reset playlist";

//		QObject* trackModel = qvariant_cast<QObject*>(m_currentTrack);
//		qDebug() << QQmlProperty(trackModel, "trackTitle").read().toString();

//    m_playlist->clear();
//}
//void QwnMediaPlayer::setCurrentTrack(Track* track)
//{
//	qDebug() << "set current track";
//}

