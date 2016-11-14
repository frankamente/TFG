import serial
import time

arduino=serial.Serial('/dev/ttyUSB0',baudrate=9600, timeout = 3.0)
arduino.close()
arduino.open()
time.sleep(1)
txt=''
i=0
necesito_sensores=1
while True:
  #hago lo que necesite y cuando quiera algo del arduino:
  
  if necesito_sensores==1:
    print "Lectura sensores"
    #var = raw_input("Introducir un Comando: ") # O introduzco un comando o lo envio directamente
    #var = '1' #Lee sensores // probar con 1 '1' y "1"
    arduino.write(b"1")
    time.sleep(0.1)
    while arduino.inWaiting() > 0:
      txt = arduino.readline()
      print txt
      #if i==0:
        izq=int(txt)
        print izq
      #if i==1:
        centro=int(txt)
        print centro
      if i==2:
        der=int(txt)
        print der
      txt = ''
      i=i+1
      necesito_sensores=0
  arduino.close()
