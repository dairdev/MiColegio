#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QObject>
#include <QtSql>
#include <QMessageBox>
#include <QLabel>
#include <QSizePolicy>
#include <QMdiSubWindow>

class MdiChild;
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:    
    ~MainWindow();
    explicit MainWindow(QWidget *parent = 0);
    void setUserName(QString user);
    
private slots:

    void on_actionAlumnos_triggered();

    void on_actionProductos_triggered();

    void on_actionSistema_triggered();

    void on_actionVentas_triggered();

    void on_actionCompras_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *lblUsuario;
};

#endif // MAINWINDOW_H
