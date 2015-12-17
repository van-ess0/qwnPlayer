#include "QwnMediaPlayer.h"
#include <QFile>
#include <QStandardPaths>
#include "SettingsManager.h"

QwnMediaPlayer::QwnMediaPlayer(QObject *parent) : QObject(parent)
{
	m_player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
	m_playlist = new QMediaPlaylist;
	m_player->setPlaylist(m_playlist);
	m_isPlaying = false;

	m_username = SettingsManager::instance()->getUserName();
	m_password = SettingsManager::instance()->getUserPassword();

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

	if (m_playlist->isEmpty()) {
		return;
	}

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
	QUrl url(path);
	url.setUserName(m_username);
	url.setPassword(m_password);
//	m_playlist->clear();
	m_playlist->addMedia(url);
}

//void QwnMediaPlayer::setCurrentTrack(Track* track)
//{
//	qDebug() << "set current track";
//}

