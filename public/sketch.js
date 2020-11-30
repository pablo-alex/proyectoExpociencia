let output = document.getElementById('output');
let actions = document.getElementById('actions');
let warning = document.getElementById('warning');

let numb = 0;
let valormax = 10;



const socket = io();



	socket.on('inicio', (data)=>{
		cantidad(data.ini);
	});

	socket.on('warning', (data)=>{
		console.log('El garage esta lleno');
		cantidad(data.ini);
	});

	socket.on('serial', (data)=>{
		console.log('Se produjo una: '+ data.value);
		numb = data.ini;

		if (data.value == 'Entrada') {
			entrada();
		}
		if (data.value == 'Salida') {
			salida();
			warning.innerHTML = `<p>
			<em>${''} </em>
			</p>`
		}
	
		cantidad(data.ini);
	});

function entrada() {
	clock = new Date() 
 	hour =   clock.getHours() 
 	minutes = clock.getMinutes() 
 	seconds = clock.getSeconds() 

	actions.innerHTML += `<p>
    <strong>${hour.toString() + ':' + minutes.toString() + ':' + seconds.toString()}</strong>: ${'Un auto acaba de entrar al Parqueo'}
<p>`
}

function salida() {
	clock = new Date() 
 	hour =   clock.getHours() 
 	minutes = clock.getMinutes() 
 	seconds = clock.getSeconds() 
 	
	actions.innerHTML += `<p>
    <strong>${hour.toString() + ':' + minutes.toString() + ':' + seconds.toString()}</strong>: ${'Un auto acaba de salir del Parqueo'}
<p>`
}

function limite(){
	warning.innerHTML = `<p>
	<em>${'Se ha llegado a la capacidad maxima'} </em>
	</p>`
}

function cantidad(todo){
	output.innerHTML = `<p>
	<em>${'La Cantidad de Automoviles dentro es: ' + todo } </em>
	</p>`

	if (todo==10){
		limite();
	}
}

