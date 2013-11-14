#include "frmventas.h"
#include "ui_frmventas.h"



FrmVentas::FrmVentas(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrmVentas)
{
    ui->setupUi(this);
    alumnoId=1;
    ui->tabWidget->setCurrentIndex(0);
    ui->filterDesde->setDate(QDate::currentDate());
    ui->filterHasta->setDate(QDate::currentDate());
    ui->btnAddDetalle->setEnabled(FALSE);
    ui->tabDetalles->setEnabled(FALSE);
    ui->txtTotal->setText("0.0");

    this->listarVentas();
    productosModel = new QSqlTableModel(ui->cmbProducto);
    productosModel->setTable("producto");
    ui->cmbProducto->setModel(this->productosModel);
    ui->cmbProducto->setModelColumn(productosModel->fieldIndex("descripcion"));
    if(!productosModel->select()){
        QMessageBox::critical(0,QObject::tr("Database Error"), productosModel->lastError().text());
    }

    mapperProductos=new QDataWidgetMapper(ui->cmbProducto);
    mapperProductos->setModel(productosModel);
    mapperProductos->addMapping(ui->txtPunitario, productosModel->fieldIndex("precio"));
    mapperProductos->toFirst();

    this->alumnoId = 0;
    this->ventaId = 0;

    this->calcularTotalItem();
}

FrmVentas::~FrmVentas()
{
    delete ui;
}

void FrmVentas::listarVentas(){
    ventasModel=new QSqlTableModel(ui->tbwVentas);
    ventasModel->setTable("venta");

    QString filters=QString("emision >= '%1' and emision <=  '%2'").arg(ui->filterDesde->date().toString("yyyy-MM-dd")).arg(ui->filterHasta->date().toString("yyyy-MM-dd"));

    if(!ui->filterCliente->text().trimmed().isEmpty()){
        filters.append(" and cliente like '%" + ui->filterCliente->text().trimmed() + "%' ");
    }

    ventasModel->setFilter(filters);

    ventasModel->setHeaderData(ventasModel->fieldIndex("emision"),Qt::Horizontal,tr("Emision"));
    ventasModel->setHeaderData(ventasModel->fieldIndex("cliente"),Qt::Horizontal,tr("Cliente"));
    ventasModel->setHeaderData(ventasModel->fieldIndex("monto"),Qt::Horizontal,tr("Total"));
    ventasModel->setHeaderData(ventasModel->fieldIndex("monto_cancelado"),Qt::Horizontal,tr("Pago"));
    ventasModel->setHeaderData(ventasModel->fieldIndex("descuento"),Qt::Horizontal,tr("Dcto."));

    if(!ventasModel->select()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              ventasModel->lastError().text());
    }

    ui->tbwVentas->setModel(ventasModel);
    ui->tbwVentas->setColumnHidden(ventasModel->fieldIndex("id"), true);
    ui->tbwVentas->setColumnHidden(ventasModel->fieldIndex("alumno_id"), true);
    ui->tbwVentas->setColumnHidden(ventasModel->fieldIndex("es_activo"), true);
    ui->tbwVentas->setColumnHidden(ventasModel->fieldIndex("estado"), true);
    ui->tbwVentas->setColumnHidden(ventasModel->fieldIndex("creado_por"), true);
    ui->tbwVentas->setColumnHidden(ventasModel->fieldIndex("modificado_por"), true);
    ui->tbwVentas->setColumnHidden(ventasModel->fieldIndex("personal_id"), true);
    ui->tbwVentas->setColumnWidth(1, 110);
    ui->tbwVentas->setColumnWidth(2, 100);
    ui->tbwVentas->setColumnWidth(3, 300);
    ui->tbwVentas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tbwVentas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbwVentas->setItemDelegate(new QSqlRelationalDelegate(ui->tbwVentas));

    mapper = new QDataWidgetMapper(this);
    //mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel(ventasModel);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->setCurrentIndex(ventasModel->fieldIndex("id"));

    connect(ui->tbwVentas->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));
}

void FrmVentas::on_btnNuevo_clicked()
{
    //Go to Tab Venta
    this->ui->tabWidget->setCurrentIndex(1);
    ui->dteEmision->setDate(QDate::currentDate());
    this->ventaId=0;
    this->alumnoId=0;
    ui->tbwDetallesVenta->model()->removeRows(0, ui->tbwDetallesVenta->model()->rowCount());
    ui->tabDetalles->setEnabled(TRUE);    
}

