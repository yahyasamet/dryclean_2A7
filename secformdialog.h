#ifndef SECFORMDIALOG_H
#define SECFORMDIALOG_H

#include <QDialog>

namespace Ui {
class SECFORMDialog;
}

class SECFORMDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SECFORMDialog(QWidget *parent = nullptr);
    ~SECFORMDialog();

private:
    Ui::SECFORMDialog *ui;
};

#endif // SECFORMDIALOG_H
