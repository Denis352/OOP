#include <QCoreApplication>
#include <QDebug>
#include "QtServer.h"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    qDebug() << "=== Qt6 Polynomial Server ===";
    qDebug() << "Using Qt version:" << QT_VERSION_STR;

    QtServer server(12345);
    server.start();

    qDebug() << "Server is running. Press Ctrl+C to stop.";

    return app.exec();
}