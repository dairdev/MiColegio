#include "frmcompras.h"
#include "ui_frmcompras.h"

FrmCompras::FrmCompras(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrmCompras)
{
    ui->setupUi(this);
}

FrmCompras::~FrmCompras()
{
    delete ui;
}
