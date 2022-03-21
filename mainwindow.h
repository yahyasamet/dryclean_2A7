#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "livraisons.h"
#include <QMainWindow>
#include <QCompleter>
#include <QDirModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void webShow(const QString &url);
    int on_Calendrier_clicked();

private slots:

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





private:
    Ui::MainWindow *ui;
    livraisons C;
    QCompleter *stringcompleter,*modelcompleter;
};
#endif // MAINWINDOW_H
