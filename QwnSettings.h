#ifndef QWNSETTINGS_H
#define QWNSETTINGS_H

#include "Macros.h"

class QwnSettings : public QObject
{
	Q_OBJECT

	QML_PROPERTY(QString, url, setUrl, urlChanged)
	QML_PROPERTY(QString, username, setUsername, usernameChanged)
	QML_PROPERTY(QString, password, setPassword, passwordChanged)
	QML_PROPERTY_READONLY(bool, is_initialized)

private:
	QString m_filePath;

public:
	explicit QwnSettings(QObject *parent = 0);

private slots:
	void slotUrlChanged();
	void slotUsernameChanged();
	void slotPasswordChanged();

public slots:
	void initialize();
};

#endif // QWNSETTINGS_H
