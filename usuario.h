#ifndef USUARIO_H
#define USUARIO_H

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "json.hpp"

/*! \file */

//! Clase usuario
 /*! La clase usuario hace referencia a la tabla 'usuarios' de la BBDD
  * Aquí, encontraremos las funcionalidades para poder cargar, crear y
  * actualizar nuevos registros en la tabla.
 */


using JSON = nlohmann::json;

class Usuario
{

private:
    int m_idUser = 0;         /*!< Id del usuario. */
    QString m_user;           /*!< nombre del usuario. */
    QString m_pass;           /*!< contraseña del usuario. */

public:
    Usuario();
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
    void load(JSON received);
    JSON loguear(int id_Server);

    ///RESPUESTAS
    JSON RespuestaRegistro(int id_Server , JSON cliente , bool ok);

};

#endif // USUARIO_H
