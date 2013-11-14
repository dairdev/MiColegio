#include "myapplication.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>

MyApplication::MyApplication(int argc, char *argv[]):
    QApplication(argc, argv)
{
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("../MiColegio/data/myschool");
//    if(!db.open()){
//        QMessageBox::critical(this->activeWindow(), "Unable to initialize Database",
//                              "Error initializing database: " + db.lastError().text());
//    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("micolegio");
    db.setUserName("root");
    db.setPassword("mysqldinfantas");
    if(!db.open()){
        QMessageBox::critical(this->activeWindow(), "Unable to initialize Database",
                              "Error initializing database: " + db.lastError().text());
    }
}

void MyApplication::setUserId(int userId)
{
    this->uid=userId;
}

int MyApplication::getUserId()
{
    return this->uid;
}
