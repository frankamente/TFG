int primeraVez=0;
int esX, esY = 0;
void comunicar()
{
  int aaa = 0;

  if ( role == 1 && recibido == false)
  {
    if (esX == 0 && esY == 0)
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
        if (aaa == 0) {
          Serial.print("Tengo el cero");
          esX = 0;
          esY = 0;
          recibido=1;
          radio.write(receive_payload,len );
        }
        else if(primeraVez==1){
          posY=aaa;
          
        }
        Serial.print("A: ");
        Serial.println(aaa);
        // First, stop listening so we can talk
        radio.stopListening();

        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Sent response."));

        // Now, resume listening so we catch the next packets.
        radio.startListening();
      }

    }




    if (esX == 1 && esY == 0)
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
        if (aaa == 999) {
          Serial.print("Tengo X");
          esX = 0;
          esY = 1;
        }
        else posX = aaa;
        Serial.print("\nPosx: "); Serial.println(posX);
        Serial.print("A: ");
        Serial.println(aaa);
        // First, stop listening so we can talk
        radio.stopListening();

        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Sent response."));

        // Now, resume listening so we catch the next packets.
        radio.startListening();
      }

    }



    if (esX == 0 && esY == 1)
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
        if (aaa == 000) {
          Serial.print("POZOOOOOOOOOO");
          esX = 0;
          esY = 0;
        }
        else
        {
          posY = aaa;
          recibido = true;
          primeraVez=1;
        }

        // First, stop listening so we can talk
        radio.stopListening();

        // Send the final one back.
        radio.write( receive_payload, len );
        Serial.println(F("Sent response."));

        // Now, resume listening so we catch the next packets.
        radio.startListening();
      }

    }
  }
  // if there is data ready
}

void accion() {
  /*if (posX > 250) {
    int aviso = giro_derecha(5);
    Serial.print("\nAviso: ");Serial.println(aviso);
    if (aviso == 1) {
      avz = 0;
      Serial.println("OK");
      recibido = false;
    }
  }
  else {
    int aviso = avanzar(5);
    if (aviso == 1) {
      avz = 0;
      Serial.println("OK");
      recibido = false;
    }
  }*/
  int aviso = giro_izquierda(5);
    Serial.print("\nAviso: ");Serial.println(aviso);
    if (aviso == 1) {
      avz = 0;
      Serial.println("OK");
      recibido = false;
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


