int primeraVez = 0;
uint8_t len1;
void comunicar()
{

  int aaa = 0;

  if ( role == 1 && recibido == false)
  {

    while ( radio.available() )
    {

      // Fetch the payload, and see if this was the last one.
      uint8_t len = radio.getDynamicPayloadSize();
      len1=len;
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
        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Respuesta de giro izquierda enviado."));
        recibido = true;

      }
      else if (aaa == 2) {
        Serial.print("Recibo giro derecha");
        esX = 2;
        radio.stopListening();
        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Respuesta de giro derecha enviado."));
        recibido = true;

      }
      else if (aaa == 3) {
        Serial.print("Recibo Stop");
        esX = 3;
        radio.stopListening();
        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Respuesta de stop enviado."));
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
    giro_izquierda(7);

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
    giro_derecha(10);

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
    avanzar(15);
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


