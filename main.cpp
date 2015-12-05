#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "OwnCloudClient.h"
#include "ResponseDecoder.h"
#include "QwnMediaPlayer.h"
#include "MusicLibrary.h"

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


	Track* track_one = new Track(1, "Number One", "audio/mp3", "./one.mp3");
	Track* track_two = new Track(2, "Number Two", "audio/mp3", "./two.mp3");
	Album* album_one = new Album("Album One", 2001);
	album_one->addTrack(track_one);
	album_one->addTrack(track_two);

	Track* track_three = new Track(3, "Number 3", "audio/mp3", "./three.mp3");
	Track* track_four = new Track(4, "Number 4", "audio/mp3", "./four.mp3");

	Album* album_two = new Album("Album Two", 2002);
	album_two->addTrack(track_three);
	album_two->addTrack(track_four);

	Artist* artist_one = new Artist("Artist One");
	artist_one->addAlbum(album_one);
	artist_one->setName("Artist One");

	Artist* artist_two = new Artist("Artist Two");
	artist_two->addAlbum(album_two);
	artist_two->setName("Artist Two");

	QList<QObject*> artists;
	artists.append(artist_one);
	artists.append(artist_two);

	Models::SubListedListModel* m_artistModel = new Models::SubListedListModel(new Artist("empty", NULL));
	m_artistModel->appendRow(artist_one);
	m_artistModel->appendRow(artist_two);

	qRegisterMetaType< QList<Artist*> >("ArtistList");

	OwnCloudClient* cloudClient = new OwnCloudClient();
	ResponseDecoder* decoder = new ResponseDecoder();
	QObject::connect(cloudClient, SIGNAL(signalCollectionData(QByteArray)),
					 decoder, SLOT(slotCollectionData(QByteArray)));

	MusicLibrary* musicLibrary = new MusicLibrary();
	musicLibrary->setArtistList(artists);
//	QObject::connect(decoder, SIGNAL(signalCollectionDataParsed(QList<Artist*>)),
//					 musicLibrary, SLOT(slotCollectionDataParsed(QList<Artist*>)));

	// Register our component type with QML.
	// Need for ability to directly call object from qml
	qmlRegisterType<QwnMediaPlayer>("com.qwnplayer", 1, 0, "QwnMediaPlayer");

	// Need to connect quit and create qml component
	QQuickView view;
	QQmlEngine* engine = view.engine();
	QObject::connect(engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

	QQmlContext* context = engine->rootContext();
//	context->setContextObject(musicLibrary);
//	context->setContextProperty("artistList",
//								QVariant::fromValue(musicLibrary->getArtistList()));
	context->setContextProperty("artistModel", m_artistModel);

	QQmlComponent component(engine, QUrl("qrc:/main.qml"));

	QObject* topLevel = component.create(context);
	QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
	Q_UNUSED(window)
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



//	QObject::connect(decoder, SIGNAL(signalCollectionDataParsed(QList<Artist*>)),
//						 &mainWindow, SLOT(slotCollectionDataParsed(QList<Artist*>)));
//	QObject::connect(cloudClient, SIGNAL(signalLog(QString)),
//						 &mainWindow, SLOT(slotLog(QString)));
	cloudClient->auth();



//	mainWindow.show();
//	view->show();
    return app.exec();
}

