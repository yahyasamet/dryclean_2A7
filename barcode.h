#ifndef BARCODE_H
#define BARCODE_H

#include <QString>
#include <QList>

class BarCode
{
public:
    BarCode();
    QString process128BCode(QString code);
    QString processEAN13Code(QString code);
private:
    void initCode128B();
    void initEAN13();

private:

    QList<QString> char128BList;
    QList<QString> code128BValue;


    QList<QString> preCodeWayList;
    QList<QString> codeAEAN13Value;
    QList<QString> codeBEAN13Value;
    QList<QString> codeCEAN13Value;

};

#endif // BARCODE_H
