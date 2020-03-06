*******************************************
*Proyecto creado por Valentín Gracia Sastre*
*******************************************

# Proyecto eBOARD

El proyecto consiste en un programa cliente y uno servidor que se comunican entre
ellos mediante websocket y mensajes JSON.

Se almacenan datos de jugadores y usuarios en una base de datos y se pueden crear
usuarios y jugadores.

## En qué consiste eBOARD

Es una aplicación diseñada para IOS y Android.
Está enfocada para qué clubes adquieran este servicio para hacer que el entrenador pueda realizar
su trabajo de forma más sencilla. En la aplicación podrá crear sus jugadores, hacer sus quintetos 
inicial, llevar las estadísitcas de cada uno de los jugadores...

## Pre-requisitos

Para el proyecto se necesita la libreria IXWebSocket para poder crear el servidor Websocket.
Para poder descargarlo entra en: [IXWebSocket](https://github.com/machinezone/IXWebSocket).

También se necesita una libreria para poder manejar JSON.
Para poder descargarlo entra en: [nlohmann/json](https://github.com/nlohmann/json).

## Estado de la aplicación

En estos momentos la aplicación se encuentra en desarrollo, las funciones que se pueden realizar son: Iniciar sesión, registrarse y crear jugadores.

## Conceptos que faltan por implementar en la aplicación

**Diferentes funcionalidades como**
- Crear personal del staff: son los ayudantes del entrenador
- Crear un marcador en tiempo real, para que el entrenador pueda utilizarlo en los entrenamientos y partidos
- Ver los equipos a los cuáles se va a enfrentar el equipo. Cuando entres dentro de cada equipo tendrás diferentes posibilidades:
    1. Saldrá el mejor jugador de ese equipo en función de los puntos por partido, asistencias por partido, rebotes por partido... que lleve a lo largo de la temporada
    2. Se verá quién es el entrenador del otro equipo para saber cual es su forma de jugar los partidos, que tácticas utiliza...
- Se podrán crear equipos visitantes por si nuestro equipo algún día hace algún amistoso y no tiene registrado ese equipo.
- se podrán guardar las estadísitcas de cada uno de los jugadores de nuestro equipo y cuando el entrenador lo desee podrá sacar un análisis o un informe con unas gráficas para verlo todo más visual.

## Usabilidad de la aplicación
- Cuando entras en la aplicación pide que te loguees, en caso de que no tengas ningún usuario, deberás pulsar en el botón de registrase.
- Si pulsas el botón se te abrirá una ventana para poder registrarte, una vez finalizado te pedirá que te loguees. Cuando lo hayas hecho ya podrás empezar a disfrutar del programa.


## Tecnología empleada

**Servidor**
- C++ El lenguaje de programación elegido para el servidor.
- Qt El framework de c++ usado en el proyecto.

**Cliente**
- HTML Lenguaje de marca para crear la página del cliente.
- CSS Para darle diseño a la página.
- JS Para interactuar con el servidor y enviar peticiones.

**Base de datos**
- Nombre de la BBDD: AplicacionBaloncesto
- PhpPgAdmin Es una página web que administra bases de datos PostgressSQL
- Usuarios disponibles para hacer el login:
- 1: usuario -> valen, pass -> 1234
- 3: usuario -> javi, pass -> javi

## Autores

- Valentín Gracia Sastre (Desarrollo)

## Licencia

**The MIT License (MIT)**

**Copyright (c) 2020-present Valentín Gracia**

Por la presente, se otorga permiso, de forma gratuita, a cualquier persona que obtenga una copia de este software y los archivos de documentación asociados (el "Software"),
para negociar el Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, modificación, fusión, publicar, distribuir, sublicenciar y / o vender copias del Software,
y permitir que las personas a quienes se les proporcione el Software lo hagan.

## Gestión de errores

- Problemas al conectar la base de datos con el servidor, conectar cliente y servidor.
- Problemas para hacer las traducciones, me faltaba el paso de distribuir para que funcionaran.
- Problemas con el lenguaje javaScript, ya que no tenia conocimientos previos.
- Problemas al recoger los datos de un mensaje JSON.
- Problemas para hacer el certificado, la clave pública ascii.

