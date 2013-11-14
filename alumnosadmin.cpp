#include "alumnosadmin.h"
#include "ui_alumnosadmin.h"

AlumnosAdmin::AlumnosAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlumnosAdmin)
{
    ui->setupUi(this);


}

AlumnosAdmin::~AlumnosAdmin()
{
    delete ui;
}
