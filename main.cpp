#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "OwnCloudClient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	OwnCloudClient* cloudClient = new OwnCloudClient();
	cloudClient->auth();

    return app.exec();
}

