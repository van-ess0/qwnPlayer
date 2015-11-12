#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "OwnCloudClient.h"
#include "ResponseDecoder.h"
#include "MainWindow.h"
#include "MediaPlayer.h"

#include <QApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickWindow>

#include <QStringList>


int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	// For single qml file
//	QQmlApplicationEngine engine;
//	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


	// Register our component type with QML.
	// Need for ability to directly call object from qml
	qmlRegisterType<QwnMediaPlayer>("com.qwnplayer", 1, 0, "QwnMediaPlayer");

	// Need to connect quit and create qml component
	QQmlEngine engine;
	QObject::connect(&engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

	QQmlComponent component(&engine, QUrl("qrc:/main.qml"));
	QObject* topLevel = component.create();
	QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);


	qRegisterMetaType< QList<Artist*> >("ArtistList");

	OwnCloudClient* cloudClient = new OwnCloudClient();


	ResponseDecoder* decoder = new ResponseDecoder();

	// Other way to connect some qml objects with c++ objects

//	QwnMediaPlayer* player = new QwnMediaPlayer(); // or get it from window like a child
//	QQuickItem* playbutton = window->findChild<QQuickItem*>("playbutton");

//	QObject::connect(playbutton, SIGNAL(qmlSignal(QString)),
//					 player, SLOT(qmlSlot(QString)));
//	QObject::connect(playbutton, SIGNAL(qmlSignalEmpty()),
//					 player, SLOT(qmlSlotEmpty()));
//	QObject::connect(playbutton, SIGNAL(qmlSignalEmpty()),
//					 player, SIGNAL(testSig()));



	QObject::connect(cloudClient, SIGNAL(signalCollectionData(QByteArray)),
					 decoder, SLOT(slotCollectionData(QByteArray)));
//	QObject::connect(decoder, SIGNAL(signalCollectionDataParsed(QList<Artist*>)),
//						 &mainWindow, SLOT(slotCollectionDataParsed(QList<Artist*>)));
//	QObject::connect(cloudClient, SIGNAL(signalLog(QString)),
//						 &mainWindow, SLOT(slotLog(QString)));
	cloudClient->auth();

//	mainWindow.show();
//	view->show();
    return app.exec();
}

