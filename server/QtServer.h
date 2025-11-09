#ifndef QTSERVER_H
#define QTSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QDebug>

class QtServer : public QObject {
    Q_OBJECT

public:
    explicit QtServer(quint16 port = 12345, QObject* parent = nullptr);
    ~QtServer();

    void start();
    void stop();

private slots:
    void processDatagram();

private:
    QUdpSocket* socket;
    quint16 port;

    QByteArray processRequest(const QByteArray& request);
    // Временно убираем - будут проблемы с линковкой
    // Polynom parsePolynom(const QJsonArray& jsonArray);
    // Polynom executeOperation(const QString& operation, const Polynom& p1, const Polynom& p2);
};

#endif