#include <iostream>
#include <QSqlDatabase>
#include <QDebug>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"

#include "servidor.h"


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

///1:
     JSON crearJugador(JSON recibido){
     idServer++;
     JSON jsonMessage;
     jsonMessage["idmsgServer"]=idServer;
     jsonMessage["action"]="responseCrearJugador";
     jsonMessage["respuesta"]="Jugador creado";
     jsonMessage["datos"]=recibido;
     return jsonMessage;
 }
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


/*JSON borrarJugador(JSON recibido){
     idServer++;
     JSON jsonMessage;
     jsonMessage["idmsgServer"]=idServer;
     JSON borrarJugador(JSON recibido){
     jsonMessage["respuesta"]="Jugador borrado";
     jsonMessage["datos"]=recibido;
     return jsonMessage;
}
}*/

 int main(int argc, char *argv[])
 {
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
                                                         webSocket->send(crearJugador(receivedObject).dump());
                                                     }
                                                }
                                                 if (exists(receivedObject, "action")) {
                                                     if (receivedObject["action"] =="crearStaff"){
                                                         webSocket->send(crearStaff(receivedObject).dump());
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
