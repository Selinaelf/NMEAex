#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>


// Function to parse and interpret GPRMC NMEA sentence


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort s2;
    QSerialPort serial;
    void parseGPRMC(const QList<QByteArray> &fields) {
        static int i= 0;
        qDebug () << "PARSE GPMRC RUBNED " << i;
        ++i;
        qDebug() << "SIZE " << fields.size();

        for(auto &x : fields) {
            qDebug () << "GELDİ " << x;
        }

        if (fields.size() == 12) {

            QByteArray time = fields.at(1);
            QByteArray status = fields.at(2);
            QByteArray latitude = fields.at(3);
            QByteArray longitude = fields.at(5);
            QByteArray speed = fields.at(7);
            QByteArray course = fields.at(8);
            QByteArray date = fields.at(9);
            QByteArray magneticVariation = fields.at(10);

            qDebug() << "GPRMC Sentence:";
            qDebug() << "Time:" << time;
            qDebug() << "Status:" << status;
            qDebug() << "Latitude:" << latitude;
            qDebug() << "Longitude:" << longitude;
            qDebug() << "Speed:" << speed;
            qDebug() << "Course:" << course;
            qDebug() << "Date:" << date;
            qDebug() << "Magnetic Variation:" << magneticVariation;
        } else {
            qDebug() << "Invalid GPRMC sentence!";
        }
};


    // Function to parse NMEA messages
    void parseNmeaMessage(const QByteArray &message) {
        if (message.startsWith('$')) {
            QList<QByteArray> fields = message.mid(1).split(',');
            QByteArray sentenceIdentifier = fields.at(0);

            // Parse NMEA sentences based on sentenceIdentifier
            if (sentenceIdentifier == "GPRMC") {
                parseGPRMC(fields); // Call the parseGPRMC function to handle the GPRMC sentence
            }

            else {
                qDebug() << "Unsupported NMEA Sentence:" << sentenceIdentifier;
                qDebug() << "Data fields:" << fields;
            }
        }
    }


public slots:
    void DoStuff ()
    {
        QByteArray data = s2.readAll();
        // Process the received data (split NMEA messages and handle each one)
        qDebug() << "IN WHILE";
        parseNmeaMessage(data); // Pass the full NMEA sentence for parsing


    }

private:
    Ui::MainWindow *ui;
    //QSerialPort serial;

};
#endif // MAINWINDOW_H
