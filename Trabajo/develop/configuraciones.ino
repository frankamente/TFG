void configInterrupciones() // Interrupciones del encoder. 
{
  pinMode(OUT1, INPUT);
  pinMode(OUT2, INPUT);
  // Activacion de la resistencia interna pull-up
  digitalWrite (OUT1, HIGH );
  digitalWrite (OUT2, HIGH );
  // La interrupcion  0 monitorea los cambios de estado del pin 2.
  attachInterrupt(0, inter0, RISING);
  // La interrupcion  1 monitorea los cambios de estado del pin 3.
  attachInterrupt(1, inter1, RISING);
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
