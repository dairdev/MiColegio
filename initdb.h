#ifndef INITDB_H
#define INITDB_H

#include <QtSql/QSqlDatabase>
#include <QDir>


QSqlDatabase initDb()
{        
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","micolegio");
    /*QString dbDir = QDir::currentPath();
    dbDir.append("/data/myschool");*/    
    db.setDatabaseName("../MiColegio/data/myschool");
    return db;
}

#endif // INITDB_H
