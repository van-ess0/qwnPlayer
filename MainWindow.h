#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>

#include "Artist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
//	QList<Artist*> m_collection;
	QMediaPlayer* player;
	QMap<QString, QString> m_collection;
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

public slots:
	void slotCollectionDataParsed(QList<Artist*>);
	void slotLog(QString);

private slots:
	void slotButtonClicked(bool);
	void slotCopyButtonClicked(bool);
};

#endif // MAINWINDOW_H
