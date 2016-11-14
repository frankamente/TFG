/*Definimos El Trigger, el echo de cada Ultrasonido.*/
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// Definicion de pines de ultrasonidos
#define TRIGGER_PIN1  14  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     15  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN2  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     5  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN3  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN3     7  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN4  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN4     9  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN5   17// Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN5    16   // Arduino pin tied to echo pin on the ultrasonic sensor.

// Definicion de pines de Encoder
#define OUT1  2  // PIN ENTRADA 1 ENCODER
#define OUT2  3  // PIN ENTRADA 2 ENCODER

// Definicion de pines motores
#define IN3  20    // Input3 conectada al pin 5
#define IN4  21    // Input4 conectada al pin 4 
#define ENB  11    // ENB conectada al pin 3 de Arduino
#define IN1  18    // Input3 conectada al pin 5
#define IN2  19    // Input4 conectada al pin 4 
#define ENA  10    // ENB conectada al pin 3 de Arduino

// Tiempos de ejecucion de funciones
#define tsensores  200
#define tmotoreson  600
#define tmotoresoff  100
