void comunicar()
{
  if (Serial.available ()) // si hay datos disponibles para leer
  {
    val = Serial.read (); 
    switch(opciones){
      case 0: // Elegimos la opción
        switch(val)
        {
          case '1':
            Serial.println("Caso 1");
          break;

          case '2':
            leer_sensores();
            Serial.println("dos");
          break;

          case '3':
            opciones=1;
          break;

          case '4':
            //

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
          break;
          case '3':
            Serial.println("Caso 3, opcion 1");

          break;
          }
      break;

      case 2:
      
      break;

      case 3:
      
      break;
    }
    
      
    


  }
  
}