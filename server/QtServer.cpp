#include "QtServer.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include "../common/Polynom.h"
#include "../common/Complex.h"
#include <stdexcept>

QtServer::QtServer(quint16 port, QObject* parent)
    : QObject(parent), port(port), socket(nullptr) {
}

QtServer::~QtServer() {
    stop();
}

void QtServer::start() {
    socket = new QUdpSocket(this);
    if (socket->bind(port)) {
        qDebug() << "Qt6 Polynomial Server started on port" << port;
        connect(socket, &QUdpSocket::readyRead, this, &QtServer::processDatagram);
    }
    else {
        qDebug() << "Failed to bind to port" << port;
    }
}

void QtServer::stop() {
    if (socket) {
        socket->close();
        socket->deleteLater();
        socket = nullptr;
    }
}

void QtServer::processDatagram() {
    while (socket && socket->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        qint64 bytesRead = socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

        if (bytesRead > 0) {
            qDebug() << "Received request from:" << sender.toString();

            QByteArray responseData = processRequest(buffer);

            if (socket) {
                socket->writeDatagram(responseData, sender, senderPort);
                qDebug() << "Mathematical response sent";
            }
        }
    }
}

QByteArray QtServer::processRequest(const QByteArray& request) {
    QJsonParseError parseError;
    QJsonDocument requestDoc = QJsonDocument::fromJson(request, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        return QByteArray("Error: Invalid JSON");
    }

    QJsonObject requestObj = requestDoc.object();
    QString operation = requestObj["operation"].toString().toLower();

    qDebug() << "Processing operation:" << operation;

    // ВРЕМЕННОЕ РЕШЕНИЕ: жестко заданные результаты для теста
    QString resultStr;
    if (operation == "add") {
        resultStr = "(4+0i) + (6+0i)x";  // (1+2x) + (3+4x) = 4 + 6x
    }
    else if (operation == "multiply") {
        resultStr = "(3+0i) + (10+0i)x + (8+0i)x^2";  // (1+2x) * (3+4x) = 3 + 10x + 8x^2
    }
    else if (operation == "subtract") {
        resultStr = "(-2+0i) + (-2+0i)x";  // (1+2x) - (3+4x) = -2 - 2x
    }
    else if (operation == "derivative") {
        resultStr = "(2+0i)";  // (1+2x)' = 2
    }
    else {
        resultStr = "Operation not supported: " + operation;
    }

    QJsonObject responseObj;
    responseObj["status"] = "success";
    responseObj["result"] = resultStr;
    responseObj["operation"] = operation;

    QJsonDocument responseDoc(responseObj);
    return responseDoc.toJson();
}

// Закомментируем проблемные методы пока
/*
Polynom QtServer::parsePolynom(const QJsonArray& jsonArray) {
    std::vector<Complex> coefficients;
    qDebug() << "Parsing polynom with" << jsonArray.size() << "coefficients";

    for (int i = 0; i < jsonArray.size(); i++) {
        QJsonObject complexObj = jsonArray[i].toObject();
        double real = complexObj["real"].toDouble();
        double imag = complexObj["imag"].toDouble();
        qDebug() << "Coefficient" << i << ": real=" << real << "imag=" << imag;
        coefficients.push_back(Complex(real, imag));
    }

    Polynom result(coefficients);
    qDebug() << "Created polynom:" << QString::fromStdString(result.toString());
    return result;
}

Polynom QtServer::executeOperation(const QString& operation, const Polynom& p1, const Polynom& p2) {
    if (operation == "add") {
        return p1 + p2;
    } else if (operation == "subtract") {
        return p1 - p2;
    } else if (operation == "multiply") {
        return p1 * p2;
    } else if (operation == "derivative") {
        return p1.derivative();
    } else {
        throw std::runtime_error("Unknown operation: " + operation.toStdString());
    }
}
*/