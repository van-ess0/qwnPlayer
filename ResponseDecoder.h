#ifndef RESPONSEDECODER_H
#define RESPONSEDECODER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class ResponseDecoder : public QObject
{
	Q_OBJECT
public:
	explicit ResponseDecoder(QObject *parent = 0);


	void decode(const QString& dataType, const QByteArray& data);

private:
	void decodeCollection(const QByteArray& data);
};

#endif // RESPONSEDECODER_H
