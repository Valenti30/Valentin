#include "jugador.h"
#include <QVariant>
#include <QString>

Jugador::Jugador(std::string nombre, std::string apellidos, std::string dni, std::string dorsal)
{
    this->m_nombre = nombre;
    this->m_apellidos = apellidos;
    this->m_dni = dni;
    this->m_dorsal = dorsal;
}

Jugador::~Jugador(){}

void Jugador::save()
{

    QSqlQuery query;
    query.prepare("INSERT INTO jugador (nombre, apellidos, dni, dorsal) VALUES (:nombre, :ape, :dni, :dorsal);");

    QVariant nombre = QString::fromStdString(m_nombre);
    QVariant apellidos = QString::fromStdString(m_apellidos);
    QVariant dni = QString::fromStdString(m_dni);
    QVariant dorsal = QString::fromStdString(m_dorsal);
    query.bindValue(":nombre", nombre);
    query.bindValue(":ape", apellidos);
    query.bindValue(":dni", dni);
    query.bindValue(":dni", dorsal);
    query.exec();

}

Jugador Jugador::load(std::string nombre, std::string apellidos, std::string dni, std::string dorsal)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM jugador where nombre = :nombre, apellidos = :ape, dni = :dni AND dorsal = :dorsal");

    query.bindValue(":nombre", QString::fromStdString(nombre));
    query.bindValue(":ape", QString::fromStdString(apellidos));
    query.bindValue(":dni", QString::fromStdString(dni));
    query.bindValue(":dorsal", QString::fromStdString(dorsal));
    query.exec();

    QSqlRecord rec = query.record();
    while (query.next())
    {
        QString nombre = query.value("nombre").toString();
        QString apellidos = query.value("apellidos").toString();
        QString dni = query.value("dni").toString();
        QString dorsal = query.value("dorsal").toString();

        Jugador jugador(nombre.toUtf8().constData(), apellidos.toUtf8().constData(), dni.toUtf8().constData(), dorsal.toUtf8().constData());
        jugador.m_id = query.value("idJugador").toInt();
        return jugador;
    }

}

void Jugador::remove(int id)
{

    QSqlQuery query;
    query.prepare("DELETE FROM jugador where idJugador = :id");

    query.bindValue(":id", id);
    query.exec();

}

std::list<Jugador> Jugador::find(std::string nombre)
{

    std::list<Jugador> listaJugadores = {};

    QSqlQuery query;
    query.prepare("SELECT * FROM jugador WHERE nombre LIKE :nombre");

    QString  nom = QString::fromStdString(nombre);
    query.bindValue(":nombre", QString("%%1%").arg(nom));

    query.exec();

    QSqlRecord rec = query.record();
    while (query.next())
    {

        QString nombre = query.value("nombre").toString();
        QString apellidos = query.value("apellidos").toString();
        QString dni = query.value("dni").toString();
        QString dorsal = query.value("dorsal").toString();

        Jugador jugador(nombre.toUtf8().constData(), apellidos.toUtf8().constData(), dni.toUtf8().constData(), dorsal.toUtf8().constData());
        jugador.m_id = query.value("idJugador").toInt();

        listaJugadores.push_back(jugador);

    }

    return listaJugadores;

}

JSON Jugador::toJSON()
{

    JSON jugador;
    jugador["id"] = m_id;
    jugador["nombre"] = m_nombre;
    jugador["apellidos"] = m_apellidos;
    jugador["dni"] = m_dni;
    jugador["dorsal"] = m_dorsal;

    return jugador;

}

int Jugador::getId(){ return m_id; }

std::string Jugador::getNombre(){ return m_nombre; }

std::string Jugador::getApellidos(){ return m_apellidos; }

std::string Jugador::getDni() { return m_dni; }

std::string Jugador::getDorsal() { return m_dorsal; }
