#include <NewPing.h>
#include <MsTimer2.h>
#include "define.h"

// Variables para interrupciones
volatile int etat2 = HIGH ;
volatile int etat3 = HIGH ;

// Contadores de distancia de ruedas por encoder
int distD=0,distD_a=0;
int distI=0,distI_a=0;

int errorposicion=0, errorvelocidad=0, I=0;

unsigned long tiempo = 0;
unsigned long t_actualizado = 0;
unsigned long t_actualizado1 = 0;
unsigned long t_actualizado2 = 0;

void atras(void);
void adelante(void);
void parar(void);
// Control
boolean avance=1;
boolean colision=0;
boolean marcha=0;
int dis1,dis2,dis3,dis4,dis5;
int dif_tiempo=0,tiempo_a=0;

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
int vueltasqueremos=3,pa_atras=0,pa_alante=0;
void loop() {
  tiempo = millis();
  dif_tiempo=tiempo-tiempo_a;
  distI_a=distI;
  distD_a=distD;
  Serial.println(distI);
  errorposicion=vueltasqueremos-distI;
  errorvelocidad=errorposicion/dif_tiempo;

double Kp=7995500;
double Td=0.2;
int I =int(Kp*(errorposicion+ Td*errorvelocidad));
Serial.print("Intensidad ");
    Serial.println(I);
if (I>30){

  adelante(I);
//pa_alante=0;
}
  else if(I<-15)
  {atras(-I);
//pa_atras=0;
}
else{
  parar(0);
  }
delay(10);
  distI_a=distI;
  distD_a=distD;
  tiempo_a=tiempo; 
  
}
void adelante(double correr)
{pa_alante=1;
pa_atras=0;
Serial.println("DELANTE");
  //Preparamos la salida para que el motor gire hacia delante
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  analogWrite(ENB,correr);
  analogWrite(ENA,correr);
}

void atras(double correr)
{
  pa_alante=0;
  pa_atras=1;
  Serial.println("ATRAS");
  
  //Preparamos la salida para que el motor gire hacia detras
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);  
  analogWrite(ENB,correr);
  analogWrite(ENA,correr);
}
void parar(double correr)
{
  pa_alante=0;
  pa_atras=0;
  Serial.println("PARAR");
  
  //Preparamos la salida para que el motor gire hacia detras
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);  
  analogWrite(ENB,correr);
  analogWrite(ENA,correr);
}
