#include<Servo.h>//put the servo motor library
Servo myservo;//put a name for servo motor(you can use any name)
#include<NewPing.h>//put the Ultrasonic sensor library
//define the pins for Ultrasonic sensor trig and echo.You can use any output pin from arduino board 
#define trig 2
#define echo 4
// define the pin of motor driver[L298N/L293D IC]
#define MO1 10//'MO1' mean motor one
#define MO2 11//'MO2' mean motor two
#define MO3 12//'MO3' mean motor three
#define MO4 13//'MO4' mean motor four
int pos = 90;
void setup() {
myservo.attach(9);//attach a pin for servo motor
Serial.begin(9600);//command to start serial monitor
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
//we get below pins as a output from motor driver.So,these pins mode is output.When we write a arduino code we should mention the mode of pin ,like pinMode,OUTPUT or INPUT.
pinMode(MO1,OUTPUT);
pinMode(MO2,OUTPUT);
pinMode(MO3,OUTPUT);
pinMode(MO4,OUTPUT);
myservo.write(pos);//servo motor can turn 0-180 degrees.We should turn the middle position[90],because the ulatrasonic sensor we placed in top of the servo motor
}

void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  long t =pulseIn(echo,HIGH);

  long cm =t/29.1/2;
  Serial.print(cm);
  Serial.println("cm");
//HIGH mean is 'on' and LOW mean is 'off'
  if(cm < 15){
    //when distance < 15cm stopped car 
    digitalWrite(MO1,LOW);//off
    digitalWrite(MO2,LOW);//off
    digitalWrite(MO3,LOW);//off
    digitalWrite(MO4,LOW);//off
    delay(100);//put a delay
    myservo.write(180);
    myservo.write(0);
    myservo.write(90);
    delay(500);
    //this time car is turning right.It also can change how you connect these MO1,MO2,MO3,MO3 pins
    digitalWrite(MO1,LOW);//off
    digitalWrite(MO2,HIGH);//turn back
    digitalWrite(MO3,LOW);//turn front
    digitalWrite(MO4,HIGH);//off
    delay(500);//put a delay
     digitalWrite(MO1,LOW);//off
    digitalWrite(MO2,LOW);//off
    digitalWrite(MO3,LOW);//off
    digitalWrite(MO4,LOW);//off
}
else{
    //when distance > 15cm car is going straight
    digitalWrite(MO1,HIGH);//on
    digitalWrite(MO2,LOW);//off
    digitalWrite(MO3,HIGH);//on
    digitalWrite(MO4,LOW);//off
}
}
/* 
 *  MO1 and MO3 is Right Hand Side motors pins.MO2 and MO4 is Left Hand Side motors pins.
 */
