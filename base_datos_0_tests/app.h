#ifndef APP_H
#define APP_H

#include "doctest.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>

class Db
{

public:
    QSqlDatabase m_db;
    Db();
    ~Db();
    bool init();
    void close();
    QSqlError lastError();
    bool insert();
};

class usuario
{

public:
    usuario();
    int m_idUser = 0;
    QString m_user;
    QString m_pass;



    ///BBDD conectores
    bool save();
    void load(Db db,int id);


};


class App : public QObject
{
    Q_OBJECT

    doctest::Context m_context;

public:
    App(QObject *parent = nullptr);

public slots:
    void run();
};

#endif // APP_H
