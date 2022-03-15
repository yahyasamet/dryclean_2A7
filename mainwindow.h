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

private slots:
    void on_ajouter_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();
    void on_comboBox_activated(int index);
    void on_comboBox_2_activated(int index);


    void on_excel_1_clicked();
    void on_Statistique_clicked();
    void on_excel_2_clicked();

    void on_Statistique_3_clicked();

    void on_combo_finance_activated(int index);

    void on_mat_activated(int index);

    void on_mat_2_activated(int index);

    void on_lineEdit_7_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    finances C;
    QStringList files;
    QCompleter *stringcompleter,*modelcompleter;

};

#endif // MAINWINDOW_H
