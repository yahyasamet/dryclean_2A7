#ifndef CHAT_H
#define CHAT_H

#include <QDialog>

namespace Ui {
class chat;
}
class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    ~chat();
    QString hostname() const;
    quint16 port() const;

private slots:
    void on_accepter_button_clicked();

    void on_annuler_button_clicked();

private:
    Ui::chat *ui;
    QString mHostName;
    quint16 mPort;

};
inline  QString chat::hostname() const
   {
       return mHostName;
   }
inline  quint16 chat::port() const
   {
       return mPort;
   }


#endif // CHAT_H
