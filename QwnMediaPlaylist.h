#ifndef QWNMEDIAPLAYLIST_H
#define QWNMEDIAPLAYLIST_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

class QwnMediaPlaylist : public QObject
{
	Q_OBJECT
public:
	explicit QwnMediaPlaylist(QObject *parent = 0) : QObject(parent)
	{

	}

signals:

public slots:
};

#endif // QWNMEDIAPLAYLIST_H
