#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>
#include <QSqlQuery>
#include <myapplication.h>

namespace Ui {
class DlgLogin;
}

class DlgLogin : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgLogin(QWidget *parent = 0);
    ~DlgLogin();
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_DlgLogin_rejected();

private:
    Ui::DlgLogin *ui;
};

#endif // DLGLOGIN_H
