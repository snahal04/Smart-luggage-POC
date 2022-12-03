

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
      motor1(O):  :(O)motor4
           |  |
           |  |
      motor2(O):__:(O)motor3

*/
#include <Servo.h> //To Control Servo motor

#define MAX_DISTANCE 200
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

boolean goesForward = false;
boolean goesBackward = false;
// int distance = 100;
unsigned int speedSet = 0;

/* Declaring Middle Ultrasonic Pins */
#define Mtrig A1
#define Mecho A0
unsigned int Mduration = 0, Mdistance = 0;

/* Declaring Right Ultrasonic Pins */
// #define Rtrig A2
// #define Recho A3
// not using
// unsigned int Rduration = 0, Rdistance = 0;

/* Declaring left Ultrasonic Pins */
// #define Ltrig A4
// #define Lecho A5
// not using
// unsigned int Lduration = 0, Ldistance = 0;

#define RIGHT A2 // Right IR sensor connected to analog pin A2 of Arduino Uno:
#define LEFT A3  // Left IR sensor connected to analog pin A3 of Arduino Uno:

Servo myservo;
int pos = 0;

unsigned int Right_Value = 0; // Variable to store Right IR sensor value:
unsigned int Left_Value = 0;  // Variable to store Left IR sensor value:
unsigned int count = 0;
unsigned int R_S = 0;
unsigned int L_S = 0;

void setup()
{

    // motor1.setSpeed(255); // Motor Maximum Speed Configured.
    // // motor1.run(RELEASE);  // Motor is Configured in Release mode.
    // motor2.setSpeed(255);
    // // motor2.run(RELEASE);
    // motor3.setSpeed(255);
    // // motor3.run(RELEASE);
    // motor4.setSpeed(255);
    // // motor4.run(RELEASE);

    /* Configure input and output port of sensors */
    pinMode(Mtrig, OUTPUT);
    pinMode(Mecho, INPUT);
    // Right
    // pinMode(Rtrig, OUTPUT);
    // pinMode(Recho, INPUT);
    // // Left
    // pinMode(Ltrig, OUTPUT);
    // pinMode(Lecho, INPUT);

    Serial.begin(9600); // initailize serial communication at 9600 bits per second:
    myservo.attach(10); // servo attached to pin 10 of Arduino UNO

    {
        for (pos = 90; pos <= 180; pos += 1)
        {                       // goes from 90 degrees to 180 degrees:
            myservo.write(pos); // tell servo to move according to the value of 'pos' variable:
            delay(15);          // wait 15ms for the servo to reach the position:
        }
        for (pos = 180; pos >= 0; pos -= 1)
        {                       // goes from 180 degrees to 0 degrees:
            myservo.write(pos); // tell servo to move according to the value of 'pos' variable:
            delay(15);          // wait 15ms for the servo to reach the position:
        }
        for (pos = 0; pos <= 90; pos += 1)
        {                       // goes from 180 degrees to 0 degrees:
            myservo.write(pos); // tell servo to move according to the value of 'pos' variable:
            delay(15);          // wait 15ms for the servo to reach the position:
        }
    }
    myservo.write(90);
    delay(2000);
    pinMode(RIGHT, INPUT); // set analog pin RIGHT as an input:
    pinMode(LEFT, INPUT);  // set analog pin RIGHT as an input:
}

