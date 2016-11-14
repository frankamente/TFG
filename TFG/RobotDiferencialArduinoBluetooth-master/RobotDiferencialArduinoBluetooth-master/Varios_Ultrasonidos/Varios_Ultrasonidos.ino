#include <NewPing.h>
/*Definimos El Trigger, el echo de cada Ultrasonido.*/


#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

/*#define TRIGGER_PIN1  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     11  // Arduino pin tied to echo pin on the ultrasonic sensor.*/

#define TRIGGER_PIN1  16  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     17  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN2  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     5  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN3  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN3     7  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN4  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN4     9  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN5  0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN5     1  // Arduino pin tied to echo pin on the ultrasonic sensor.

/* Definimos cada ultrasonido*/

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar5(TRIGGER_PIN5, ECHO_PIN5, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS1 = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping1: ");
  Serial.print(uS1 / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  
  unsigned int uS2 = sonar2.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping2: ");
  Serial.print(uS2 / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");

  unsigned int uS3 = sonar3.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping3: ");
  Serial.print(uS3 / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  
  unsigned int uS4 = sonar4.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping4: ");
  Serial.print(uS4 / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  
    unsigned int uS5 = sonar5.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping5: ");
  Serial.print(uS5 / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  

    
}
