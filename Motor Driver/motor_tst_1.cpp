/* Human Following + Obstacle avoiding Robot
    Team :
    Snahal Kumar
    Somya Sinha
    Sagar Jha
    Mentor : Dr.Sumeet Gupta

*/

/* Recommended libraries
    https://downloads.arduino.cc/libraries/github.com/adafruit/Adafruit_Motor_Shield_library-1.0.1.zip
    Add this Zip File in Sketch > include Library > Add .zip Library.
    Install the libraries Tools > Manage Libraries > Adafruit Motor Shield V2 & V1 both (Install).
*/

#include <AFMotor.h>

/*  Motor Connections(M)
            __
      M1(O):  :(O)M2
           |  |
           |  |
      M3(O):__:(O)M4

*/

AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);
int i = 0;

/* Declaring Middle Ultrasonic Pins */
#define Mtrig A0;
#define Mecho A1;
int Mduration = 0, Mdistance = 0;

/* Declaring Right Ultrasonic Pins */
#define Rtrig A2;
#define Recho A3;
int Rduration = 0, Rdistance = 0;

/* Declaring left Ultrasonic Pins */
#define Ltrig A4;
#define Lecho A5;
int Lduration = 0, Ldistance = 0;

void setup()
{

    M1.setSpeed(255); // Motor Maximum Speed Configured.
    M1.run(RELEASE);  // Motor is Configured in Release mode.
    M2.setSpeed(255);
    M2.run(RELEASE);
    M3.setSpeed(255);
    M3.run(RELEASE);
    M4.setSpeed(255);
    M4.run(RELEASE);

    /* Configure input and output port of sensors */
    pinMode(Mtrig, OUTPUT);
    pinMode(Mecho, INPUT);
    // Right
    pinMode(Rtrig, OUTPUT);
    pinMode(Recho, INPUT);
    // Left
    pinMode(Ltrig, OUTPUT);
    pinMode(Lecho, INPUT);
    Serial.begin(9600); // Settng baudrate
}

void loop()
{

    //Middle ultrasonic 
    digitalWrite(Mtrig, LOW);
    delayMicroseconds(5);
    digitalWrite(Mtrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Mtrig, LOW);

    // Read the signal from the sensor
    pinMode(Mecho, INPUT);
    Mduration = pulseIn(Mecho, HIGH); // in microsecond

    // Convert the time into a distance
    //##Distance = (Time x speed of sound in cm/ms ) / 2(sound has to travel back and forth.)
    Mdistance = (Mduration / 2) * 0.0343; // Divide by 29.1 or multiply by 0.0343

    digitalWrite(Rtrig, LOW);
    delayMicroseconds(5);
    digitalWrite(Rtrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Rtrig, LOW);

    // Read the signal from the sensor
    pinMode(Recho, INPUT);
    Rduration = pulseIn(Recho, HIGH); // in microsecond

    // Convert the time into a distance
    //##Distance = (Time x speed of sound in cm/ms ) / 2(sound has to travel back and forth.)
    Rdistance = (Rduration / 2) * 0.0343; // Divide by 29.1 or multiply by 0.0343

    digitalWrite(Ltrig, LOW);
    delayMicroseconds(5);
    digitalWrite(Ltrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Ltrig, LOW);

    // Read the signal from the sensor
    pinMode(Mecho, INPUT);
    Lduration = pulseIn(Lecho, HIGH); // in microsecond

    // Convert the time into a distance
    //##Distance = (Time x speed of sound in cm/ms ) / 2(sound has to travel back and forth.)
    Ldistance = (Lduration / 2) * 0.0343; // Divide by 29.1 or multiply by 0.0343
}

void moveForward()
{
    // Accelerate FORWARD
    M1.run(FORWARD);
    M2.run(FORWARD);
    M3.run(FORWARD);
    M4.run(FORWARD);

    // To avoid shock on start we accelerate it slowely.
    for (i = 0; i < 100; i++)
    {
        M1.setSpeed(i);
        M2.setSpeed(i);
        M3.setSpeed(i);
        M4.setSpeed(i);
        // ( 30 usec * 100 )/1000 = 3 sec to accelerate
        delay(30);
    }
}

void moveLeft()
{
    M1.run(BACKWARD);
    M1.setSpeed(50);

    M3.run(BACKWARD);
    M3.setSpeed(70);

    M2.run(FORWARD);
    M2.setSpeed(120);

    M4.run(FORWARD);
    M4.setSpeed(120);
    delay(200);
}

void moveRight()
{
    M2.run(BACKWARD);
    M2.setSpeed(50);

    M4.run(BACKWARD);
    M4.setSpeed(70);

    M1.run(FORWARD);
    M1.setSpeed(120);

    M3.run(FORWARD);
    M3.setSpeed(120);
    delay(200);
}

void moveBack()
{
    // Accelerate FORWARD
    M1.run(BACKWARD);
    M2.run(BACKWARD);
    M3.run(BACKWARD);
    M4.run(BACKWARD);
    M1.setSpeed(50);
    M2.setSpeed(50);
    M3.setSpeed(50);
    M4.setSpeed(50);
    while ()

    // // To avoid shock on start we accelerate it slowely.
    // for (i = 0; i < 100; i++)
    // {
    //     M1.setSpeed(i);
    //     M2.setSpeed(i);
    //     M3.setSpeed(i);
    //     M4.setSpeed(i);
    //     // ( 30 usec * 100 )/1000 = 3 sec to accelerate
    //     delay(30);
    // }
    // delay(500);
}

/*
 * ######### SPEED OF EACH MOTOR ########
 */
void speedM1(int speed1, int delay1)
{
    for (int j = 0; j < speed1; j++)
    {
        M1.setSpeed(j);
        delay(delay1);
    }
}
void speedM2(int speed1, int delay1)
{
    for (int j = 0; j < speed1; j++)
    {
        M2.setSpeed(j);
        delay(delay1);
    }
}
void speedM3(int speed1, int delay1)
{
    for (int j = 0; j < speed1; j++)
    {
        M3.setSpeed(j);
        delay(delay1);
    }
}
void speedM4(int speed1, int delay1)
{
    for (int j = 0; j < speed1; j++)
    {
        M4.setSpeed(j);
        delay(delay1);
    }
}

/*############################################*/
