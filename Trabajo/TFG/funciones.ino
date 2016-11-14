//////////////////// Configuraciones de Motores ///////////////////////////

void mover_adelante()
{
  //Preparamos la salida para que el motor gire hacia adelante
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


/////////////////// Opciones de Movimiento ///////////////////////////

void parar()
{
  adelante = 0;
  atras = 0;
  mover_adelante();
  velocidad(0, 0);
}

void avanza(double vel)
{
  adelante = 1;
  atras = 0;
  mover_adelante();
  velocidad(vel, vel);
}

void retrocede(double vel)
{
  adelante = 0;
  atras = 1;
  mover_atras();
  velocidad(vel, vel);
}

void girar_izquierda_atras(int vel)
{
  adelante = 0;
  atras = 1;
  mover_atras();
  //Izq, Der
  velocidad(vel, 0);
}

void girar_izquierda_adelante(int vel)
{
  adelante = 1;
  atras = 0;
  mover_adelante();
  //Izq, Der
  velocidad(vel, 0);
}

void girar_derecha_atras(int vel)
{
  adelante = 0;
  atras = 1;
  mover_atras();
  //Izq, Der
  velocidad(0, vel);
}
void girar_derecha_adelante(int vel)
{
  adelante = 1;
  atras = 0;
  mover_adelante();
  //Izq, Der
  velocidad(0, vel);
}


////////////////////// Velocidad Movimiento ////////////////////////

void velocidad(int velI, int velD)
{
  analogWrite(ENA, velI);
  analogWrite(ENB, velD);
}


///////////////////// Lectura Sensores //////////////////////////////

void leer_sensores() // Sensor 1 izquierda, 2 centro, 3 derecha
{

  unsigned int uS1 = sonar1.ping();
  if (uS1 / US_ROUNDTRIP_CM == 0)
  {
    dis1 = 200;
  }
  else
  {
    dis1 = uS1 / US_ROUNDTRIP_CM;
  }
  unsigned int uS2 = sonar2.ping();
  if (uS2 / US_ROUNDTRIP_CM == 0)
  {
    dis2 = 200;
  }
  else
  {
    dis2 = uS2 / US_ROUNDTRIP_CM;
  }
  unsigned int uS3 = sonar3.ping();
  if (uS3 / US_ROUNDTRIP_CM == 0)
  {
    dis3 = 200;
  }
  else
  {
    dis3 = uS3 / US_ROUNDTRIP_CM;
  }


  if (dis1 < 20 || dis2 < 30 || dis3 < 20 )
  {
    colision = true;
  }
  else
  {
    colision = false;
  }
  //Serial.print("Izquierda: ");
  Serial.println(dis1);
  //Serial.print("Centro: ");
  Serial.println(dis2);
  //Serial.print("Derecha: ");
  Serial.println(dis3);
}


////////////////////////////// Controlador //////////////////////////////////

int control(int vueltas_deseadas, int dist)
{
  double Kp = 75;
  double Ti = 0.24;

  dif_tiempo = tiempo - tiempo_a;
  errorposicion = vueltas_deseadas - dist;
  int_err = int_err_1 + (errorposicion * 0.001);
  errorvelocidad = errorposicion / dif_tiempo;
  intensidad = int(Kp * (errorposicion + (1 / Ti) * int_err));
  int_err_1 = int_err;

  return intensidad;
}


//////////////////////////// Movimientos ///////////////////////////////

int avanzar(int vueltas)
{

  intensidad = control(vueltas, distI);
  Serial.print("Intensidad: ");
  Serial.print(intensidad);
  Serial.print(" DistanciaI: ");
  Serial.println(distI);
  if (intensidad > 30) {
    avanza(intensidad);
  }
  else if (intensidad < -15)
  {
    retrocede(-intensidad);
  }
  else
  {
    parar();
    choque = false;
    detectado = 0;
    if (rectifica)
    {
      rectifica = false;
      reset = true;
    }
    else
    {
      movimiento = false;
    }
    Serial.println("Para avz ");
    distI = 0;
    distD = 0;
    return (1);
  }
}

int retroceder(int vueltas)
{
  intensidad = control(vueltas, distI);
  Serial.print("Intensidad: ");
  Serial.print(intensidad);
  Serial.print(" DistanciaI: ");
  Serial.println(distI);
  if (intensidad > 30) {
    avanza(intensidad);
  }
  else if (intensidad < -15)
  {
    retrocede(-intensidad);
  }
  else {
    parar();
    choque = false;
    detectado = 0;
    if (rectifica)
    {
      rectifica = false;
      reset = true;
    }
    else
    {
      movimiento = false;
    }
    Serial.println("Para atras ");
    distI = 0;
    distD = 0;
    return (1);
  }
}

int giro_derecha(int vueltas)
{
  intensidad = control(vueltas, distI);
  Serial.print("Intensidad: ");
  Serial.print(intensidad);
  Serial.print(" DistanciaI: ");
  Serial.println(distI);
  if (intensidad > 30) {
    girar_izquierda_adelante(intensidad);
  }
  else if (intensidad < -15)
  {
    girar_izquierda_atras(-intensidad);
  }
  else {
    parar();
    choque = false;
    detectado = 0;
    if (rectifica)
    {
      rectifica = false;
      reset = true;
    }
    else
    {
      movimiento = false;
    }
    Serial.println("Para der ");
    distI = 0;
    distD = 0;
    return 1;
  }
}

int giro_derecha_atras(int vueltas)
{
  intensidad = control(vueltas, distD);
  if (intensidad > 30) {
    girar_derecha_adelante(intensidad);
  }
  else if (intensidad < -15)
  {
    girar_derecha_atras(-intensidad);
  }
  else {
    parar();
    choque = false;
    detectado = 0;
    if (rectifica)
    {
      rectifica = false;
      reset = true;
    }
    else
    {
      movimiento = false;
    }
    Serial.println("Para der atras ");
    distI = 0;
    distD = 0;
    return 1;
  }
}

int giro_izquierda(int vueltas)
{
  Serial.println("Giro izq ");
  intensidad = control(vueltas, distD);
  Serial.print("Intensidad: ");
  Serial.print(intensidad);
  Serial.print(" DistanciaD: ");
  Serial.println(distD);
  if (intensidad > 30) {
    girar_derecha_adelante(intensidad);
  }
  else if (intensidad < -15)
  {
    girar_derecha_atras(-intensidad);
  }
  else {
    parar();
    choque = false;
    detectado = 0;
    if (rectifica)
    {
      rectifica = false;
      reset = true;
    }
    else
    {
      movimiento = false;
    }
    Serial.println("Para izq ");
    distI = 0;
    distD = 0;
    return 1;
  }
}

void giro_izquierda_atras(int vueltas)
{
  intensidad = control(vueltas, distI);
  if (intensidad > 30) {
    girar_izquierda_adelante(intensidad);
  }
  else if (intensidad < -15)
  {
    girar_izquierda_atras(-intensidad);
  }
  else {
    parar();
    choque = false;
    detectado = 0;
    if (rectifica)
    {
      rectifica = false;
      reset = true;
    }
    else
    {
      movimiento = false;
    }
    Serial.println("Para izq atras ");
  }
}


//////////////////////////////// Interrupciones Encoders  ////////////////////////////////////

void  inter0 ()   // Se ejecuta cuando se detecta un cambio de estado del Pin 2
{
  if (adelante == 1 && atras == 0)
  {
    distI++;
  }
  else if (adelante == 0 && atras == 1)
  {
    distI--;
  }
}


void  inter1 ()   // Se ejecuta cuando se detecta un cambio de estado del Pin 3
{
  if (adelante == 1 && atras == 0)
  {
    distD++;
  }
  else if (adelante == 0 && atras == 1)
  {
    distD--;
  }
}

