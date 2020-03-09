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

int Usuario::getUserId(){
    return m_idUser;
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


Usuario::Usuario(){

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
        q.prepare("UPDATE jugadores SET usuario = :user, pass = crypt(:password , gen_salt('bf')) WHERE id = :iduser");
        q.bindValue(":iduser", m_idUser);
        q.bindValue(":user", m_user);
        q.bindValue(":password", m_pass);
    }
    else
    {
    //INSERT
       qDebug() << "Insert";
       q.prepare("INSERT INTO usuarios (usuario, pass) VALUES (:user, crypt(:password , gen_salt('bf')))");
       q.bindValue(":user", m_user);
       q.bindValue(":password", m_pass);
    } //end if

    bool result {q.exec()};

    qDebug() << result;
    qDebug() << q.lastError();
    return result;
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
    q.prepare("SELECT * from usuarios where idusuario = :iduser LIMIT 1");
    q.bindValue(":iduser", id);
    q.next();

    bool result {q.exec()};
    qDebug() << "cargando...";

    if (result) {
        q.next();
        m_idUser = id;
        m_user = q.value("usuario").toString();
        m_pass = q.value("pass").toString();
        qDebug() << m_idUser;
    }else {
        qDebug() << q.lastError().text();
    } //end if

}

JSON Usuario::loguear(int id_Server){
    JSON respuesta;
    respuesta["id_Servidor"] = id_Server;
    QSqlQuery q2;
    q2.prepare("SELECT * from usuarios WHERE usuario = :nombre and pass = crypt(:password , pass)");
    q2.bindValue(":nombre", m_user);
    q2.bindValue(":password", m_pass);
    q2.next();

    bool result {q2.exec()};

    qDebug() << result;
    qDebug() << q2.lastError();

    if (result) {
        if(q2.next()){
            qDebug() << "entra1";
            respuesta["respuesta"] = "te has logueado con éxito";
            load(q2.value("idusuario").toInt());
        }else{
            qDebug() << "entra2";
            respuesta["respuesta"] = "el usuario y la contraseña no son validos";
        }
    }//end if
    return  respuesta;
}

JSON Usuario::RespuestaRegistro(int id_Server , JSON cliente , bool ok){
    JSON respuesta;
    respuesta["id_Servidor"] = id_Server;
    respuesta["id_Cliente"] = cliente["id_Cliente"];
    if(ok){
        respuesta["respuesta"] = "usuario registrado con éxito";
    }else{
        respuesta["respuesta"] = "se ha producido un error";
    }
    return respuesta;
}







