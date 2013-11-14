#include "dlglogin.h"
#include "ui_dlglogin.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QSqlError>
#include <QStatusBar>
#include <QDebug>
#include <mainwindow.h>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QLabel>

DlgLogin::DlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLogin)
{
    ui->setupUi(this);
}


DlgLogin::~DlgLogin()
{
    delete ui;
}

void DlgLogin::on_buttonBox_accepted()
{
    try {

            QByteArray byteArray = ui->txtPassword->text().toUtf8();
            const char* cString = byteArray.constData();
            QString pwd=QString(QCryptographicHash::hash(cString, QCryptographicHash::Md5).toHex());
            QSqlTableModel personal;
            personal.setTable("personal");
            QString filter=QString("login='%1' and pwd='%2'").arg(ui->txtUsuario->text().trimmed()).arg(pwd);
            personal.setFilter(filter);
            personal.select();
            if(personal.rowCount()>0){
                MainWindow* w=(MainWindow *) this->parent();
                w->statusBar()->showMessage(tr("Ready"));
                QSqlRecord record=personal.record(0);
                QString userName= QString("%1 %2").arg(record.value("nombre").toString()).arg(record.value("paterno").toString());
                w->setUserName(userName.toUpper());
                qApp->setProperty("user",record.value("id"));
                qApp->setProperty("profile",record.value("perfil_id"));
//                qDebug()<< qApp->property("profile");
            }else{
                ui->lblStateLogin->setText("Usuario o Contraseña errada");
                this->setVisible(true);
            }
    } catch (...) {
        QMessageBox::information(this, "info", "We are in throwExcept()",
                                 QMessageBox::Ok);
    }

}

void DlgLogin::on_buttonBox_rejected()
{
    qDebug() << "Quit app";
    qApp->quit();
}

void DlgLogin::on_DlgLogin_rejected()
{    
    qApp->quit();
}
