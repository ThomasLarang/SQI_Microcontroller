#include <AccelStepper.h>

AccelStepper stepperX(AccelStepper::DRIVER, 9, 5);
AccelStepper stepperY(AccelStepper::DRIVER, 13, 12);
#define EN_Y 10 
#define EN_X 11
#define AMBIENT  6
#define LASER  15
#define BLUE  14
//#define MS1 13
//#define MS2 12
//#define MS3 11
#define HomeSwitch 16
//#define MS1_value LOW
//#define MS2_value LOW
//#define MS3_value LOW
String user_input;
int LEDinput;
int value;
int ImageGrabDelay = 0.01;
String X_value;


void setup()
{  
  pinMode(EN_X, OUTPUT);
  pinMode(EN_Y, OUTPUT);
  pinMode(AMBIENT, OUTPUT);
  pinMode(LASER, OUTPUT);
  pinMode(BLUE, OUTPUT);
//  pinMode(MS1, OUTPUT);
//  pinMode(MS2, OUTPUT);
//  pinMode(MS3, OUTPUT);
  pinMode(HomeSwitch, INPUT);
  stepperX.setMaxSpeed(100000.0); //Default 400000
  stepperX.setAcceleration(50000.0); //Default 800000
  stepperY.setMaxSpeed(100000.0); //Default 100000
  stepperY.setAcceleration(50000.0); //Default 500000
  //stepper.setEnablePin(5);
  digitalWrite(EN_Y, HIGH);
  digitalWrite(EN_X, LOW);
  stepperX.setPinsInverted(true, false, true);
  stepperX.setCurrentPosition(0);   
  stepperY.setPinsInverted(true, false, true);
  stepperY.setCurrentPosition(0); 
  Serial.begin(115200); //Open Serial connection for debugging
  Serial.setTimeout(10);
  Serial.println("Begin motor control");
//  digitalWrite(MS1, MS1_value);
//  digitalWrite(MS2, MS2_value);
//  digitalWrite(MS3, MS3_value);

    
}
void loop()
{


  while(Serial.available()){
      user_input = Serial.readStringUntil('\n'); //Read user input and trigger appropriate function
       //Pull enable pin low to allow motor control
      if (user_input.startsWith("Home")) {
        homing();
        Serial.println(String(user_input));
        
      }
      else if (user_input.startsWith("X_M")) {
        
        user_input.remove(0, 3);
        stepperX.moveTo(user_input.toInt());
        stepperX.runToPosition();
        ///delay(ImageGrabDelay);
        Serial.println("X_M"+String(user_input));
        
      }
      else if (user_input.startsWith("Y_M")) {
        
        user_input.remove(0, 3);  
        stepperY.moveTo(user_input.toInt());
        stepperY.runToPosition();
        ///delay(ImageGrabDelay);
        Serial.println("Y_M"+String(user_input));
        
      }
      else if (user_input.startsWith("Enable")) {
        digitalWrite(EN_X, LOW);
        digitalWrite(EN_Y, HIGH);
        Serial.println(String(user_input));        
      }
      else if (user_input.startsWith("Disable")) {
        digitalWrite(EN_X, HIGH);
        digitalWrite(EN_Y, LOW);
        Serial.println(String(user_input));
        
      }

      else if (user_input.startsWith("BLUE_LIGHT_ON")) {
        digitalWrite(BLUE, HIGH);
        //Serial.println("BLUE LIGHT ON"); 
      }    
      else if (user_input.startsWith("BLUE_LIGHT_OFF")) {
        digitalWrite(BLUE, LOW);
        //Serial.println("BLUE LIGHT OFF"); 
      }    
      else if (user_input.startsWith("LASER_LIGHT_ON")) {
        digitalWrite(LASER, HIGH);
        //Serial.println("LASER LIGHT ON"); 
      }    
      else if (user_input.startsWith("LASER_LIGHT_OFF")) {
        digitalWrite(LASER, LOW);
        //Serial.println("LASER LIGHT OFF"); 
      }      
      else if (user_input.startsWith("AMBIENT_LIGHT_ON")) {
        digitalWrite(AMBIENT, HIGH);
        //Serial.println("AMBIENT LIGHT ON"); 
      }    
      else if (user_input.startsWith("AMBIENT_LIGHT_OFF")) {
        digitalWrite(AMBIENT, LOW);
        //Serial.println("AMBIENT LIGHT OFF"); 
      }    
      
  }

}
void homing()
{
  digitalWrite(EN_X, LOW);
  digitalWrite(EN_Y, HIGH);
  if(digitalRead(HomeSwitch) == HIGH){
  stepperX.moveTo(1000);
  stepperX.runToPosition();
  stepperY.moveTo(1000);
  stepperY.runToPosition();  
  delay(10);
  }
  
  while(digitalRead(HomeSwitch) == LOW){
  stepperX.move(-30);
  stepperX.run();
  }
  
  stepperX.moveTo(1000);
  stepperX.run();
  while(digitalRead(HomeSwitch) == LOW)
  {
  stepperX.move(-1);
  stepperX.run();
  delay(1);
  }
  stepperX.setCurrentPosition(0);
  stepperX.moveTo(100);
  stepperX.runToPosition();

  while(digitalRead(HomeSwitch) == LOW){
  stepperY.move(-30);
  stepperY.run();
  }
  Serial.println("Home switch closed");
  stepperY.moveTo(800);
  stepperY.run();
  while(digitalRead(HomeSwitch) == LOW)
  {
    
  stepperY.move(-1);
  stepperY.run();
  delay(1);
  }
  stepperY.setCurrentPosition(0);
  stepperY.moveTo(100);
  stepperY.runToPosition();
}
//
//void SmallForwardSteps()
//{
//  digitalWrite(EN, LOW);
//  stepperX.move(50);
//  digitalWrite(EN, HIGH);
//}
//void SmallBackwardSteps()
//{
//  digitalWrite(EN, LOW);
//  stepperX.move(-50);
//  digitalWrite(EN, HIGH);
//}
