/*
 * created by Snahal Kumar
 * Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 
int tPin = 11;    // Trigger
int ePin = 12;    // Echo
long duration, cm;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600); //baudrate
  
  //Define inputs and outputs
  pinMode(tPin, OUTPUT);
  pinMode(ePin, INPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(tPin, LOW);
  delayMicroseconds(5);
  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW);
 
  // Read the signal from the sensor
  pinMode(ePin, INPUT);
  duration = pulseIn(ePin, HIGH); //in microsecond
 
  // Convert the time into a distance 
  //##Distance = (Time x speed of sound in cm/ms ) / 2(sound has to travel back and forth.)
  cm = (duration/2)* 0.0343;     // Divide by 29.1 or multiply by 0.0343
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}
