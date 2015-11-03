#ifndef TRACK_H
#define TRACK_H

#include <QObject>

class Track : public QObject
{
	Q_OBJECT
private:
	quint32 m_number;
	QString m_title;
	QString m_audioType;
	QString m_serverPath;
public:
	explicit Track(const quint32 number,
				   const QString& title,
				   const QString& type,
				   const QString& path,
				   QObject *parent = 0);
	quint32 getNumber() const {
		return m_number;
	}
	QString getTitle() const {
		return m_title;
	}
	QString getType() const {
		return m_audioType;
	}
	QString getServerPath() const {
		return m_serverPath;
	}
};

#endif // TRACK_H
