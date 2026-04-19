#include <Servo.h>  
#include <LiquidCrystal_I2C.h>

Servo myServo;  
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int trigPin = 9;
int echoPin = 10;  
int irPin = 7;    
long duration;
float distance;  
int choose; //the kid choose in app
int score=0;

void setup() {  
  Serial.begin(9600);  
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  pinMode(irPin, INPUT);  
  myServo.attach(6);
  myServo.write(70); 

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to Element Explorer");
}  

void loop() {  

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  

  duration = pulseIn(echoPin, HIGH, 30000);  

  
  distance = duration * 0.034 / 2;  

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 7 && distance < 8.5) {   
  delay(1000);

    int irState = digitalRead(irPin);  
    Serial.print("IR: ");
    Serial.println(irState);

    if (irState == LOW) {       
      myServo.write(5);  
    } else {  
      myServo.write(170);  
    }  
    delay(1000);        
    myServo.write(70); 

    lcd.clear();
    if(choose == irstate){
      lcd.setCursor(0,0);
      lcd.print("Great Job!");
      score++;
      lcd.setCursor(0,1);
      lcd.print(score);
    }
    else{
      lcd.setCursor(0,0);
      lcd.print("Try again ");
      lcd.setCursor(0,1);
      lcd.print(score);
    } 
  }  
}