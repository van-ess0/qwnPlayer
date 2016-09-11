#include "QwnMediaPlayer.h"

QwnMediaPlayer::QwnMediaPlayer(QObject *parent) : QObject(parent)
{
	m_player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
	m_playlist = new QMediaPlaylist;
	m_player->setPlaylist(m_playlist);
	m_isPlaying = false;

	m_musicLibrary = NULL;

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

	connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
			this, SLOT(stateChanged(QMediaPlayer::State)));
	connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
			this, SIGNAL(signalPlayingStateChanged(QMediaPlayer::State)));
	connect(m_player, SIGNAL(error(QMediaPlayer::Error)),
            this, SLOT(slotError(QMediaPlayer::Error)));

	connect(m_player, SIGNAL(mediaChanged(QMediaContent)),
			this, SLOT(slotMediaChanged(QMediaContent)));

	connect(m_playlist, SIGNAL(currentIndexChanged(int)),
			this, SLOT(slotCurrentIndexChanged(int)));


	m_currentPlaylist = new Models::ListModel(new Track(0, "empty", "empty", "empty", 0, NULL));
	m_currentPlaylist->setSorting(false);
	m_currentTrackIndex = 0;

//	connect(this, SIGNAL(currentIndexChanged()));

#ifdef Q_OS_ANDROID
    m_androidPlayer = new NotificationClient(this);
    connect(m_androidPlayer, SIGNAL(bufferingChanged(qint32)),
            this, SLOT(slotBufferStatusChanged(int)));
    connect(m_androidPlayer, SIGNAL(durationChanged(qint64)),
            this, SLOT(durationChanged(qint64)));
    connect(m_androidPlayer, SIGNAL(progressChanged(qint64)),
            this, SLOT(positionChanged(qint64)));
    connect(m_androidPlayer, SIGNAL(error(qint32,qint32)),
            this, SLOT(onErrorAndroid(qint32,qint32)));
    connect(m_androidPlayer, SIGNAL(info(qint32,qint32)),
            this, SLOT(onInfoAndroid(qint32,qint32)));

    connect(m_androidPlayer, SIGNAL(stateChanged(qint32)),
            this


#else
    m_androidPlayer = NULL;
#endif
}

void QwnMediaPlayer::setMusicLibrary(MusicLibrary* library)
{
	m_musicLibrary = library;
}

void QwnMediaPlayer::setContext(QQmlContext* context)
{
	context->setContextProperty("currentPlaylist", m_currentPlaylist);
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
}

void QwnMediaPlayer::durationChanged(qint64 duration)
{
	qDebug() << "durationChanged" << duration;
	emit signalDurationChanged(duration);
}

void QwnMediaPlayer::seek(int seconds)
{
	m_player->setPosition(seconds * 1000);
}

void QwnMediaPlayer::stateChanged(QMediaPlayer::State state)
{
	qDebug() << "stateChanged" << state;
}

void QwnMediaPlayer::slotError(QMediaPlayer::Error error)
{
    qDebug() << "error" << error <<

#ifndef Q_OS_ANDROID
                m_player->errorString();
#else
                m_androidErrorString;
#endif
}

void QwnMediaPlayer::slotMediaChanged(QMediaContent content)
{
	Q_UNUSED(content)
	qDebug() << "media changed";
}

void QwnMediaPlayer::slotCurrentIndexChanged(int index)
{
	qDebug() << "current index changed: " << index;
	if (index < 0) {
		return;
	}
	if (index >= m_currentPlaylist->rowCount()) {
		return;
	}

	setCurrentTrackIndex(index);

	QMap<QString, QVariant> itemData = m_currentPlaylist->get(index).toMap();

	QString trackTitle = itemData["trackTitle"].toString();
	quint64 albumId = itemData["trackAlbumId"].toULongLong();

	Album* album = m_musicLibrary->getAlbum(albumId);
	quint64 artistId = album->getArtistId();
	Artist* artist = m_musicLibrary->getArtist(artistId);

	qint32 coverId = album->getOwncloudId();
//	QString coverPath = album->getCover();
//	if (!coverPath.isNull()) {
//		QStringList stringList = coverPath.split("/");
//		QString strTemp = stringList.at(7);
//		coverId = strTemp.toInt();
//	}

	emit signalPlayingTrackChanged(trackTitle, artist->getName(), album->getName());
	emit signalCoverChanged(coverId);
    emit signalCurrentTrackIndexChanged(index);
}

