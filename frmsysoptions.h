#ifndef FRMSYSOPTIONS_H
#define FRMSYSOPTIONS_H

#include <QTabWidget>
#include <QListWidgetItem>
#include <QSqlTableModel>

namespace Ui {
class FrmSysOptions;
}

class FrmSysOptions : public QTabWidget
{
    Q_OBJECT
    
public:
    explicit FrmSysOptions(QWidget *parent = 0);
    ~FrmSysOptions();
    
private slots:    

    void on_btnGuardar_pressed();        

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::FrmSysOptions *ui;

    QSqlTableModel *modelBancos;
    QSqlTableModel *modelCategorias;
    QSqlTableModel *modelMarcas;
    QSqlTableModel *modelTallas;
};

#endif // FRMSYSOPTIONS_H
