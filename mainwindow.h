#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "employe.h"
#include <QCompleter>
#include "fournisseurs.h"
#include "commande.h"
#include <QDirModel>
#include "barcodebox.h"
#include <QCompleter>
#include <QDirModel>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCompleter>
#include "historique.h"
#include "barcode.h"
#include <QSystemTrayIcon>
#include "finances.h"
#include<QSound>
#include "equipements.h"
#include "livraisons.h"
#include "secformdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStringList cinlist();
        QStringList matlist();
        void  setupSummaryTable();
        QString id_increment();
        void idout(int);
   QTimer *monTimer;
   void webShow(const QString &url);

public slots:

    void produceBarCode128Slot();//code 128
    void produceBarCodeEAN13Slot();//EAN 13
    void savePictureSlot();

private slots:
    void on_forgot_password_clicked();

    void on_login_clicked();

    void on_ajouter_employe_clicked();

    void on_supprimer_employe_clicked();

    void on_modifier_employe_clicked();

    void on_gestion_employes_clicked();

    void on_tri_emp_activated(int index);

    void on_recherche_employe_textChanged(const QString &arg1);

    void on_cin_employe_2_activated(const QString &arg1);

    void on_confirm_password_clicked();

    void on_change_password_clicked();

    void on_annuler_pass_clicked();

    void on_fournisseurs_2_clicked();

    void on_ajouter_f_clicked();
     void on_supprimer_f_clicked();
     void on_modifier_f_clicked();
     void on_rechercheA_f_textChanged(const QString &arg1);
     void on_rechercheA_f_textEdited(const QString &arg1);
     void on_Tri_f_activated(const QString &arg1);
     void sendMail();
     void on_recipient_combo_f_activated(const QString &);
     void on_combo_box_modifier_f_activated(const QString &arg1);


     void on_pb_ajouter_2_clicked();
     void on_pb_supprimer_2_clicked();
     void on_pb_modifier_2_clicked();
     void on_comboBox_3_activated(int index);

     void on_modifier_combo_2_activated(int index);

     void on_supprimer_combo_activated(int index);

     void on_recherche_2_textChanged(const QString &arg);

     void on_commandes_2_clicked();


     void on_ajouterf_clicked();
         void on_supprimerf_clicked();
         void on_modifierf_clicked();
         void on_comboBox_trie_f_activated(int index);
         void on_comboBox_trie_f_2_activated(int index);



         void on_Statistique_clicked();


         void on_Statistique_3_clicked();

         void on_combo_finance_activated(int index);

         void on_mat_activated(int index);

         void on_mat_2_activated(int index);

         void on_recherche_f_textChanged(const QString &arg1);
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

         void on_calcultotal_5_clicked();

         void on_excel_clicked();

         void on_tabWidget_2_f_tabBarClicked(int index);

         void on_Ajouter_equipement_clicked();

         void on_Modifier_equipement_clicked();

         void on_Supprimer_equipement_clicked();

         void on_Trier_equipement_activated(const QString &arg1);

         void on_Rechercher_equipement_textChanged(const QString &arg1);

         void on_chatbox_clicked();

         void on_combo_ref_activated(const QString &arg1);
         void finTempo();

         void on_facebook_clicked();

         void on_instagram_clicked();
         void on_livraisons_2_clicked();

         void on_equipements_2_clicked();

         void on_gestion_equipements_clicked();

         void on_gestion_fournisseurs_clicked();

         void on_gestion_commandes_clicked();

         void on_gestion_livraisons_clicked();

         void on_gestion_finances_clicked();

         void on_pushButton_2_clicked();
         void on_supprimer_clicked();
         void on_modifier_clicked();
         void on_comboBox_activated(const QString &arg1);
         void on_pushButton_5_clicked();
         void on_le_id_2_activated();
         void on_Rechercher_livraisons_textEdited(const QString &arg1);
         void on_Rechercher_livraisons_textChanged(const QString &arg1);

         void showAddrWeb();

         QString on_le_id_3_activated();

         void on_Calendrier_clicked();

         void on_goPushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    employe emp;
    QCompleter *StringCompleter,*ModelCompleter;
    Fournisseurs f;
    QCompleter *stringcompleter,*modelcompleter;

    Commande Etmp;
    QSystemTrayIcon * mSystemTrayIcon;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *produceCode128Button;
    QPushButton *produceEAN13Button;
    QPushButton *savePictureButton;
    BarCodeBox *barCodeBox;

    finances C;
    QStringList files;
    QSound *son;

    equipements E;
    QSound *success,*error;

    livraisons L;
    SECFORMDialog *secDialog;
};
#endif // MAINWINDOW_H
