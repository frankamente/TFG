void comunicar()
{
  if (Serial.available ()) // si hay datos disponibles para leer
  {
    val = Serial.read (); 
    switch(opciones){
      case 0: // Elegimos la opción
        switch(val)
        {
          case '0':
            //
          break;

          case '1':
            leer_sensores();
            Serial.println("UNO");
          break;

          case '2':
            opciones=1;
          break;

          case '3':
            //

          break;

          default:
            Serial.println("Reposo");
          break;
        }

      break;

      case 1:
      
      break;

      case 2:
      
      break;

      case 3:
      
      break;
    }
    
      
    


  }
}
