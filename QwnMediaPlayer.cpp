#include "QwnMediaPlayer.h"
#include <QFile>
#include <QStandardPaths>

QwnMediaPlayer::QwnMediaPlayer(QObject *parent) : QObject(parent)
{
	player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);

	connect(player, SIGNAL(audioAvailableChanged(bool)),
			this, SLOT(slotAudioAvailabilityChanged(bool)));
	connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
			this, SLOT(slotMediaStatusChanged(QMediaPlayer::MediaStatus)));
	connect(player, SIGNAL(bufferStatusChanged(int)),
			this, SLOT(slotBufferStatusChanged(int)));
	connect(player, SIGNAL(positionChanged(qint64)),
			this, SLOT(positionChanged(qint64)));
	connect(player, SIGNAL(durationChanged(qint64)),
			this, SLOT(durationChanged(qint64)));
//	connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)),
//			this, SLOT(seek(int)));
	connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
			this, SLOT(stateChanged(QMediaPlayer::State)));
	connect(player, SIGNAL(error(QMediaPlayer::Error)),
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
	player->setPosition(seconds * 1000);
}

void QwnMediaPlayer::stateChanged(QMediaPlayer::State state)
{
	qDebug() << "stateChanged" << state;
}

void QwnMediaPlayer::error(QMediaPlayer::Error error)
{
	qDebug() << "error" << error << player->errorString();
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

	QString homeLocation =  QStandardPaths::locate(QStandardPaths::AppLocalDataLocation,
												   QString(),
												   QStandardPaths::LocateDirectory);
	qDebug() << homeLocation;

	QFile::copy(":/resources/sound_cut2.mp3" , homeLocation + "sound_cut2.mp3");

//	QUrl url("http://vaness0.ga:83/owncloud/remote.php/webdav/04. Narcissistic Cannibal.mp3");
//	url.setUserName("degree");
//	url.setPassword("Fcnhjabpbrf95");
//	player->setMedia(url);

	player->setMedia(QUrl::fromLocalFile(homeLocation + "sound_cut2.mp3"));
	player->play();
}

void QwnMediaPlayer::nextTrack()
{
	qDebug() << "next track";
}

void QwnMediaPlayer::prevTrack()
{
	qDebug() << "prev track";
}

void QwnMediaPlayer::shuffleToggle()
{
	qDebug() << "shuffle toggled";
}

void QwnMediaPlayer::cycleToggle()
{
	qDebug() << "cycle toggled";
}

