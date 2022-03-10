#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QWidget"
#include <QMessageBox>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
#include <QTabWidget>
#include<QDebug>
#include<QFileDialog>
#include<QPdfWriter>
#include<QFile>
#include <QList>
#include<QStringList>
#include <iostream>
#include<QTextDocument>
#include<QUrl>
#include <QPixmap>
#include <QValidator>
#include <QIntValidator>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include "finances.h"
using namespace QtCharts;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tabledepence->setModel(C.afficher());
    ui->tablerevenue->setModel(C.afficher2());
    ui->radioButton->setChecked(true);
    QStringList list,list2;

    list=cinlist();
    list2=matlist();
    ui->mat->addItems(list);
    ui->mat_3->addItems(list);
    ui->mat_2->addItems(list2);
    ui->mat_4->addItems(list2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_ajouter_clicked()
{


    QIntValidator v(100, 900, this);
    int pos = 0;
    QString ID_FINANCES=ui->id->text();
    int MONTANT_FINANCE=ui->montant->text().toInt();
    QString MATRICULE_FISC=ui->mat_2->currentText();
    int ID_COMMANDE=ui->mat->currentText().toInt();
    int TYPE_TRANSACTION1;
    if (ui->radioButton->isChecked())
    TYPE_TRANSACTION1=0;
    else
    TYPE_TRANSACTION1=1;
    QDate DATE_FINANCES=ui->date->date();
    QString PROVENANCE=ui->provenance->text();
    finances C( DATE_FINANCES, TYPE_TRANSACTION1, PROVENANCE, MONTANT_FINANCE, ID_FINANCES, MATRICULE_FISC, ID_COMMANDE);
    QString idstring=ui->id->text();
    QString montantstring=ui->montant->text();

    if (PROVENANCE=="")
    {
        QMessageBox::information(this, "erreur d'ajout","entrer la provenance du produit");
    }
    else if (!(v.validate(idstring,pos)))
    {
        QMessageBox::information(this, "erreur d'ajout","entrer que des numero dans l'id");
    }
    else if (C.recherche_id(ID_FINANCES))
    {
        QMessageBox::information(this, "erreur d'ajout","id déjà existant =");
    }
    else if (!(v.validate(montantstring,pos)))
    {
        QMessageBox::information(this, "erreur d'ajout","entrer que des numero dans le montant");
    }
    else
    {
    bool test=C.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");
    ui->tabledepence->setModel(C.afficher());
    ui->tablerevenue->setModel(C.afficher2());
    QStringList list,list2;
    ui->mat->clear();
    ui->mat_2->clear();
    ui->mat_3->clear();
    ui->mat_4->clear();
    list=cinlist();
    list2=matlist();
    ui->mat->addItems(list);
    ui->mat_3->addItems(list);
    ui->mat_2->addItems(list2);
    ui->mat_4->addItems(list2);
    ui->id->clear();
    ui->montant->clear();
    ui->provenance->clear();
    ui->date->clear();
    // Put the focus back into the input box so they can type again:
   ui->id->setFocus();
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
    }
}
void MainWindow::on_supprimer_clicked()
{
    QModelIndex index = ui->tabledepence->selectionModel()->currentIndex();
        QString id = index.data(Qt::DisplayRole).toString();
        QModelIndex index2 = ui->tablerevenue->selectionModel()->currentIndex();
            QString id2 = index2.data(Qt::DisplayRole).toString();
       if (id!="")
       {
      QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Supprimer", "Etes vous sur de supprimer",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            bool test=C.supprimer(id);
            if(test)
            {
      ui->tabledepence->setModel(C.afficher());
      QMessageBox::information(nullptr,"Suppression","Chambre supprimé");
      QStringList list,list2;
      ui->mat->clear();
      ui->mat_2->clear();
      ui->mat_3->clear();
      ui->mat_4->clear();
      list=cinlist();
      list2=matlist();
      ui->mat->addItems(list);
      ui->mat_3->addItems(list);
      ui->mat_2->addItems(list2);
      ui->mat_4->addItems(list2);}
        }
       }
       else if (id2!="")
       {
           QMessageBox::StandardButton reply;
             reply = QMessageBox::question(this, "Supprimer", "Etes vous sur de supprimer",
                                           QMessageBox::Yes|QMessageBox::No);
             if (reply == QMessageBox::Yes) {
                 bool test=C.supprimer(id2);
                 if(test)
                 {
           ui->tablerevenue->setModel(C.afficher2());
           QMessageBox::information(nullptr,"Suppression","Chambre supprimé");
           QStringList list,list2;
           ui->mat->clear();
           ui->mat_2->clear();
           ui->mat_3->clear();
           ui->mat_4->clear();
           list=cinlist();
           list2=matlist();
           ui->mat->addItems(list);
           ui->mat_3->addItems(list);
           ui->mat_2->addItems(list2);
           ui->mat_4->addItems(list2);}
             }
       }
}

