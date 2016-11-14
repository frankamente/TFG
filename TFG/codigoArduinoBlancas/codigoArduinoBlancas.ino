#include <NewPing.h>
#include <MsTimer2.h>
#include "define.h"
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(22, 23);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
int role = 1; // Receptor 1, Emisor 0
const int min_payload_size = 4;
const int max_payload_size = 32;
const int payload_size_increments_by = 1;
int next_payload_size = min_payload_size;
char receive_payload[max_payload_size + 1]; // +1 to allow room for a terminating NULL char
/*
  Esta variable nos va a servir para poder hacer diferentes funciones dentro de la comunicación
  Si su valor es 0 -> Nuestra comunicación hará las funciones generales, estar en reposo o cambiar de función.
  Si su valor es 1 -> Entrará en el modo movimiento, en este modo utilizamos otras funciones específicas.
*/
int opciones = 0;
int posX, posY = 0;

/// Contadores de distancia de ruedas por encoder
int distD = 0, distDA = 0;
int distI = 0, distIA = 0;
int adelante = 0, atras = 0;
int estado = 0;
int intensidad = 0, errorposicion = 0, errorvelocidad = 0, int_err = 0, int_err_1 = 0;
int vu = 0, avz = 0;


int p_tray = 0;
boolean movimiento = false;
boolean rectifica = false;
boolean reset = false;
boolean fin = false;
boolean sitio = false;
boolean recibido = false;

unsigned long tiempo = 0;
unsigned long t_actualizado = 0;


boolean colision = false, choque = false;
int detectado = 0;
int dis = 0;
int dif_tiempo = 0, tiempo_a = 50;

/// Definimos cada ultrasonido

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



void setup() {
   pinMode(13, OUTPUT);
  Serial.begin(115200);
  radio.begin();
  // enable dynamic payloads
  radio.enableDynamicPayloads();
  // optionally, increase the delay between retries & # of retries
  radio.setRetries(5, 15);
  // Open pipes to other nodes for communication
  if ( role == 0 )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1, pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1, pipes[0]);
  }
  // Start listening
  radio.startListening();
  // Dump the configuration of the rf unit for debugging
  radio.printDetails();
  configInterrupciones();
  configMotores();
}

int esX = 0;
int esY = 0;
int contador = 0;
void loop() {

  tiempo = millis();



  if (recibido == false && sitio == false)
  {
    leer_sensores();
    Serial.println("Estoy en el primero");
    Serial.println("Contador: ");
    Serial.println(contador);
    
    if (dis >= 40 && dis <= 85) {
      contador++;
      if (contador > 7) {
        contador = 0;
        parar();
        comunicar();
        sitio = true;
      }

    }
    else if (dis > 85) {
      avanzar(5);
    }
    else if (dis < 40) {
      avanzar(-5);
    }

  }
  else if (recibido == false && sitio == true) {
    delay(100);
    Serial.println("Estoy en el segundo");
    radio.startListening();
    comunicar();
  }
  if (recibido == true)
  {

    Serial.println("Estoy en el tercero");
    radio.stopListening();
    accion();
  }


  delay(20);
}
