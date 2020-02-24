#ifndef USUARIO_H
#define USUARIO_H

#include <QString>
#include <QSqlQuery>
#include <QVariant>

class usuario
{

private:
    int m_idUser = 0;
    QString m_user;
    QString m_pass;

public:
    ///GET
    int getUserId();
    QString getUser();
    QString getPass();

    ///SET
    void setUser(QString user);
    void setPass(QString pass);


    ///BBDD conectores
    bool save();
    void load(int id);


};

#endif // USUARIO_H
