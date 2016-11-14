int primeraVez = 0;
uint8_t len1;
void comunicar()
{

  int aaa = 9;
  Serial.println("Entra en comunicar");
  if ( recibido == false)
  {
    

    while ( radio.available() )
    {
      Serial.println("Esperando dato");
      // Fetch the payload, and see if this was the last one.
      uint8_t len = radio.getDynamicPayloadSize();
      len1 = len;
      // If a corrupt dynamic payload is received, it will be flushed
      if (!len) {
        continue;
      }

      radio.read( receive_payload, len );

      // Put a zero at the end for easy printing
      receive_payload[len] = 0;

      // Spew it
      Serial.print(F("Got response size="));
      Serial.print(len);
      Serial.print(F(" value="));
      Serial.println(receive_payload);
      aaa = atoi(receive_payload);
      if (aaa == 1) {
        Serial.print("Recibo giro izquierda");
        esX = 1;
        radio.stopListening();

        recibido = true;

      }
      else if (aaa == 2) {
        Serial.print("Recibo giro derecha");
        esX = 2;
        radio.stopListening();
        // Send the final one back.
        radio.write( receive_payload, len );
        recibido = true;

      }
      else if (aaa == 3) {
        Serial.print("Recibo Stop");
        esX = 3;
        radio.stopListening();
        // Send the final one back.
        radio.write( receive_payload, len );
        recibido = true;

      }

      else if (aaa == 0) {
        Serial.print("Recibo Inicial");
        esX = 0;
        radio.stopListening();
        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Respuesta de inicio enviado."));
        recibido = false;
        parar();
        sitio = true;

      }

      else {
        Serial.println(F("No recibo nada o no es lo que espero."));
        esX = 0;

      }
      Serial.print("A: ");
      Serial.println(aaa);
      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  }
}

void accion() {
  if (esX == 1) {
    giro_izquierda(8);

    if (fin == true) {
      esX = 0;
      Serial.println("OK");
      recibido = false;
      sitio = false;
      radio.stopListening();
      // Send the final one back.
      radio.write( receive_payload, len1 );

    }
  }
  else if (esX == 2) {
    giro_derecha(8);

    if (fin == true) {
      esX = 0;
      Serial.println("OK");
      recibido = false;
      sitio = false;
      radio.stopListening();

      // Send the final one back.
      radio.write( receive_payload, len1 );

    }
  }
  else if (esX == 3) {
    parar();
     esX = 0;
    Serial.println("OK");
    recibido = false;
    sitio = false;
    radio.stopListening();
    // Send the final one back.
    radio.write( receive_payload, len1 );
    while(1){
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(100);              // wait for a second
      digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
      delay(100);
    }

    
  }

    /*
      if (avz == 1) { //0 parado, 1 adelante, 2 atras
      int aviso = avanzar(vu);
      if (aviso == 1) {
      avz = 0;
      Serial.println("OK");
      recibido = false;
      }
      }
      if (avz == 2) { //0 parado, 1 adelante, 2 atras
      int aviso = retroceder(vu);
      if (aviso == 1) {
      avz = 0;
      Serial.println("OK");
      recibido = false;
      }
      }
      if (avz == 3) { //0 parado, 1 adelante, 2 atras
      int aviso = giro_derecha_atras(vu);
      if (aviso == 1) {
      avz = 0;
      Serial.println("OK");
      recibido = false;
      }
      }
    */
  }


