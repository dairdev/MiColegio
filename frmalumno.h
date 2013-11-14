#ifndef FRMALUMNO_H
#define FRMALUMNO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QDateTime>
#include <QSqlQuery>
#include <myapplication.h>

namespace Ui {
class FrmAlumno;
}

class FrmAlumno : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmAlumno(QWidget *parent = 0);
    ~FrmAlumno();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::FrmAlumno *ui;
    QSqlTableModel *model;
    int alumnoIndex;
};

#endif // FRMALUMNO_H
