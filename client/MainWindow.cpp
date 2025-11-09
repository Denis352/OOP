#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons to slots
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->subtractButton, &QPushButton::clicked, this, &MainWindow::on_subtractButton_clicked);
    connect(ui->multiplyButton, &QPushButton::clicked, this, &MainWindow::on_multiplyButton_clicked);
    connect(ui->derivativeButton, &QPushButton::clicked, this, &MainWindow::on_derivativeButton_clicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);

    // Create socket for network communication
    socket = new QUdpSocket(this);
    connect(socket, &QUdpSocket::readyRead, this, &MainWindow::onServerResponse);

    setWindowTitle("Polynomial Calculator Client");
    ui->statusbar->showMessage("Ready to work");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    ui->statusbar->showMessage("Performing addition...");
    sendOperation("add");
}

void MainWindow::on_subtractButton_clicked()
{
    ui->statusbar->showMessage("Performing subtraction...");
    sendOperation("subtract");
}

void MainWindow::on_multiplyButton_clicked()
{
    ui->statusbar->showMessage("Performing multiplication...");
    sendOperation("multiply");
}

void MainWindow::on_derivativeButton_clicked()
{
    ui->statusbar->showMessage("Calculating derivative...");
    sendOperation("derivative");
}

void MainWindow::on_clearButton_clicked()
{
    ui->polynom1Input->clear();
    ui->polynom2Input->clear();
    ui->resultDisplay->clear();
    ui->statusbar->showMessage("Fields cleared");
}

void MainWindow::sendOperation(const QString& operation)
{
    // Simple test request
    QJsonObject requestObj;
    requestObj["operation"] = operation;

    // Fixed polynomials for testing
    if (operation == "derivative") {
        requestObj["polynom1"] = QJsonArray{
            QJsonObject{{"real", 1}, {"imag", 0}},
            QJsonObject{{"real", 2}, {"imag", 0}},
            QJsonObject{{"real", 3}, {"imag", 0}}
        };
        requestObj["polynom2"] = QJsonArray{};
    }
    else {
        requestObj["polynom1"] = QJsonArray{
            QJsonObject{{"real", 1}, {"imag", 0}},
            QJsonObject{{"real", 2}, {"imag", 0}}
        };
        requestObj["polynom2"] = QJsonArray{
            QJsonObject{{"real", 3}, {"imag", 0}},
            QJsonObject{{"real", 4}, {"imag", 0}}
        };
    }

    QJsonDocument requestDoc(requestObj);
    QByteArray requestData = requestDoc.toJson();

    // Send to local server
    socket->writeDatagram(requestData, QHostAddress::LocalHost, 12345);
    ui->resultDisplay->setPlainText("Request sent to server...");
}

void MainWindow::onServerResponse()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

        QJsonDocument responseDoc = QJsonDocument::fromJson(buffer);
        QJsonObject responseObj = responseDoc.object();

        QString status = responseObj["status"].toString();
        QString result = responseObj["result"].toString();
        QString operation = responseObj["operation"].toString();

        if (status == "success") {
            ui->resultDisplay->setPlainText(
                QString("Operation: %1\nResult: %2").arg(operation).arg(result)
            );
            ui->statusbar->showMessage("Operation completed successfully");
        }
        else {
            ui->resultDisplay->setPlainText("Error: " + responseObj["message"].toString());
            ui->statusbar->showMessage("Execution error");
        }
    }
}