void FrmVentas::on_btnGuardar_clicked()
{
    //Validar los campos fecha y cliente y que tenga como minimo un item
    if (!ui->txtCliente->text().trimmed().isEmpty()){
        const int userId = qApp->property("user").toInt();
        QSqlQuery queryVenta;
        if (ui->tabWidget->currentIndex()==0){
            queryVenta.prepare("INSERT INTO `micolegio`.`venta`(`emision`,`monto`,`estado`,`cliente`,`monto_cancelado`,`descuento`,"
                               "`alumno_id`, `creado_por`,`personal_id`)"
                               " VALUES ( :emision, :monto, :estado, :cliente, :monto_cancelado, :descuento, :alumno_id, :creado_por, :personal_id ) ");

            queryVenta.bindValue(":creado_por",userId);
            queryVenta.bindValue(":personal_id", userId);

        }else{
            queryVenta.prepare("UPDATE `micolegio`.`venta` SET emision= :emision, monto= :monto, estado= :estado, cliente= :cliente, monto_cancelado= :monto_cancelado, "
                               "descuento= :descuento, alumno_id= :alumno_id, modificado_por= :modificado_por, modificado_en = CURRENT_TIMESTAMP "
                               "where id= :ventaId ");

            queryVenta.bindValue(":ventaId", this->ventaId);            
            queryVenta.bindValue(":modificado_por", userId);            
        }

        queryVenta.bindValue(":emision", ui->dteEmision->date());
        queryVenta.bindValue(":monto", ui->txtTotal->text().toDouble());
        char estado = (ui->txtMontoCancelado->value() == ui->txtTotal->text().toDouble()) ? 'C' : 'P' ;
        queryVenta.bindValue(":estado", estado);
        queryVenta.bindValue(":cliente", ui->txtCliente->text());
        queryVenta.bindValue(":monto_cancelado", ui->txtMontoCancelado->value());
        queryVenta.bindValue(":descuento", ui->nDescuento->value());
        queryVenta.bindValue(":alumno_id", this->alumnoId);                

        if(!queryVenta.exec()){
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  queryVenta.lastError().text());
        }else{
            this->ventaId=queryVenta.lastInsertId().toInt();
            ui->btnAddDetalle->setEnabled(true);
            QMessageBox msgBox;
            msgBox.setText("La venta fue grabada con exito");
            msgBox.exec();
            this->listarVentas();
        }
    }

}

void FrmVentas::buscarPorDni(){
    if (this->ui->txtDniAlumno->text().toInt() > 100){
        QSqlQuery query;
        query.prepare("select id, nombre, paterno, materno, dni from alumno where dni=:dni");
        query.bindValue(":dni", this->ui->txtDniAlumno->text().toInt());
        if (query.exec()){
            while(query.next()){
                this->alumnoId=query.value(0).toInt();
                ui->txtCliente->setText(QString("%1 %2 %3").arg(query.value(1).toString()).arg(query.value(2).toString()).arg(query.value(3).toString()));
            }
        }
    }
}

void FrmVentas::on_txtDniAlumno_returnPressed()
{
    this->buscarPorDni();
}

void FrmVentas::on_txtDniAlumno_lostFocus()
{
    this->buscarPorDni();
}

void FrmVentas::on_btnBuscar_pressed()
{
    this->listarVentas();
}

void FrmVentas::on_btnAddDetalle_pressed()
{
    //Save the detail item in the sell
    if (ui->txtCantidad->value() > 0){
        QSqlQuery query;
        if (this->ventaId > 0){
            query.prepare("insert into micolegio.detalleventa(unidades, precio, total, descuento, producto_id, venta_id, creado_por)"
                          "values (:unidades, :precio, :total, :descuento, :producto_id, :venta_id, :creado_por);");

            query.bindValue(":unidades", ui->txtCantidad->value());
            query.bindValue(":precio", ui->txtPunitario->value());
            query.bindValue(":total", ui->dpTotal->value());
            query.bindValue(":descuento", ui->dpDescuento->value());
            query.bindValue(":producto_id", ui->cmbProducto->model()->data(ui->cmbProducto->model()->index(ui->cmbProducto->currentIndex(),0)).toInt());
            query.bindValue(":venta_id", this->ventaId);
            int userId = qApp->property("user").toInt();
            query.bindValue(":creado_por",userId);
            if(!query.exec()){
                QMessageBox::critical(0, QObject::tr("Database Error"),
                                      query.lastError().text());
            }else{
                this->listarDetalles();
            }
        }
    }

}

