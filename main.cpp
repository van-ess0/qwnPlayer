#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "OwnCloudClient.h"
#include "ResponseDecoder.h"
#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	MainWindow mainWindow;
	qRegisterMetaType< QList<Artist*> >("ArtistList");

	OwnCloudClient* cloudClient = new OwnCloudClient();


	ResponseDecoder* decoder = new ResponseDecoder();

	QObject::connect(cloudClient, SIGNAL(signalCollectionData(QByteArray)),
					 decoder, SLOT(slotCollectionData(QByteArray)));
	QObject::connect(decoder, SIGNAL(signalCollectionDataParsed(QList<Artist*>)),
						 &mainWindow, SLOT(slotCollectionDataParsed(QList<Artist*>)));
	cloudClient->auth();

	mainWindow.show();
    return app.exec();
}

