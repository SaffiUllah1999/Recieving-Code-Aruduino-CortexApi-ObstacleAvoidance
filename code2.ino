#include <SoftwareSerial.h>
#include <stdio.h>
#include <NewPing.h>

SoftwareSerial xbee(2, 3);

#define echoPin 11 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 12 // attach pin D3 Arduino to pin Trig of HC-SR04
NewPing sonar(trigPin, echoPin);
int distance;
int voteBack;
char c1,c2;
int pin1 = 5;
int pin2 = 6;
int pin3 = 9;
int pin4 = 10;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;

int valup = 0;
int speed = 0;
char tmp;
void setup()
{
    long duration; // variable for the duration of sound wave travel
    int distance;  // variable for the distance measurement

    pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT

    xbee.begin(9600);
    Serial.begin(9600);
    Serial.println("Starting XBee Comunication");
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    speed = 200;
}
void loop()
{
    delay(40);
    distance = sonar.ping_cm();

    if (distance>10 && distance < 50)
    {
        Serial.println("Critical distance less than 50");
        analogWrite(pin1, 0);
        analogWrite(pin2, 0);
        analogWrite(pin3, 0);
        analogWrite(pin4, 0);
        control();
    }
    else
    {
        control();
    }
}

void control()
{
    if (xbee.available())
    {
        tmp = xbee.read();

        if (tmp == 'f')
        {
          voteBack=0;
//          if(voteBack>0){
//            voteBack--;
//          }
//          else{
//            
//          }

            Serial.println("forward pin on");
            digitalWrite(pin1, HIGH); // Forward high
            digitalWrite(pin2, LOW);
            digitalWrite(pin3, LOW);
            digitalWrite(pin4, LOW);
        }

         else if (tmp == 'c ')
        {
             Serial.println("Stopping");
             analogWrite(pin1, 0);
             analogWrite(pin2, 0);
             analogWrite(pin3, 0);
             analogWrite(pin4, 0);
        
        
         }
        else if (tmp == 'l')
        {
          voteBack=0;
//          if(voteBack>0){
//            voteBack--;
//          }
//          else{
//            
//          }
            Serial.println("left pin on");
            digitalWrite(pin3, HIGH); // left
            digitalWrite(pin2, LOW);
            digitalWrite(pin1, LOW);
            digitalWrite(pin4, LOW);
        }

        else if (tmp == 'r')
        {
          voteBack=0;
//          if(voteBack>0){
//            voteBack--;
//            
//          }
//          else{
//            
//          }
            Serial.println("right pin on");
            digitalWrite(pin4, HIGH); // right
            digitalWrite(pin2, LOW);
            digitalWrite(pin3, LOW);
            digitalWrite(pin1, LOW);
        }

        else if (tmp == 'b')
        {
          voteBack++;
//             c1 = xbee.read();
//             c2 = xbee.read();
           
//            
//            Serial.println(c1);
//            Serial.println(c2);
//           
//            if (tmp == c1)
//                if (c1 == c2)
//                {
//                    digitalWrite(pin4, LOW);
//                    digitalWrite(pin3, LOW);
//                    digitalWrite(pin1, LOW);
//                    digitalWrite(pin2, HIGH); // backward on
//                }
//                else
//                {
//                    analogWrite(pin1, 0);
//                    analogWrite(pin2, 0);
//                    analogWrite(pin3, 0);
//                    analogWrite(pin4, 0);
//                }
//
//            else {
//                
//                    analogWrite(pin1, 0);
//                    analogWrite(pin2, 0);
//                    analogWrite(pin3, 0);
//                    analogWrite(pin4, 0);
//
//            }

//             voteBack++;

             if (voteBack > 9)
             {
                 Serial.println("backward pin on");
                 digitalWrite(pin2, HIGH);
                 digitalWrite(pin4, LOW);
                 digitalWrite(pin3, LOW);
                 digitalWrite(pin1, LOW);
                 //voteBack = 0;
             }
             else
             {
                 analogWrite(pin1, 0);
                 analogWrite(pin2, 0);
                 analogWrite(pin3, 0);
                 analogWrite(pin4, 0);
             }
        }
    }
//    delay(50);
}
