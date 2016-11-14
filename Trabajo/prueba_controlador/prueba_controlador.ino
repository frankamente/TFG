#include <NewPing.h>
#include <MsTimer2.h>
#include "define.h"
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


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

unsigned long tiempo = 0, tiempo_i = 0, tiempo_f = 0;
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

  configInterrupciones();
  configMotores();
}

void loop() {
  int t_anterior = 0, distI_anterior = 0;
  float pruebas = 0.0;
  double velocidadd = 0.0;
  tiempo = millis();
  if (tiempo < 10) {
    tiempo_i = millis();
    girar_izquierda_adelante(70);
    distI = 0;
  }
  if (tiempo > 30000 && tiempo < 30010) {
    girar_izquierda_adelante(100);
    tiempo_i = millis();
    distI = 0;
  }

  tiempo_f = millis();
  if (tiempo>60000){
    girar_izquierda_adelante(0);
    tiempo_f=0;
    tiempo_i=0;
  }
  velocidadd = 2.5 * distI / (tiempo_f - tiempo_i);
  tiempo = millis();
  Serial.print(velocidadd);
  Serial.print(",");




}
