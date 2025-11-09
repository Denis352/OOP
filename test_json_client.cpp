#include <QUdpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    QUdpSocket socket;

    // Создаем JSON запрос на сложение полиномов
    QJsonObject requestObj;
    requestObj["operation"] = "add";

    // Полином 1: 1 + 2x
    QJsonArray poly1;
    poly1.append(QJsonObject{ {"real", 1}, {"imag", 0} });
    poly1.append(QJsonObject{ {"real", 2}, {"imag", 0} });
    requestObj["polynom1"] = poly1;

    // Полином 2: 3 + 4x  
    QJsonArray poly2;
    poly2.append(QJsonObject{ {"real", 3}, {"imag", 0} });
    poly2.append(QJsonObject{ {"real", 4}, {"imag", 0} });
    requestObj["polynom2"] = poly2;

    QJsonDocument requestDoc(requestObj);
    QByteArray requestData = requestDoc.toJson();

    qDebug() << "Sending JSON request:" << requestData;
    qint64 bytesSent = socket.writeDatagram(requestData, QHostAddress::LocalHost, 12345);

    if (bytesSent == -1) {
        qDebug() << "Failed to send data";
        return 1;
    }

    qDebug() << "Request sent, waiting for response...";

    // Ждем ответ - упрощенная версия без QNetworkDatagram
    QTimer::singleShot(3000, [&]() {
        while (socket.hasPendingDatagrams()) {
            QByteArray buffer;
            buffer.resize(socket.pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            qint64 bytesRead = socket.readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
            if (bytesRead > 0) {
                QJsonDocument responseDoc = QJsonDocument::fromJson(buffer);
                QJsonObject responseObj = responseDoc.object();

                qDebug() << "Server response:";
                qDebug() << "Status:" << responseObj["status"].toString();
                qDebug() << "Operation:" << responseObj["operation"].toString();

                if (responseObj["status"] == "success") {
                    qDebug() << "Result:" << responseObj["result"].toString();
                }
                else {
                    qDebug() << "Error:" << responseObj["message"].toString();
                }
            }
        }
        QCoreApplication::quit();
        });

    return app.exec();
}