#include "app.h"
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QSqlQuery>


App::App(QObject *parent) : QObject(parent)
{
    QTimer::singleShot(0, this, SLOT(run()));
}

usuario::usuario(){

}


void usuario::load(Db db , int id){
    QSqlQuery q(db.m_db);
    q.prepare("SELECT * from usuario where idusuario = :iduser LIMIT 1");
    q.bindValue(":iduser", id);
    bool result {q.exec()};
    qDebug() << q.size();

    if (result) {
        q.next();
        m_idUser = id;
        m_user = q.value("nombre").toString();
        m_pass = q.value("password").toString();
    } //end if

}
void App::run()
{
    qDebug() << "running...";

    m_context.run(); // run
    if (m_context.shouldExit())
    {
        QCoreApplication::quit();
    } // end if

}

Db::~Db()
{
    if (m_db.isOpen())
    {
        m_db.close();
    } // end if
}

bool Db::insert()
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO usuario (nombre , password) VALUES (:nombre , :pass)");
    query.bindValue(":nombre", "valen");
    query.bindValue(":pass", "1234");
    bool result = query.exec();
qDebug() << query.lastError().text();
    return result;
}

Db::Db()
{
    if (!QSqlDatabase::contains( "MyDb"))
    {
        m_db = QSqlDatabase::addDatabase("QPSQL", "MyDb");
    }
    else
    {
        m_db = QSqlDatabase::database("MyDb");
    } // end if
    m_db.setHostName("localhost");
    m_db.setPort(5432);
    m_db.setUserName("postgres");
    m_db.setPassword("");

}

void Db::close()
{
    m_db.close();
}

bool Db::init()
{
    bool result = 0;

    m_db.close();
    m_db.setDatabaseName("template1");

    bool ok = m_db.open();

    if (ok)
    {

        qDebug() << "Borrando...";
        QSqlQuery q0("DROP DATABASE IF EXISTS prueba_doctest", m_db);
        if (q0.lastError().type() == QSqlError::NoError)
        {
            qDebug() << "Creando...";
            QSqlQuery q1("CREATE DATABASE prueba_doctest", m_db);
            if (q1.lastError().type() == QSqlError::NoError)
            {
                m_db.close();
                m_db.setDatabaseName("prueba_doctest");
                m_db.open();

                /// Crea estructura en la base de datos
                QString sql {"CREATE TABLE usuario ( \
                    idUsuario     SERIAL, \
                    nombre    varchar(40), \
                    password    varchar(40), \
                    PRIMARY KEY(idUsuario) \
                )"};

                qDebug() << "Iniciando...";
                QSqlQuery q2(sql, m_db);
                if (q2.lastError().type() == QSqlError::NoError)
                {
                    result = true;
                } // end if
            }
            else
            {
                qDebug() << "BB:" << m_db.lastError().text();
            } // end if

        }
        else
        {
            qDebug() << "AA:" << m_db.lastError().text();
        } // end if

    } // end if

    return result;
}

QSqlError Db::lastError()
{
    return m_db.lastError();
}

TEST_CASE("base datos #0")
{
    Db db;
    int ok = db.init();

    if (ok)
    {
        qDebug() << "DB UP AND RUNNING";

        SUBCASE("Insertar #0")
        {
            CHECK( db.insert() == true );
        }

    }
    else
    {
        qDebug() << db.lastError().text();

    } // end if

}

TEST_CASE("base datos #1")
{
    Db db;
    int ok = db.init();
    usuario u;

    if (ok)
    {
        qDebug() << "DB UP AND RUNNING";
        db.insert();

        SUBCASE("CargarUsuario #0")
        {
            u.load(db , 1);
            CHECK( u.m_user == "valen" );
        }

    }
    else
    {
        qDebug() << db.lastError().text();

    } // end if

}




