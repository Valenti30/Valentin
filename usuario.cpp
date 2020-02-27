#include "usuario.h"
#include <QDebug>
#include <QSqlError>

/*! \file */

///GETTERS


/**
 * @brief Obtener el nombre del usuario
 * @return Código del usuario
 */
QString Usuario::getUser(){
    return m_user;
}
/**
 * @brief Obtener la contraseña del usuario
 * @return Contraseña del usuario
 */
QString Usuario::getPass(){
    return m_pass;
}


///SET


/**
 * @brief Modificar el nombre del usuario
 * @param idUser -> Nuevo nombre del usuario
 */
void Usuario::setUser(QString idUser) {
    m_user = idUser;
}
/**
 * @brief Modificar la contraseña de un usuario
 * @param pass -> Nueva contraseña
 */
void Usuario::setPass(QString pass){
    m_pass = pass;
}

///OPERACIONES de la BBDD

/**
 * @brief Actualiza o inserta un nuevo usuario a la BBDD
 * @return si se ha realizado la consulta sin errores
 */

bool Usuario::save(){
    QSqlQuery q;

    if (m_idUser > 0)
    {
    //UPDATE
        qDebug() << "Update";
        q.prepare("UPDATE jugadores SET usuario = :user, pass = :password WHERE id = :iduser");
        q.bindValue(":iduser", m_idUser);
        q.bindValue(":user", m_user);
        q.bindValue(":password", m_pass);
    }
    else
    {
    //INSERT
       qDebug() << "Insert";
       q.prepare("INSERT INTO usuarios (usuario, pass) VALUES (:user, :password)");
       q.bindValue(":user", m_user);
       q.bindValue(":password", m_pass);
    } //end if

    bool result {q.exec()};

    qDebug() << result;
    qDebug() << q.lastError();
}

/**
 * @brief Carga los datos de un usuario
 * @param received --> pasa un JSON
 */

void Usuario::load(JSON received){
    m_idUser = -1;
    m_user = QString::fromStdString(received["usuario"]);
    m_pass = QString::fromStdString(received["password"]);
}

/**
 * @brief Carga los datos de un usuario en el objeto usuario
 * @param id --> id del usuario a cargar
 */

void Usuario::load(int id){
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

