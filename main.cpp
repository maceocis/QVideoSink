#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "producer.h"
#include "gstpipeline.h"
#include "rendyboi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    std::string uri = "com.heine.components";
    int majorVersion = 1;
    int minorVersion = 0;

    qmlRegisterType<Rendyboi>(
        uri.c_str(),
        majorVersion,
        minorVersion,
        "Rendyboi"
    );

    Gstpipeline gstpipe;
    engine.rootContext()->setContextProperty("gstpipe", &gstpipe);
    gstpipe.gstpipeline_init();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
    gstpipe.gstpipeline_deinit();
}


