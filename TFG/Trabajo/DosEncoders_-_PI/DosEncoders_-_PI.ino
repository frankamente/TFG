#include <NewPing.h>
#include <MsTimer2.h>
#include "define.h"

/// Contadores de distancia de ruedas por encoder
int distD=0,distDA=0;
int distI=0,distIA=0;
int adelante=0,atras=0;
int estado=0;
int intensidad=0,errorposicion=0, errorvelocidad=0,int_err=0,int_err_1=0;

/// Trayectoria
char  val;
char vueltas[2];
boolean recibido=false;
int fil=20;
int i=0,j=0,r=0;
             // Estado  Vuelt  
int tray[20][2]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};           
              
int p_tray=0;
boolean movimiento=false;
boolean rectifica=false;
boolean reset=false;
boolean fin=false;

unsigned long tiempo = 0;
unsigned long t_actualizado = 0;


boolean colision=false,choque=false;
int detectado=0;
int dis1,dis2,dis3;
int dif_tiempo=0,tiempo_a=50;

/// Definimos cada ultrasonido

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
              Serial.begin(9600);
            
              configInterrupciones();
              configMotores();
              }
 
void loop() {
  
  tiempo = millis();
    
 // if(recibido=true) 
  //{
    if (Serial.available ()) // si hay datos disponibles para leer
   {
      val = Serial.read (); 
      switch(val){
                  case '0':
                    //recibido=false;
                    Serial.println("Reposo");
                    //recibido=false;
                  break;
                
                  case '1':
                    leer_sensores();
                    Serial.println("UNO");
                  break;
                 
                 case '2':
                    giro_izquierda(tray[p_tray][1]);
                    Serial.println("Dos");
                 break;
                 
                 case '3':
              Serial.println("Tres");
                 break;
                } 
   //}         

   /*////////////////////////////////// Mientras no llegue ningún dato, espera 10 ms y actualiza el tiempo y las distancias */
    delay(10);
    tiempo_a=tiempo;
    
    distDA=distD;
    distIA=distI;
  }
}
