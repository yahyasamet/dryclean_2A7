#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QList>
#include <QtCharts>
#include <QChartView>
#include <QMainWindow>
#include "finances.h"

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

private:
    Ui::MainWindow *ui;
    finances C;
    QStringList files;

};

#endif // MAINWINDOW_H
