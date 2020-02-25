#include <iostream>
#include <QSqlDatabase>
#include <QDebug>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"

#include "jugador.h"
#include "servidor.h"
#include "usuario.h"

///variables necesarias
bool g_logueado;
int g_id_usuario;
Servidor::Servidor(int puerto)
{
    this->m_puerto = puerto;
}


 using JSON = nlohmann::json;
 static int idServer = 0;
 //Esto sirve para ver si existe el mensaje
 bool exists (const JSON& json, const std::string& key)
 {
     return json.find(key) != json.end();
 }

 ///FUNCIÓN PARA HACER LOGIN EN LA APP

 void login(ix::WebSocket *webSocket, JSON received){
     std::string user;
     std::string pass;

     received["user"].get_to(user);
     received["pass"].get_to(pass);

     ///Consulta para buscar el usuario en la BBDD
     QSqlQuery q;
     q.prepare("SELECT * FROM usuarios WHERE usuario = :user");
     q.bindValue(":user", user.c_str());
     q.exec();

     JSON respuesta;
     respuesta["type"] ="login";

     ///comprobamos si el usuario existe
     if (q.size() > 0){
         ///consulta para encriptar la contraseña
         QSqlQuery q2;
         q2.prepare("SELECT ENCRYPT(:pass, :uuid)");
         q2.bindValue(":pass", pass.c_str());
         if(q.next()){
             g_id_usuario = q.value("id").toInt();
             respuesta["id_user"] = q.value("id").toString().toStdString();
             qDebug() << "Existe el usuario, id = " << g_id_usuario;
             q2.bindValue(":uuid", q.value("uuid"));
             q2.exec();
         }

         std::string encryptedpass;

         if (q2.first()){
             encryptedpass = q2.value(0).toString().toStdString();
         }//end if

         ///comprobamos si las contraseñas coinciden
         if(encryptedpass.compare(q.value("pass").toString().toStdString()) == 0){
             respuesta["operationSuccess"] = "true";
             g_logueado = true;
         } else {
             respuesta["operationSuccess"] = "false";
             respuesta["errorMessage"] = "La contraseña no es correcta";
         } //end if
     } else {
         qDebug() << "No existe el usuario";
         respuesta["operationSuccess"] = "false";
         respuesta["errorMessage"] = "El usuario no existe";
     } //end if
 }


 void logout(ix::WebSocket *webSocket){
     ///comprobar que el usuario y la contraseña son correctos
     JSON jsonMessage = {
         {"type", "logout"},
         {"operationSuccess", true},

     };

     std::string messageToSend = jsonMessage.dump(); //convertido a JSON
     webSocket->send(messageToSend); //enviar JSON al cliente
     g_logueado = false;
 }



 void crearUsuario(ix::WebSocket *webSocket, JSON received){
     std::string user_name;
     std::string user_pass;

     received["usuario"].get_to(user_name);
     received["password"].get_to(user_pass);

     usuario u;
     u.setUser(QString::fromUtf8(user_name.c_str()));
     u.setPass(QString::fromUtf8(user_pass.c_str()));

     u.save();

     JSON jsonMessage = {
         {"type", "crearUsuario"},
         {"operationSuccess", true},

     };

     std::string messageToSend = jsonMessage.dump();//convertido a JSON
     webSocket->send(messageToSend); //enviar JSON al cliente
 }

 void crearJugador(ix::WebSocket *webSocket, JSON received){
     std::string nombre_jugador;
     std::string apellidos_jugador;
     std::string dni_jugador;
     std::string dorsal_jugador;
     std::string posicion_jugador;
     std::string email_jugador;

     received["nombre_jugador"].get_to(nombre_jugador);
     received["apellidos_jugador"].get_to(apellidos_jugador);
     received["dni_jugador"].get_to(dni_jugador);
     received["dorsal_jugador"].get_to(dorsal_jugador);
     received["posicion_jugador"].get_to(posicion_jugador);
     received["email_jugador"].get_to(email_jugador);

     Jugador j;
     j.setNombre(QString::fromUtf8(nombre_jugador.c_str()));
     j.setApellidos(QString::fromUtf8(apellidos_jugador.c_str()));
     j.setDni(QString::fromUtf8(dni_jugador.c_str()));
     j.setDorsal(std::stoi(dorsal_jugador));//int
     j.setPosicion(std::stoi(posicion_jugador));//int
     j.setEmail(QString::fromUtf8(email_jugador.c_str()));

     j.save();

     ///crear el jugador en la bbdd
     JSON jsonMessage = {
         {"type", "crearJugador"},
         {"operationSuccess", true},

     };

     std::string messageToSend = jsonMessage.dump();//convertido a JSON
     webSocket->send(messageToSend); //enviar JSON al cliente
 }

