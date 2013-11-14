#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QApplication>


class MyApplication : public QApplication
{
    Q_OBJECT
private:
    QString dbURL;
    QString user;
    qint32 uid;
public:    
    explicit MyApplication(int argc, char *argv[]);    
    void setUserName();
    void setUserData(uint id, QObjectUserData *data);
    void setUserId(int userId);
    int getUserId();
signals:
    
public slots:
    
};

#endif // MYAPPLICATION_H
