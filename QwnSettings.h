#ifndef QWNSETTINGS_H
#define QWNSETTINGS_H

#include <QObject>

class QwnSettings : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString url
			   READ url
			   WRITE setUrl
			   NOTIFY urlChanged)

	Q_PROPERTY(QString username
			   READ username
			   WRITE setUsername
			   NOTIFY usernameChanged)

	Q_PROPERTY(QString password
			   READ password
			   WRITE setPassword
			   NOTIFY passwordChanged)

	Q_PROPERTY(bool is_initialized
			   READ is_initialized)

private:
	QString m_filePath;
	QString m_url;
	QString m_username;
	QString m_password;
	bool m_is_initialized;

public:
	explicit QwnSettings(QObject *parent = 0);

	QString url() const;
	QString username() const;
	QString password() const;
	bool is_initialized() const;

	void setUrl(const QString& url);
	void setUsername(const QString& username);
	void setPassword(const QString& password);

signals:
	void urlChanged();
	void usernameChanged();
	void passwordChanged();

private slots:
	void slotUrlChanged();
	void slotUsernameChanged();
	void slotPasswordChanged();

public slots:
	void initialize();
};

#endif // QWNSETTINGS_H
