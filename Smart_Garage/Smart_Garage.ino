#include <Servo.h>
#include <LiquidCrystal.h>
Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//define ultrasonic pins
#define trigPin 9
#define echoPin 10
#define Warningbulb 2

// defines variables
long duration;
int distance;

void ultrasonic() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}



//open function
void open(){
for (pos = 90; pos <= 180; pos += 1) { 
     // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
 }

 //close function
void close(){
  
  for (pos = 180; pos >= 90; pos -= 1) { 
   // goes from 90 degrees to 0 degrees
   // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void setup() {
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("The Temp is");
//motor pins mode
   myservo.attach(3);  // attaches the servo on pin 3 to the servo object
 myservo.write(90);
//ultrasonic pins mode
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(Warningbulb, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
  
}

void loop() {
  float temp = analogRead(A0);
  temp= temp* 0.43945;
  if(temp>60){
    digitalWrite(2,HIGH);
  }
  else{digitalWrite(2,LOW);
  
  }
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(temp);
  lcd.setCursor(10,1);
  lcd.print("`C");
  ultrasonic();
  if(distance>=20&&distance<=25){
    delay(5000);
    if(distance>=20&&distance<=25){
     open();
    delay (10000);
  close();
    delay (10000);
  }  
  }
  
}
