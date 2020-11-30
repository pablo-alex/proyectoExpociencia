//Este codigo nos permitia girar un motor paso a paso
//de acuerdo a los valores que recibiamos por la comunicacion serial
//Ejm: Dato de entrada: 35 --> Grados a Girar 35°

//definicion de pines
const int pinMotor1 = 8;    // 28BYJ48 - In1
const int pinMotor2 = 9;    // 28BYJ48 - In2
const int pinMotor3 = 10;   // 28BYJ48 - In3
const int pinMotor4 = 11;   // 28BYJ48 - In4

const int trigPin = 7;
const int echoPin = 4;
const int led = 2;
 
//definicion variables
int velocidadMotor = 1000;  // variable para determinar la velocidad 
// 800 maxima - minima 1000 o mas
int contadorPasos = 0;      // contador para los pasos
int pasosPorVuelta = 4076;  // pasos para una vuelta completa
int tmp =0;
int divGrados = 0;
int flag = 0;
int prevDist = 0;
// Tablas con la secuencia de encendido 
// quitar signo de comentar a la necesaria)
 
//secuencia 1-fase usar velocidadMotor = 2000
//const int cantidadPasos = 4;
//const int tablaPasos[4] = { B1000, B0100, B0010, B0001 };
 
//secuencia 2-fases usar velocidadMotor = 2000
//const int cantidadPasos = 4;
//const int tablaPasos[4] = { B1001, B1100, B0110, B0011 };
 
//secuencia media fase usar velocidadMotor = 1000
const int cantidadPasos = 8;
const int tablaPasos[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };


void setup() {
  //declarar pines como salida
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotor3, OUTPUT);
  pinMode(pinMotor4, OUTPUT);
  
  // pines ultrasonido
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duracion, distancia ;
  digitalWrite(trigPin, LOW);        // Nos aseguramos de que el trigger est� desactivado
  delayMicroseconds(2);              // Para asegurarnos de que el trigger esta LOW
  digitalWrite(trigPin, HIGH);       // Activamos el pulso de salida
  delayMicroseconds(10);             // Esperamos 10�s. El pulso sigue active este tiempo
  digitalWrite(trigPin, LOW);        // Cortamos el pulso y a esperar el echo
  duracion = pulseIn(echoPin, HIGH) ;
  //distancia = duracion / 2 / 29.1  ;
  distancia = duracion / (2 * 29.1)  ;
  //Serial.println(String(distancia) + " cm.") ;
  int Limite = 20 ;                  // Medida en vac�o del sensor
  if ( distancia < Limite)
     digitalWrite ( led , HIGH) ;
  else
    digitalWrite( led , LOW) ;
  delay (100) ;                  // Para limitar el n�mero de mediciones

  if (prevDist!=distancia){
    if (prevDist<distancia){
      flag = distancia - prevDist;
      posGirar(flag * 10);
    }
    if (prevDist>distancia){
      flag = prevDist- distancia;
      negGirar(flag * 10);
    }
    prevDist = distancia;
    Serial.println(String(distancia) + " cm.") ;
//    Serial.println(String(prevDist) + " prevCm.") ;
//    Serial.println(String(flag) + " flag.") ;
  }
  
//  posGirar(10); 
//  delay(6000);
}

void posGirar(int grados){
  divGrados = grados / 10;
  tmp = 140 * divGrados;
  for (int i = 0; i < tmp; i++)
  {
    sentidoHorario();
    delayMicroseconds(velocidadMotor);
  }
}

void negGirar(int grados){
  divGrados = grados / 10;
  tmp = 140 * divGrados;
  for (int i = 0; i < tmp; i++)
  {
    sentidoAntihorario();
    delayMicroseconds(velocidadMotor);
  }
}
void sentidoHorario() // en direcci�n de las agujas del reloj
{
contadorPasos++;
if (contadorPasos >= cantidadPasos) contadorPasos = 0;
escribirSalidas(contadorPasos);
}
 
void sentidoAntihorario()// en direcci�n contraria a las agujas del reloj
{
contadorPasos--;
if (contadorPasos < 0) contadorPasos = cantidadPasos - 1;
escribirSalidas(contadorPasos);
}
 
void escribirSalidas(int paso)
{
digitalWrite(pinMotor1, bitRead(tablaPasos[paso], 0));
digitalWrite(pinMotor2, bitRead(tablaPasos[paso], 1));
digitalWrite(pinMotor3, bitRead(tablaPasos[paso], 2));
digitalWrite(pinMotor4, bitRead(tablaPasos[paso], 3));
}