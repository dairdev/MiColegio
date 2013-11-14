#ifndef FRMPRODUCTOS_H
#define FRMPRODUCTOS_H

#include <QFrame>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

namespace Ui {
class frmproductos;
}

class frmproductos : public QFrame
{
    Q_OBJECT
    
public:
    explicit frmproductos(QWidget *parent = 0);
    ~frmproductos();
    
private slots:    

    void on_btnNuevo_pressed();       

private:
    Ui::frmproductos *ui;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
};

#endif // FRMPRODUCTOS_H
