#include "frmalumnos.h"
#include "ui_frmalumnos.h"
#include <QtSql>
#include <QMessageBox>
#include <QStringListModel>
#include <genderitemdelegate.h>
#include <gendercelldelegate.h>

FrmAlumnos::FrmAlumnos(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrmAlumnos)
{    

    ui->setupUi(this);

    alumnosModel = new QSqlRelationalTableModel(ui->tbwAlumnos);
    alumnosModel->setTable("alumno");
    alumnosModel->setFilter(" id > 1 ");
    alumnosModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    alumnosModel->setHeaderData(alumnosModel->fieldIndex("nombre"),Qt::Horizontal,tr("Nombres"));
    alumnosModel->setHeaderData(alumnosModel->fieldIndex("paterno"),Qt::Horizontal,tr("Paterno"));
    alumnosModel->setHeaderData(alumnosModel->fieldIndex("materno"),Qt::Horizontal,tr("Materno"));
    alumnosModel->setHeaderData(alumnosModel->fieldIndex("dni"),Qt::Horizontal,tr("Dni"));    
    alumnosModel->setHeaderData(alumnosModel->fieldIndex("nacimiento"),Qt::Horizontal,tr("Nacimiento"));
    alumnosModel->setHeaderData(alumnosModel->fieldIndex("creado_en"),Qt::Horizontal,tr("Fec. Creacion"));
    alumnosModel->setHeaderData(alumnosModel->fieldIndex("modificado_en"),Qt::Horizontal,tr("Fec. Modificac."));


    // Populate the model
    if (!alumnosModel->select()) {
        QMessageBox::critical(this, "Unable to initialize Database",
                              "Error initializing database: " + alumnosModel->lastError().text());
        return;
    }

    ui->tbwAlumnos->setModel(alumnosModel);
    ui->tbwAlumnos->setColumnHidden(alumnosModel->fieldIndex("id"), true);    
    ui->tbwAlumnos->setColumnHidden(alumnosModel->fieldIndex("aula_id"), true);
    ui->tbwAlumnos->setColumnHidden(alumnosModel->fieldIndex("es_activo"), true);
    ui->tbwAlumnos->setColumnHidden(alumnosModel->fieldIndex("estado"), true);    
    ui->tbwAlumnos->setColumnHidden(alumnosModel->fieldIndex("sexo"), true);
    ui->tbwAlumnos->setColumnHidden(alumnosModel->fieldIndex("creado_por"), true);
    ui->tbwAlumnos->setColumnHidden(alumnosModel->fieldIndex("modificado_por"), true);
    ui->tbwAlumnos->setColumnHidden(alumnosModel->fieldIndex("personal_id"), true);
    ui->tbwAlumnos->setColumnWidth(1, 100);
    ui->tbwAlumnos->setColumnWidth(2, 100);
    ui->tbwAlumnos->setColumnWidth(3, 100);
    ui->tbwAlumnos->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tbwAlumnos->setSelectionBehavior(QAbstractItemView::SelectRows);    
    ui->tbwAlumnos->setItemDelegate(new QSqlRelationalDelegate(ui->tbwAlumnos));    

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel(alumnosModel);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->setCurrentIndex(alumnosModel->fieldIndex("id"));    

    connect(ui->tbwAlumnos->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));    

}

FrmAlumnos::~FrmAlumnos()
{
    delete ui;
}


void FrmAlumnos::on_btnNuevo_clicked()
{
    FrmAlumno *dlg=new FrmAlumno(this);
    dlg->show();
    if (dlg->exec() == QDialog::Accepted){
        this->mapper->submit();
        alumnosModel->submit();
        alumnosModel->select();
    }
}

void FrmAlumnos::on_btnBorrar_clicked()
{
    int row = mapper->currentIndex();
    alumnosModel->removeRow(row);
    mapper->submit();
    mapper->setCurrentIndex(qMin(row, alumnosModel->rowCount() - 1));
}
