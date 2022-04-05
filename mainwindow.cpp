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
#include<QSound>
#include "finances.h"
using namespace QtCharts;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tabledepence->setModel(C.afficher());
    ui->tablerevenue->setModel(C.afficher2());
    ui->radioButton_f->setChecked(true);
    QStringList list,list2;
    Historique h;
    ui->historiquef->setText(h.load());
    list=cinlist();
    list2=matlist();
    ui->mat->addItems(list);
    ui->mat_3->addItems(list);
    ui->mat_2->addItems(list2);
    ui->mat_4->addItems(list2);
    QSqlQuery qry;
    qry.prepare("select ID_FINANCES from finances");
    qry.exec();
    while(qry.next()){
    ui->combo_finance->addItem(qry.value(0).toString());
    }
     QSqlQuery qry1;
    qry1.prepare("select * from finances");
    qry1.exec();
    QStringList completionlist;
    while(qry1.next()){
    completionlist <<qry1.value(0).toString() <<qry1.value(4).toString()<<qry1.value(5).toString()<<qry1.value(6).toString();
     }
     stringcompleter=new QCompleter(completionlist,this);
     stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
     ui->recherche_f->setCompleter(stringcompleter);
     C.excel_dynamique();
        setImCorp();
        setliq();
        setrev();
        setdep();
        setfisc();
        son =new QSound(":/son/son_QT/Simple_Beep2.wav");
}

MainWindow::~MainWindow()
{
    delete ui;
}
//************************debut crud************************

