#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "commande.h"
#include <QMainWindow>
#include <QCompleter>
#include <QDirModel>

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
private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();
    void on_comboBox_2_activated(int index);


private:
    Ui::MainWindow *ui;
    Commande Etmp;
    QCompleter * StringCompleter;
    QCompleter * ModelCompleter;
    QSystemTrayIcon * mSystemTrayIcon;
};
#endif // MAINWINDOW_H
