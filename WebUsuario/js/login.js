
class Usuario {
    
    constructor(id, nombre, pass) {
        this._id = id;
        this._nombre = nombre;
        this._pass = pass;
    }
    
    get id()
    {
        return this._id;
    }
    
}

var usuario;





function iniciarSesion()
{
    if(getLogeado() == false){
        var nombre=document.getElementById("usuario_login").value;
        var pass=document.getElementById("contrasenya_login").value;
        if(document.getElementById("usuario_login").value != "" || document.getElementById("contrasenya_login").value != ""){
            var Json = {action: "iniciarSesion", usuario: nombre, password: pass};
            socket.send(JSON.stringify(Json));
        
        }
    }

    console.log(nombre);
    console.log(pass);
}

function cerrarCapa()
{
    var el = document.getElementById("id01"); 
    el.style.display = "none"; 

}
function cerrarCapa2()
{
    var el = document.getElementById("id02"); 
    el.style.display = "none"; 

}
function cerrarCapa3()
{
    var el = document.getElementById("id03"); 
    el.style.display = "none"; 

}


window.onload = function(){
    cerrarCapa();
    
}

function crearUsuario(){

    var usuarioValue = document.getElementById("usuario").value;
    var passValue = document.getElementById("password").value;
    var typeValue = "crearUsuario";
    //id mensaje cliente
    var Json = {action: typeValue , usuario: usuarioValue , password: passValue};
    socket.send(JSON.stringify(Json));
    
}

function crearJugador()
{
    id_jugador++;
    var id_mensaje = dameIdMensaje();
    var nombreValue = document.getElementById("nombre").value
    var apellidosValue = document.getElementById("apellidos").value;
    var dniValue = document.getElementById("dni").value;
    var dorsalValue = document.getElementById("dorsal").value;
    var posicionValue = document.getElementById("posicion").value;
    var emailValue = document.getElementById("email").value;

    var Json = {action: "crearJugador", nombre: nombreValue, apellidos: apellidosValue, dni: dniValue, dorsal: dorsalValue, posicion: posicionValue, email: emailValue};
    socket.send(JSON.stringify(Json));

}

/*
function crearJugador(item)
{
    
    var seccion = document.getElementsByClassName("jugador")[0];
    var articulo = document.createElement("JUGADOR");
            
    var imagen = document.createElement("IMG");
    imagen.setAttribute("src", "img/alberto.jpg");
    figure.appendChild(imagen);
            
    var lista = document.createElement("UL");
    var nombre = document.createElement("LI");
    nombre.innerHTML = item.nombre;
    lista.appendChild(nombre);
    var apellido = document.createElement("LI");
    apellido.innerHTML = item.apellido;
    lista.appendChild(apellido);

    articulo.appendChild(figure);
    articulo.appendChild(lista);
    seccion.appendChild(articulo);


 
// Get the modal
var modal = document.getElementById('id01');

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) {
  if (event.target == modal) {
    modal.style.display = "none";
  }
}
}
*/
