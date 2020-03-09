
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

//socket.oneError(){

    
//}

function entrar(){

    document.getElementById("id01").style.display = "none"; 
    document.getElementById("id02").style.display = "none"; 
    document.getElementById("marcador").style.display = "none";
    document.getElementById("principal").style.display = "block"; 
    document.getElementById("contenido").style.display = "block";
}

function iniciarSesion()
{
    
        var nombre=document.getElementById("usuario_login").value;
        var pass=document.getElementById("contrasenya_login").value;
        if(document.getElementById("usuario_login").value != "" || document.getElementById("contrasenya_login").value != ""){
            var Json = {action: "iniciarSesion", usuario: nombre, password: pass};
            socket.send(JSON.stringify(Json));
        
}
    

    console.log(nombre);
    console.log(pass);
}

function cerrarCapa2()
{
    var el = document.getElementById("id02"); 
    el.style.display = "none"; 
    document.getElementById("form1").reset();

    document.getElementById("id01").style.display = "block";
}
function cerrarCapa3()
{
    var el = document.getElementById("id03"); 
    el.style.display = "none"; 

}
function cerrarCapa4()
{
    var el = document.getElementById("id03"); 
    el.style.display = "none"; 
    var la = document.getElementById("id04"); 
    la.style.display = "block"; 
}
function cerrarCapa5()
{
    var el = document.getElementById("marcador"); 
    el.style.display = "none"; 
    var la = document.getElementById("principal"); 
    la.style.display = "block"; 
    var le = document.getElementById("contenido"); 
    le.style.display = "block"; 
}

function logout()
{
    var ja = document.getElementById("principal"); 
    ja.style.display = "none"; 
    
    var ju = document.getElementById("contenido"); 
    ju.style.display = "none"; 
    var el = document.getElementById("id03"); 
    el.style.display = "none"; 
    var la = document.getElementById("id04"); 
    la.style.display = "none"; 
    var li = document.getElementById("id02"); 
    li.style.display = "none";
    var lo = document.getElementById("id01"); 
    lo.style.display = "block";
     var Json = {action: "logout"};
    socket.send(JSON.stringify(Json));
    document.getElementById("form1").reset();
}

/*window.onload = function(){
    cerrarCapa();
    
}*/

function crearUsuario(){
    
    var id_mensaje = dameIdMensaje();
    var usuarioValue = document.getElementById("usuario").value;
    var passValue = document.getElementById("password").value;
    var typeValue = "crearUsuario";
    if(usuarioValue != "" && passValue != ""){
        var Json = {id_Cliente: id_mensaje ,action: typeValue , usuario: usuarioValue , password: passValue};
        socket.send(JSON.stringify(Json));
        document.getElementById("form2").reset();
        document.getElementById("form1").reset();
    }else{
    
        document.getElementById("error").style.display = "block";
    }

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
    var posicionNumero = posicionValue.split("-");
    var emailValue = document.getElementById("email").value;
    
    var comprobar1 = /^([1-9][1-9][1-9][1-9][1-9][1-9][1-9][1-9][a-zA-Z])$/.test(dniValue);
    var comprobar2 = /^([1-9]+)$/.test(dorsalValue);
    var comprobar3 = emailValue.split("@");
    
    if(nombreValue != "" && apellidosValue != "" && dniValue != "" && dorsalValue != "" && posicionValue != "" && posicionNumero != "" && emailValue != ""){
        if(comprobar1 && comprobar2 && comprobar3[1] != null){
            var Json = {id_Cliente: id_mensaje, action: "crearJugador", nombre: nombreValue, apellidos: apellidosValue, dni: dniValue, dorsal: dorsalValue, posicion: posicionNumero[0], email: emailValue};
            socket.send(JSON.stringify(Json));
            document.getElementById("form3").reset();
            cerrarCapa3();
        }
    }
    



}

function listarJugadores(){

    var id_mensaje = dameIdMensaje();
    var Json = {id_Cliente: id_mensaje , action : "listarJugadores"};
    socket.send(JSON.stringify(Json));
    
}

function llenarListas(array1){

    array1.forEach(element => recogerDatos(element));
}

function recogerDatos(element){
    var lista = document.getElementById("lista");
    var id = element.jugador.idJugador;
    var nombre = element.jugador.nombre;
    var apellidos = element.jugador.apellidos;
    var dni = element.jugador.dni;
    var dorsal = element.jugador.dorsal;
    var posicion = element.jugador.posicion;
    var email = element.jugador.email;
    var option = document.createElement("option");
    option.text = "ID:   "+ id + "   Nombre:   "+ nombre + "   Apellidos:   " + apellidos + "    Dni:    "+ dni + "   Dorsal:   "+ dorsal + "   Posición:   " + posicion + "   Email:   " + email;
    lista.add(option);
}

function deleteJug(){
    var lista = document.getElementById("lista").value;
    var id = lista.split(" ");
    var Json = {action: "eliminarJugador" , id: id[1]};
    socket.send(JSON.stringify(Json));
    listarJugadores();
}




function mostrarRegistro()
{

    document.getElementById("id01").style.display= "none";
    document.getElementById("id02").style.display = "block"; 
    document.getElementById("form2").reset();
}

function marcador()
{
    document.getElementById("id01").style.display= "none";
    document.getElementById("principal").style.display = "none";
    document.getElementById("marcador").style.display = "block"; 
}
