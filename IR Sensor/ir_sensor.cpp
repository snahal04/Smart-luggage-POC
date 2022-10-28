//ir sensor code
/*
 * created by Somya Sinha
 * IR Sensor
 *
    IR Sensor Pins:
        VCC: +5VDC
        OUT : Output Pin as  - Pin11
        GND: GND
 */

//IR sensor range is 2-7 cm.

int irpin = 3;
int led = 13;

void setup()
{
  pinMode(led,OUTPUT);  // configuring pin 13 as output pin to glow led
  pinMode(irpin,INPUT);    //configuring pin 3 as input pin to detect object
  Serial.begin(9600);  //baudrate
}
void loop()
{
  if(digitalRead(irpin)==LOW) //If object is not detected
  {
    digitalWrite(led,HIGH); //turn the led high
    delay(10);   //delay of 10 microseconds
  }
  else
  {
     digitalWrite(led,LOW);
    delay(10);   //delay of 10 microseconds
    
  }
  
}
