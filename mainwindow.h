#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fournisseurs.h"
#include<QCompleter>
#include<QDirModel>
#include "smtp.h"
#include <QMessageBox>
#include <QUrl>

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
    void on_ajouter_clicked();
     void on_supprimer_clicked();
     void on_modifier_clicked();
     void on_combo_box_modifier_activated(const QString &arg);
     void on_rechercheA_textChanged(const QString &arg1);
     void on_rechercheA_textEdited(const QString &arg1);
     void on_Tri_activated(const QString &arg1);
     void sendMail();



    // void on_sendemailButton_clicked();

    // void on_recipient_combo_activated(const QString &);

     void on_recipient_combo_activated(const QString &);

private:
    Ui::MainWindow *ui;
    Fournisseurs f;
     QCompleter *stringcompleter,*modelcompleter;

};
#endif // MAINWINDOW_H