void QwnMediaPlayer::onErrorAndroid(qint32 what, qint32 extra)
{
    QString errorString;
    QMediaPlayer::Error error = QMediaPlayer::ResourceError;

    switch (what) {
    case NotificationClient::MEDIA_ERROR_UNKNOWN:
        errorString = QLatin1String("Error:");
        break;
    case NotificationClient::MEDIA_ERROR_SERVER_DIED:
        errorString = QLatin1String("Error: Server died");
        error = QMediaPlayer::ServiceMissingError;
        break;
    case NotificationClient::MEDIA_ERROR_INVALID_STATE:
        errorString = QLatin1String("Error: Invalid state");
        error = QMediaPlayer::ServiceMissingError;
        break;
    }

    switch (extra) {
    case NotificationClient::MEDIA_ERROR_IO: // Network OR file error
        errorString += QLatin1String(" (I/O operation failed)");
        error = QMediaPlayer::NetworkError;
//        setMediaStatus(QMediaPlayer::InvalidMedia);
        break;
    case NotificationClient::MEDIA_ERROR_MALFORMED:
        errorString += QLatin1String(" (Malformed bitstream)");
        error = QMediaPlayer::FormatError;
//        setMediaStatus(QMediaPlayer::InvalidMedia);
        break;
    case NotificationClient::MEDIA_ERROR_UNSUPPORTED:
        errorString += QLatin1String(" (Unsupported media)");
        error = QMediaPlayer::FormatError;
//        setMediaStatus(QMediaPlayer::InvalidMedia);
        break;
    case NotificationClient::MEDIA_ERROR_TIMED_OUT:
        errorString += QLatin1String(" (Timed out)");
        break;
    case NotificationClient::MEDIA_ERROR_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK:
        errorString += QLatin1String(" (Unable to start progressive playback')");
        error = QMediaPlayer::FormatError;
//        setMediaStatus(QMediaPlayer::InvalidMedia);
        break;
    case NotificationClient::MEDIA_ERROR_BAD_THINGS_ARE_GOING_TO_HAPPEN:
        errorString += QLatin1String(" (Unknown error/Insufficient resources)");
        error = QMediaPlayer::ServiceMissingError;
        break;
    }

    emit this->androidError(error);
    m_androidErrorString = errorString;
}

void QwnMediaPlayer::onInfoAndroid(qint32 what, qint32 extra)
{
    Q_UNUSED(extra);
    switch (what) {
    case NotificationClient::MEDIA_INFO_UNKNOWN:
        break;
    case NotificationClient::MEDIA_INFO_VIDEO_TRACK_LAGGING:
        // IGNORE
        break;
    case NotificationClient::MEDIA_INFO_VIDEO_RENDERING_START:
        break;
    case NotificationClient::MEDIA_INFO_BUFFERING_START:
//        mPendingState = mCurrentState;
//        setState(QMediaPlayer::PausedState);
//        setMediaStatus(QMediaPlayer::StalledMedia);
        break;
    case NotificationClient::MEDIA_INFO_BUFFERING_END:
//        if (mCurrentState != QMediaPlayer::StoppedState)
//            flushPendingStates();
        break;
    case NotificationClient::MEDIA_INFO_BAD_INTERLEAVING:
        break;
    case NotificationClient::MEDIA_INFO_NOT_SEEKABLE:
//        setSeekable(false);
        break;
    case NotificationClient::MEDIA_INFO_METADATA_UPDATE:
//        Q_EMIT metaDataUpdated();
        break;
    }
}

void QwnMediaPlayer::onStateChanged(qint32 state)
{
    // If reloading, don't report state changes unless the new state is Prepared or Error.
//    if ((mState & NotificationClient::Stopped)
//        && (state & (NotificationClient::Prepared
//                     | NotificationClient::Error
//                     | NotificationClient::Uninitialized)) == 0) {
//        return;
//    }
}

