#include "frmcategoria.h"
#include "ui_frmcategoria.h"

FrmCategoria::FrmCategoria(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmCategoria)
{
    ui->setupUi(this);
}

FrmCategoria::~FrmCategoria()
{
    delete ui;
}