void FrmVentas::on_cmbProducto_editTextChanged(const QString &arg1)
{
    QString aux=arg1.trimmed();
    if (aux.length() > 3){
        ui->cmbProducto->findText(arg1, Qt::MatchContains);
    }
}

void FrmVentas::calcularTotalItem(){
    double precioUnitario=ui->txtPunitario->value();
    int cantidad = ui->txtCantidad->value();
    double total=cantidad*precioUnitario;
    ui->dpTotal->setValue(total);
}

void FrmVentas::listarDetalles()
{

    if (this->ventaId > 0) {
        this->detallesModel=new QSqlRelationalTableModel(ui->tbwDetallesVenta);
        this->detallesModel->setTable("detalleventa");

        this->detallesModel->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
        this->detallesModel->setRelation(detallesModel->fieldIndex("producto_id"), QSqlRelation("producto","id","descripcion"));

        this->detallesModel->setFilter(QString("venta_id=%1").arg(this->ventaId));

        this->detallesModel->setHeaderData(detallesModel->fieldIndex("producto_id"),Qt::Horizontal,tr("Producto"));
        this->detallesModel->setHeaderData(detallesModel->fieldIndex("unidades"),Qt::Horizontal,tr("Cantidad"));
        this->detallesModel->setHeaderData(detallesModel->fieldIndex("precio"),Qt::Horizontal,tr("P.Unit."));
        this->detallesModel->setHeaderData(detallesModel->fieldIndex("descuento"),Qt::Horizontal,tr("Dscto."));
        this->detallesModel->setHeaderData(detallesModel->fieldIndex("total"),Qt::Horizontal,tr("Total"));

        this->detallesModel->select();

        double total=0.0;
        for (int row=0; row< this->detallesModel->rowCount(); ++row){
            QSqlRecord record=this->detallesModel->record(row);
            total=total + record.value("total").toDouble();
        }
        ui->txtTotal->setText(QString::number(total));

        ui->tbwDetallesVenta->setModel(this->detallesModel);
        ui->tbwDetallesVenta->setColumnHidden(detallesModel->fieldIndex("id"), true);
        ui->tbwDetallesVenta->setColumnHidden(detallesModel->fieldIndex("venta_id"), true);
        ui->tbwDetallesVenta->setColumnHidden(detallesModel->fieldIndex("igv"), true);
        ui->tbwDetallesVenta->setColumnHidden(detallesModel->fieldIndex("creado_en"), true);
        ui->tbwDetallesVenta->setColumnHidden(detallesModel->fieldIndex("creado_por"), true);
        ui->tbwDetallesVenta->setColumnHidden(detallesModel->fieldIndex("modificado_en"), true);
        ui->tbwDetallesVenta->setColumnHidden(detallesModel->fieldIndex("modificado_por"), true);
        ui->tbwDetallesVenta->setColumnHidden(detallesModel->fieldIndex("producto_id"), true);

        ui->tbwDetallesVenta->setColumnWidth(5, 300);
        ui->tbwDetallesVenta->resizeColumnsToContents();
        ui->tbwDetallesVenta->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tbwDetallesVenta->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tbwDetallesVenta->setItemDelegate(new QSqlRelationalDelegate(ui->tbwDetallesVenta));
    }

}

void FrmVentas::on_cmbProducto_currentIndexChanged(int index)
{
    if (mapperProductos != NULL && index > 0){
        mapperProductos->setCurrentIndex(index);
        this->calcularTotalItem();
    }
}

void FrmVentas::on_txtCantidad_valueChanged(int arg1)
{
    if (arg1 > 0){
        this->calcularTotalItem();
    }
}