///1:
     /*JSON crearJugador(JSON recibido)
     {
         idServer++;
         JSON jsonMessage;
         jsonMessage["idmsgServer"]=idServer;
         jsonMessage["action"]="responseCrearJugador";
         jsonMessage["respuesta"]="Jugador creado";
         jsonMessage["datos"]=recibido;
         return jsonMessage;
    }*/
///2:
    JSON crearStaff(JSON recibido){
    idServer++;
    JSON jsonMessage;
    jsonMessage["idmsgServer"]=idServer;
    jsonMessage["action"]="responseCrearStaff";
    jsonMessage["respuesta"]="Personal staff creado";
    jsonMessage["datos"]=recibido;
    return jsonMessage;
}
///3:
    JSON iniciarSesion(JSON recibido){
    idServer++;
    JSON jsonMessage;
    jsonMessage["idmsgServer"]=idServer;
    jsonMessage["action"]="iniciarSesion";
    jsonMessage["respuesta"]="Sesión iniciada correctamente";
    jsonMessage["datos"]=recibido;
    return jsonMessage;
}


 int main(int argc, char *argv[])
 {
     g_logueado = false;
    ///Para conectar la bbdd
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    bool conectado {false};


     ix::WebSocketServer server(9990, "0.0.0.0");

     server.setOnConnectionCallback(
        [&server, &db, &conectado](std::shared_ptr<ix::WebSocket> webSocket,
                   std::shared_ptr<ix::ConnectionState> connectionState)
         {
             webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server, &db, &conectado](const ix::WebSocketMessagePtr msg)
                 {
                     if (msg->type == ix::WebSocketMessageType::Open)
                     {
                         std::cout << "New connection" << std::endl;

                        ///Conectar la bbdd:
                        db.setHostName("localhost");
                        db.setDatabaseName("AplicacionBaloncesto");
                        db.setUserName("postgres");
                        db.setPassword("");

                        conectado = db.open();
                        qDebug() << conectado;
                          JSON jsonmessage=
                          {
                              {"type", "1"},
                              {"Message", "Hola"}
                          };

                         ///Método para crear una jugada nueva.
                          //void crearJugada(object)
                          //{
                         /// 1) Comprobar datos obligatorios
                         /// 2) Verificaciones.
                         /// 3) Inserción en Base de datos
                         /// 4) Comprobar errores.
                         /// 5) Enviar mensaje con respuesta al cliente.
                         ///
                          /*
                         std::string query {"INSERT INTO jugadas ...."};

                         if (object.payload["tipoJugada"] == "Ataque")
                         {
                              /// TODO
                         }
                         else
                         {
                              /// TODO
                         }
                         }*/

                         std::string messageToSend = jsonmessage.dump();
                         webSocket->send(messageToSend);

                         /*
                          JSON jsonmessageConexionRemota=
                          {
                          {"type", "6"},
                          {"Message", "Conexion Remota"}
                          {"Message", "Se ha establecido conexion remota con el usuario + id_usuario"}
                          {"Message", "Fin de la conexion remota"}
                          {"id", "5"}
                          };
                          */
                         
                         //cada vez que recibo mns comproobar campos de JSON
                         //if {
                         //respuesta["action"] == select *;

                                             }
                                             else if (msg->type == ix::WebSocketMessageType::Close)
                                             {
                                                 std::cout << "Bye bye connection" << std::endl;
                                             }
                                             else if (msg->type == ix::WebSocketMessageType::Message)
                                            {
                                                 if (!msg->binary)
                                                 {
                                                     /// Text format
                                                     std::cout << "Received message: " << msg->str << std::endl;
                                                 }

                                                 //webSocket->send(msg->str, msg->binary);
                                                 auto receivedObject = JSON::parse(msg->str);

                                                 ///COMPROBACIÓN SI EL MNS ES VÁLIDO
                                                 if(exists(receivedObject, "message"))
                                                 {
                                                     JSON respuesta;
                                                     respuesta["message"]="Bienvenido";
                                                     webSocket->send(respuesta.dump());
                                                 }
                                                 if (exists(receivedObject, "action")) {
                                                     if (receivedObject["action"] =="crearJugador") {
                                                         crearJugador(webSocket.get() , receivedObject);
                                                     }

                                                     if (receivedObject["action"] =="crearStaff"){
                                                         webSocket->send(crearStaff(receivedObject).dump());
                                                    }

                                                     if (receivedObject["action"] =="iniciarSesion"){
                                                         webSocket->send(iniciarSesion(receivedObject).dump());
                                                    }
                                                 }




                                             }
                                         }
                                     );
                                 }
                             );

                             auto res = server.listen();
                            if (!res.first)
                             {
                                 // Error handling
                                 std::cerr << "errrrrroooooorrr" << std::endl;
                                 return 1;
                             }

server.start();
server.wait();
server.stop();








}
