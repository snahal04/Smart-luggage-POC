/* Human Following + Obstacle avoiding Robot
 *  Team : 
 *  Snahal Kumar
 *  Somya Sinha
 *  Sagar Jha
 *  Mentor : Dr.Sumeet Gupta
 *  
 */

/* Recommended libraries
 *  https://downloads.arduino.cc/libraries/github.com/adafruit/Adafruit_Motor_Shield_library-1.0.1.zip
 *  Add this Zip File in Sketch > include Library > Add .zip Library.
 *  Install the libraries Tools > Manage Libraries > Adafruit Motor Shield V2 & V1 both (Install).
 */

#include<AFMotor.h>

/*  Motor Connections(M)
 *          __
 *    M1(O):  :(O)M2
 *         |  |
 *         |  |
 *    M3(O):__:(O)M4
 *   
 */
 
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
