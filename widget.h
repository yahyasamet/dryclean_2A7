#ifndef WIDGET_H
#define WIDGET_H
#include <QTcpSocket>
#include <QDialog>

namespace Ui {
class widget;
}

class widget : public QDialog
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();
    QString load();
    QString get_temps();
private slots:
    void on_pushButton_clicked();

    void on_connecter_clicked();

    void on_connecter_2_clicked();


private:
    Ui::widget *ui;
    QTcpSocket *mSocket;
    QString tmp;
};

#endif // WIDGET_H
