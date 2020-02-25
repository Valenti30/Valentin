#ifndef JUGADOR_H
#define JUGADOR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QVariant>
#include "json.hpp"

using JSON = nlohmann::json;

class Jugador
{

private:
    int m_idJugador = 0;
    QString m_nombre;
    QString m_apellidos;
    QString m_dni;
    int m_dorsal;
    int m_posicion;
    QString m_email;

public:
    ///GET
    QString getNombre();
    QString getApellidos();
    QString getDni();
    int getDorsal();
    int getPosicion();
    QString getEmail();


    ///SET
    void setNombre(QString nombre);
    void setApellidos(QString apellidos);
    void setDni(QString dni);
    void setDorsal(int dorsal);
    void setPosicion(int posicion);
    void setEmail(QString email);

    ///BBDD connectors
     bool save();
     void load(int id);



};

#endif // JUGADOR_H