void MainWindow::on_ajouterf_clicked()
{

    son->play();
    QIntValidator v(0, 1000000, this);
    int pos = 0;
    QString ID_FINANCES=id_increment();
    int MONTANT_FINANCE=ui->montant_ajout_f->text().toInt();
    QString MATRICULE_FISC=ui->mat_2->currentText();
    QString ID_COMMANDE=ui->mat->currentText();
    int TYPE_TRANSACTION1;
    if (ui->radioButton_f->isChecked())
    TYPE_TRANSACTION1=0;
    else if (ui->radioButton_2_f->isChecked())
    TYPE_TRANSACTION1=1;
    QDate DATE_FINANCES=ui->date_ajout_f->date();
    QString PROVENANCE=ui->provenance_f->text();
    finances C( DATE_FINANCES, TYPE_TRANSACTION1, PROVENANCE, MONTANT_FINANCE, ID_FINANCES, MATRICULE_FISC, ID_COMMANDE);

    QString montantstring=ui->montant_ajout_f->text();

    if (PROVENANCE=="")
    {
        QMessageBox::information(this, "erreur d'ajout","entrer la provenance du produit");
    }

    else if (C.recherche_id(ID_FINANCES))
    {
        QMessageBox::information(this, "erreur d'ajout","id déjà existant =");
    }
    else if (C.DateValide(DATE_FINANCES))
    {
        QMessageBox::information(this, "erreur d'ajout","date doit être inferieur à la date actuelle");

    }
    else if (!(v.validate(montantstring,pos)))
    {
        QMessageBox::information(this, "erreur d'ajout","entrer que des numero dans le montant");
    }
    else if (montantstring==NULL)
    {
        QMessageBox::information(this, "erreur d'ajout","le montant ne doit pas être vide");
    }
    else
    {
    bool test=C.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");
    idout(ID_FINANCES.toInt());
    ui->tabledepence->setModel(C.afficher());
    ui->tablerevenue->setModel(C.afficher2());
    Historique h;
    h.save(ID_FINANCES,"Ajout");
    ui->historiquef->setText(h.load());
    QStringList list,list2;
    ui->mat->clear();
    ui->mat_2->clear();
    ui->mat_3->clear();
    ui->mat_4->clear();
    ui->combo_finance->clear();
    list=cinlist();
    list2=matlist();
    ui->mat->addItems(list);
    ui->mat_3->addItems(list);
    ui->mat_2->addItems(list2);
    ui->mat_4->addItems(list2);

    ui->montant_ajout_f->clear();
    ui->provenance_f->clear();
    ui->date_ajout_f->clear();
    QSqlQuery qry;
    qry.prepare("select ID_FINANCES from finances");
    qry.exec();
    while(qry.next()){
    ui->combo_finance->addItem(qry.value(0).toString());
    }
    C.excel_dynamique();
    // Put the focus back into the input box so they can type again:
   QSqlQuery qry1;
  qry1.prepare("select * from finances");
  qry1.exec();
  QStringList completionlist;
  while(qry1.next()){
  completionlist <<qry1.value(0).toString() <<qry1.value(4).toString()<<qry1.value(5).toString()<<qry1.value(6).toString();
   }
   stringcompleter=new QCompleter(completionlist,this);
   stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
   ui->recherche_f->setCompleter(stringcompleter);
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
    }
}
void MainWindow::on_supprimerf_clicked()
{
    son->play();
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
      Historique h;
      h.save(id,"supprimer");
      ui->historiquef->setText(h.load());
      QMessageBox::information(nullptr,"Suppression","operation supprimé");
      QStringList list,list2;
      ui->mat->clear();
      ui->mat_2->clear();
      ui->mat_3->clear();
      ui->mat_4->clear();
      ui->combo_finance->clear();
      list=cinlist();
      list2=matlist();
      ui->mat->addItems(list);
      ui->mat_3->addItems(list);
      ui->mat_2->addItems(list2);
      ui->mat_4->addItems(list2);
      QSqlQuery qry;
      qry.prepare("select ID_FINANCES from finances");
      qry.exec();
      while(qry.next()){
      ui->combo_finance->addItem(qry.value(0).toString());
      }      }
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
           QMessageBox::information(nullptr,"Suppression","operation modifié");
           QSqlQuery qry1;
          qry1.prepare("select * from finances");
          qry1.exec();
          QStringList completionlist;
          while(qry1.next()){
          completionlist <<qry1.value(0).toString() <<qry1.value(4).toString()<<qry1.value(5).toString()<<qry1.value(6).toString();
           }
           stringcompleter=new QCompleter(completionlist,this);
           stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
           ui->recherche_f->setCompleter(stringcompleter);
           QStringList list,list2;
           ui->mat->clear();
           ui->mat_2->clear();
           ui->mat_3->clear();
           ui->mat_4->clear();
           ui->combo_finance->clear();
           list=cinlist();
           list2=matlist();
           ui->mat->addItems(list);
           ui->mat_3->addItems(list);
           ui->mat_2->addItems(list2);
           ui->mat_4->addItems(list2);
           QSqlQuery qry;
           qry.prepare("select ID_FINANCES from finances");
           qry.exec();
           while(qry.next()){
           ui->combo_finance->addItem(qry.value(0).toString());
           }}
                 C.excel_dynamique();
             }
       }
}

