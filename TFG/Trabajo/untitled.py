#EL OK SIRVE

import serial
import time

arduino=serial.Serial('/dev/ttyUSB0',baudrate=9600, timeout = 3.0)
arduino.close()
arduino.open()
time.sleep(1)
txt=''
i=0
z=3 # Si quiero enviar variable
z=byte([z])
necesito_sensores=1
while True:
  #hago lo que necesite y cuando quiera algo del arduino:
  
  if necesito_sensores==1:
    print "Lectura sensores"
    #var = raw_input("Introducir un Comando: ") # O introduzco un comando o lo envio directamente
    #var = '1' #Lee sensores // probar con 1 '1' y "1"
    arduino.write(b"3")
    arduino.write(z)  # si quiero enviar variable
    time.sleep(0.1)
    while arduino.inWaiting() > 0:
      txt = arduino.readline()
      print txt
      if i==0:
        izq=txt
        print izq
      if izq=="OK":
        print "SIRVE"
        break
      txt = ''
      #i=i+1
      necesito_sensores=0
    print "BREAK SIRVE"
  arduino.close()
