#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "equipements.h"
#include <QMainWindow>
#include<QCompleter>
#include<QDirModel>
#include <QSound>
#include"arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *monTimer,*monTimer2;

private slots:
    void on_Ajouter_equipement_clicked();

    void on_Modifier_equipement_clicked();

    void on_Supprimer_equipement_clicked();

    void on_Trier_equipement_activated(const QString &arg1);

    void on_Rechercher_equipement_textChanged(const QString &arg1);

    void on_chatbox_clicked();

    void on_combo_ref_activated(const QString &arg1);
    void finTempo();
    void finTempo2();
    void on_facebook_clicked();

    void on_instagram_clicked();
    QString on_combo_ref_2_activated(const QString &arg1);

    void on_Demarrer_arduino_clicked();
    void update_label();
    void on_Eteindre_arduino_clicked();

private:
    Ui::MainWindow *ui;
    equipements E;
    QCompleter *stringcompleter,*modelcompleter;
    QSound *son,*success,*error;
    QByteArray data,dataa; // variable contenant les données reçues
    Arduino A; // objet temporaire
    //QString dataa;

};
#endif // MAINWINDOW_H
