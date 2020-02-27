#ifndef JUGADOR_H
#define JUGADOR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QVariant>
#include "json.hpp"

/*! \file */

//! Clase jugador
 /*! La clase jugador hace referencia a la tabla 'jugadores' de la BBDD
  * Aquí, encontraremos las funcionalidades para poder cargar, crear y
  * actualizar nuevos registros en la tabla.
 */


using JSON = nlohmann::json;

class Jugador
{

private:
    int m_idJugador = 0;        /*!< Id del jugador. */
    QString m_nombre;           /*!< nombre del jugador. */
    QString m_apellidos;        /*!< apellidos del jugador. */
    QString m_dni;              /*!< dni del jugador. */
    int m_dorsal;               /*!< dorsal del jugador. */
    int m_posicion;             /*!< posicion del jugador: BASE: 1, ALERO: 2, ESCOLTA: 3, ALA-PIVOT: 4, PIVOT: 5 */
    QString m_email;            /*!< email del jugador. */

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
     void load(JSON received);



};

#endif // JUGADOR_H

