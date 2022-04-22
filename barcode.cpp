#include "barcode.h"
#include <QDebug>
#include <QMessageBox>

BarCode::BarCode()
{
    initCode128B();
    initEAN13();
}

QString BarCode::process128BCode(QString code)
{
    int checkId=104;//Le chiffre de contrôle du code128B initialise l'identifiant qui stocke le chiffre de départ
    QString barCodes;//Utilisé pour stocker les chaînes bs
    barCodes.append("bbsbssbssss");//bit de démarrage StartB
    QString temp;
    int indexId;
    int num = code.size();//Obtenir la longueur du nombre d'entrée
    if(num == 0)
    {
        //qDebug()<<"Veuillez entrer un nombre：";
        QMessageBox::information(0,"barcode","Veuillez saisir le numéro");
        return NULL;
    }
    //encodage caractère par caractère
    for(int i=0;i<num;i++)
    {
        temp=code.mid(i,1);
        indexId = char128BList.indexOf(temp);//Obtenir la position correspondant au caractère
        if(indexId == -1)
        {
            //qDebug()<<"L'entrée contient des caractères non codables";
            QMessageBox::information(0,"barcode","L'entrée contient des caractères non codables");
            return NULL;
        }
        else
        {
            barCodes.append(code128BValue.at(indexId));//Ajouter l'encodage correspondant au caractère
            checkId +=(i+1)*indexId;//Calculer le chiffre de contrôle
        }
    }
    /*Calcul du chiffre de contrôle Code128 :
     *(valeur ID correspondant au bit de départ (B:104) + position de chaque bit de données dans l'ensemble des données (à partir de 1) × valeur ID correspondant à chaque bit de données) %103
     */
    checkId %=103;
    barCodes.append(code128BValue.at(checkId));//code bs avec chiffre de contrôle supplémentaire
    barCodes.append("bbsssbbbsbsbb");//Bit d'arrêt StopB
    /*Laisser 11 blancs de plus au début et à la fin, il n'appartient en fait pas au codage 128B, voici la zone vide qui imite EAN13,
     *Générer le code à barre correctement, mais fonctionnellement parlant, il ne doit pas être placé ici. Cependant, pour la commodité du traitement, faisons d'abord ceci
     */
    barCodes.prepend("sssssssssss");
    barCodes.append("sssssssssss");
    return barCodes;
}

