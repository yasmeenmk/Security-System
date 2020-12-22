
/* 
Yasmin Kullab 
	Security System 
This code explans a Security System that will detect the presnce of a 
person at a secure door. The system will prompt to the user to enter a 
passcode. 
If the passcode is not entered with 60 seconds, the alarm will
sound. 
*/

// this constant won't change. It's the pin number of the sensor's output:


#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // numbers of the interface pins

const int pingPin = 7; // pin number of he sensor's output
long time0;
String password= "2019"; //needed password!
long time1;
long dist;
long timepassed;
bool Show;
bool timecalc;
String enterpass;




void setup() {
  lcd.begin(16, 2); // set up the LCD's number of colums and rows
 
  Serial.begin(9600);
  
  Show = true;
  timecalc = true;
}

void loop() {
 
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW); 
  delayMicroseconds(2);
  
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  
  digitalWrite(pingPin, LOW);
    pinMode(pingPin, INPUT);
  
  timepassed = pulseIn(pingPin, HIGH);
  
  dist = microsecondsToFeet(timepassed);
// if at any time during the processs the person no longer detected in the 
// range the system shall reset  
  if(dist <= 2){
   
    if(timecalc){
      time0= millis();
      timecalc = false;
    }
    
  time1=millis()-time0;
    
     if(time1 <= 60000){
     
       if (Show){      
         lcd.clear();
         passwordshow();
         Show=false;
         
         
}
       
   // if the passcode is correct, then send the seril monitor at the LED Welcome  
       if (Serial.available() > 0){
       enterpass = Serial.readStringUntil('\n');     
       
         Serial.println(enterpass);
		
         if(enterpass == password){
          lcd.clear();
          lcd.print("Welcome");
         
           Serial.println("Welcome!");
          delay(3000); 
        }
    Show=true;
    timecalc=true;
  } 
     }
else  {
  tone(8,255);
}
}
else  {
  lcd.clear();
  Show= true ;
  noTone(8);
  timecalc=true; }
}
          
          
void passwordshow(){
  lcd.print("Enter Password:");
    Serial.println("Enter Password:");    }
 

long microsecondsToFeet(long microseconds) {
  return microseconds / 74 / 2 / 7.9;
}      
          
          





