#ifndef RESPONSEDECODER_H
#define RESPONSEDECODER_H

#include <QObject>
#include "Artist.h"

class ResponseDecoder : public QObject
{
	Q_OBJECT
public:
	explicit ResponseDecoder(QObject *parent = 0);


	void decode(const QString& dataType, const QByteArray& data);

private:
	void decodeCollection(const QByteArray& data);

public slots:
	void slotCollectionData(QByteArray);

signals:
	void signalCollectionDataParsed(QList<Artist*>);
};

#endif // RESPONSEDECODER_H
