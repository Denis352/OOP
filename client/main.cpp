#include "MainWindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    qDebug() << "Starting Polynomial GUI Client...";

    MainWindow window;
    window.show();

    return app.exec();
}
