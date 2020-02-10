#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <list>
#include <QSqlQuery>
#include <QSqlRecord>
#include "json.hpp"

using JSON = nlohmann::json;

class Jugador
{

public:
    Jugador(std::string nombre, std::string apellidos, std::string dni);
    JSON toJSON();
    Jugador fromJSON(JSON);
    void save();
    static Jugador load(std::string nombre, std::string apellidos);
    void remove(int);
    static std::list<Jugador> find(std::string);
    ~Jugador();
    int getId();
    std::string getNombre();
    std::string getApellidos();
    std::string getDni();

private:
    int m_id{0};
    std::string m_nombre{""};
    std::string m_apellidos{""};
    std::string m_dni{""};

};

#endif // JUGADOR_H

