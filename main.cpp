#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "TelnetConnection.cpp"

int main(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    QObject* rootObject = engine.rootObjects().first();
    QObject* textContainer = rootObject->findChild<QObject*>("textContainer");

    TelnetConnection* connection = new TelnetConnection("192.168.10.128", textContainer);
    bool result = connection->open();

    if (!result) {
        return -1;
    }
            
    connection->beginUpdates();

    return app.exec();
}
