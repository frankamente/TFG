#include <NewPing.h>
#include <MsTimer2.h>
#include "define.h"

// Variables para interrupciones
volatile int etat2 = HIGH ;
volatile int etat3 = HIGH ;

// Contadores de distancia de ruedas por encoder
int distD=0;
int distI=0;
int I =0;
int estado=1;
int errorposicion=0, errorvelocidad=0;

unsigned long tiempo = 0;
unsigned long t_actualizado = 0;
unsigned long t_actualizado1 = 0;
unsigned long t_actualizado2 = 0;


// Control
boolean avance=1;
boolean colision=0;
boolean marcha=0;
int dis1,dis2,dis3,dis4,dis5;
int dif_tiempo=0,tiempo_a=0;
int vueltasqueremos=0,pa_atras=0,pa_alante=0;

/* Definimos cada ultrasonido*/

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar5(TRIGGER_PIN5, ECHO_PIN5, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.

  configInterrupciones();
  configMotores();
 }
 
void loop() {
  
  tiempo = millis();
  Serial.println(distI);
  
  switch(estado){
    case 1:
    vueltasqueremos=3;
    control(vueltasqueremos);
    delay(100);
  break;
    case 2:
    vueltasqueremos=0;
   control(vueltasqueremos);
   delay(100);
   break;
   }
}


