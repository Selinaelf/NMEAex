#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QString serialPortName;
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        if (1){
            serialPortName = portInfo.portName();
            qDebug()<<"serial port name is:  " << serialPortName;
        }
        else
            qDebug() << "No available serial port.";
    }



    // serial port setlemek
    //QSerialPort serial, s2;
    serial.setPortName("/dev/ttys002");
    serial.setBaudRate(QSerialPort::Baud115200); // Adjust the baud rate as per your requirements
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    s2.setPortName("/dev/ttys004");
    s2.setBaudRate(QSerialPort::Baud115200); // Adjust the baud rate as per your requirements
    s2.setDataBits(QSerialPort::Data8);
    s2.setParity(QSerialPort::NoParity);
    s2.setStopBits(QSerialPort::OneStop);
    s2.setFlowControl(QSerialPort::NoFlowControl);

    qDebug () << "AAAAAA";

    // Open the serial port
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port:" << serial.errorString();

        return;
    }
    if (!s2.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port:" << serial.errorString();
        return;
    }

    qDebug() << "Serial port opened. Sending and receiving data...";

    serial.open(QSerialPort::ReadWrite);
    s2.open(QSerialPort::ReadWrite);

    qDebug() << serial.isOpen() << s2.isOpen();


    // Example: Send a sample NMEA message
    QByteArray sampleNmeaMessage = "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A\r\n";
    serial.write(sampleNmeaMessage);

    // Wait for the data to be sent (you may use a better way to handle this in a real application)
    connect (& this->s2, SIGNAL(readyRead()), this, SLOT(DoStuff()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