void MainWindow::on_modifierf_clicked()
{
   /* QModelIndex index = ui->tabledepence->selectionModel()->currentIndex();
    QString id = index.data(Qt::DisplayRole).toString();
    QModelIndex index2 = ui->tablerevenue->selectionModel()->currentIndex();
        QString id2 = index2.data(Qt::DisplayRole).toString();*/
    son->play();
    QMessageBox msg;
    QIntValidator v(0, 10000, this);
    int pos = 0;

    QString id=ui->combo_finance->currentText();
    QString montantstring=ui->montant_2_f->text();
    QString PROVENANCE=ui->provenance_2_f->text();

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
    C.setDATE_FINANCES(ui->date_2_f->date());
    C.setPROVENANCE(ui->provenance_2_f->text());
    C.setMONTANT_FINANCE(ui->montant_2_f->text().toInt());
    C.setID_COMMANDE(ui->mat_3->currentText());
    C.setMATRICULE_FISC(ui->mat_4->currentText());
    if (ui->radioButton_3_f->isChecked())
     C.setTYPE_TRANSACTION(0);
    else if (ui->radioButton_4_f->isChecked())
     C.setTYPE_TRANSACTION(1);


    bool test=C.modifier(C.getID_FINANCES());
    if(test)
    {
        QSqlQuery qry1;
       qry1.prepare("select * from finances");
       qry1.exec();
       QStringList completionlist;
       while(qry1.next()){
       completionlist <<qry1.value(0).toString() <<qry1.value(4).toString()<<qry1.value(5).toString()<<qry1.value(6).toString();
        }
        stringcompleter=new QCompleter(completionlist,this);
        stringcompleter->setCaseSensitivity(Qt::CaseInsensitive);
        ui->recherche_f->setCompleter(stringcompleter);
        Historique h;
        h.save(id,"modifier");
        ui->historiquef->setText(h.load());
        msg.setText("modification avec succès");
        ui->tabledepence->setModel(C.afficher());
        ui->tablerevenue->setModel(C.afficher2());
        QStringList list,list2;
        ui->mat->clear();
        ui->mat_2->clear();
        ui->mat_3->clear();
        ui->mat_4->clear();
        ui->combo_finance->clear();
        list=cinlist();
        list2=matlist();
        ui->mat->addItems(list);
        ui->mat_3->addItems(list);
        ui->mat_2->addItems(list2);
        ui->mat_4->addItems(list2);
        QSqlQuery qry;
        qry.prepare("select ID_FINANCES from finances");
        qry.exec();
        while(qry.next()){
        ui->combo_finance->addItem(qry.value(0).toString());
        }
        C.excel_dynamique();
    }
    else
        msg.setText("echec de modification");

    msg.exec();
    }

}

void MainWindow::on_comboBox_trie_f_activated(int index)
{
    if(index==0)
    {
        ui->tabledepence->setModel(C.Trie(0,"DATE_FINANCES"));
    }
    else if (index==1)
    {
        ui->tabledepence->setModel(C.Trie(0,"DATE_FINANCES DESC"));
    }
    else if (index==2)
    {
        ui->tabledepence->setModel(C.Trie(0,"MONTANT_FINANCE"));
    }
    else if (index==3)
    {
        ui->tabledepence->setModel(C.Trie(0,"MONTANT_FINANCE DESC"));
    }

}

void MainWindow::on_comboBox_trie_f_2_activated(int index)
{
    if(index==0)
    {
        ui->tablerevenue->setModel(C.Trie(1,"DATE_FINANCES"));
    }
    else if (index==1)
    {
        ui->tablerevenue->setModel(C.Trie(1,"DATE_FINANCES DESC"));
    }
    else if (index==2)
    {
        ui->tablerevenue->setModel(C.Trie(1,"MONTANT_FINANCE"));
    }
    else if (index==3)
    {
        ui->tablerevenue->setModel(C.Trie(1,"MONTANT_FINANCE DESC"));
    }

}
//************************fin crud************************



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
    chart->setTitle(" gain: NB: "+ QString::number(tranche_montant2-tranche_montant1));
    chart->legend()->hide();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

    for(auto slice : series->slices())
        slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));

    chartView->resize(851,591);
    chartView->setParent(ui->horizontalFramestat);
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
    chart->setTitle("depenses");
    chart->legend()->hide();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

    for(auto slice : series->slices())
        slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));

    chartView->resize(851,591);
    chartView->setParent(ui->horizontalFramestat);
    chartView->show();
}
QStringList MainWindow::cinlist()
{
    QSqlQuery query;


    query.prepare("SELECT DISTINCT REF_CMD FROM finances f full join commandes c on c.REF_CMD = f.ID_COMMANDE where REF_CMD is not null");
   QStringList list;
   list.push_back(NULL);
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


    query.prepare("SELECT DISTINCT matricule_f FROM finances f full join fournisseur f2 on f.MATRICULE_FISC = f2.matricule_f where matricule_f is not null  "); //MATRICULE_FISC IS not NULL
   QStringList list;
    list.push_back(NULL);
      if(query.exec())
      {
          while( query.next() )
          {
              list.push_back(query.value(0).toString()) ;
          }
      }
      return list;
}