void FrmVentas::on_tbwVentas_doubleClicked(const QModelIndex &index)
{    
    if (index.isValid()){
        this->ventaId= this->ventasModel->data(this->ventasModel->index(mapper->currentIndex(),0)).toInt();
        //Set the values in the Tab Detalle
        ui->dteEmision->setDate(this->ventasModel->data(this->ventasModel->index(mapper->currentIndex(),this->ventasModel->fieldIndex("emision"))).toDate());
        ui->txtCliente->setText(this->ventasModel->data(this->ventasModel->index(mapper->currentIndex(),this->ventasModel->fieldIndex("cliente"))).toString());
        this->alumnoId=this->ventasModel->data(this->ventasModel->index(mapper->currentIndex(),this->ventasModel->fieldIndex("alumno_id"))).toInt();

        this->listarDetalles();
        ui->btnAddDetalle->setEnabled(TRUE);
        ui->tabDetalles->setEnabled(TRUE);
        this->calcularTotalItem();
        this->ui->tabWidget->setCurrentIndex(1);
    }
}

void FrmVentas::on_btnImprimir_pressed()
{
    QPrinter printer;    
    printer.setPageSize(QPrinter::A4);
    //qDebug() << ui->tabWidget->currentIndex();
    if (ui->tabWidget->currentIndex()==1){
        printer.setPageSize(QPrinter::A7);
    }
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Document"));

    if (dialog->exec() != QDialog::Accepted)
        return;

    QPainter painter;    
    painter.begin(&printer);

    const int yStep=15;
    int xMax = printer.pageRect().width();

    if (this->ventaId > 0){

        QSqlRecord record=this->ventasModel->record(this->ventasModel->data(this->ventasModel->index(mapper->currentIndex(),0)).toInt());
        double total=0;
        for (int i=0; i<2; i++){            
            int yIni=16;
            QFont headerFont("Times", 14, QFont::Normal);
            QFont headerFont2 = QFont("Times", 10, QFont::Bold);
            headerFont2.setItalic(true);
            QFont defaultFont("Times", 10, QFont::Normal);

            painter.setFont(headerFont);
            painter.drawText(QPoint(20,10), "I.E.P. JUAN PABLO II");
            painter.setFont(headerFont2);
            painter.drawText(QPoint(15,yIni + 10),"El arte de enseñar con amor");
            painter.setFont(defaultFont);
            yIni+=10;
            painter.drawText(QPoint(5,yIni + yStep), "Av. Huamantanga 1925 - Jaen - Peru");
            painter.drawText(QPoint(2,yIni + yStep*2), "Consorcio Educativo MARIEL'S");
            painter.drawText(QPoint(2,yIni + yStep*3), "RUC 20487476634");
            painter.drawText(QPoint(2,yIni + yStep*4), "Ticket Boleta Num :  0001 - 0000012345");
            painter.drawText(QPoint(2,yIni + yStep*5), "Cliente : ");
            painter.drawText(QPoint(2,yIni + yStep*6), "Direccion : ");
            painter.drawText(QPoint(2,yIni + yStep*7),QString("Fecha : ").append(record.value("emision").toDate().toString("dd-MMM-yy")));
            painter.setPen(QPen(Qt::DashLine));
            painter.drawLine(QPoint(2,yIni + 2 + yStep*7), QPoint(xMax-2,yIni + 2 + yStep*7));
            painter.drawText(QPoint(2,yIni + yStep*8), "Descripcion                         Cant. Valor");
            painter.drawLine(QPoint(2,yIni + 2 + yStep*8), QPoint(xMax-2,yIni + 2 + yStep*8));
            yIni=yIni + yStep*9;

            if (this->detallesModel->rowCount() > 0){
                for (int row=0; row< this->detallesModel->rowCount(); ++row){                                        

                    QSqlRecord recordDetail=this->detallesModel->record(row);
                    //Descripcion
                    painter.drawText(QPoint(2,yIni + yStep*row), recordDetail.value("descripcion").toString());
                    //Cantidad
                    painter.drawText(QPoint(xMax-50,yIni + yStep*row), recordDetail.value("unidades").toString());
                    //Monto
                    painter.drawText(QPoint(xMax-25,yIni + yStep*row),recordDetail.value("total").toString());
                    total+=recordDetail.value("total").toDouble();
                }                
            }
            painter.drawLine(QPoint(2,printer.pageRect().height()-40), QPoint(xMax-2,printer.pageRect().height()-40));
            painter.drawText(QPoint(2,printer.pageRect().height()-28), tr("Total"));
            painter.drawText(QPoint(xMax-25,printer.pageRect().height()-28), QString::number(total));
            printer.newPage();
        }

    }else{        

        printer.setPageSize(QPrinter::A4);

        QFont headerFont("Serif", 14, QFont::Normal);
        QFont defaultFont("Serif", 10, QFont::Normal);
        QFont boldFont("Serif", 10, QFont::Bold);
        int yIni=20;
        QImage image;
        image.load(":/images/insigniaJPII.png");
        painter.drawImage(QPoint(5,yIni), image);

        painter.setFont(headerFont);
        painter.drawText(QPoint(120,yIni + 30), "I.E.P. JUAN PABLO II");
        painter.drawText(QPoint(120,yIni + 60), "REPORTE DE VENTAS");

        painter.setFont(boldFont);
        int yTop=90;
        const int headerHeight=30;
        int xIni=5;
        QPen penBold;  // creates a default pen

        penBold.setStyle(Qt::SolidLine);
        penBold.setWidth(3);
        penBold.setBrush(Qt::black);
        penBold.setCapStyle(Qt::RoundCap);
        penBold.setJoinStyle(Qt::RoundJoin);
        painter.setPen(penBold);
        //N
        painter.drawRect(QRect(QPoint(xIni, yIni + yTop),QSize(20,headerHeight)));
        painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),"N");
        xIni+=20;
        //Fecha
        painter.drawRect(QRect(QPoint(xIni, yIni + yTop),QSize(120,headerHeight)));
        painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),"Fecha");
        xIni+=120;
        //Cliente
        painter.drawRect(QRect(QPoint(xIni, yIni + yTop),QSize(340,headerHeight)));
        painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),"Cliente");
        xIni+=340;
        //Total
        painter.drawRect(QRect(QPoint(xIni, yIni + yTop),QSize(120,headerHeight)));
        painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),"Total");
        xIni+=120;
        //Monto Cancelado
        painter.drawRect(QRect(QPoint(xIni, yIni + yTop),QSize(120,headerHeight)));
        painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),"Monto Canc.");

        xIni=5;
        yTop+=headerHeight;
        painter.setFont(defaultFont);
        //Recorrer el modelo
        if (this->ventasModel->rowCount() > 0){
            for (int row=0; row< this->ventasModel->rowCount(); ++row){
                QSqlRecord record=this->ventasModel->record(row);
                //N
                painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),QString::number(row+1));
                xIni+=20;
                //Fecha
                painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),record.value("emision").toDate().toString("dd-MMM-yy"));
                xIni+=120;
                //Cliente
                painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),record.value("cliente").toString());
                xIni+=340;
                //Total
                painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),record.value("monto").toString());
                xIni+=120;
                //Monto Cancelado
                painter.drawText(QPoint(xIni + 5,yIni + yTop + 20),record.value("monto_cancelado").toString());
                xIni=5;
                yTop+=headerHeight;
            }
        }
    }

    painter.end();
}

void FrmVentas::on_btnBorrar_pressed()
{
    if(ui->tabWidget->currentIndex()==0){
        //Delete record in the list of sales
        QSqlRecord record=this->ventasModel->record(this->ventasModel->data(this->ventasModel->index(this->mapper->currentIndex(),0)).toInt());
        if (!record.isEmpty()){
            QSqlQuery query;
            query.prepare("DELETE FROM venta WHERE id = :ventaId");
            query.bindValue(":ventaId", record.value("id").toInt());
            if (query.exec()){
                this->listarVentas();
            }else{
                QMessageBox::critical(0, QObject::tr("Database Error"),
                                      query.lastError().text());
            }
        }
    }else{
        if (this->ventaId > 0){
            //Delete record in the list of details
            QSqlQuery query;
            query.prepare("DELETE FROM detalleventa WHERE id = :ventaId");
            query.bindValue(":ventaId", this->ventaId);
            if (query.exec()){
                this->listarDetalles();
            }else{
                QMessageBox::critical(0, QObject::tr("Database Error"),
                                      query.lastError().text());
            }
        }
    }
}
