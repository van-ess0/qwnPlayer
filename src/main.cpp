#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "OwnCloudClient.h"
#include "ResponseDecoder.h"
#include "QwnMediaPlayer.h"
#include "QwnSettings.h"
#include "MusicLibrary.h"

#include <QQuickView>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickWindow>

#include <QStringList>
#include "SettingsManager.h"
#include "QwnImageProvider.h"
#include "NotificationClient.h"

#ifdef SAILFISH_OS_HACK
#include <sailfishapp.h>
#define LoadGui SailfishApp::application(argc, argv)
#else
#define LoadGui new QGuiApplication(argc, argv)
#endif

int main(int argc, char *argv[])
{
	// Run right application with params
	QGuiApplication* app = LoadGui;

	// Debug message pattern
	qSetMessagePattern("[%{time yyyyMMdd h:mm:ss.zzz}]\
	[%{if-debug}DEBUG%{endif}\%{if-info}INFO%{endif}%{if-warning}WARNING%{endif}\%{if-critical}CRITICAL%{endif}%{if-fatal}FATAL%{endif}]\
	[%{file}:%{line} %{function}] - %{message}");

	// Register type for signal-slot
	qRegisterMetaType< QList<Artist*> >("ArtistList");

	// Register our component types with QML.
	// Need for ability to directly call object from qml
	qmlRegisterType<QwnMediaPlayer>("com.qwnplayer", 1, 0, "QwnMediaPlayer");
	qmlRegisterType<QwnSettings>("com.qwnplayer", 1, 0, "QwnSettings");
	qmlRegisterType<OwnCloudClient>("com.qwnplayer", 1, 0, "OwnCloudClient");
	qmlRegisterType<NotificationClient>("com.qwnplayer", 1, 0, "NotificationClient");

//	NotificationClient *notificationClient = new NotificationClient(&view);
//    view.engine()->rootContext()->setContextProperty(QLatin1String("notificationClient"),
//                                                     notificationClient);

	QQuickView view;
	QQmlEngine* engine = view.engine();

	// Need to connect quit and create qml component
	QObject::connect(engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

	// Set custom image provider for downloading with auth
	QwnImageProvider* imageProvider = new QwnImageProvider(QQmlImageProviderBase::Image);
	engine->addImageProvider("qwnImageProvider", imageProvider);

	// Set context for artist model and create music library
	QQmlContext* context = engine->rootContext();
	MusicLibrary* musicLibrary = new MusicLibrary(context);

	// Create main qml component from engine and conext
	QQmlComponent component(engine, QUrl("qrc:/qml/main.qml"));
	QObject* topLevel = component.create(context);
	if (!component.isReady()) {
		qDebug() << component.errors();
		app->quit();
		return 0;
	}

	// Take window object from qml for further actions
	QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);

	// Take cloud client object from qml
	QObject* cloudClientObject = window->findChild<QObject*>("cloudClient");
	OwnCloudClient* cloudClient = qobject_cast<OwnCloudClient*>(cloudClientObject);

	// Create json decoder component
	ResponseDecoder* decoder = new ResponseDecoder();
	QObject::connect(cloudClient, SIGNAL(signalCollectionData(QByteArray)),
					 decoder, SLOT(slotCollectionData(QByteArray)));
	QObject::connect(decoder, SIGNAL(signalCollectionDataParsed(QList<Artist*>)),
					 musicLibrary, SLOT(slotCollectionDataParsed(QList<Artist*>)));

	// Take player object from qml
	QObject* mediaPlayerObject = window->findChild<QObject*>("mediaPlayer");
	QwnMediaPlayer* mediaPlayer = qobject_cast<QwnMediaPlayer*>(mediaPlayerObject);

	// Set library component and context to player
	mediaPlayer->setMusicLibrary(musicLibrary);
	mediaPlayer->setContext(context);

	return app->exec();
}
