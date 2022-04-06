#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "commande.h"
#include <QMainWindow>
#include <QCompleter>
#include <QDirModel>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCompleter>
#include "barcodebox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSystemTrayIcon;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

bool genererFacture(QString ref,QString cinS,QString qtt,QString Date,QString mt,QString type,QString livr,QString cin_e,QString nom);

public slots:
    void produceBarCode128Slot();//code 128
    void produceBarCodeEAN13Slot();//EAN 13
    void savePictureSlot();

private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();
    void on_comboBox_2_activated(int index);


    //void on_recuperer_clicked();

    void on_modifier_combo_activated(int index);

   // void on_supprimer_combo_activated(int index);


    void on_recherche_textChanged(const QString &arg);

private:
    Ui::MainWindow *ui;
    Commande Etmp;
    QCompleter * StringCompleter;
    QCompleter * ModelCompleter;
    QSystemTrayIcon * mSystemTrayIcon;
    QLabel *label;
//QPrinter Facture;
    QPushButton *produceCode128Button;
    //QPushButton *produceEAN13Button;
    QPushButton *savePictureButton;
    //QComboBox *cin;
    BarCodeBox *barCodeBox;

};
#endif // MAINWINDOW_H
