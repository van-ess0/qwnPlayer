#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "OwnCloudClient.h"
#include "ResponseDecoder.h"
#include "QwnMediaPlayer.h"
#include "QwnSettings.h"
#include "MusicLibrary.h"

#include <QApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickWindow>

#include <QStringList>
#include "SettingsManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qSetMessagePattern("[%{time yyyyMMdd h:mm:ss.zzz}]\
    [%{if-debug}DEBUG%{endif}\%{if-info}INFO%{endif}%{if-warning}WARNING%{endif}\
%{if-critical}CRITICAL%{endif}%{if-fatal}FATAL%{endif}]\
    [%{file}:%{line} %{function}] - %{message}");


//	SettingsManager::instance()->setFile("settings.conf");
//	qDebug() << SettingsManager::instance()->getOwnCloudHost();

    // For single qml file
//	QQmlApplicationEngine engine;
//	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    qRegisterMetaType< QList<Artist*> >("ArtistList");
//	qRegisterMetaType< Models::SubListedListModel* >("SubListedListModel");



//	musicLibrary->setArtistList(artists);
//	QObject::connect(decoder, SIGNAL(signalCollectionDataParsed(QList<Artist*>)),
//					 musicLibrary, SLOT(slotCollectionDataParsed(QList<Artist*>)));

//	Models::SubListedListModel* m_artistModel
//			= musicLibrary->getArtistModel();
    // Register our component type with QML.
    // Need for ability to directly call object from qml
    qmlRegisterType<QwnMediaPlayer>("com.qwnplayer", 1, 0, "QwnMediaPlayer");
    qmlRegisterType<QwnSettings>("com.qwnplayer", 1, 0, "QwnSettings");
    qmlRegisterType<OwnCloudClient>("com.qwnplayer", 1, 0, "OwnCloudClient");


    // Need to connect quit and create qml component
    QQuickView view;
    QQmlEngine* engine = view.engine();
    QObject::connect(engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

    QQmlContext* context = engine->rootContext();
//	context->setContextObject(musicLibrary);
//	context->setContextProperty("artistList",
//								QVariant::fromValue(musicLibrary->getArtistList()));
//	context->setContextProperty("artistModel", m_artistModel);

	MusicLibrary* musicLibrary = new MusicLibrary();
    context->setContextProperty("artistModel", musicLibrary->getArtistModel());

//	QObject::connect(decoder, SIGNAL(signalCollectionDataParsed(Models::SubListedListModel*)),
//					 musicLibrary, SLOT(slotCollectionDataParsed(Models::SubListedListModel*)));

    QQmlComponent component(engine, QUrl("qrc:/qml/main.qml"));

    QObject* topLevel = component.create(context);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
//	Q_UNUSED(window)
//	view.setSource(QUrl("qrc:/HomePage.qml"));
//	view.show();


    // Other way to connect some qml objects with c++ objects

//	QwnMediaPlayer* player = new QwnMediaPlayer(); // or get it from window like a child
//	QQuickItem* playbutton = window->findChild<QQuickItem*>("playbutton");

//	QObject::connect(playbutton, SIGNAL(qmlSignal(QString)),
//					 player, SLOT(qmlSlot(QString)));
//	QObject::connect(playbutton, SIGNAL(qmlSignalEmpty()),
//					 player, SLOT(qmlSlotEmpty()));
//	QObject::connect(playbutton, SIGNAL(qmlSignalEmpty()),
//					 player, SIGNAL(testSig()));
//	QQuickItem* connectionPage = window->findChild<QQuickItem*>("ConnectionPage");
//	QObject::connect(connectionPage, SIGNAL(qmlSignalAuth()),
//					 cloudClient, SLOT(auth()));

	QObject* cloudClientObject = window->findChild<QObject*>("cloudClient");
	OwnCloudClient* cloudClient = qobject_cast<OwnCloudClient*>(cloudClientObject);

    ResponseDecoder* decoder = new ResponseDecoder();
    QObject::connect(cloudClient, SIGNAL(signalCollectionData(QByteArray)),
                     decoder, SLOT(slotCollectionData(QByteArray)));

	QObject* mediaPlayerObject = window->findChild<QObject*>("mediaPlayer");
	QwnMediaPlayer* mediaPlayer = qobject_cast<QwnMediaPlayer*>(mediaPlayerObject);
	mediaPlayer->setMusicLibrary(musicLibrary);

	QObject::connect(decoder, SIGNAL(signalCollectionDataParsed(QList<Artist*>)),
					 musicLibrary, SLOT(slotCollectionDataParsed(QList<Artist*>)));
//	QObject::connect(decoder, SIGNAL(signalCollectionDataParsed(QList<Artist*>)),
//						 &mainWindow, SLOT(slotCollectionDataParsed(QList<Artist*>)));
//	QObject::connect(cloudClient, SIGNAL(signalLog(QString)),
//						 &mainWindow, SLOT(slotLog(QString)));
//	cloudClient->auth();



//	mainWindow.show();
//	view->show();
    return app.exec();
}
