#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>

namespace Ui {
class Producto;
}

class Producto : public QDialog
{
    Q_OBJECT
    
public:
    explicit Producto(QWidget *parent = 0);
    void setProductoModel(QSqlRelationalTableModel *model);    
    ~Producto();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::Producto *ui;
    QSqlRelationalTableModel *model;
//    QDataWidgetMapper *mapper;
    int productoIndex;
};

#endif // PRODUCTO_H
