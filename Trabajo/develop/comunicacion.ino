int primeraVez = 0;

void comunicar()
{
  
  int aaa = 0;

  if ( role == 1 && recibido == false)
  {

    while ( radio.available() )
    {

      // Fetch the payload, and see if this was the last one.
      uint8_t len = radio.getDynamicPayloadSize();

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
        esY = 0;
        radio.stopListening();
        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Respuesta de giro izquierda enviado."));
        recibido = 1;

      }
      else if (aaa == 2) {
        Serial.print("Recibo giro derecha");
        esX = 2;
        esY = 0;
        radio.stopListening();
        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Respuesta de giro derecha enviado."));
        recibido = 1;

      }
      else if (aaa == 3) {
        Serial.print("Recibo Stop");
        esX = 3;
        esY = 0;
        radio.stopListening();
        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Respuesta de stop enviado."));
        recibido = 1;

      }
      else {
        Serial.println(F("No recibo nada o no es lo que espero."));
        esX = 3;
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
    giro_izquierda(7);

    if (fin == true) {
      esX = 0;
      Serial.println("OK");
      recibido = false;
      sitio=false;
    }
  }
  else if (esX == 2) {
    giro_derecha(7);

    if (fin == true) {
      esX = 0;
      Serial.println("OK");
      recibido = false;
      sitio=false;
    }
  }
  else if (esX == 3) {
    avanzar(15);
    if (fin == true) {
      esX = 0;
      Serial.println("OK");
      recibido = false;
      sitio=false;
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


