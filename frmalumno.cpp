#include "frmalumno.h"
#include "ui_frmalumno.h"

FrmAlumno::FrmAlumno(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmAlumno)
{
    ui->setupUi(this);

    model=new QSqlTableModel(this);
    model->setTable("alumno");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->alumnoIndex=-1;
}

FrmAlumno::~FrmAlumno()
{
    delete ui;
}

void FrmAlumno::on_buttonBox_accepted()
{
    QSqlDatabase db=QSqlDatabase::database();
    try {
        QSqlQuery query;
        query.prepare("INSERT INTO alumno(`nombre`,`paterno`,`materno`,`nacimiento`,`sexo`,`personal_id`,`creado_por`) "
                      "VALUES ( :nombre, :paterno, :materno, :nacimiento, :sexo, :personal_id, :creado_por)");
        query.bindValue(":nombre",ui->txtNombre->text());
        query.bindValue(":paterno",ui->txtPaterno->text());
        query.bindValue(":materno",ui->txtMaterno->text());
        query.bindValue(":nacimiento",ui->dtpAlumnoNacimiento->date());
        query.bindValue(":sexo",ui->cmbGenero->currentIndex());
        int userId = qApp->property("user").toInt();
        query.bindValue(":personal_id",userId);
        query.bindValue(":creado_por",userId);
        if(!query.exec()){
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                              query.lastError().text());
        }
    } catch (...) {
        qDebug()<<db.lastError().text();
    }
}
