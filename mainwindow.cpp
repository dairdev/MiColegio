#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frmalumnos.h"
#include "frmproductos.h"
#include "frmsysoptions.h"
#include "frmventas.h"
#include "frmcompras.h"
#include "dlglogin.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QLocale::setDefault(QLocale(QLocale::Spanish, QLocale::Peru));
    ui->setupUi(this);
    QPixmap userIcon(tr(":/images/maintoolbar/user.png"));
    QLabel *lblUserIcon= new QLabel();
    lblUserIcon->setPixmap(userIcon);
    this->lblUsuario= new QLabel(tr("Usuario"));
    qDebug() << lblUsuario->winId();
    QWidget *userArea = new QWidget(this);
    QHBoxLayout *userAreaLayout = new QHBoxLayout(this);
    userAreaLayout->addWidget(lblUserIcon);
    userAreaLayout->addWidget(lblUsuario);
    userArea->setLayout(userAreaLayout);
    userArea->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);
    ui->toolBarUser->addWidget(userArea);
    this->addToolBar(Qt::TopToolBarArea, ui->toolBarUser);
    this->addToolBar(Qt::LeftToolBarArea, ui->toolBar);

    DlgLogin *loginDialog=new DlgLogin(this);
    loginDialog->show();
}

void MainWindow::setUserName(QString user)
{
    this->lblUsuario->setText(user);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAlumnos_triggered()
{
    FrmAlumnos* frmAlumnos=new FrmAlumnos();    
    ui->mdiArea->addSubWindow(frmAlumnos);
    frmAlumnos->show();
}

void MainWindow::on_actionProductos_triggered()
{
    //QList<QMdiSubWindow *> lista= ui->mdiArea->subWindowList(QMdiArea::CreationOrder);
    bool canAdd = TRUE;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()){
        if (window->windowTitle()=="Productos"){
            canAdd=FALSE;
        }
    }
    if (canAdd==TRUE){
        frmproductos* frm=new frmproductos();
        ui->mdiArea->addSubWindow(frm);
        frm->show();
    }
}

void MainWindow::on_actionSistema_triggered()
{
    FrmSysOptions *frm=new FrmSysOptions();
    ui->mdiArea->addSubWindow(frm);
    frm->show();
}

void MainWindow::on_actionVentas_triggered()
{
    bool canAdd = TRUE;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()){
        if (window->windowTitle()=="Ventas"){
            canAdd=FALSE;
        }
    }
    if (canAdd==TRUE){
        FrmVentas *frm=new FrmVentas();
        ui->mdiArea->addSubWindow(frm);
        frm->show();
    }
}

void MainWindow::on_actionCompras_triggered()
{
    bool canAdd = TRUE;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()){
        if (window->windowTitle()=="Compras"){
            canAdd=FALSE;
        }
    }
    if (canAdd==TRUE){
        FrmCompras *frm=new FrmCompras();
        ui->mdiArea->addSubWindow(frm);
        frm->show();
    }
}
