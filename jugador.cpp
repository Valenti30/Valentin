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

bool Jugador::save(){

    QSqlQuery q;

    //UPDATE
    if (m_idJugador > 0){
        qDebug() << "Update";
        q.prepare("UPDATE jugadores SET nombre = :nombre, apellidos = :apellidos, dni = :dni, dorsal = :dorsal, posicion = :posicion, email = :email");
        q.bindValue(":idjugador", m_idJugador);
        q.bindValue(":nombre", m_nombre);
        q.bindValue(":apellidos", m_apellidos);
        q.bindValue(":dni", m_dni);
        q.bindValue(":dorsal", m_dorsal);
        q.bindValue(":posicion", m_posicion);
        q.bindValue(":email", m_email);

    }
    else
    {
    //INSERT
        qDebug() << "Insert";
        q.prepare("INSERT INTO jugadores (nombre, apellidos, dni, dorsal, posicion, email) VALUES (:nombre, :apellidos, :dni, :dorsal, :posicion, :email)");
        q.bindValue(":nombre", m_nombre);
        q.bindValue(":apellidos", m_apellidos);
        q.bindValue(":dni", m_dni);
        q.bindValue(":dorsal", m_dorsal);
        q.bindValue(":posicion", m_posicion);
        q.bindValue(":email", m_email);
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
    q.prepare("SELECT * FROM jugador where id = :idJugador LIMIT 1");
    q.bindValue(":idJugador", id);
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

        qDebug() << m_nombre + m_apellidos + m_dni + m_dorsal + m_posicion + m_email;
    } //end if
}
