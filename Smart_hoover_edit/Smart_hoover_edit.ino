#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <Servo.h>
Servo myservo;
  int i=0,pos;
 
#define in1 A3 //Motor1  L293D Pin in1 
#define in2 A2 //Motor1  L293D Pin in1 
#define in3 A1 //Motor2  L293D Pin in1 
#define in4 A0 //Motor2  L293D Pin in1 

#define trigPin1 A4       //front side ultro sonic sensor
#define echoPin1 A5
#define trigPin2 13
#define echoPin2 12

long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;

void setup()
{
myservo.attach(9);// servo motor in connected in which pin 
Serial.begin (9600);//serial communication
lcd.begin(16, 2);// (16/2) dispaly 
lcd.setCursor(0, 0);
lcd.print(" Auto- Cleaning ");
lcd.setCursor(0, 1);
lcd.print("     Robot      ");
pinMode(trigPin1, OUTPUT);
pinMode(11, OUTPUT);//relay
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);

pinMode(in1, OUTPUT); // declare as output for L293D Pin in1 
pinMode(in2, OUTPUT); // declare as output for L293D Pin in2 
pinMode(in3, OUTPUT); // declare as output for L293D Pin in3   
pinMode(in4, OUTPUT); // declare as output for L293D Pin in4 
}

void loop() {
 for(pos=0;pos<=180;pos++){
myservo.write(pos);
delay(15); }
delay(500);
//speed of the motor
digitalWrite(11,HIGH);
lcd.setCursor(0, 0);
lcd.print(" Auto- Cleaning "); //lcd first line display
lcd.setCursor(0, 1);
lcd.print("     Robot      "); //lcd second line display
SonarSensor(trigPin1, echoPin1);
FrontSensor = distance;
SonarSensor(trigPin2, echoPin2);
BackSensor = distance;

Serial.print("F:");
Serial.println(FrontSensor); 
Serial.print("  B:");
Serial.println(BackSensor);
delay(300); 
for(pos=180;pos>=0;pos--){
myservo.write(pos);
delay(15); }
delay(500);
//speed of the motor //speed of the motor
if( FrontSensor>20 && BackSensor>20)
{
  Serial.println("forword");
  forword();
}

if( FrontSensor<20 && BackSensor<20)
{
  Stop();
  Serial.println("reverse");
  reverse();
  delay(2000);
  turnRight();
  delay(2000);
}

if(FrontSensor<20)
{
  Serial.println("right ");
  turnRight();
}

if(BackSensor<20)
{
  Serial.println("left");
  turnLeft();
}

}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
}

void forword(){  //forword
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
Serial.println("Forward");
}

void reverse(){  //forword
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, HIGH);  //Right Motor backword Pin 
digitalWrite(in3, HIGH);  //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
Serial.println("reverse");
}

void turnRight(){ //turnRight
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin  
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
Serial.println("right");
}

void turnLeft(){ //turnLeft
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3 , HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 
Serial.println("left");
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW); //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
Serial.println("stop");
delay(1000);
}
