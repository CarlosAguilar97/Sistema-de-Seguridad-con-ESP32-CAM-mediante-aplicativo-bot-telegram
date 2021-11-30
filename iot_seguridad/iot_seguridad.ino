#include <SoftwareSerial.h>
#define CONFIG_GSM_RXPIN 9
#define CONFIG_GSM_TXPIN 8

SoftwareSerial swseri = SoftwareSerial(CONFIG_GSM_RXPIN, CONFIG_GSM_TXPIN);
String Numero_cliente = "935794318";

const int LED = 13;
const int Sirena = 12;

int sensorPir = 2; // declaramos el sensor PIR en el pin 2
int valPir = 0; //variable para asignar la lectura del sensor PIR

int sensorFuego = 3; // declaramos el sensor de fuego en el pin 3
int valFuego = 0; //variable para asignar la lectura del sensor de fuego

int sensorMq = 4; // declaramos el sensor de gas en el pin 4
int valMQ = 0; //variable para asignar la lectura del sensor de gas

int sensorContacto = 5; // declaramos el sensor de contacto en el pin 5
int valContacto = 0; //variable para asignar la lectura del sensor de contacto

int estado_senPir = 0;
int estado_senGas = 0;
int estado_senFuego = 0;
int estado_senPuerta = 0;

int valorSensor = 0;
int val;
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Sirena, OUTPUT);
  pinMode(sensorPir, INPUT);
  pinMode(sensorFuego, INPUT);
  pinMode(sensorMq, INPUT);
  pinMode(sensorContacto, INPUT);
  pinMode(7, INPUT);
  char Letra = Serial.read();
  Serial.begin(115200);
}
void loop() {
  
  if (Serial.available()) {
    
    if ((Letra == 'H') || (digitalRead(7) == HIGH)) {
      
      
    digitalWrite(LED, LOW);


    //========= SENSOR DE FUEGO =====================================
    valFuego = analogRead(A0);
    Serial.println(valFuego);
    if  (valFuego < 600) {
      Serial.println("Fuego detectado!!!");
      if (estado_senFuego == 0) {
        Enviar_msj("Alerta!... Se detecto fuego en en la sala, ingrese a la Aplicación Blynk para capturar imagenes");
        Serial.println("F");
        estado_senFuego = 1;
      }
    }
    else {
      Serial.println("Sin detecion de fuego");
    }
    //==============================================================

    //========= SENSOR DE PUERTA ====================================
    valContacto = digitalRead(sensorContacto);
    Serial.println(valContacto);

    if  (valContacto == 0) {
      Serial.println("Puerta Abierta") ;
      if (estado_senPuerta == 0) {
        Enviar_msj("Alerta!... Movimiento en la puerta de sala, ingrese a la Aplicación Blynk para capturar imagenes");
        Serial.println("P");
        estado_senPuerta = 1;
      }
    }
    else {
      Serial.println("Puerta Cerrada");
    }

    //==============================================================

    //========= SENSOR DE GAS ====================================
    valMQ = analogRead(A1);
    Serial.println(valMQ);

    valMQ = digitalRead(sensorMq);
    Serial.println(valMQ);

    if  (valMQ == 0) {
      Serial.println("Gas detectado");
      if (estado_senGas == 0) {
        Enviar_msj("Alerta!... Se detecto gas en la cocina , ingrese a la Aplicación Blynk para capturar imagenes");
        Serial.println("G");
        estado_senGas = 1;
      }
    }
    else {
      Serial.println(" sin deteccion de gas ");
    }
    //==============================================================

    //========= SENSOR DE MOVIMIENTO ====================================
    valPir = digitalRead(sensorPir);
    //Serial.println(valPir);

    if  (valPir == 1) {
      digitalWrite(Sirena, HIGH);
      Serial.println("Intrusoo");
      if (estado_senPir == 0) {
        Enviar_msj("Alerta!... Movimiento detectado , ingrese a la Aplicación Blynk para obtener imagenes");
        Serial.println("M");
        estado_senPir = 1;
      }
    }
    else {
      digitalWrite(Sirena, LOW);
      Serial.println("Sin movimiento");
    }

    //==============================================================

    delay(1000);
      
      
      
    }
    }
    else if (Letra == 'L') {
      digitalWrite(LED, HIGH);
      estado_senPir = 0;
    }
}
  
 
void Enviar_msj(String msj)
{
  swseri.println("AT+CMGF=1");
  delay(100);

  // ENVIAR EL COMANDO DE ENVIO DE SMS INCLUYENDO EL DESTINATARIO DEL MENSAJE
  swseri.println("AT+CMGS=\"+51935794318\"");
  delay(100);

  // ENVIAR EL CUERPO DEL MENSAJE
  swseri.print(msj);
  delay(500);

  // ENVIAR EL CARACTER DE CONTROL ASCII 26 (SUB) 0X1A INDICANDO EL FINAL DEL CUERPO DEL MENSAJE
  swseri.print(char(0x1A));
  Serial.println("Mensaje enviado");
  delay(2000);
}
