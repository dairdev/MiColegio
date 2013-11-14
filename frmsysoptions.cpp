#include "frmsysoptions.h"
#include "ui_frmsysoptions.h"
#include <QtDebug>

FrmSysOptions::FrmSysOptions(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::FrmSysOptions)
{
    ui->setupUi(this);    
    ui->listWidget->setCurrentRow(0);

    ui->tbwBancos->setAlternatingRowColors(true);
    ui->tbwCategorias->setAlternatingRowColors(true);
    ui->tbwMarcas->setAlternatingRowColors(true);
    ui->tbwTallas->setAlternatingRowColors(true);    

    ui->tbwBancos->setColumnWidth(1,300);
    ui->tbwCategorias->setColumnWidth(1,300);
    ui->tbwMarcas->setColumnWidth(1,300);
    ui->tbwTallas->setColumnWidth(1,300);

    modelBancos=new QSqlTableModel(ui->tbwBancos);
    ui->tbwBancos->setModel(modelBancos);
    modelBancos->setTable("banco");
    modelBancos->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelBancos->select();

    modelCategorias=new QSqlTableModel(ui->tbwCategorias);
    ui->tbwCategorias->setModel(modelCategorias);
    modelCategorias->setTable("categoria");
    modelCategorias->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelCategorias->select();

    modelMarcas=new QSqlTableModel(ui->tbwMarcas);
    ui->tbwMarcas->setModel(modelMarcas);
    modelMarcas->setTable("marca");
    modelMarcas->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelMarcas->select();

    modelTallas=new QSqlTableModel(ui->tbwTallas);
    ui->tbwTallas->setModel(modelTallas);
    modelTallas->setTable("talla");
    modelTallas->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelTallas->select();

    ui->tbwBancos->hideColumn(modelBancos->fieldIndex("id"));
    ui->tbwCategorias->hideColumn(modelCategorias->fieldIndex("id"));
    ui->tbwMarcas->hideColumn(modelMarcas->fieldIndex("id"));
    ui->tbwTallas->hideColumn(modelTallas->fieldIndex("id"));
}

FrmSysOptions::~FrmSysOptions()
{
    delete ui;
}

void FrmSysOptions::on_btnGuardar_pressed()
{
    QString name;
    switch(ui->stackedWidget->currentIndex()){
    case 0:
        name=ui->txtBancoNombre->text();
        break;
    case 1:
        name=ui->txtCategoriaNombre->text();
        break;
    case 2:
        name=ui->txtMarcaNombre->text();
        break;
    case 3:
        name=ui->txtTallaNombre->text();
        break;
    }

    if (!(name.isNull() && name.isEmpty())){
        switch(ui->stackedWidget->currentIndex()){
        case 0:
            modelBancos->insertRows(0,1);
            modelBancos->setData(modelBancos->index(0,1),name.trimmed());
            modelBancos->submitAll();
            modelBancos->select();
            break;
        case 1:
            modelCategorias->insertRows(0,1);
            modelCategorias->setData(modelCategorias->index(0,1),name.trimmed());
            modelCategorias->submitAll();
            modelCategorias->select();
            break;
        case 2:
            modelMarcas->insertRows(0,1);
            modelMarcas->setData(modelMarcas->index(0,1),name.trimmed());
            modelMarcas->submitAll();
            modelMarcas->select();
            break;
        case 3:
            modelTallas->insertRows(0,1);
            modelTallas->setData(modelTallas->index(0,1),name.trimmed());
            modelTallas->submitAll();
            modelTallas->select();
            break;
        }

    }
}

void FrmSysOptions::on_listWidget_currentRowChanged(int currentRow)
{
    ui->stackedWidget->setCurrentIndex(currentRow);
}
