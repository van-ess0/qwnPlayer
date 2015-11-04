#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->pushButton, SIGNAL(clicked(bool)),
			this, SLOT(slotButtonClicked(bool)));
	connect(ui->pushButton_2, SIGNAL(clicked(bool)),
			this, SLOT(slotCopyButtonClicked(bool)));



	player = new QMediaPlayer;

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
	connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)),
			this, SLOT(seek(int)));
	connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
			this, SLOT(stateChanged(QMediaPlayer::State)));
	connect(player, SIGNAL(error(QMediaPlayer::Error)),
			this, SLOT(error(QMediaPlayer::Error)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::slotCollectionDataParsed(QList<Artist*> artists)
{
	qDebug() << artists.size();


	foreach (Artist* artist, artists) {
		foreach (Album* album, artist->getAlbumList()) {
			foreach (Track* track, album->getTrackList()) {
				ui->listWidget->addItem(track->getTitle());
				m_collection.insert(track->getTitle(), track->getServerPath());
			}
		}
	}

	//	m_collection = artists;
}

void MainWindow::slotLog(QString string)
{
	ui->textEdit->setText(ui->textEdit->toPlainText() + "  " + string);
}
#include <QFileInfo>
#include <QtConcurrent/QtConcurrentRun>

void MainWindow::slotButtonClicked(bool)
{
//	QString path = m_collection.value(ui->listWidget->currentItem()->text());
//	QUrl url(path);
//	url.setUserName("degree");
//	url.setPassword("Fcnhjabpbrf95");

//	ui->textEdit->setText(ui->textEdit->toPlainText() + "  " + url.toString());

//	QMediaPlaylist* playlist = new QMediaPlaylist(player);

//	playlist->addMedia(QUrl::fromLocalFile("/Users/surat/Downloads/01. Uprising.mp3"));

//	playlist->setCurrentIndex(1);

//	const QString path = "C:/Users/surat/Downloads/01. Uprising.mp3";
//	QUrl url(QFileInfo(path).absoluteFilePath());

	QString homeLocation =  QStandardPaths::locate(QStandardPaths::AppLocalDataLocation,
												   QString(),
												   QStandardPaths::LocateDirectory);

	player->setMedia(QUrl::fromLocalFile(homeLocation + "sound_cut.mp3"));
	ui->horizontalSlider->setRange(0, player->duration() / 1000);

//	player->setVolume(50);

	player->play();
	qDebug() << player->error() << player->state() << player->mediaStatus() << player->currentMedia().isNull();
}

void MainWindow::slotCopyButtonClicked(bool)
{
	QString homeLocation =  QStandardPaths::locate(QStandardPaths::AppLocalDataLocation,
												   QString(),
												   QStandardPaths::LocateDirectory);
	qDebug() << homeLocation;
	ui->textEdit->setText(homeLocation);
	QFile::copy(":/resources/sound_cut.mp3" , homeLocation + "sound_cut.mp3");
	QFile::copy(":/resources/sound_cut2.mp3" , homeLocation + "sound_cut2.mp3");
	QDir dir(homeLocation);
	foreach (QString file, dir.entryList()) {
		ui->listWidget->addItem(file);
	}

}

void MainWindow::slotAudioAvailabilityChanged(bool value)
{
	qDebug() << "AA changed" << value;
}

void MainWindow::slotMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
	qDebug() << "status" << status;
}

void MainWindow::slotBufferStatusChanged(int percentFilled)
{
	qDebug() << "slotBufferStatusChanged" << percentFilled;
}

void MainWindow::positionChanged(qint64 progress)
{
	qDebug() << "positionChanged" << progress;
	if (!ui->horizontalSlider->isSliderDown()) {
		ui->horizontalSlider->setValue(progress / 1000);
	}
//	updateDurationInfo(progress / 1000);
}

void MainWindow::durationChanged(qint64 duration)
{
	qDebug() << "durationChanged" << duration;
	ui->horizontalSlider->setMaximum(duration / 1000);
}

void MainWindow::seek(int seconds)
{
	player->setPosition(seconds * 1000);
}

void MainWindow::stateChanged(QMediaPlayer::State state)
{
	qDebug() << "stateChanged" << state;
}

void MainWindow::error(QMediaPlayer::Error error)
{
	qDebug() << "error" << error << player->errorString();
}