void MainWindow::on_combo_finance_activated(int index)
{
    QSqlQuery query;
    QString ID_FINANCES=ui->combo_finance->currentText() ;
   query.prepare("Select * from finances where ID_FINANCES=:ID_FINANCES" );
           query.bindValue(":ID_FINANCES",ID_FINANCES) ;
           query.exec();
    query.next() ;
   // E.recuperer_equipement(REFERENCE_EQUIPEMENT);
    ui->montant_2_f->setText(query.value(2).toString());
    ui->date_2_f->setDate(query.value(1).toDate());
    ui->provenance_2_f->setText(query.value(4).toString());
    int TYPE_TRANSACTION=query.value(3).toString().toInt();
    if(TYPE_TRANSACTION==0)
    ui->radioButton_3_f->setChecked("");
    else
    ui->radioButton_4_f->setChecked("");
   // ui->combo_cin_2->setCurrentIndex(query.value(5).toInt());
    ui->mat_3->setCurrentText(query.value(5).toString());
    ui->mat_4->setCurrentText(query.value(6).toString());

}

void MainWindow::on_mat_activated(int index)
{
    QSqlQuery query;
    QString REF_CMD=ui->mat->currentText() ;
   query.prepare("Select * from commandes where REF_CMD=:REF_CMD" );
           query.bindValue(":REF_CMD",REF_CMD) ;
           query.exec();
    query.next() ;
    ui->montant_ajout_f->setText(query.value(4).toString());
    ui->date_ajout_f->setDate(query.value(5).toDate());
    ui->provenance_f->setText(query.value(3).toString());

    ui->radioButton_2_f->setChecked("");

    ui->mat_2->setCurrentText("");

}

void MainWindow::on_mat_2_activated(int index)
{
    QSqlQuery query;
    QString MATRICULE_F=ui->mat_2->currentText() ;
   query.prepare("Select * from fournisseur where MATRICULE_F=:MATRICULE_F" );
           query.bindValue(":MATRICULE_F",MATRICULE_F) ;
           query.exec();
    query.next() ;
    ui->montant_ajout_f->setText(query.value(7).toString());
    ui->provenance_f->setText(query.value(1).toString());

    ui->radioButton_f->setChecked("");

    ui->mat->setCurrentText(NULL);

}

void MainWindow::on_recherche_f_textChanged(const QString &arg1)
{
    if (arg1 != NULL)
    ui->tabledepence->setModel(C.recherche_avancee(arg1));
    else
     ui->tabledepence->setModel(C.afficher());

}

void MainWindow::on_tabledepence_doubleClicked(const QModelIndex &index)
{
        QString id = index.data(Qt::DisplayRole).toString();
        bool test=C.supprimer(id);
        if(test)
        {
  ui->tabledepence->setModel(C.afficher());
        }
}

