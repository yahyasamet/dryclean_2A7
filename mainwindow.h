#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "employe.h"
#include <QCompleter>

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

private:
    Ui::MainWindow *ui;
    employe emp;
    QCompleter *StringCompleter,*ModelCompleter;
};
#endif // MAINWINDOW_H
