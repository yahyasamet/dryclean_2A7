#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "equipements.h"
#include <QMainWindow>
#include<QCompleter>
#include<QDirModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Ajouter_equipement_clicked();

    void on_Modifier_equipement_clicked();

    void on_Supprimer_equipement_clicked();

    void on_Trier_equipement_activated(const QString &arg1);

    void on_Rechercher_equipement_textChanged(const QString &arg1);

    void on_chatbox_clicked();

    void on_combo_ref_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    equipements E;
    QCompleter *stringcompleter,*modelcompleter;

};
#endif // MAINWINDOW_H
