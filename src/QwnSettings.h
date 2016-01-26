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

	QML_PROPERTY(QString, globalAccentColor, setGlobalAccentColor, globalAccentColorChanged)
	QML_PROPERTY(QString, globalBackgroundColor, setGlobalBackgroundColor, globalBackgroundColorChanged)
	QML_PROPERTY(QString, globalRectangleColor, setGlobalRectangleColor, globalRectangleColorChanged)
	QML_PROPERTY(QString, globalRectangleBorderColor, setGlobalRectangleBorderColor, globalRectangleBorderColorChanged)

private:
	QString m_homeLocation;
	QString m_filePath;

public:
	explicit QwnSettings(QObject *parent = 0);

signals:
    void signalSettingsFilled();

private slots:
	void slotUrlChanged();
	void slotUsernameChanged();
	void slotPasswordChanged();

public slots:
	void initialize();
	void saveAllSettings();
};

#endif // QWNSETTINGS_H
