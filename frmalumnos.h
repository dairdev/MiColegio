#ifndef FRMALUMNOS_H
#define FRMALUMNOS_H

#include <QFrame>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>
#include <frmalumno.h>

namespace Ui {
class FrmAlumnos;
}

class FrmAlumnos : public QFrame
{
    Q_OBJECT
    
public:
    explicit FrmAlumnos(QWidget *parent = 0);
    ~FrmAlumnos();
    
private:
    Ui::FrmAlumnos *ui;    
    QSqlRelationalTableModel *alumnosModel;
    QDataWidgetMapper *mapper;


private slots:    
    void on_btnNuevo_clicked();
    void on_btnBorrar_clicked();
};

#endif // FRMALUMNOS_H
