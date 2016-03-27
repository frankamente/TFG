void comunicar(){
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

              
                 break;
      }
         
    
  }
}

