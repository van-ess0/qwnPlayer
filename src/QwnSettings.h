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
	QML_PROPERTY_READONLY(bool, isFirstLaunch)

	QML_PROPERTY(QString, globalAccentColor, setGlobalAccentColor, globalAccentColorChanged)
	QML_PROPERTY(QString, globalBackgroundColor, setGlobalBackgroundColor, globalBackgroundColorChanged)
	QML_PROPERTY(QString, globalRectangleColor, setGlobalRectangleColor, globalRectangleColorChanged)
	QML_PROPERTY(QString, globalRectangleBorderColor, setGlobalRectangleBorderColor, globalRectangleBorderColorChanged)
	QML_PROPERTY(bool, menuShowPermanent, setMenuShowPermanent, menuShowPermanentChanged)

private:
	QString m_homeLocation;
	QString m_filePath;

public:
	explicit QwnSettings(QObject *parent = 0);


	// TODO fix
//signals:
//    void signalSettingsFilled();

private slots:
	void slotUrlChanged();
	void slotUsernameChanged();
	void slotPasswordChanged();
	void slotGlobalAccentColorChanged();
	void slotGlobalBackgroundColorChanged();
	void slotGlobalRectangleColorChanged();
	void slotGlobalRectangleBorderColorChanged();
	void slotMenuShowPermanentChanged();

public slots:
	void initialize();
	void saveAllSettings();
};

#endif // QWNSETTINGS_H
