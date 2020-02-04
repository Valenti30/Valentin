#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"

#include "json.hpp";
using JSON = nlohmann::json;
static int idServer = 0;
//Esto sirve para ver si existe el mensaje
bool exists (const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}

JSON crearJugador(JSON recibido){
    idServer++;
    JSON jsonMessage;
    jsonMessage["idmsgServer"]=idServer;
    jsonMessage["action"]="responseCrearJugador";
    jsonMessage["respuesta"]="Jugador creado";
    jsonMessage["datos"]=recibido;
    return jsonMessage;
}

JSON borrarJugador(JSON recibido){
    idServer++;
    JSON jsonMessage;
    jsonMessage["idmsgServer"]=idServer;
    jsonMessage["action"]="responseCrearJugador";
    jsonMessage["respuesta"]="Jugador borrado";
    jsonMessage["datos"]=recibido;
    return jsonMessage;
}

int main(int argc, char *argv[])
{

    ix::WebSocketServer server(9990, "0.0.0.0");

    server.setOnConnectionCallback(
        [&server](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server](const ix::WebSocketMessagePtr msg)
                {
                    if (msg->type == ix::WebSocketMessageType::Open)
                    {
                        std::cout << "New connection" << std::endl;
                         JSON jsonmessage=
                         {
                              {"type", "1"},
                              {"Message", "Hola"}
                         };

                         ///Mensajes que mandará el servidor al cliente

                         JSON jsonmessageInicio=
                         {
                             {"result", "1"}, /// 0: Todo bien; No 0: Error
                             {"errorMessage", "La contraseña es incorrecta"},
                             {"id", /* AUTOGENERADO EN EL SERVIDOR */},
                             {"idClient", /* ID COPIADO DEL MENSAJE RECIBIDO */}
                         };


                         ///Mensajes que mandará el cliente al servidor

                         JSON jsonmessageInicioSesion=
                         {
                             {"type", "InicioSesion"},
                             {"usuario", "usuario"},
                             {"contraseña", "12345"},
                             {"id", "1"},
                         };


                         JSON jsonmessageFin=
                         {
                             {"type", "CerrarSesion"},
                             {"id", "2"},
                         };

                         JSON jsonmessageUsuarios=
                         {
                             {"type", "4"},
                             {"Message", "Creación usuarios"},
                             {"Message", "Usuario creado con éxito"},
                             {"id", "3"}
                         };

                         JSON jsonmessageJugadas=
                         {
                             {"type", "5"},
                             {"Message", "Creación jugadas"},
                             {"Message", "Ataque | Defensa"},
                             {"id", "4"}
                         };

                         ///Método para crear una jugada nueva.
                         //void crearJugada(object)
                         //{
                             /// 1) Comprobar datos obligatorios
                             /// 2) Verificaciones.
                             /// 3) Inserción en Base de datos
                             /// 4) Comprobar errores.
                             /// 5) Enviar mensaje con respuesta al cliente.
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

                        /*if (exists(receivedObject, "action")) {
                            if (receivedObject["action"] == "crearJugador") {
                                webSocket->send(crearJugador(receivedObject).dump());
                            }
                        }*/


                        //std::cout << receivedObject["message"] << std::endl;
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

/*
 * JSON jsonmessage=
 * {
 *      {"type", "1"},
 *      {"Message", "Hola"}
 * }
*/










