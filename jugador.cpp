#include "jugador.h"
#include <QDebug>
#include <QSqlError>


///GET
QString Jugador::getNombre(){
    return m_nombre;
}
QString Jugador::getApellidos(){
    return m_apellidos;
}
QString Jugador::getDni(){
    return m_dni;
}
int Jugador::getDorsal(){
    return m_dorsal;
}
int Jugador::getPosicion(){
    return m_posicion;
}
QString Jugador::getEmail(){
    return m_email;
}

///SET
void Jugador::setNombre(QString nombre){
    m_nombre = nombre;
}
void Jugador::setApellidos(QString apellidos){
    m_apellidos = apellidos;
}
void Jugador::setDni(QString dni){
    m_dni = dni;
}
void Jugador::setDorsal(int dorsal){
    m_dorsal = dorsal;
}
void Jugador::setPosicion(int posicion){
    m_posicion = posicion;
}
void Jugador::setEmail(QString email){
    m_email = email;
}


bool Jugador::save(){
    QSqlQuery q;

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
    } else {
        qDebug() << "Insert";
        q.prepare("INSERT INTO jugadores (nombre, apellidos, dni, dorsal, posicion, email) VALUES ('ivan', 'mart', '46d', '4', '2', 'ivan@ivan')");
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
}

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