QString BarCode::processEAN13Code(QString code)
{
    if(code.size() != 12)
    {
        //qDebug()<<" Veuillez saisir un numéro à 12 chiffres ：";
        QMessageBox::information(0,"barcode","Veuillez saisir un numéro à 12 chiffres：");
        return NULL;
    }
    //C1 C2 CC checkId Les variables sont utilisées pour calculer l'algorithme de chiffre de contrôle
    int C1=0;//Ajouter des chiffres impairs (13 chiffres commencent à 1 et n'ajoutent pas le treizième chiffre)
    int C2=0;//Additionner et multiplier les chiffres pairs numérotés par 3
    int CC=0;//C1+C2 prennent le chiffre un
    int checkId=0;
    QString barCodes;
    barCodes.append("00000000000");
    barCodes.append("101");
    bool ok;
    int preNo=code.mid(0,1).toInt(&ok);
    if(!ok)
    {
        //qDebug()<<"Les caractères saisis ne doivent pas contenir de symboles non numériques";
        QMessageBox::information(0,"barcode","Les caractères saisis ne doivent pas contenir de symboles non numériques");
        return NULL;
    }
    if(!preNo)
    {
        //qDebug()<<"Le préambule ne peut pas être 0";
        QMessageBox::information(0,"barcode","Le préambule ne peut pas être 0");
        return NULL;
    }
    //qDebug()<<"preNo:"<<preNo;
    C1+=preNo;
    //La méthode de codage A ou B du symbole de données de gauche est obtenue par le préambule, et la preCodeWayList correspond à 1-9
    QString preCodeWay = preCodeWayList.at(preNo-1);
    //Caractère de données gauche 6 bits
    for(int i=1;i<7;i++)
    {
        int index = code.mid(i,1).toInt(&ok);
        if(!ok)
        {
            //qDebug()<<"Les caractères saisis ne doivent pas contenir de symboles non numériques";
            QMessageBox::information(0,"barcode","Les caractères saisis ne doivent pas contenir de symboles non numériques");
            return NULL;
        }
        if(i%2)
        {
            C2+=index;
        }
        else
        {
            C1+=index;
        }
        //Ajouter l'encodage de caractères dans le mode d'encodage correspondant à la chaîne
        if(preCodeWay.at(i-1)=='A')
        {
            barCodes.append(codeAEAN13Value.at(index));
        }
        else if(preCodeWay.at(i-1)=='B')
        {
            barCodes.append(codeBEAN13Value.at(index));
        }
    }
    barCodes.append("01010");//délimiteur médian

    for(int j=7;j<12;j++)
    {
        int index = code.mid(j,1).toInt(&ok);
        if(!ok)
        {
            //qDebug()<<"Les caractères saisis ne doivent pas contenir de symboles non numériques";
            QMessageBox::information(0,"barcode","Les caractères saisis ne doivent pas contenir de symboles non numériques");
            return NULL;
        }
        if(j%2)
        {
            C2+=index;
        }
        else
        {
            C1+=index;
        }
        barCodes.append(codeCEAN13Value.at(index));
    }
    //qDebug()<<"C2:"<<C2<<"C1:"<<C1;
    CC=(C1+C2*3)%10;
    checkId=(10-CC)%10;
    qDebug()<<"checkId:"<<checkId;
    barCodes.append(codeCEAN13Value.at(checkId));//vérifier le code
    barCodes.append("101");
    barCodes.append("0000000");
    return barCodes;
}
void BarCode::initCode128B()
{
    /*******************************code128B*******************************/
    //Les multi-caractères sont généralement des caractères de contrôle, qui ne sont pas utilisés.
    char128BList<<"SP"<<"!"<<"\""<<"#"<<"$"<<"%"<<"&"<<"'"<<"("<<")"
            <<"*"<<"+"<<","<<"-"<<"."<<"/"<<"0"<<"1"<<"2"<<"3"
            <<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<":"<<";"<<"<"<<"="
            <<">"<<"?"<<"@"<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"
            <<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"<<"O"<<"P"<<"Q"
            <<"R"<<"S"<<"T"<<"U"<<"V"<<"W"<<"X"<<"Y"<<"Z"<<"["
            <<"\\"<<"]"<<"^"<<"_"<<"`"<<"a"<<"b"<<"c"<<"d"<<"e"
            <<"f"<<"g"<<"h"<<"i"<<"j"<<"k"<<"l"<<"m"<<"n"<<"o"
            <<"p"<<"q"<<"r"<<"s"<<"t"<<"u"<<"v"<<"w"<<"x"<<"y"
            <<"z"<<"{"<<"|"<<"}"<<"~"<<"DEL"<<"FNC3"<<"FNC2"<<"SHIFT"<<"CODEC"
            <<"FNC4"<<"CODEA"<<"FNC1"<<"StartA"<<"StartB"<<"StartC"<<"Stop";

    code128BValue<<"bbsbbssbbss"<<"bbssbbsbbss"<<"bbssbbssbbs"<<"bssbssbbsss"<<"bssbsssbbss"<<"bsssbssbbss"<<"bssbbssbsss"<<"bssbbsssbss"<<"bsssbbssbss"<<"bbssbssbsss"
            <<"bbssbsssbss"<<"bbsssbssbss"<<"bsbbssbbbss"<<"bssbbsbbbss"<<"bssbbssbbbs"<<"bsbbbssbbss"<<"bssbbbsbbss"<<"bssbbbssbbs"<<"bbssbbbssbs"<<"bbssbsbbbss"
            <<"bbssbssbbbs"<<"bbsbbbssbss"<<"bbssbbbsbss"<<"bbbsbbsbbbs"<<"bbbsbssbbss"<<"bbbssbsbbss"<<"bbbssbssbbs"<<"bbbsbbssbss"<<"bbbssbbsbss"<<"bbbssbbssbs"
            <<"bbsbbsbbsss"<<"bbsbbsssbbs"<<"bbsssbbsbbs"<<"bsbsssbbsss"<<"bsssbsbbsss"<<"bsssbsssbbs"<<"bsbbsssbsss"<<"bsssbbsbsss"<<"bsssbbsssbs"<<"bbsbsssbsss"
            <<"bbsssbsbsss"<<"bbsssbsssbs"<<"bsbbsbbbsss"<<"bsbbsssbbbs"<<"bsssbbsbbbs"<<"bsbbbsbbsss"<<"bsbbbsssbbs"<<"bsssbbbsbbs"<<"bbbsbbbsbbs"<<"bbsbsssbbbs"
            <<"bbsssbsbbbs"<<"bbsbbbsbsss"<<"bbsbbbsssbs"<<"bbsbbbsbbbs"<<"bbbsbsbbsss"<<"bbbsbsssbbs"<<"bbbsssbsbbs"<<"bbbsbbsbsss"<<"bbbsbbsssbs"<<"bbbsssbbsbs"
            <<"bbbsbbbbsbs"<<"bbssbssssbs"<<"bbbbsssbsbs"<<"bsbssbbssss"<<"bsbssssbbss"<<"bssbsbbssss"<<"bssbssssbbs"<<"bssssbsbbss"<<"bssssbssbbs"<<"bsbbssbssss"
            <<"bsbbssssbss"<<"bssbbsbssss"<<"bssbbssssbs"<<"bssssbbsbss"<<"bssssbbssbs"<<"bbssssbssbs"<<"bbssbsbssss"<<"bbbbsbbbsbs"<<"bbssssbsbss"<<"bsssbbbbsbs"
            <<"bsbssbbbbss"<<"bssbsbbbbss"<<"bssbssbbbbs"<<"bsbbbbssbss"<<"bssbbbbsbss"<<"bssbbbbssbs"<<"bbbbsbssbss"<<"bbbbssbsbss"<<"bbbbssbssbs"<<"bbsbbsbbbbs"
            <<"bbsbbbbsbbs"<<"bbbbsbbsbbs"<<"bsbsbbbbsss"<<"bsbsssbbbbs"<<"bsssbsbbbbs"<<"bsbbbbsbsss"<<"bsbbbbsssbs"<<"bbbbsbsbsss"<<"bbbbsbsssbs"<<"bsbbbsbbbbs"
            <<"bsbbbbsbbbs"<<"bbbsbsbbbbs"<<"bbbbsbsbbbs"<<"bbsbssssbss"<<"bbsbssbssss"<<"bbsbssbbbss"<<"bbsssbbbsbsbb";

}
void BarCode::initEAN13()
{
    /***********************************EAN13******************************/

    preCodeWayList<<"AAAAAA"<<"AABABB"<<"AABBAB"<<"ABAABB"<<"ABBAAB"<<"ABBBAA"<<"ABABAB"<<"ABABBA"<<"ABBABA";

    codeAEAN13Value<<"0001101"<<"0011001"<<"0010011"<<"0111101"<<"0100011"
                   <<"0110001"<<"0101111"<<"0111011"<<"0110111"<<"0001011";

    codeBEAN13Value<<"0100111"<<"0110011"<<"0011011"<<"0100001"<<"0011101"
                   <<"0111001"<<"0000101"<<"0010001"<<"0001001"<<"0010111";

    codeCEAN13Value<<"1110010"<<"1100110"<<"1101100"<<"1000010"<<"1011100"
                   <<"1001110"<<"1010000"<<"1000100"<<"1001000"<<"1110100";
}
