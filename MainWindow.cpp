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
//	player->setVolume(50);

	QtConcurrent::run(player, &QMediaPlayer::play);
}

void MainWindow::slotCopyButtonClicked(bool)
{
	QString homeLocation =  QStandardPaths::locate(QStandardPaths::AppLocalDataLocation,
												   QString(),
												   QStandardPaths::LocateDirectory);
	qDebug() << homeLocation;
	ui->textEdit->setText(homeLocation);
	QFile::copy(":/resources/sound_cut.mp3" , homeLocation + "sound_cut.mp3");
	QDir dir(homeLocation);
	foreach (QString file, dir.entryList()) {
		ui->listWidget->addItem(file);
	}
	player->setMedia(QUrl::fromLocalFile(homeLocation + "sound_cut.mp3"));
}

