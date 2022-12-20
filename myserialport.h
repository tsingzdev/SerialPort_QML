#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QColor>
#include <QDateTime>
#include <QFile>
#include <QDir>
//#include <QTimer>

#define ASIIC_TYPE true
#define HEX_TYPE false

class MySerialPort : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool recDataModel READ readRecDataModel WRITE setRecDataModel)

public:
    explicit MySerialPort(QObject *parent = nullptr);
    ~MySerialPort();
    QSerialPort *myPort;

    bool recDataModel=ASIIC_TYPE;
    void setRecDataModel(bool s){recDataModel=s;}
    bool readRecDataModel(){return recDataModel;}


public:
    void printToFile(QByteArray data);

signals:
    void portNameSignal(QString portName);
    void displayRecDataSignal(QString);
    void authorChanged();
    void returnOpenResultSignal(bool);

public slots:
    void setPort();
    void setBaud(int);
    void setStopBits(int);
    void setDataBase(int);
    void setParity(int);
    void initPort();
    void initConnect();
    void openPort(QString value);
    void readData_slot();  //接收数据
    void writeData(QString ,bool);   //发送数据
    bool readIsMyPortOpen();

public:


};

#endif // MYSERIALPORT_H
