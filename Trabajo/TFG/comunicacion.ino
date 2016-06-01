void comunicar()
{

  
  if (Serial.available ()) // si hay datos disponibles para leer
  {
    val = Serial.read (); 
    recibido=true;
    switch(opciones){
      case 0: // Elegimos la opción
        switch(val)
        {
          case '1':
            Serial.println("Caso 1");
            avz=1;
            vu=5;
          break;

          case '2':
            leer_sensores();
            Serial.println("dos");
          break;

          case '3':
            opciones=1;
            Serial.println("OK");
          break;

          case '4':
            //
            avz=3;
            vu=10;
            
          break;

          case '5':
            //
            avz=1;
            vu=-10;
            
          break;
          default:
            Serial.println("Reposo");
          break;
        }

      break;

      case 1:
        switch(val)
        {
          case '1':
            Serial.println("Caso 1, opcion 1");
            avz=1;
            vu=1;
          break;
          case '3':
            Serial.println("Caso 3, opcion 1");
            opciones=0;

          break;
          }
      break;

      case 2:
      
      break;

      case 3:
      
      break;
    }
    
      
    


  }
  //Serial.print("Opciones: ");
  //Serial.println(opciones);
}
void recibir(){
  
  if(avz==1){ //0 parado, 1 adelante, 2 atras
    int aviso= avanzar(vu);
    if (aviso==1){
      avz=0;
      Serial.println("OK");
      recibido=false;}
  }

  if(avz==2){ //0 parado, 1 adelante, 2 atras
    int aviso= retroceder(vu);
    if (aviso==1){
      avz=0;
      Serial.println("OK");
      recibido=false;}
  }
  if(avz==3){ //0 parado, 1 adelante, 2 atras
    int aviso= giro_derecha_atras(vu);
    if (aviso==1){
      avz=0;
      Serial.println("OK");
      recibido=false;}
  }
  
}