void MainWindow::on_modifier_clicked()
{
    QModelIndex index = ui->tabledepence->selectionModel()->currentIndex();
    QString id = index.data(Qt::DisplayRole).toString();
    QModelIndex index2 = ui->tablerevenue->selectionModel()->currentIndex();
        QString id2 = index2.data(Qt::DisplayRole).toString();
        if(id!="")
        {
    QMessageBox msg;
    QIntValidator v(100, 900, this);
    int pos = 0;
    QString montantstring=ui->montant_2->text();
    QString PROVENANCE=ui->provenance_2->text();

    if (PROVENANCE=="")
    {
        QMessageBox::information(this, "erreur d'ajout","entrer la provenance du produit");
    }
    else if (!(v.validate(montantstring,pos)))
    {
        QMessageBox::information(this, "erreur d'ajout","entrer que des numero dans le montant");
    }
    else
    {

    finances C;
    C.setID_FINANCES(id);
    C.setDATE_FINANCES(ui->date_2->date());
    C.setPROVENANCE(ui->provenance_2->text());
    C.setMONTANT_FINANCE(ui->montant_2->text().toInt());
    C.setID_COMMANDE(ui->mat_3->currentText().toInt());
    C.setMATRICULE_FISC(ui->mat_4->currentText());
    if (ui->radioButton->isChecked())
     C.setTYPE_TRANSACTION(0);
    else
     C.setTYPE_TRANSACTION(1);


    bool test=C.modifier(C.getID_FINANCES());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->tabledepence->setModel(C.afficher());
        ui->tablerevenue->setModel(C.afficher2());
        QStringList list,list2;
        ui->mat->clear();
        ui->mat_2->clear();
        ui->mat_3->clear();
        ui->mat_4->clear();
        list=cinlist();
        list2=matlist();
        ui->mat->addItems(list);
        ui->mat_3->addItems(list);
        ui->mat_2->addItems(list2);
        ui->mat_4->addItems(list2);

    }
    else
        msg.setText("echec de modification");

    msg.exec();
    }
        }
        else if (id2!="")
        {
            QMessageBox msg;
            QIntValidator v(100, 900, this);
            int pos = 0;
            QString montantstring=ui->montant_2->text();
            QString PROVENANCE=ui->provenance_2->text();

            if (PROVENANCE=="")
            {
                QMessageBox::information(this, "erreur d'ajout","entrer la provenance du produit");
            }
            else if (!(v.validate(montantstring,pos)))
            {
                QMessageBox::information(this, "erreur d'ajout","entrer que des numero dans le montant");
            }
            else
            {

            finances C;
            C.setID_FINANCES(id);
            C.setDATE_FINANCES(ui->date_2->date());
            C.setPROVENANCE(ui->provenance_2->text());
            C.setMONTANT_FINANCE(ui->montant_2->text().toInt());
            C.setID_COMMANDE(ui->mat_3->currentText().toInt());
            C.setMATRICULE_FISC(ui->mat_4->currentText());
            if (ui->radioButton->isChecked())
             C.setTYPE_TRANSACTION(0);
            else
             C.setTYPE_TRANSACTION(1);


            bool test=C.modifier(C.getID_FINANCES());
            if(test)
            {
                msg.setText("modification avec succès");
                ui->tabledepence->setModel(C.afficher());
                ui->tablerevenue->setModel(C.afficher2());
                QStringList list,list2;
                ui->mat->clear();
                ui->mat_2->clear();
                ui->mat_3->clear();
                ui->mat_4->clear();
                list=cinlist();
                list2=matlist();
                ui->mat->addItems(list);
                ui->mat_3->addItems(list);
                ui->mat_2->addItems(list2);
                ui->mat_4->addItems(list2);

            }
            else
                msg.setText("echec de modification");

            msg.exec();
            }
        }
}

