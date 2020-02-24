#include "usuario.h"
#include <QDebug>
#include <QSqlError>



///GET
QString usuario::getUser(){
    return m_user;
}
QString usuario::getPass(){
    return m_pass;
}
/*QString usuario::getUserId(){
    return m_idUser;
}*/

///SET
void usuario::setUser(QString idUser) {
    m_user = idUser;
}
void usuario::setPass(QString pass){
    m_pass = pass;
}

bool usuario::save(){
    QSqlQuery q;

    if (m_idUser > 0)
    {
        qDebug() << "Update";
        q.prepare("UPDATE jugadores SET usuario = :user, pass = :password WHERE id = :iduser");
        q.bindValue(":iduser", m_idUser);
        q.bindValue(":user", m_user);
        q.bindValue(":password", m_pass);
    }
    else
    {
       qDebug() << "Insert";
       q.prepare("INSERT INTO usuarios (usuario, pass) VALUES (:user, ::password)");
       q.bindValue(":user", m_user);
       q.bindValue(":password", m_pass);
    } //end if

    bool result {q.exec()};

    qDebug() << result;
    qDebug() << q.lastError();
}

void usuario::load(int id){
    QSqlQuery q;
    q.prepare("SELECT * from usuario where id = :iduser LIMIT 1");
    q.bindValue(":iduser", id);
    bool result {q.exec()};
    qDebug() << q.size();

    if (result) {
        q.next();
        m_idUser = id;
        m_user = q.value("usuario").toString();
        m_pass = q.value("pass").toString();
    } //end if

}

