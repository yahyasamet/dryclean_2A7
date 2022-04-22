#include "barcodebox.h"

#include <QDebug>
#include <QMessageBox>


BarCodeBox::BarCodeBox(const QString &title, QWidget *parent) :
    QGroupBox(title,parent)
{
    barCodes="";
    barCodeWidth = 0;
}

void BarCodeBox::setBarCodes(QString barCodes)
{
    this->barCodes=barCodes;
    int num = barCodes.size();//Obtenir la taille de la chaîne encodée bs ou 01 bs:code128 01:EAN13
    barCodeWidth=num*PEN_WIDTH;//Stocker la largeur du code-barres généré
}

void BarCodeBox::drawBarCode(QPainter &painter, int x, int y)
{
    int num = barCodes.size();
    painter.setPen(QPen(Qt::black,PEN_WIDTH));
    for(int i=0;i<num;i++)
    {
        if(barCodes.at(i)=='b')//Dessinez une ligne noire de deux pixels de large, un pixel est trop étroit pour rechercher le code128
        {
            painter.drawLine(x+i*PEN_WIDTH,y,x+i*PEN_WIDTH,y+BARCODE_HEIGHT);
        }
        else if(barCodes.at(i)=='1')//Pour EAN13, parce que la barre du démarreur, du séparateur intermédiaire et du terminateur est plus longue, elle doit être traitée séparément
        {
            //Étant donné que le nombre de chiffres de EAN13 est fixé à 13, le nombre de modules de barre occupés est fixe et la position du caractère de début, du séparateur central et du terminateur est également fixe.
            if((i>10&&i<14)||(i>55&&i<61)||(i>102&&i<106))
            {
                painter.drawLine(x+i*PEN_WIDTH,y,x+i*PEN_WIDTH,y+BARCODE_HEIGHT+6);
            }
            else
            {
                painter.drawLine(x+i*PEN_WIDTH,y,x+i*PEN_WIDTH,y+BARCODE_HEIGHT);
            }
        }
    }
}
void BarCodeBox::savePicture()
{
    if(barCodeWidth==0)
    {
        return;
    }
    QPixmap pixmap(barCodeWidth+8,BARCODE_HEIGHT+24);
    //Rendez la zone spécifiée du composant dans le pixmap, le premier paramètre est le périphérique cible pour le rendu et le deuxième paramètre est le point de départ du rendu sur le périphérique cible,
    //Le troisième paramètre spécifie la zone de la partie rendue
    this->render(&pixmap,QPoint(0,0),QRegion(posX-4,posY-12,barCodeWidth+8,BARCODE_HEIGHT+24));//Rendre la page du widget dans le pixmap
    pixmap=pixmap.scaled(400,300);//Mettez l'image à l'échelle à la taille spécifiée, le paramètre par défaut ignore le rapport d'aspect
    //Le premier paramètre spécifie le nom du fichier enregistré, le second est le format d'image et le troisième est la qualité d'image 0-100
    if(pixmap.save("C:/Users/Amira/Desktop/esprit/sem2/qt/integration/Barcode.png","PNG",90))//enregistrer l'image
    {
        QMessageBox::information(this,"Sucess","success");
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Erreur");
    }
}
void BarCodeBox::paintEvent(QPaintEvent *event)
{
    QGroupBox::paintEvent(event);//Appelez d'abord le gestionnaire d'événement redraw de la classe parent, sinon la bordure et le titre par défaut de la zone de groupe ne seront pas affichés
    if(barCodeWidth==0)
    {
        return;
    }
    //QPainter ne peut être appelé que dans paintEvent par défaut, et le périphérique en cours de dessin doit également réécrire paintEvent

    QPainter painter(this);//Définir un objet pour QPainter
    painter.setPen(Qt::NoPen);//Parce qu'on veut utiliser drawRect() pour remplir uniquement la couleur et ne pas dessiner la ligne de bord,on n'a pas besoin d'un pinceau
    painter.setBrush(QBrush(Qt::white));//La zone d'arrière-plan du code est blanche
    posX = (this->width()-barCodeWidth)/2;//La position x du sommet gauche du code à barre
    posY = (this->height()-BARCODE_HEIGHT)/2;//La position y du sommet gauche du code à barre dans la case
    //Dessinez d'abord une zone légèrement plus grande que le code à barre
    painter.drawRect(posX-4,posY-12,barCodeWidth+8,BARCODE_HEIGHT+24);
    //dessiner le code à barre
    drawBarCode(painter,posX,posY);

}
