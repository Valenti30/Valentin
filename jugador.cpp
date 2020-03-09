#include "jugador.h"
#include <QDebug>
#include <QSqlError>

/*! \file */


///GETTERS


/**
 * @brief Obtener el nombre del jugador
 * @return nombre del jugador
 */
QString Jugador::getNombre(){
    return m_nombre;
}

Jugador::Jugador(){

}

/**
 * @brief Obtener los apellidos del jugador
 * @return apellidos del jugador
 */
QString Jugador::getApellidos(){
    return m_apellidos;
}

/**
 * @brief Obtener el dni del jugador
 * @return dni del jugador
 */
QString Jugador::getDni(){
    return m_dni;
}

/**
 * @brief Obtener el dorsal del jugador
 * @return dorsal del jugador
 */
int Jugador::getDorsal(){
    return m_dorsal;
}

/**
 * @brief Obtener la posicion del jugador
 * @return posicion del jugador
 */
int Jugador::getPosicion(){
    return m_posicion;
}

/**
 * @brief Obtener el email del jugador
 * @return email del jugador
 */
QString Jugador::getEmail(){
    return m_email;
}



///SETTERS


/**
 * @brief Modificar el nombre del jugador
 * @param nombre --> Nuevo nombre del jugador
 */
void Jugador::setNombre(QString nombre){
    m_nombre = nombre;
}

/**
 * @brief Modificar los apellidos del jugador
 * @param apellidos --> Nuevos apellidos del jugador
 */
void Jugador::setApellidos(QString apellidos){
    m_apellidos = apellidos;
}

/**
 * @brief Modificar el dni del jugador
 * @param dni --> Nuevo dni del jugador
 */
void Jugador::setDni(QString dni){
    m_dni = dni;
}

/**
 * @brief Modificar el dorsal del jugador
 * @param dorsal --> Nuevo dorsal del jugador
 */
void Jugador::setDorsal(int dorsal){
    m_dorsal = dorsal;
}

/**
 * @brief Modificar la posicion del jugador
 * @param posicion --> Nueva posicion del jugador
 */
void Jugador::setPosicion(int posicion){
    m_posicion = posicion;
}

/**
 * @brief Modificar el email del jugador
 * @param email --> Nuevo email del jugador
 */
void Jugador::setEmail(QString email){
    m_email = email;
}


///OPERACIONES de la BBDD


/**
 * @brief Actualiza o inserta un nuevo jugador a la BBDD
 * @return Si se ha realizado la consulta sin errores
 */

bool Jugador::save(int idUsuario){

    QSqlQuery q;

    //UPDATE
    if (m_idJugador > 0){
        qDebug() << "Update";
        q.prepare("UPDATE jugadores SET nombre = :nombre, apellidos = :apellidos, dni = :dni, dorsal = :dorsal, posicion = :posicion, email = :email WHERE idjugadores = :idjugador");
        q.bindValue(":idjugador", m_idJugador);
        q.bindValue(":nombre", m_nombre);
        q.bindValue(":apellidos", m_apellidos);
        q.bindValue(":dni", m_dni);
        q.bindValue(":dorsal", m_dorsal);
        q.bindValue(":posicion", m_posicion);
        q.bindValue(":email", m_email);
        q.next();
    }
    else
    {
    //INSERT
        qDebug() << "Insert";

        q.prepare("INSERT INTO jugadores (nombre, apellidos, dni, dorsal, posicion, email , idusuario) VALUES (:nombre, :apellidos, :dni, :dorsal, :posicion, :email , :idUsuario)");
        q.bindValue(":nombre", m_nombre);
        q.bindValue(":apellidos", m_apellidos);
        q.bindValue(":dni", m_dni);
        q.bindValue(":dorsal", m_dorsal);
        q.bindValue(":posicion", m_posicion);
        q.bindValue(":email", m_email);
        q.bindValue(":idUsuario", idUsuario);
        q.next();
    }//end if

    bool result {q.exec()};
    qDebug() << result;
    qDebug() << q.lastError();

} //end if

/**
 * @brief Carga los datos de un jugador
 * @param received --> pasa un JSON
 */

void Jugador::load(JSON received){
    m_idJugador = -1;
    m_nombre = QString::fromStdString(received["nombre"]);
    m_apellidos = QString::fromStdString(received["apellidos"]);
    m_dni = QString::fromStdString(received["dni"]);
    m_dorsal = QString::fromStdString(received["dorsal"]).toInt();
    m_posicion = QString::fromStdString(received["posicion"]).toInt();
    m_email = QString::fromStdString(received["email"]);
}

/**
 * @brief Carga los datos de un jugador en el objeto jugador
 * @param id --> id del jugador a cargar
 */


void Jugador::load(int id)
{

    QSqlQuery q;
    q.prepare("SELECT * FROM jugadores where idjugadores = :idJugador LIMIT 1");
    q.bindValue(":idJugador", id);
    q.next();
    bool result {q.exec()};
    qDebug() << q.size();

    if (result)
    {
        q.next();
        m_idJugador = id;
        m_nombre = q.value("nombre").toString();
        m_apellidos = q.value("apellidos").toString();
        m_dni = q.value("dni").toString();
        m_dorsal = q.value("dorsal").toInt();
        m_posicion = q.value("posicion").toInt();
        m_email = q.value("email").toString();

    }else {
        qDebug() << q.lastError().text();
    } //end if
}

void Jugador::deleteJug(int idJugador){
    QSqlQuery q;
    q.prepare("DELETE FROM jugadores where idjugadores = :idJugador");
    q.bindValue(":idJugador", idJugador);
    q.next();

    bool result {q.exec()};
    qDebug() << q.size();

    if(result)
    {
        q.next();
    }else{
        qDebug() << q.lastError().text();
    }
}

JSON Jugador::lista(int idUsuario, JSON cliente , int idServer){
    QSqlQuery q;
    q.prepare("SELECT * FROM jugadores WHERE idusuario = :idUsuario");
    q.bindValue(":idUsuario" , idUsuario);
    q.next();

    JSON respuesta;
    respuesta["idServidor"] = idServer;
    respuesta["idCliente"] = cliente["id_Cliente"];
    bool result {q.exec()};
    if (result){
            while(q.next()){
                Jugador jugador;
                jugador.load( q.value("idjugadores").toInt());


                if(jugador.m_idJugador > 0){
                    respuesta["jugadores"].push_back(toJSON(jugador));
                }
            }
        }else {
            qDebug() << q.lastError().text();
        }

        if(q.size() > 0){
            qDebug() << "hola";
            respuesta["respuesta"] = "listado de jugadores";
        }else {
            qDebug() << "caracola";
            respuesta["respuesta"] = "no hay jugadores";
        }

return respuesta;
}

JSON Jugador::toJSON(Jugador jugador){
    JSON jugadorJSON;
    jugadorJSON["jugador"]["idJugador"] = jugador.m_idJugador;
    jugadorJSON["jugador"]["nombre"] = jugador.m_nombre.toStdString();
    jugadorJSON["jugador"]["apellidos"] = jugador.m_apellidos.toStdString();
    jugadorJSON["jugador"]["dni"] = jugador.m_dni.toStdString();
    jugadorJSON["jugador"]["dorsal"] = jugador.m_dorsal;
    jugadorJSON["jugador"]["posicion"] = jugador.m_posicion;
    jugadorJSON["jugador"]["email"] = jugador.m_email.toStdString();
    return jugadorJSON;
}



