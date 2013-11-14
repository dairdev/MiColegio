#ifndef ALUMNOSADMIN_H
#define ALUMNOSADMIN_H

#include <QWidget>

namespace Ui {
class AlumnosAdmin;
}

class AlumnosAdmin : public QWidget
{
    Q_OBJECT
    
public:
    explicit AlumnosAdmin(QWidget *parent = 0);
    ~AlumnosAdmin();
    
private:
    Ui::AlumnosAdmin *ui;
};

#endif // ALUMNOSADMIN_H
