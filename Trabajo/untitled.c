///////////////////// Lectura Sensores /////////////////////

void leer_sensores() // Sensor 1 izquierda, 2 centro, 3 derecha
{

    unsigned int uS1 = sonar1.ping();
    if(uS1 / US_ROUNDTRIP_CM==0)
    {
      dis1=200;
    }
    else
    {
      dis1=uS1 / US_ROUNDTRIP_CM;
    }
    unsigned int uS2 = sonar2.ping();
    if(uS2 / US_ROUNDTRIP_CM==0)
    {
      dis2=200;
    }
    else
    {
      dis2=uS2 / US_ROUNDTRIP_CM;
    }
    unsigned int uS3 = sonar3.ping();
    if(uS3 / US_ROUNDTRIP_CM==0)
    {
      dis3=200;
    }
    else
    {
      dis3=uS3 / US_ROUNDTRIP_CM;
    }
    
    
    if(dis1<20 || dis2<30 || dis3<20 )
    {
      colision=true;
    }
    else
    {
      colision=false;
    }
    //Serial.print("Izquierda: ");
    Serial.println(dis1);
    //Serial.print("Centro: ");
    Serial.println(dis2);
    //Serial.print("Derecha: ");
    Serial.println(dis3);
}


//////////////////////////////// Interrupciones Encoders  ////////////////////////////////////

void  inter0 ()   // Se ejecuta cuando se detecta un cambio de estado del Pin 2
{  
  if(adelante==1 && atras==0)
  {
    distI++;
  }
  else if (adelante==0 && atras==1)
  {
    distI--;
  }
}


void  inter1 ()   // Se ejecuta cuando se detecta un cambio de estado del Pin 3
{  
  if(adelante==1 && atras==0)
  {
    distD++;
  }
  else if (adelante==0 && atras==1)
  {
    distD--;
  }
}

///////////////////// Movimiento /////////////////////

void movimiento(int direccion, int distancia, int angulo) // Direccion: 0 adelante 1 atras 
{
    if (direccion==0)
    {
        adelante=1;
        
    }


}