void QwnMediaPlayer::playToggle()
{
	qDebug() << "play toggled";

	if (m_playlist->isEmpty()) {
		return;
	}

	if (m_isPlaying) {
#ifdef Q_OS_ANDROID
        m_androidPlayer->pause();
#else
        m_player->pause();
#endif
	} else {
#ifdef Q_OS_ANDROID
        m_androidPlayer->play();
#else
        m_player->play();
#endif
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
	if (0 == m_currentPlaylist->rowCount()) {
		return;
	}
	qDebug() << "shuffle toggled";

	m_player->stop();
	m_isPlaying = false;
	m_playlist->clear();

	QList<Models::ListItem*> tempList;

	while (0 != m_currentPlaylist->rowCount()) {

		Track* track = qobject_cast<Track*>(m_currentPlaylist->takeRow(qrand() % m_currentPlaylist->rowCount()));
		tempList.append(track);

		QUrl url = QUrl(track->getServerPath());
		url.setUserName(SettingsManager::instance()->getUserName());
		url.setPassword(SettingsManager::instance()->getUserPassword());
		m_playlist->addMedia(url);
	}

	m_currentPlaylist->appendRows(tempList);
	m_player->play();
	m_isPlaying = true;
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

void QwnMediaPlayer::setCurrentPosition(qint64 position)
{
	qDebug() << "Position set to " << position;
#ifdef Q_OS_ANDROID

    const int seekPosition = (position > INT_MAX) ? INT_MAX : position;

    if (seekPosition == this->position())
        return;


    m_androidPlayer->seekTo(seekPosition);
#else
	m_player->setPosition(position);
#endif
}

void QwnMediaPlayer::stopPlaying()
{
	qDebug() << "stop";
#ifdef Q_OS_ANDROID
    m_androidPlayer->stop();
#else
    m_player->stop();
#endif

	m_playlist->clear();
	m_currentPlaylist->clear();

	m_isPlaying = false;
}

void QwnMediaPlayer::startPlaying()
{
	qDebug() << "play";
	m_isPlaying = true;

#ifdef Q_OS_ANDROID
    m_androidPlayer->play();
#else
    m_player->play();
#endif
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

	quint64 artistId = QQmlProperty(artistModel, "artistId").read().toULongLong();
	quint64 albumId = QQmlProperty(albumModel, "albumId").read().toULongLong();
	quint64 trackId = QQmlProperty(trackModel, "trackId").read().toULongLong();

	addTrackToCurrentPlaylist(m_musicLibrary->getTrack(artistId, albumId, trackId));
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

	QVariant var = QQmlProperty(albumModel, "albumTracks").read();
	QSharedPointer<Models::ListModel> tracks = var.value< QSharedPointer<Models::ListModel> >();

	if (tracks.isNull()) {
		qDebug() << "cast album tracks error";
		return;
	}

	foreach (Models::ListItem* track, tracks->toList()) {
		addTrackToCurrentPlaylist(qobject_cast<Track*>(track));
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

	QVariant var = QQmlProperty(artistModel, "artistAlbums").read();
	QSharedPointer<Models::SubListedListModel> albums = var.value< QSharedPointer<Models::SubListedListModel> >();

	if (albums.isNull()) {
		qDebug() << "cast album tracks error";
		return;
	}

	foreach (Models::ListItem* album, albums->toList()) {
		Album* album_obj = qobject_cast<Album*>(album);

		foreach (Models::ListItem* track, album_obj->submodel()->toList()) {
			addTrackToCurrentPlaylist(qobject_cast<Track*>(track));
		}
	}
}

void QwnMediaPlayer::changeCurrentTrackIndex(int index)
{
	m_playlist->setCurrentIndex(index);
}

void QwnMediaPlayer::addTrackToCurrentPlaylist(Track* track)
{
	// TODO: rewrite memory eating

	Track* newTrackObj = new Track(*track);

	QUrl url = QUrl(newTrackObj->getServerPath());
	url.setUserName(SettingsManager::instance()->getUserName());
	url.setPassword(SettingsManager::instance()->getUserPassword());

	m_currentPlaylist->appendRow(newTrackObj);
	m_playlist->addMedia(url);
}
