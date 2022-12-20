#include "myserialport.h"



int count=0;
QByteArray dataText;


MySerialPort::MySerialPort(QObject *parent) : QObject(parent)
{
    myPort=new QSerialPort;
}

MySerialPort::~MySerialPort()
{
    delete myPort;
}

void MySerialPort::printToFile(QByteArray data)
{
    QFile file;
    QString fileName = "C:/Users/";
    QString userName = QDir::home().dirName();
    fileName.append(userName).append("/Desktop/SerialLog.txt");

    file.setFileName(fileName);
    if(file.open(QIODevice::WriteOnly )){
        file.write(data.toHex(' '));
        file.close();
    }
}


bool MySerialPort::readIsMyPortOpen()
{
    return myPort->isOpen();
}

void MySerialPort::initPort()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() <<  "===========发现可用串口：===============";
//        QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");  //毫秒
//        qDebug() << "["<<timeStr<<"]";
        qDebug() << "Name : " << info.portName();
        emit portNameSignal(info.portName());
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Serial Number: " << info.serialNumber();
        qDebug() << "System Location: " << info.systemLocation();
        qDebug() << "Vendor Identifier: " << info.vendorIdentifier();
        qDebug() << "Product Identifier: " << info.productIdentifier();
        qDebug() << "======================================";
    }
}

//建立信号槽连接
void MySerialPort::initConnect()
{
    connect(myPort,&QSerialPort::readyRead,this,&MySerialPort::readData_slot);
}

void MySerialPort::openPort(QString value)
{
    QStringList list=value.split('/');
    int btnState=list[0].toInt();
    QString port=list[1];

    if(btnState==1)   //1 串口打开标志
    {
        //设置串口名字
        myPort->setPortName(port);

        /*
        myPort->setPortName(comName);
        myPort->setBaudRate(baud);
        myPort->setBaudRate(baud);
        myPort->setFlowControl(QSerialPort::NoFlowControl);
        myPort->setDataBits(QSerialPort::Data8);
        myPort->setStopBits(QSerialPort::OneStop);
        myPort->open(QIODevice::ReadWrite);*/


        if(myPort->open(QIODevice::ReadWrite))
        {
            connect(myPort,&QSerialPort::readyRead,this,&MySerialPort::readData_slot);
            qDebug()<<"============打开串口：===============";
            qDebug()<<"Reading port: " << myPort->portName()<<myPort->baudRate()<<myPort->dataBits();
        }
        else
        {

        }
    }
    else if(btnState==0)
    {
        myPort->close();
    }
    emit returnOpenResultSignal(myPort->isOpen());

}

void MySerialPort::readData_slot()
{
    QByteArray buff;
    buff=myPort->readAll();

    qDebug() << "[buff] size:  "  << buff.size() << ", content: "<<  buff;

    if (buff.isEmpty()) return;

    dataText.append(buff);
    printToFile(dataText);

    if(recDataModel==ASIIC_TYPE)  //ASIIC
    {
        emit displayRecDataSignal(buff.data());
    }
    else
    {
        QString str=buff.toHex();
        QString str1;
        for(int i = 0; i < str.length()/2;i++)
        {
            str1 += str.mid(i*2,2) + " ";
        }
//        emit displayRecDataSignal(str1);
    }
}

void MySerialPort::writeData(QString s,bool dataModel)
{

    qDebug() <<"PortName: " << myPort->portName()<< "; BaudRate: " << myPort->baudRate()<< "; Databits: " << myPort->dataBits();
    QByteArray str;
    if(myPort->isOpen())
    {
        if(dataModel==ASIIC_TYPE)
        {
            str=s.toLatin1();
        }
        else
        {
            str=QByteArray::fromHex(s.toLatin1());
        }
        int m_size = myPort->write(str);
        QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");  //毫秒
        qDebug() << "["<<timeStr<<"] Port TX, Size " << m_size <<": "<< str;

    }
    else
    {

    }
}

void MySerialPort::setPort()
{

}

//波特率
void MySerialPort::setBaud(int baud)
{
    myPort->setBaudRate(baud);
}
//停止位
void MySerialPort::setStopBits(int Stopbit)
{
    if(Stopbit == 1)
        myPort->setStopBits(QSerialPort::OneStop);
    if(Stopbit == 3)
        myPort->setStopBits(QSerialPort::OneAndHalfStop);
    if(Stopbit == 2)
        myPort->setStopBits(QSerialPort::TwoStop);
}


//数据位
void MySerialPort::setDataBase(int dataBase)
{

    if(dataBase==5)
        myPort->setDataBits(QSerialPort::Data5);
    else if(dataBase==6)
        myPort->setDataBits(QSerialPort::Data6);
    else if(dataBase==7)
        myPort->setDataBits(QSerialPort::Data7);
    else if(dataBase==8)
        myPort->setDataBits(QSerialPort::Data8);

}

//校验位
void MySerialPort::setParity(int parity)
{
    if(parity == 0)
        myPort->setParity(QSerialPort::NoParity);
    if(parity == 3)
        myPort->setParity(QSerialPort::OddParity);
    if(parity == 2)
        myPort->setParity(QSerialPort::EvenParity);
}

