#include "arduino.h"

Arduino::Arduino()
{
    data="";
       arduino_port_name="";
       arduino_is_available=false;
       serial=new QSerialPort;
}
QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}
QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_arduino()//ydetecti ana port mawjoud fih l'arduino
{
    foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts())
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
{
  if(serial_port_info.vendorIdentifier()== arduino_uno_vendor_id && serial_port_info.productIdentifier()==arduino_uno_producy_id)
  {
   arduino_is_available=true;
arduino_port_name=serial_port_info.portName();
  }
      }
}
qDebug()<<" Le nom du port Arduino est :" <<arduino_port_name;
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
        return 0;
    }
return 1;
}
return -1;
}
int Arduino::close_arduino()
{
    if(serial->isOpen())
    {
        serial->close();
        return 0;
    }
    return 1;
}
QString Arduino::read_from_arduino()
{
     QStringList list;
    if(serial->isReadable()){
        //data=serial->readAll();
      //  QString temp = QString::fromStdString(data.toStdString());
       // return temp;
        while (serial->canReadLine()) {
            QByteArray data = serial->readLine();
           list = QString(data).split(',');

    }
}
     qDebug()<<"read:"<<list.join(',');
    return list.join(',');

}
int Arduino::write_to_arduino(QString d)
{
    int i = 0;
    int size = d.size();
    qDebug()<<"write:"<<d;
    QString line = "";
    int c = 0;
    while(i < size){
        line.append(d[i]);
        if(c == 24){
            int sended = serial->write(line.toUtf8(), 24);
            serial->flush();
            line.clear();
            c = 0;
        }
        i++;
        c++;
    }
    if(c > 0){
        serial->write(line.toUtf8(), c);
    }
    serial->flush();

}
