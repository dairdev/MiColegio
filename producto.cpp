#include "producto.h"
#include "ui_producto.h"

Producto::Producto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Producto)
{
    ui->setupUi(this);
    model=new QSqlRelationalTableModel(this);
    model->setTable("producto");
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    model->setRelation(model->fieldIndex("categoria_id"), QSqlRelation("categoria", "id", "nombre"));
    model->setRelation(model->fieldIndex("marca_id"), QSqlRelation("marca", "id", "nombre"));
    model->setRelation(model->fieldIndex("talla_id"), QSqlRelation("talla", "id", "nombre"));

    QSqlTableModel *mdlCategory=new QSqlTableModel(this);
    mdlCategory->setTable("categoria");
    ui->cmbCategoria->setModel(mdlCategory);
    ui->cmbCategoria->setModelColumn(mdlCategory->fieldIndex("nombre"));
    mdlCategory->select();


    QSqlTableModel *mdlTalla=new QSqlTableModel(this);
    mdlTalla->setTable("talla");
    ui->cmbTalla->setModel(mdlTalla);
    ui->cmbTalla->setModelColumn(mdlTalla->fieldIndex("nombre"));
    mdlTalla->select();

    QSqlTableModel *mdlMarca=new QSqlTableModel(this);
    mdlMarca->setTable("marca");
    ui->cmbMarca->setModel(mdlMarca);
    ui->cmbMarca->setModelColumn(mdlMarca->fieldIndex("nombre"));
    mdlMarca->select();

    this->productoIndex=-1;
}

Producto::~Producto()
{
    delete ui;
}

void Producto::on_buttonBox_accepted()
{
    if (ui->txtDescripcion->text().trimmed().length() > 0){

        try {
            QSqlDatabase db=QSqlDatabase::database();
            QSqlQuery query;

            query.prepare("INSERT INTO `producto`(`descripcion`,`precio`,`talla_id`,`categoria_id`,`marca_id`,`creado_por`)"
                          " VALUES( :descripcion, :precio, :talla_id, :categoria_id, :marca_id, :creado_por)");

            query.bindValue(":descripcion",ui->txtDescripcion->text());

            query.bindValue(":precio",ui->precio->text());

            query.bindValue(":talla_id",ui->cmbTalla->model()->data(ui->cmbTalla->model()->index(ui->cmbTalla->currentIndex(),0)).toInt());

            query.bindValue(":categoria_id",ui->cmbCategoria->model()->data(ui->cmbCategoria->model()->index(ui->cmbCategoria->currentIndex(),0)).toInt());

            query.bindValue(":marca_id",ui->cmbMarca->model()->data(ui->cmbMarca->model()->index(ui->cmbMarca->currentIndex(),0)).toInt());

            int userId = qApp->property("user").toInt();
            query.bindValue(":creado_por",userId);

            if(!query.exec()){
                QMessageBox::critical(0, QObject::tr("Database Error"),
                                      query.lastError().text());
            }
        } catch (...) {
            qDebug()<< "There is an error";
        }
    }else{
        QMessageBox::critical(0, QObject::tr("System"),
                              "Debe introducir la descripcion del producto");
    }
}