void loop()
{
    int distanceR = 0;
    int distanceL = 0;
    delay(40);
    distanceMeasure();

    //######################################################

    // if ((Ldistance < 12 && Ldistance > 5 && Rdistance < 12 && Rdistance > 5) || Mdistance < 15 && Mdistance > 5) // count = 0 means first start so accelerate then move constant
    // {
    //     // count = 1;
    //     // moveForward();
    //     velocity();
    // }
    // else if ((Mdistance < 5 || Ldistance < 5 || Rdistance < 5)) // when robot is moving and person moves back withn 50 cm then robot moves back
    // {
    //     // count = 0;
    //     moveBack();
    // }
    // else if (Ldistance < 12 && Rdistance < 12 && Mdistance < 10 && count == 1) // constant movement
    // {
    //     // count = 2;
    //     velocity();
    // }

    //     if (Ldistance > 120 && Rdistance > 120 && Mdistance > 100) // Human is 120 cm far from robot then robot will first speeds up fro 3 second and still if it not gets in range then stops
    //     {
    //         stop();
    //     }
    // else if (Ldistance > 12 && Rdistance > 12 && Mdistance > 14 )
    // {
    //     instantstop();
    // }
    // else if (Ldistance < 12 && Ldistance > 5 && Rdistance > 12 && Mdistance < 14 && Mdistance > 5 )
    // {
    //     moveLeft();
    // }
    // else if (Rdistance < 12 && Rdistance > 5 && Ldistance > 12 && Mdistance < 14 && Mdistance > 5 )
    // {
    //     moveRight();
    // }
    // else if (Ldistance == 5 && Rdistance == 5 && Mdistance == 5 )
    // {
    //     count = 0;
    //     instantstop();
    // }
    // if (Mdistance < 10 && Mdistance > 5)
    // {
    //     velocity();
    // }
    // else if (Mdistance < 5)
    // {
    //     moveBack();
    // }
    // else if (Mdistance > 10){
    //     instantstop();
    // }
    Right_Value = digitalRead(RIGHT); // read the value from Right IR sensor:
    Left_Value = digitalRead(LEFT);   // read the value from Left IR sensor:

    Serial.print("RIGHT : ");
    Serial.println(Right_Value);
    Serial.print("LEFT : ");
    Serial.println(Left_Value);

    if (Mdistance < 40 && Mdistance > 15 && (Right_Value == 1) && (Left_Value == 1))
    {
        moveForward();
        // delay(2000);
        Serial.println("******************FORWARD");
    }
    else if ((Right_Value == 0 && Left_Value == 1) || (Right_Value == 1 && Left_Value == 0))
    {
        moveStop();
        // count++;
        Serial.print("RIGHT : ");
        Serial.println(Right_Value);
        Serial.print("LEFT : ");
        Serial.println(Left_Value);
        if ((Right_Value == 0 && Left_Value == 1))
        {
            // delay(1000);
            Serial.println("***************** Right first");
            while (Left_Value)
            {
                Left_Value = digitalRead(LEFT);
                delay(20);
            }
            Serial.println("***************** START ");
            // delay(1000);
        }
        else if ((Right_Value == 1 && Left_Value == 0))
        {
            // delay(1000);
            Serial.println("*****************Left First ");
            while (Right_Value)
            {
                Right_Value = digitalRead(RIGHT);
                delay(20);
            }
            Serial.println("***************** START");
            // delay(1000);
        }

        // turnLeft();
        //        delay(2000);
        // Serial.println("******************RIGHT");
    }
    // else if ((Right_Value == 1) && (Left_Value == 0))
    // {
    //     // turnRight();
    //     //        delay(2000);
    //     // Serial.println("******************LEFT");
    // }
    else if (Mdistance < 10 && (Right_Value == 0) && (Left_Value == 0))
    {
        moveBackward();
        // delay(2000);
        Serial.println("******************BACK");
    }
    else if (Mdistance > 40 && (Right_Value == 1) && (Left_Value == 1))
    {
        moveStop();
        delay(100);
    // here:
        distanceR = lookRight();
        delay(500);
        distanceL = lookLeft();
        delay(500);
        // if (distanceL < 40)
        // {
        //     turnLeft(200);
        //     moveStop();
        // }
        // else if (distanceR < 40)
        // {
        //     turnRight(200);
        //     moveStop();
        // }
        // else
        // {
        //     goto here;
        // }
        // F_Right();
    }
    else
    {
        moveStop();
        // delay(2000);
        Serial.println("******************STOP");
    }

    //######################################################
}

void distanceMeasure()
{
    // Middle ultrasonic
    digitalWrite(Mtrig, LOW);
    delayMicroseconds(2);
    digitalWrite(Mtrig, HIGH);
    delayMicroseconds(6);
    digitalWrite(Mtrig, LOW);

    // Read the signal from the sensor
    pinMode(Mecho, INPUT);
    Mduration = pulseIn(Mecho, HIGH); // in microsecond

    // Convert the time into a distance
    //##Distance = (Time x speed of sound in cm/ms ) / 2(sound has to travel back and forth.)
    Mdistance = (Mduration / 2) * 0.0343; // Divide by 29.1 or multiply by 0.0343
    Serial.print(" Middle : ");
    Serial.println(Mdistance);

    // digitalWrite(Rtrig, LOW);
    // delayMicroseconds(2);
    // digitalWrite(Rtrig, HIGH);
    // delayMicroseconds(6);
    // digitalWrite(Rtrig, LOW);

    // // Read the signal from the sensor
    // pinMode(Recho, INPUT);
    // Rduration = pulseIn(Recho, HIGH); // in microsecond

    // // Convert the time into a distance
    // //##Distance = (Time x speed of sound in cm/ms ) / 2(sound has to travel back and forth.)
    // Rdistance = (Rduration / 2) * 0.0343; // Divide by 29.1 or multiply by 0.0343
    // Serial.print(" Right : ");
    // Serial.println(Rdistance);

    // digitalWrite(Ltrig, LOW);
    // delayMicroseconds(2);
    // digitalWrite(Ltrig, HIGH);
    // delayMicroseconds(6);
    // digitalWrite(Ltrig, LOW);

    // // Read the signal from the sensor
    // pinMode(Mecho, INPUT);
    // Lduration = pulseIn(Lecho, HIGH); // in microsecond
    // // Convert the time into a distance
    // //##Distance = (Time x speed of sound in cm/ms ) / 2(sound has to travel back and forth.)
    // Ldistance = (Lduration / 2) * 0.0343; // Divide by 29.1 or multiply by 0.0343
    // Serial.print(" left : ");
    // Serial.println(Ldistance);

    // Not Needed
    delay(2);
}

