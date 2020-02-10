#include "usuario.h"
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QSqlError>

Usuario::Usuario(std::string nombre, std::string password, std::string email)
{
    this->m_nombre = nombre;
    this->m_password = password;
    this->m_email = email;
}

void Usuario::save()
{
    QSqlQuery query;
    query.prepare("INSERT INTO usuario (nombre, password, email) VALUES (:nombre, crypt(:pass, gen_salt('bf')), :email);");

    QVariant nombre = QString::fromStdString(m_nombre);
    QVariant pass = QString::fromStdString(m_password);
    QVariant email = QString::fromStdString(m_email);
    query.bindValue(":nombre", nombre);
    query.bindValue(":pass", pass);
    query.bindValue(":email", email);
    query.exec();

    QString error (query.lastError().text());

    if(error == " ")
    {
        query.prepare("select * from usuario order by idusuario desc limit 1;");
        query.exec();
        QSqlRecord rec = query.record();
        while (query.next())
        {
            int id = query.value("idusuario").toInt();
            this->m_id = id;
        }
    }else
    {
        qDebug() << error;
    }

}

Usuario Usuario::load(std::string email, std::string password)
{

    Usuario usuario("", "", "");

    QSqlQuery query;
    query.prepare("SELECT (password = crypt(:password, password)) AS pwd_match  FROM usuario where email = :email;");

    QVariant eml = QString::fromStdString(email);
    QVariant pas = QString::fromStdString(password);
    query.bindValue(":email", eml);
    query.bindValue(":password", pas);
    query.exec();

    bool passCorrect = false;
    QSqlRecord rec = query.record();
    while (query.next())
    {
        passCorrect = QVariant(query.value("pwd_match")).toBool();
    } // end while

    if(passCorrect)
    {

        query.prepare("SELECT * from usuario where email = :email");
        query.bindValue(":email", eml);
        query.exec();

        QSqlRecord rec = query.record();
        while (query.next())
        {
            QString nombre = query.value("nombre").toString();
            QString pass = query.value("password").toString();
            QString email = query.value("email").toString();

            Usuario user(nombre.toUtf8().constData(), pass.toUtf8().constData(), email.toUtf8().constData());
            user.m_id = query.value("idusuario").toInt();
            return user;
        }

    } // end if


    return usuario;

}

void Usuario::remove(int id)
{

    QSqlQuery query;
    query.prepare("DELETE FROM usuario where idusuario = :id");

    query.bindValue(":id", id);
    query.exec();

}

JSON Usuario::toJSON()
{

    JSON usuario;
    usuario["id"] = m_id;
    usuario["nombre"] = m_nombre;
    usuario["pass"] = m_password;
    usuario["email"] = m_email;

    return usuario;

}

int Usuario::getId(){ return m_id; }
std::string Usuario::getNombre(){ return m_nombre; }
std::string Usuario::getPassword(){ return m_password; }
std::string Usuario::getEmail(){ return m_email; }
