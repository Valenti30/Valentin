
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
    var nombre=document.getElementById("usuario_login").value;
    var pass=document.getElementById("contrasenya_login").value;
    var Json = {action: "iniciarSesion",nombre: nombre, contrasenya: pass};
    socket.send(JSON.stringify(Json));
    
    console.log(nombre);
    console.log(pass);
}

function cerrarCapa()
{
    var el = document.getElementById("id01"); 
    el.style.display = "none"; 

}

window.onload = function(){
    cerrarCapa();
    
}


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
