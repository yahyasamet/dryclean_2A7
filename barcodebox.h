#ifndef BARCODEBOX_H
#define BARCODEBOX_H

#include <QGroupBox>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>

#define BARCODE_HEIGHT 70 //hauteur du code à barre
#define PEN_WIDTH 2 //Largeur du pinceau Pixels

class BarCodeBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit BarCodeBox(const QString & title,QWidget *parent = 0);
    void setBarCodes(QString barCodes);
    void drawBarCode(QPainter &painter,int x,int y);
    void savePicture();

protected:
    void paintEvent(QPaintEvent * event);

signals:

public slots:

private:
    QString barCodes;
    int barCodeWidth;//Stocker la largeur du code à barre généré
    int posX;
    int posY;

};

#endif // BARCODEBOX_H
