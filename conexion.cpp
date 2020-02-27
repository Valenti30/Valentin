
/*! \file */

//! Clase conexion
 /*! La clase conexion al final no la uso, implementé la conexión de la bbdd en la clase
  * del servidor. Lo replanteé de diferente forma y al final no ha sido necesaria.
  * No la borra ya que a lo mejor si replanteo la idea podría necesitarla.
 */


/*#include "conexion.h"
#include <iostream>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QString>

Conexion::Conexion()
{
}

void Conexion::processLine(std::string line)
{

    std::string newLine = line.substr(0, line.rfind("\n"));

    std::string clave = newLine.substr(0, newLine.rfind("="));
    std::string valor = newLine.substr(newLine.rfind("=") + 1, newLine.size());

    m_propiedades[clave] = valor;

}

void Conexion::readFile()
{

    QString nombreArchivo = "/home/usuario/C++/servidorAplicacionBaloncesto/BaseDatos/";

    if(QFile::exists(nombreArchivo) ){

        QFile file(nombreArchivo);


        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while(!file.atEnd())
            {
                std::string line = QString(file.readLine()).toUtf8().constData();
                processLine(line);

            }
        } // end if

    }
    else
    {
        qDebug() << "No se encuentra el archivo " + nombreArchivo;
        exit(0);
    } // end if

}

void Conexion::loadProperties()
{

    readFile();

    m_hostName = QString::fromUtf8(m_propiedades["hostname"].c_str());
    m_databaseName = QString::fromUtf8(m_propiedades["databaseName"].c_str());
    m_port = std::stoi(m_propiedades["port"]);
    m_userName = QString::fromUtf8(m_propiedades["username"].c_str());;
    m_password = QString::fromUtf8(m_propiedades["paswword"].c_str());;

}

bool Conexion::open()
{

    /// 1) Cargar propiedades
    loadProperties();
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(m_hostName);
    m_db.setDatabaseName(m_databaseName);
    m_db.setPort(5432);
    m_db.setUserName(m_userName);
    m_db.setPassword(m_password);


    /// 2) Abrir conexión
    bool ok = m_db.open();

    return ok;

}

void Conexion::close()
{

    m_db.close();

}*/

