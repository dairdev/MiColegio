#ifndef FRMVENTAS_H
#define FRMVENTAS_H

#include <QFrame>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QSqlError>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QPicture>
#include <QImage>
#include <QImageReader>
#include <QStaticText>

namespace Ui {
class FrmVentas;
}

class FrmVentas : public QFrame
{
    Q_OBJECT

public:
    explicit FrmVentas(QWidget *parent = 0);
    ~FrmVentas();

private slots:

    void on_btnNuevo_clicked();

    void on_btnGuardar_clicked();

    void on_txtDniAlumno_returnPressed();

    void on_txtDniAlumno_lostFocus();

    void on_btnBuscar_pressed();

    void on_btnAddDetalle_pressed();

    void on_cmbProducto_editTextChanged(const QString &arg1);

    void on_cmbProducto_currentIndexChanged(int index);    

    void on_txtCantidad_valueChanged(int arg1);

    void on_tbwVentas_doubleClicked(const QModelIndex &index);

    void on_btnImprimir_pressed();

    void on_btnBorrar_pressed();    

private:
    Ui::FrmVentas *ui;
    int alumnoId;
    int ventaId;
    QSqlTableModel *ventasModel;
    QSqlRelationalTableModel *detallesModel;
    QDataWidgetMapper *mapper;
    QDataWidgetMapper *mapperProductos;
    QSqlTableModel *productosModel;

    void buscarPorDni();
    void listarVentas();
    void calcularTotalItem();
    void listarDetalles();
};

#endif // FRMVENTAS_H
