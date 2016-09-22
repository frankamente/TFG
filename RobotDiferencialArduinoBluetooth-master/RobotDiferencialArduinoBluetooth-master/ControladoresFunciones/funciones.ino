void mover_adelante()
{
  //Preparamos la salida para que el motor gire hacia delante
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
}

void mover_atras()
{
  //Preparamos la salida para que el motor gire hacia detras
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);  
}
void parar(double correr)
{
  pa_alante=0;
  pa_atras=0;
  Serial.println("PARAR");
  if(estado==1){
    estado=2;
  }
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);  
  analogWrite(ENB,correr);
  analogWrite(ENA,correr);
}

void adelante(double correr)
{pa_alante=1;
pa_atras=0;
Serial.println("DELANTE");
  mover_adelante();
  velocidad(correr);
}

void atras(double correr)
{
  pa_alante=0;
  pa_atras=1;
  Serial.println("ATRAS");
  mover_atras();  
  velocidad(correr);
}

void girar_izquierda_atras()
{
  //Preparamos la salida para que el motor gire hacia delante
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
}

void girar_izquierda_adelante()
{
  //Preparamos la salida para que el motor gire hacia delante
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
}

void girar_derecha_atras()
{
  //Preparamos la salida para que el motor gire hacia delante
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
}
void girar_derecha_adelante()
{
  //Preparamos la salida para que el motor gire hacia delante
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
}

void velocidad(int vel)
{
  analogWrite(ENB,vel);
  analogWrite(ENA,vel);
}


void leer_sensores()
{
   // lee y muestra valor de ultrasonidos
    //Serial.println("Sensores entra");
    unsigned int uS1 = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    //Serial.print("Ping1: ");
    if(uS1 / US_ROUNDTRIP_CM==0)
    {
      dis1=200;
    }
    else
    {
      dis1=uS1 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis1); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
    
    unsigned int uS2 = sonar2.ping(); // Send ping, get ping time in microseconds (uS).
   // Serial.print("Ping2: ");
    if(uS2 / US_ROUNDTRIP_CM==0)
    {
      dis2=200;
    }
    else
    {
      dis2=uS2 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis2); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
  
    unsigned int uS3 = sonar3.ping(); // Send ping, get ping time in microseconds (uS).
    //Serial.print("Ping3: ");
    if(uS3 / US_ROUNDTRIP_CM==0)
    {
      dis3=200;
    }
    else
    {
      dis3=uS3 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis3); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
    
    unsigned int uS4 = sonar4.ping(); // Send ping, get ping time in microseconds (uS).
    //Serial.print("Ping4: ");
    if(uS4 / US_ROUNDTRIP_CM==0)
    {
      dis4=200;
    }
    else
    {
      dis4=uS4 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis4); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
    
    unsigned int uS5 = sonar5.ping(); // Send ping, get ping time in microseconds (uS).
    //Serial.print("Ping5: ");
    if(uS5 / US_ROUNDTRIP_CM==0)
    {
      dis5=200;
    }
    else
    {
      dis5=uS5 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis5); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
    
    if(dis1<10 || dis2<20 || dis3<20 || dis4<20 || dis5<10 )
    {
      colision=1;
    }
    else
    {
      colision=0;
    }
    //Serial.print("colision "); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println(colision);
}


void  inter0 ()   {  // Se ejecuta cuando se detecta un cambio de estado del Pin 2
  int EncoderI;
  EncoderI=digitalRead(OUT1); 
  if(pa_alante==1 && pa_atras==0){
    distI++;}
  else if (pa_alante==0 && pa_atras==1){
    distI--;}
  etat2 =! etat2;  // Cambia el estado. De HIGH a LOW y de LOW a HIGH
  

}


void  inter1 ()   {  // Se ejecuta cuando se detecta un cambio de estado del Pin 3
  
  if(distD==avance){
    distD=0;}
   else{
    distD++;
   }
    
  etat3 =! etat3;  // Cambia el estado. De HIGH a LOW y de LOW a HIGH
  
  int EncoderD;
  EncoderD=digitalRead(OUT2);
}
void control(int vueltasqueremos)
{
  dif_tiempo=tiempo-tiempo_a;
  errorposicion=vueltasqueremos-distI;
  errorvelocidad=errorposicion/dif_tiempo;
  double Kp=7995500;
  double Td=0.2;
  I =int(Kp*(errorposicion+ Td*errorvelocidad));
  Serial.print("Intensidad: ");
  Serial.println(I);
  if (I>30){
    adelante(I);
  }
  else if(I<-15)
  {
    atras(-I);
  }
  else{
    parar(0);
  }
  delay(10);
  tiempo_a=tiempo; 
}
