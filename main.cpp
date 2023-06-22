#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "producer.h"
#include "gstpipeline.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Producer * frameProvider = new Producer();
    Gstpipeline gstpipe;
    gstpipe.gstpipeline_init(frameProvider);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("frameProvider", frameProvider);
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