void MainWindow::on_tablerevenue_doubleClicked(const QModelIndex &index)
{
    QString id = index.data(Qt::DisplayRole).toString();
    bool test=C.supprimer(id);
    if(test)
    {
ui->tablerevenue->setModel(C.afficher2());
    }
}
//************************bilan financier************************
void MainWindow::setImCorp()
{
    QStringList list= { "terrain", "batiment(s)", "materiels informatique", "equipements", "divers","total" };
    ui->ImCorp->setRowCount(1);
    ui->ImCorp->setColumnCount(6);
    ui->ImCorp->setHorizontalHeaderLabels(list);
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (MATRICULE_FISC IS not NULL) ");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();
    QString s = QString::number(tranche_montant1);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(s);
    ui->ImCorp->setItem(0,3,item);
}
void MainWindow::setliq()
{
    QStringList list= { "caisse", "banque","total" };
    ui->liq->setRowCount(1);
    ui->liq->setColumnCount(3);
    ui->liq->setHorizontalHeaderLabels(list);
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (ID_COMMANDE IS not NULL) ");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();
    QString s = QString::number(tranche_montant1);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(s);
    ui->liq->setItem(0,0,item);
}
void MainWindow::setrev()
{
    QStringList list= { "caisse", "divers","total" };
    ui->rev->setRowCount(1);
    ui->rev->setColumnCount(3);
    ui->rev->setHorizontalHeaderLabels(list);

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQueryModel * model2= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (ID_COMMANDE IS not NULL) ");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();

    model2->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (TYPE_TRANSACTION = 1) AND (ID_COMMANDE IS NULL) AND (MATRICULE_FISC IS NULL) ");
    float tranche_montant2=model2->data(model2->index(0, 0)).toFloat();

    QString s = QString::number(tranche_montant1);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(s);
    ui->rev->setItem(0,0,item);

    QString s2 = QString::number(tranche_montant2);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(s2);
    ui->rev->setItem(0,1,item2);

    float sum=0;

    for (int i=0;i<2;i++)
    {
     const QAbstractItemModel *model = ui->rev->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s3 = QString::number(sum);
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText(s3);
     ui->rev->setItem(0,2,item3);
}
void MainWindow::setdep()
{
    QStringList list= { "achat", "divers","facture", "salaire","total" };
    ui->dep->setRowCount(1);
    ui->dep->setColumnCount(5);
    ui->dep->setHorizontalHeaderLabels(list);

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQueryModel * model2= new QSqlQueryModel();
    QSqlQueryModel * model3= new QSqlQueryModel();
    QSqlQueryModel * model4= new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (MATRICULE_FISC IS not NULL) ");
    float tranche_montant1=model->data(model->index(0, 0)).toFloat();

    model2->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (TYPE_TRANSACTION = 0) AND (ID_COMMANDE IS NULL) AND (MATRICULE_FISC IS NULL) AND (PROVENANCE not like 'facture')");
    float tranche_montant2=model2->data(model2->index(0, 0)).toFloat();

    model3->setQuery("SELECT SUM(MONTANT_FINANCE) AS prix_total FROM finances where (TYPE_TRANSACTION = 0) AND (PROVENANCE = 'facture')");
    float tranche_montant3=model3->data(model3->index(0, 0)).toFloat();

    model4->setQuery("SELECT SUM(salaire) AS salaire FROM finances T1 INNER JOIN commandes T2 ON T2.REF_CMD = T1.ID_COMMANDE INNER JOIN EMPLOYES T3 ON T3.cin = T2.CIN_EMPLOYE ");
    float tranche_montant4=(model4->data(model4->index(0, 0)).toFloat())*12;

    QString s = QString::number(tranche_montant1);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(s);
    ui->dep->setItem(0,0,item);

    QString s2 = QString::number(tranche_montant2);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(s2);
    ui->dep->setItem(0,1,item2);

    QString s3 = QString::number(tranche_montant3);
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText(s3);
    ui->dep->setItem(0,2,item3);

    QString s4 = QString::number(tranche_montant4);
    QTableWidgetItem *item4 = new QTableWidgetItem;
    item4->setText(s4);
    ui->dep->setItem(0,3,item4);

    float sum=0;

    for (int i=0;i<4;i++)
    {
     const QAbstractItemModel *model = ui->dep->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s5 = QString::number(sum);
    QTableWidgetItem *item5 = new QTableWidgetItem;
    item5->setText(s5);
     ui->dep->setItem(0,4,item5);
}
void MainWindow::setfisc()
{
    QStringList list= { "résultat Net Fiscal", "pourcentage impôt","impôt","résulat fiscal final" };
    ui->fisc->setRowCount(1);
    ui->fisc->setColumnCount(4);
    ui->fisc->setHorizontalHeaderLabels(list);

     QAbstractItemModel *model = ui->rev->model();
     QString revenue_string = model->data(model->index(0, 2), Qt::DisplayRole).toString();
     float revenue= revenue_string.toInt();

     QAbstractItemModel *model2 = ui->dep->model();
     QString depense_string = model2->data(model2->index(0, 4), Qt::DisplayRole).toString();
     float depense= depense_string.toInt();

     QString somme = QString::number(revenue-depense);
     QTableWidgetItem *item = new QTableWidgetItem;
     item->setText(somme);
      ui->fisc->setItem(0,0,item);

}
void MainWindow::on_calcultotal_clicked()
{
    float sum=0;

    for (int i=0;i<5;i++)
    {
     const QAbstractItemModel *model = ui->ImCorp->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s = QString::number(sum);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(s);
     ui->ImCorp->setItem(0,5,item2);

}

void MainWindow::on_calcultotal_2_clicked()
{
    float sum=0;

    for (int i=0;i<3;i++)
    {
     const QAbstractItemModel *model = ui->liq->model();
     const QString value = model->data(model->index(0,i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s = QString::number(sum);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(s);
     ui->liq->setItem(0,2,item2);
}

void MainWindow::on_calcultotal_3_clicked()
{
    float sum=0;

    for (int i=0;i<2;i++)
    {
     const QAbstractItemModel *model = ui->rev->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s3 = QString::number(sum);
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText(s3);
     ui->rev->setItem(0,2,item3);
}

void MainWindow::on_calcultotal_4_clicked()
{
    float sum=0;

    for (int i=0;i<5;i++)
    {
     const QAbstractItemModel *model = ui->dep->model();
     const QString value = model->data(model->index(0, i), Qt::DisplayRole).toString();
     sum += value.toInt();
    }

    QString s5 = QString::number(sum);
    QTableWidgetItem *item5 = new QTableWidgetItem;
    item5->setText(s5);
     ui->dep->setItem(0,4,item5);
}

/*void MainWindow::on_tabWidget_4_tabBarClicked(int index)
{
    setImCorp();
    setliq();
    setrev();
    setdep();
    setfisc();
}*/

void MainWindow::on_calcultotal_5_clicked()
{
    double impot=0;
    float resfinal=0;


      QAbstractItemModel *model = ui->fisc->model();
      QAbstractItemModel *model2 = ui->fisc->model();

      QString restring = model->data(model->index(0, 0), Qt::DisplayRole).toString();
      QString pourimpstring = model2->data(model2->index(0, 1), Qt::DisplayRole).toString();
       impot = (restring.toInt())*(pourimpstring.toInt()*0.01);
        QString impostring = QString::number(impot);
     resfinal = (restring.toInt())-(impot);
     QString resfinalstring = QString::number(resfinal);


    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(impostring);
     ui->fisc->setItem(0,2,item);

     QTableWidgetItem *item2 = new QTableWidgetItem;
     item2->setText(resfinalstring);
      ui->fisc->setItem(0,3,item2);


}

void MainWindow::on_excel_clicked()
{
    QTableView *table;


                        table = ui->ImCorp;
                   QString filters("CSV files (.csv);;All files (.*)");
                   QString defaultFilter("CSV files (*.csv)");
                   QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                      filters, &defaultFilter);
                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
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
                       ligne(fileName);
                       part2(fileName);
                       ligne(fileName);
                       part3(fileName);
                       ligne(fileName);
                       part4(fileName);
                       ligne(fileName);
                       part5(fileName);
                   }
}
void MainWindow::part2(QString fileName)
{
    QTableView *table;
                   table = ui->liq;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
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

                   }
}
void MainWindow::part3(QString fileName)
{
    QTableView *table;
                   table = ui->rev;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
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

                   }
}
void MainWindow::part5(QString fileName)
{
    QTableView *table;
                   table = ui->fisc;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
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

                   }
}
void MainWindow::part4(QString fileName)
{
    QTableView *table;
                   table = ui->dep;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
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

                   }
}

void MainWindow::ligne(QString fileName)
{
    QTableView *table;
                   table = ui->tableWidget;



                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();

                   if (file.open(QFile::WriteOnly | QFile::Append)) {
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

                   }
}

void MainWindow::on_tabWidget_2_f_tabBarClicked(int index)
{
    setImCorp();
    setliq();
    setrev();
    setdep();
    setfisc();
}
QString MainWindow::id_increment()
{
    QString tmp="";

    int i=0;
    QFile file("C:/Users/ramya/OneDrive/Bureau/dry cleaning/finance/id.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          tmp="";
    QTextStream in(&file);
    QString line;
    while(!file.atEnd()){
    line = file.readLine();
    i++;
    }
    file.close();
    QString is=QString::number(i);
    return is;
}
void MainWindow::idout (int i)
{
    QFile file ("C:/Users/ramya/OneDrive/Bureau/dry cleaning/finance/id.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << i << "\n";
}
