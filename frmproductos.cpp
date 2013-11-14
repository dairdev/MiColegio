#include "frmproductos.h"
#include "ui_frmproductos.h"
#include "producto.h"
#include <QtSql>
#include <QMessageBox>

frmproductos::frmproductos(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::frmproductos)
{
    ui->setupUi(this);    
    model=new QSqlRelationalTableModel(this);
    model->setTable("producto");
    model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);

    model->setRelation(model->fieldIndex("categoria_id"), QSqlRelation("categoria", "id", "nombre"));
    model->setRelation(model->fieldIndex("marca_id"), QSqlRelation("marca", "id", "nombre"));
    model->setRelation(model->fieldIndex("talla_id"), QSqlRelation("talla", "id", "nombre"));

    model->setHeaderData(model->fieldIndex("nombre"), Qt::Horizontal, tr("Nombre"));
    model->setHeaderData(model->fieldIndex("precio"), Qt::Horizontal, tr("Precio"));
    model->setHeaderData(model->fieldIndex("genero"), Qt::Horizontal, tr("Genero"));
    model->setHeaderData(model->fieldIndex("categoria_id"), Qt::Horizontal, tr("Categoria"));
    model->setHeaderData(model->fieldIndex("marca_id"), Qt::Horizontal, tr("Marca"));
    model->setHeaderData(model->fieldIndex("talla_id"), Qt::Horizontal, tr("Talla"));    

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(model->fieldIndex("id"));
    ui->tableView->hideColumn(model->fieldIndex("producto_id"));
    ui->tableView->setColumnWidth(1,300);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    mapper=new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setCurrentIndex(model->fieldIndex("id"));
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);    
    mapper->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    mapper->toFirst();
    model->select();

    connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

}

frmproductos::~frmproductos()
{
    delete ui;
}

void frmproductos::on_btnNuevo_pressed()
{    
    Producto *dlg=new Producto(this);    
    dlg->show();    
    if (dlg->exec() == QDialog::Accepted){
        this->mapper->submit();
        model->submit();       
        model->select();
    }
}
