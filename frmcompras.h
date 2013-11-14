#ifndef FRMCOMPRAS_H
#define FRMCOMPRAS_H

#include <QFrame>

namespace Ui {
class FrmCompras;
}

class FrmCompras : public QFrame
{
    Q_OBJECT

public:
    explicit FrmCompras(QWidget *parent = 0);
    ~FrmCompras();

private:
    Ui::FrmCompras *ui;
};

#endif // FRMCOMPRAS_H
