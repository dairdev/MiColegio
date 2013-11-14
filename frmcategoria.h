#ifndef FRMCATEGORIA_H
#define FRMCATEGORIA_H

#include <QWidget>

namespace Ui {
class FrmCategoria;
}

class FrmCategoria : public QWidget
{
    Q_OBJECT
    
public:
    explicit FrmCategoria(QWidget *parent = 0);
    ~FrmCategoria();
    
private:
    Ui::FrmCategoria *ui;
};

#endif // FRMCATEGORIA_H
