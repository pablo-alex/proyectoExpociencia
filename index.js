const SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;
const parser = new Readline();
const mySerial = new SerialPort('COM9',{
    baudRate : 9600
  });

  mySerial.on('open', function(){
    console.log('Opened Serial Port');
  });
  
  mySerial.on('err', function (err) {
    console.log(err,message);
  });
  
const path = require('path');
const express = require('express');
const app = express();

let cant = 0;


app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (req, res) => {
    res.send('Hellow World Prueba');
    res.status(200);
});

const server = app.listen(80, () => {
    console.log('El servidor esta escuchando en el puerto', 80);
});

const SocketIO = require('socket.io');
const io = SocketIO(server);

function warning(){
  io.emit('warning', {
  ini:cant
  });
}

function inicio(){
  io.emit('inicio', {
  ini:cant
  });
} 

function enviardato(data){
    io.emit('serial', {
    value: data.toString(),
    ini:cant
   });
}

io.on('connection', (socket) => {
    if (cant==10){
      warning();
    }else {
      inicio();
    }
  console.log('Nueva Conexion', socket.id);
});


mySerial.on('data', function (data) {
  let aux;
  if (data.toString()=='Entrada'){
    aux = 1;
  }else if (data.toString()=='Salida')
  {
    aux = -1;
  }else{
    console.log('Dato invalido');
  }

  //casos que se bloqueara el envio al cliente
  if (cant==0&&data.toString()=='Salida'){
    console.log('Se llego al valor minimo');
  } else if (cant==10&&data.toString()=='Entrada'){
    console.log('Se llego a la capacidad maxima');
  } else {
    cant= cant + aux;
    enviardato(data);
  }

  console.log(data.toString()+cant.toString());
   });