void MainWindow::on_comboBox_activated(int index)
{
    if(index==0)
    {
        ui->tabledepence->setModel(C.Trie_dateD());
    }
    else if (index==1)
    {
        ui->tabledepence->setModel(C.Trie_dateC());
    }
    else if (index==2)
    {
        ui->tabledepence->setModel(C.Trie_montantD());
    }
    else if (index==3)
    {
        ui->tabledepence->setModel(C.Trie_montantC());
    }

}

void MainWindow::on_comboBox_2_activated(int index)
{
    if(index==0)
    {
        ui->tablerevenue->setModel(C.Trie_dateD2());
    }
    else if (index==1)
    {
        ui->tablerevenue->setModel(C.Trie_dateC2());
    }
    else if (index==2)
    {
        ui->tablerevenue->setModel(C.Trie_montantD2());
    }
    else if (index==3)
    {
        ui->tablerevenue->setModel(C.Trie_montantC2());
    }

}
void MainWindow::on_excel_1_clicked()
{
    QTableView *table;
                   table = ui->tabledepence;

                   QString filters("CSV files (.csv);;All files (.*)");
                   QString defaultFilter("CSV files (*.csv)");
                   QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                      filters, &defaultFilter);
                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();
                   if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }
                       file.close();
                       QMessageBox::information(nullptr, QObject::tr("export excel"),
                                                 QObject::tr("export avec succes .\n"
                                                             "Click OK to exit."), QMessageBox::Ok);
                   }
}


void MainWindow::on_excel_2_clicked()
{
    QTableView *table;
                   table = ui->tabledepence;

                   QString filters("CSV files (.csv);;All files (.*)");
                   QString defaultFilter("CSV files (*.csv)");
                   QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                      filters, &defaultFilter);
                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();
                   if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }
                       file.close();
                       QMessageBox::information(nullptr, QObject::tr("export excel"),
                                                 QObject::tr("export avec succes .\n"
                                                             "Click OK to exit."), QMessageBox::Ok);
                   }
}

void MainWindow::on_Statistique_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances WHERE TYPE_TRANSACTION = 0");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();

    model->setQuery("SELECT SUM(MONTANT_FINANCE) FROM finances WHERE TYPE_TRANSACTION = 1");
    float tranche_montant2=model->data(model->index(0, 0)).toFloat();



    float total=tranche_montant1+tranche_montant2;
    QString a=QString("depenses . "+QString::number((tranche_montant1*100)/total,'f',2)+"%" );
    QString b=QString("revenues .  "+QString::number((tranche_montant2*100)/total,'f',2)+"%" );


    QPieSeries *series = new QPieSeries();
    series->append(a,tranche_montant1);
    series->append(b,tranche_montant2);
    if (tranche_montant1!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( tranche_montant2!=0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(" gain: NB: "+ QString::number(tranche_montant1-tranche_montant2));
    chart->legend()->hide();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

    for(auto slice : series->slices())
        slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));

    chartView->resize(851,591);
    chartView->setParent(ui->horizontalFrame);
    chartView->show();


}

void MainWindow::on_Statistique_3_clicked()
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM finances where TYPE_TRANSACTION = 0 ");
    QPieSeries *series = new QPieSeries();
    if(qry.exec())
    {
        while(qry.next())
        {
            series->append(qry.value(0).toString(),qry.value(2).toInt());
        }
    }

   QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("depenses:");
    chart->legend()->hide();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

    for(auto slice : series->slices())
        slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));

    chartView->resize(400,400);
    chartView->setParent(ui->horizontalFrame);
    chartView->show();
}
QStringList MainWindow::cinlist()
{
    QSqlQuery query;


    query.prepare("SELECT REF_CMD FROM commandes");
   QStringList list;

      if(query.exec())
      {
          while( query.next() )
          {
              list.push_back(query.value(0).toString()) ;
          }
      }
      return list;
}
QStringList MainWindow::matlist()
{
    QSqlQuery query;


    query.prepare("SELECT matricule_f FROM fournisseur");
   QStringList list;

      if(query.exec())
      {
          while( query.next() )
          {
              list.push_back(query.value(0).toString()) ;
          }
      }
      return list;
}

