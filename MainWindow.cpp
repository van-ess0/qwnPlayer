#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->pushButton, SIGNAL(clicked(bool)),
			this, SLOT(slotButtonClicked(bool)));

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

void MainWindow::slotButtonClicked(bool)
{
	QString path = m_collection.value(ui->listWidget->currentItem()->text());
	QUrl url(path);
	url.setUserName("degree");
	url.setPassword("Fcnhjabpbrf95");

	qDebug() << url;

	QMediaPlaylist* playlist = new QMediaPlaylist(player);

	playlist->addMedia(url);

	playlist->setCurrentIndex(1);
	player->setVolume(50);
	player->play();
}
