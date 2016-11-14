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
int dis1,dis2,dis3,dis4,dis5;
int dif_tiempo=0,tiempo_a=50;

/// Definimos cada ultrasonido

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar5(TRIGGER_PIN5, ECHO_PIN5, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  Serial.begin(9600);

  configInterrupciones();
  configMotores();
 }
 
void loop() {
  
  tiempo = millis();
    
  if(!recibido)
  {
    if (Serial.available ()) // si hay datos disponibles para leer
   {
      val = Serial.read (); 
       if(val == 'f')
       {
         recibido=true;
         fin=false;
         movimiento=0;
         rectifica=0;
         distD=0;
         distI=0;
         j=0;
         i=0;
       }
       else if (val== 'e')
       {
         j--;
         tray[i][0]=((int)vueltas[0]-48);
         j=0;
       }
       else if (val == 'v'  )
       {
         j--;
         if(j==1)
         {
           tray[i][1]=((int)vueltas[0]-48)*10+((int)vueltas[1]-48);
         }
         else if(j==0)
         {
           tray[i][1]=((int)vueltas[0]-48);
         }
         j=0;
         i++;
       }
       else
       {
         vueltas[j]=val;
         j++;
       }
   }
   delay (100); // espera 100ms para próxima lectura
   
  }
  else
  {
/*Serial.print(" Colision: ");
Serial.print(colision);
Serial.print(" Rectifica: ");
Serial.print(rectifica);
Serial.print(" Fin: ");
Serial.println(fin);*/
    
      if (tiempo > (t_actualizado + tsensores) && !fin)
      {
         leer_sensores();
         t_actualizado = tiempo;
      }
     if( !colision && !rectifica && !fin)
     {
        detectado=0;
        if(reset)
        {
           distD=distDA;
           distI=distIA;
           reset=false;
        }
        if(!movimiento && !fin)
        {
          if(p_tray==fil-1 || tray[p_tray][0]==0 && tray[p_tray+1][0]==0 && tray[p_tray+2][0]==0  && p_tray>1)
          {
            fin=true;
            for(r=0;r<20;r++)
            {
              tray[r][0]=0;
              tray[r][1]=0;
            }
            p_tray=0;
            recibido=false;
            movimiento=false;
            rectifica=false;
            reset=false;
            estado=3;
          }
          else
          {  
            p_tray++;
            estado=tray[p_tray][0];
            int_err=0,int_err_1=0;
            distI=0;
            distD=0;
          }
          Serial.print("Punto Tray: ");
          Serial.print(p_tray);
          Serial.print(" Estado: ");
          Serial.println(estado);
          
          movimiento=true;
        }
        
        switch(estado){
          case 0:
            avanzar(tray[p_tray][1]);
          break;
        
          case 1:
            giro_derecha(tray[p_tray][1]);
          break;
         
         case 2:
            giro_izquierda(tray[p_tray][1]);
         break;
         
         case 3:
      
         break;
        } 
        delay(10);
        tiempo_a=tiempo;
        
        distDA=distD;
        distIA=distI;
     }
     else if(!fin)
     {  
         if(!choque)
         {
           distD=0;
           distI=0;
           choque=true;
         }
  
         if(dis3<30 || detectado==3)
         {
           detectado=3;
           rectifica=true;
Serial.print("Entra en esquiva 3: ");
Serial.println(dis3);
           if(tray[p_tray+1][0] == 1)
           {
             giro_derecha_atras(-2);
             tray[p_tray+1][1] = tray[p_tray+1][1] -2;
           }
           else if(tray[p_tray+1][0] == 2)
           {
             giro_izquierda_atras(-2);
             tray[p_tray+1][1] = tray[p_tray+1][1] -2;
             
           }
           else
           {
             parar();
             fin=true;
             rectifica=0;
             recibido=false;
             p_tray=0;
             for(r=0;r<20;r++)
              {
                tray[r][0]=0;
                tray[r][1]=0;
              }
           }
         }
         else if(dis4<20 || detectado==4 || dis2<20 || detectado==2)
         {
           if(dis4<20 || detectado==4)
           {
             detectado=4;
             rectifica=true;
Serial.print("Entra en esquiva 4: ");
Serial.println(dis4);
             giro_izquierda(1);
             if(tray[p_tray+1][0] == 1)
             {
               tray[p_tray+1][1] = tray[p_tray+1][1] +1;
             }
             else if(tray[p_tray+1][0] == 2)
             {
               tray[p_tray+1][1] = tray[p_tray+1][1] -1;    
             }
           }
           else if(dis2<20 || detectado==2)
           {
             detectado=2;
             rectifica=true;
Serial.print("Entra en esquiva 2: ");
Serial.println(dis2);
             giro_derecha(1);
             if(tray[p_tray+1][0] == 1)
             {
               tray[p_tray+1][1] = tray[p_tray+1][1] -1;
             }
             else if(tray[p_tray+1][0] == 2)
             {
               tray[p_tray+1][1] = tray[p_tray+1][1] +1;    
             }
           }
         }
         else if(dis1<20 || detectado==1 || dis5<20 || detectado==5)
         {
           if(dis1<20 || detectado==1)
           {
             detectado=1;
             rectifica=true;
Serial.print("Entra en esquiva 1: ");
Serial.println(dis1);
             giro_derecha(1);
             if(tray[p_tray+1][0] == 1)
             {
               tray[p_tray+1][1] = tray[p_tray+1][1] -1;
             }
             else if(tray[p_tray+1][0] == 2)
             {
               tray[p_tray+1][1] = tray[p_tray+1][1] +1;    
             }
           }
           else if(dis5<20 || detectado==5)
           {
             detectado=5;
             rectifica=true;
Serial.print("Entra en esquiva 5: ");
Serial.println(dis5);
             giro_izquierda(1);
             if(tray[p_tray+1][0] == 1)
             {
               tray[p_tray+1][1] = tray[p_tray+1][1] +1;
             }
             else if(tray[p_tray+1][0] == 2)
             {
               tray[p_tray+1][1] = tray[p_tray+1][1] -1;    
             }
           }    
         }
     }
  }
}
