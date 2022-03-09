#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "livraisons.h"
#include <QMainWindow>

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

    void on_pushButton_2_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    livraisons C;
};
#endif // MAINWINDOW_H
