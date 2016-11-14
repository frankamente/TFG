void configInterrupciones()
{
  pinMode(OUT1, INPUT);
  pinMode(OUT2, INPUT);
  // Activaci�n de la resistencia interna pull-up
  digitalWrite (OUT1, HIGH );
  digitalWrite (OUT2, HIGH );
  // La interrupci�n  0 monitorea los cambios de estado del pin 2.
  attachInterrupt(0, inter0, RISING);//CHANGE);
  // La interrupci�n  1 monitorea los cambios de estado del pin 3.
  attachInterrupt(1, inter1, RISING);//CHANGE);
  
  /*MsTimer2::set(tsensores, sensores);
  MsTimer2::start();*/
}

void configMotores()
{
   // Motor derecho
   pinMode (ENB, OUTPUT); 
   pinMode (IN3, OUTPUT);
   pinMode (IN4, OUTPUT);
   // Motor izquierdo
   pinMode (ENA, OUTPUT); 
   pinMode (IN1, OUTPUT);
   pinMode (IN2, OUTPUT);
}
