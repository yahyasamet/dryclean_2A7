#include "arduino.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QSqlQuery>

arduino::arduino()
{

}

int arduino::connect_arduino(){

    foreach(const QSerialPortInfo& serial_port_info, QSerialPortInfo::availablePorts())
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {
           if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_producy_id)
            {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();

            }
        }
    }

    qDebug() << "arduino_port_name is : " << arduino_port_name;

    if(arduino_is_available)
    {
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadWrite))
        {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return  0;
        }
        return 1;
    }

    return -1;
}

int arduino::close_arduino(){
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}

QSerialPort* arduino::getserial()
{
    return serial;
}

QString arduino::read_from_arduino(){
    QStringList list;
        if(serial->isReadable()){

            while (serial->canReadLine()) {
                QByteArray data = serial->readLine();
               list = QString(data).split(',');

        }
    }
         qDebug()<<"read:"<<list.join(',');
        return list.join(',');
}

int arduino::write_to_arduino(QByteArray d){
    if(serial->isWritable()){
        serial->write(d);
        return 1;
    }
    else{
        qDebug("Couldn't write to serial!");
        return 0;
    }
}
