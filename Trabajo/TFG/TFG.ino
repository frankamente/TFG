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

/// Trayectoria
char  val;
char vueltas[2];
boolean recibido = false;
int fil = 20;
int i = 0, j = 0, r = 0;
// Estado  Vuelt
int tray[20][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

int p_tray = 0;
boolean movimiento = false;
boolean rectifica = false;
boolean reset = false;
boolean fin = false;

unsigned long tiempo = 0;
unsigned long t_actualizado = 0;


boolean colision = false, choque = false;
int detectado = 0;
int dis1, dis2, dis3;
int dif_tiempo = 0, tiempo_a = 50;

/// Definimos cada ultrasonido

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
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

void loop() {

  tiempo = millis();

avanzar(10);

  /*/ si hay datos disponibles para leer
  if (recibido == false)
  {
    comunicar();
  }
  if (recibido == true)
  {
    accion();
  }
*/
  /*////////////////////////////////// Mientras no llegue ningún dato, espera 10 ms y actualiza el tiempo y las distancias
    delay(10);
    int a = 0;
    tiempo_a = tiempo;

    distDA = distD;
    distIA = distI;
  */
}
