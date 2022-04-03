#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QList>
#include <QtCharts>
#include <QChartView>
#include <QMainWindow>
#include<QCompleter>
#include<QDirModel>
#include "finances.h"
#include "historique.h"
#include <QKeyEvent>
#include <QSound>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStringList cinlist();
    QStringList matlist();
    void  setupSummaryTable();
    QString id_increment();
    void idout(int);


private slots:
    void on_ajouter_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();
    void on_comboBox_activated(int index);
    void on_comboBox_2_activated(int index);



    void on_Statistique_clicked();


    void on_Statistique_3_clicked();

    void on_combo_finance_activated(int index);

    void on_mat_activated(int index);

    void on_mat_2_activated(int index);

    void on_lineEdit_7_textChanged(const QString &arg1);
    void on_tabledepence_doubleClicked(const QModelIndex &index);

    void on_tablerevenue_doubleClicked(const QModelIndex &index);

    void setImCorp();
    void setliq();
    void setrev();
    void setdep();
    void setfisc();

     void part2(QString);
     void part3(QString);
     void part4(QString);
     void part5(QString);
     void ligne(QString);


    void on_calcultotal_clicked();

    void on_calcultotal_2_clicked();

    void on_calcultotal_3_clicked();

    void on_calcultotal_4_clicked();

  //  void on_tabWidget_4_tabBarClicked(int index);

    void on_calcultotal_5_clicked();

    void on_pushButton_11_clicked();

    void on_tabWidget_2_tabBarClicked(int index);


private:
    Ui::MainWindow *ui;
    finances C;
    QStringList files;
    QCompleter *stringcompleter,*modelcompleter;
    QSound *son;

};

#endif // MAINWINDOW_H