void moveStop()
{
    goesForward = false;
    goesBackward = false;
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

void moveForward()
{

    if (!goesForward)
    {
        Serial.println("!!!!!!!!!!!!     F     !!!!!!!!!!!!!!");
        goesForward = true;
        goesBackward = false;
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
        for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
        {
            motor1.setSpeed(speedSet);
            motor2.setSpeed(speedSet);
            motor3.setSpeed(speedSet);
            motor4.setSpeed(speedSet);
            delay(5);
        }
    }
}

void moveBackward()
{
    if (!goesBackward)
    {
        Serial.println("!!!!!!!!!!!!     B     !!!!!!!!!!!!!!");
        goesForward = false;
        goesBackward = true;
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
        for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
        {
            motor1.setSpeed(speedSet);
            motor2.setSpeed(speedSet);
            motor3.setSpeed(speedSet);
            motor4.setSpeed(speedSet);
            delay(5);
        }
    }
}

// void moveback()
// {
//     motor1.run(BACKWARD);
//     motor2.run(BACKWARD);
//     motor3.run(BACKWARD);
//     motor4.run(BACKWARD);
//     delay(100);
//     // motor1.run(FORWARD);
//     // motor2.run(FORWARD);
//     // motor3.run(FORWARD);
//     // motor4.run(FORWARD);
// }

int turnRight(int z)
{
    Serial.println("******* RIGHT TURN ********");
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(z);
    //    motor1.run(FORWARD);
    //    motor2.run(FORWARD);
    //    motor3.run(FORWARD);
    //    motor4.run(FORWARD);
}

int turnLeft(int z)
{
    Serial.println("******* LEFT TURN ********");
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    delay(z);
    //    motor1.run(FORWARD);
    //    motor2.run(FORWARD);
    //    motor3.run(FORWARD);
    //    motor4.run(FORWARD);
}

// void moveForward()
// {
//     // Accelerate FORWARD
//     motor1.run(FORWARD);
//     motor2.run(FORWARD);
//     motor3.run(FORWARD);
//     motor4.run(FORWARD);

//     // To avoid shock on start we accelerate it slowely.
//     for (i = 100; i < 255; i++)
//     {
//         motor1.setSpeed(i);
//         motor2.setSpeed(i);
//         motor3.setSpeed(i);
//         motor4.setSpeed(i);
//         // ( 30 usec * 100 )/1000 = 3 sec to accelerate
//         delay(10);
//     }
// }

// void velocity()
// {
//     motor1.run(FORWARD);
//     motor2.run(FORWARD);
//     motor3.run(FORWARD);
//     motor4.run(FORWARD);
//     motor1.setSpeed(255);
//     motor2.setSpeed(255);
//     motor3.setSpeed(255);
//     motor4.setSpeed(255);
//     // delay(1000);
// }

// void findServo_Right()
// {
//     unsigned int c = 0;
//     while (Mdistance > 50)
//     {
//         if (c == 1)
//         {
//             for (int i = 40; i <= 90; i++)
//             {
//                 myservo.write(i);
//                 delay(15);
//             }
//             delay(30);
//             distanceMeasure();
//             if(Mdistance < 50){return;}
//             findServo_Left();
//         }
//         for (int i = 90; i > 40; i -= 1)
//         {
//             myservo.write(i);
//             delay(15);
//         }
//         ++c;
//         delay(1000);
//         distanceMeasure();
//     }
//     for (int i = 40; i < 90; i += 1)
//     {
//         myservo.write(i);
//     }
//     turnRight(500);
// }

// void findServo_Left()
// {
//     myservo.write(90);
//     // unsigned int x = 90;
//     unsigned int c = 0;
//     while (Mdistance > 50)
//     {
//         if (c == 1)
//         {
//             for (int i = 140; i >= 90; i--)
//             {
//                 myservo.write(i);
//                 delay(15);
//             }
//             delay(30);
//             distanceMeasure();
//             if(Mdistance < 50){return;}
//             findServo_Right();
//         }
//         for (int i = 90; i <= 140; i += 1)
//         {
//             myservo.write(i);
//             delay(15);
//         }
//         // x = x + 30;
//         ++c;
//         delay(1000);
//         distanceMeasure();
//     }
//     for (int i = 140; i >= 90; i -= 1)
//     {
//         myservo.write(i);
//         delay(15);
//     }
//     // myservo.write(90);
//     turnLeft(500);
// }

// void F_Right(){
//     myservo.write(45);
//     distanceMeasure();
//     delay(50);
//     if(Mdistance < 40){
//         turnRight(100);
//         return;
//     }
//     myservo.write(90);
//     delay(10);
//     myservo.write(135);
//     distanceMeasure();
//     delay(50)
//     if(Mdistance < 40){
//         turnLeft();
//         return;
//     }
// }

int lookRight()
{
    myservo.write(40);
    delay(500);
    distanceMeasure();
    delay(500);
    if (Mdistance < 40)
    {
        myservo.write(90);
        turnRight(200);
        return 1;
    }
    myservo.write(90);
    delay(500);
    if (Mdistance < 40)
    {
        moveForward();
        return 0;
    }
    else{
        return 2;
    }
    // return Mdistance;
}

int lookLeft()
{
    myservo.write(140);
    delay(500);
    distanceMeasure();
    delay(500);
    if (Mdistance < 40)
    {
        turnLeft(200);
        return;
    }
    myservo.write(90);
    delay(500);
    if (Mdistance < 40)
    {
        moveForward();
        return;
    }
    // delay(100);
}

// void moveLeft()
// {
//     motor1.run(BACKWARD);
//     motor1.setSpeed(255);

//     motor2.run(BACKWARD);
//     motor2.setSpeed(255);

//     motor3.run(FORWARD);
//     motor3.setSpeed(255);

//     motor4.run(FORWARD);
//     motor4.setSpeed(255);
//     delay(1000);
// }

// void moveRight()
// {
//     motor3.run(BACKWARD);
//     motor3.setSpeed(255);

//     motor4.run(BACKWARD);
//     motor4.setSpeed(255);

//     motor1.run(FORWARD);
//     motor1.setSpeed(255);

//     motor2.run(FORWARD);
//     motor2.setSpeed(255);
//     delay(1000);
// }

// void moveBack()
// {
//     // Accelerate FORWARD
//     motor1.run(BACKWARD);
//     motor2.run(BACKWARD);
//     motor3.run(BACKWARD);
//     motor4.run(BACKWARD);
//     motor1.setSpeed(255);
//     motor2.setSpeed(255);
//     motor3.setSpeed(255);
//     motor4.setSpeed(255);
//     while (Mdistance < 5 || Ldistance < 5 || Rdistance < 5)
//     {
//         distanceMeasure();
//         motor1.setSpeed(255);
//         motor2.setSpeed(255);
//         motor3.setSpeed(255);
//         motor4.setSpeed(255);
//         delay(10);
//     }

//     // // To avoid shock on start we accelerate it slowely.
//     // for (i = 0; i < 100; i++)
//     // {
//     //     motor1.setSpeed(i);
//     //     motor2.setSpeed(i);
//     //     motor3.setSpeed(i);
//     //     motor4.setSpeed(i);
//     //     // ( 30 usec * 100 )/1000 = 3 sec to accelerate
//     //     delay(30);
//     // }
//     // delay(500);
// }

// // void stop()
// // {
// //     motor1.run(FORWARD);
// //     motor2.run(FORWARD);
// //     motor3.run(FORWARD);
// //     motor4.run(FORWARD);
// //     motor1.setSpeed(255);
// //     motor2.setSpeed(255);
// //     motor3.setSpeed(255);
// //     motor4.setSpeed(255);
// //     delay(1000);
// // distanceMeasure();
// // if (Ldistance < 12 || Rdistance < 12 || Mdistance < 10)
// // {
// //     // count =0;
// //     loop();
// // }
// // else
// // {
// //     // motor1.run(FORWARD);
// //     // motor2.run(FORWARD);
// //     // motor3.run(FORWARD);
// //     // motor4.run(FORWARD);
// //     for (int j = 250; j >= 0; j--)
// //     {
// //         motor1.setSpeed(j);
// //         motor2.setSpeed(j);
// //         motor3.setSpeed(j);
// //         motor4.setSpeed(j);
// //         delay(20);
// //     }
// //     while (Ldistance > 120 && Rdistance > 120 && Mdistance > 100)
// //     {
// //         distanceMeasure();
// //         motor1.run(RELEASE);
// //         motor2.run(RELEASE);
// //         motor3.run(RELEASE);
// //         motor4.run(RELEASE);
// //         motor1.setSpeed(0);
// //         motor2.setSpeed(0);
// //         motor3.setSpeed(0);
// //         motor4.setSpeed(0);
// //         count = 0;
// //     }
// // }
// // }

// void instantstop()
// {
//     motor1.run(RELEASE);
//     motor2.run(RELEASE);
//     motor3.run(RELEASE);
//     motor4.run(RELEASE);
//     motor1.setSpeed(0);
//     motor2.setSpeed(0);
//     motor3.setSpeed(0);
//     motor4.setSpeed(0);
//     // while ((Ldistance == 50 && Rdistance == 50) || Mdistance == 50)
//     // {
//     //     distanceMeasure();
//     //     motor1.setSpeed(0);
//     //     motor2.setSpeed(0);
//     //     motor3.setSpeed(0);
//     //     motor4.setSpeed(0);
//     //     count = 0;
//     // }
// }

// void loop()
// {
//     distanceMeasure();

//     //######################################################

//     // if ((Ldistance < 12 && Ldistance > 5 && Rdistance < 12 && Rdistance > 5) || Mdistance < 15 && Mdistance > 5) // count = 0 means first start so accelerate then move constant
//     // {
//     //     // count = 1;
//     //     // moveForward();
//     //     velocity();
//     // }
//     // else if ((Mdistance < 5 || Ldistance < 5 || Rdistance < 5)) // when robot is moving and person moves back withn 50 cm then robot moves back
//     // {
//     //     // count = 0;
//     //     moveBack();
//     // }
//     // else if (Ldistance < 12 && Rdistance < 12 && Mdistance < 10 && count == 1) // constant movement
//     // {
//     //     // count = 2;
//     //     velocity();
//     // }

//     //     if (Ldistance > 120 && Rdistance > 120 && Mdistance > 100) // Human is 120 cm far from robot then robot will first speeds up fro 3 second and still if it not gets in range then stops
//     //     {
//     //         stop();
//     //     }
//     // else if (Ldistance > 12 && Rdistance > 12 && Mdistance > 14 )
//     // {
//     //     instantstop();
//     // }
//     // else if (Ldistance < 12 && Ldistance > 5 && Rdistance > 12 && Mdistance < 14 && Mdistance > 5 )
//     // {
//     //     moveLeft();
//     // }
//     // else if (Rdistance < 12 && Rdistance > 5 && Ldistance > 12 && Mdistance < 14 && Mdistance > 5 )
//     // {
//     //     moveRight();
//     // }
//     // else if (Ldistance == 5 && Rdistance == 5 && Mdistance == 5 )
//     // {
//     //     count = 0;
//     //     instantstop();
//     // }
//     if (Mdistance < 10 && Mdistance > 5)
//     {
//         velocity();
//     }
//     else if (Mdistance < 5)
//     {
//         moveBack();
//     }
//     else if (Mdistance > 10){
//         instantstop();
//     }

//     //######################################################
// }

// /*
//  * ######### SPEED OF EACH MOTOR ########
//  */
// // void speedmotor1(int speed1, int delay1)
// // {
// //     for (int j = 0; j < speed1; j++)
// //     {
// //         motor1.setSpeed(j);
// //         delay(delay1);
// //     }
// // }
// // void speedmotor2(int speed1, int delay1)
// // {
// //     for (int j = 0; j < speed1; j++)
// //     {
// //         motor2.setSpeed(j);
// //         delay(delay1);
// //     }
// // }
// // void speedmotor3(int speed1, int delay1)
// // {
// //     for (int j = 0; j < speed1; j++)
// //     {
// //         motor3.setSpeed(j);
// //         delay(delay1);
// //     }
// // }
// // void speedmotor4(int speed1, int delay1)
// // {
// //     for (int j = 0; j < speed1; j++)
// //     {
// //         motor4.setSpeed(j);
// //         delay(delay1);
// //     }
// // }

/*############################################*/
