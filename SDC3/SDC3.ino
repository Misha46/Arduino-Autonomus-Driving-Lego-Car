#include <Servo.h>    //include libraria pentru servomotor
Servo myservo;        // create servo object to control a servo

#define ENA 5         //channel 1 de la driver motor 
#define ENB 6         //channel 2 de la driver motor 
#define IN1 7         //motor 1 (il folosim)
#define IN2 8         //motor 2 
#define IN3 9         //motor 3 
#define IN4 11        //motor 4 (il folosim) 
#define LED1 36       //farul 1
#define LED2 37       //farul 2

#define trigPin1 22     //pin trigger senzor 1 fata
#define echoPin1 23     //pin echo senzor 1 fata
#define trigPin2 24     //pin trigger senzor 2 45 grade stanga
#define echoPin2 25     //pin echo senzor 2 45 grade stanga
#define trigPin3 26     //pin trigger senzor 3 45 grade dreapta
#define echoPin3 27     //pin echo senzor 3 45 grade dreapta
#define trigPin4 28     //pin trigger senzor 4 stanga
#define echoPin4 29     //pin echo senzor 4 stanga
#define trigPin5 30     //pin trigger senzor 5 dreapta
#define echoPin5 31     //pin echo senzor 5 dreapta
#define trigPin6 32     //pin trigger senzor 6 spate
#define echoPin6 33     //pin echo senzor  6 spate

//#define ir1 38
//#define ir2 39
//#define ir3 40
//#define ir4 41
//#define ir5 42

unsigned char carSpeed1 = 95 ;
unsigned char carSpeed2 = 95  ;

long duration, distance, distance1, distance2, distance3, distance4, distance5, distance6, difference, absDiff;

void forward() {               //functie deplasare fata
  analogWrite(ENA, carSpeed1);
  analogWrite(ENB, carSpeed1);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  myservo.write(110);
  Serial.println("Forward");
}

void back() {                //functie deplasare spate
  analogWrite(ENA, carSpeed1);
  analogWrite(ENB, carSpeed1);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  myservo.write(110);
  Serial.println("Back");
}

void left() {               // functie deplasare stanga
  analogWrite(ENA, carSpeed2);
  analogWrite(ENB, carSpeed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  myservo.write(10);
  Serial.println("Left");
}

void right() {                //functie deplasare dreapta
  analogWrite(ENA, carSpeed2);
  analogWrite(ENB, carSpeed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  myservo.write(190);
  Serial.println("Right");
}

void backLeft() {
  analogWrite(ENA, carSpeed1);
  analogWrite(ENB, carSpeed1);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  myservo.write(0 );
  Serial.write("backLeft");
}

void backRight() {
  analogWrite(ENA, carSpeed1);
  analogWrite(ENB, carSpeed1);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  myservo.write(190);
  Serial.write("backRight");
}

void stop() {                //functie stop
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  myservo.write(90);
  delay(1000);
  Serial.println("Stop!");
}

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);
  pinMode(trigPin6, OUTPUT);
  pinMode(echoPin6, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();   // masina sta pe loc cand e pornita
  myservo.attach(3);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  Serial.begin(9600);
}

void loop() {
  SonarSensor(trigPin1, echoPin1);
  distance1 = distance;
  SonarSensor(trigPin2, echoPin2);
  distance2 = distance;
  SonarSensor(trigPin3, echoPin3);
  distance3 = distance;
  SonarSensor(trigPin4, echoPin4);
  distance4 = distance;
  SonarSensor(trigPin5, echoPin5);
  distance5 = distance;
  SonarSensor(trigPin6, echoPin6);
  distance6 = distance;

  //  if (distance1 >= 200 || distance1 < 0){
  //    distance1 = 0;
  //  }
  //
  //  if (distance2 >= 200 || distance2 < 0){
  //    distance2 = 0;
  //  }
  //  if (distance3 >= 200 || distance3 < 0){
  //    distance3 = 0;
  //  }
  //  if (distance4 >= 200 || distance4 < 0){
  //    distance4 = 0;
  //  }
  //  if (distance5 >= 500 || distance5 < 0){
  //    distance5 = 0;
  //  }
  //  if (distance6 >= 200 || distance6 < 0){
  //    distance6 = 0;
  //  }


  if ( distance1 >= 15 && distance1 <= 30 && distance2 > distance3 ) {
    left();
  } else if (distance1 >= 15 && distance1 <= 30 && distance3 > distance2) {
    right();
  } else if (distance2 <= 20) {
    right();
  } else if (distance3 <= 20) {
    left();
  } else if (distance1 <= 8 && distance2 <= 8 && distance3 <= 8 && distance1 >= 1 && distance2 >= 1 && distance3 >= 1 ) {
    emergencyBack();
  } else if (distance1 <= 8 && distance1 >= 1 && distance2 >= 1 && distance3 >= 1) {
    emergencyBack();
  } else if (distance2 <= 8 && distance1 >= 1 && distance2 >= 1 && distance3 >= 1) {
    emergencyBack();
  } else if (distance3 <= 8 && distance1 >= 1 && distance2 >= 1 && distance3 >= 1) {
    emergencyBack();
  } else {
    forward();
  }

    Serial.print(distance1);
    Serial.print("    ");
    Serial.print(distance2);
    Serial.print("    ");
    Serial.print(distance3);
    Serial.print("    ");
    Serial.print(distance4);
    Serial.print("    ");
    Serial.print(distance5);
    Serial.print("    ");
    Serial.println(distance6);
    

}

void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

}

void emergencyBack() {
  if (distance2 < distance3) {
    backLeft();
    delay(100);
    if(distance6 < 5){
      
    } else if (distance6 > 5){
    backLeft();
    delay(100);
    } else if (distance6 < 5){
      
    } else if (distance6 > 5){
    backLeft();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backLeft();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backLeft();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backLeft();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backLeft();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backLeft();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backLeft();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backLeft();
    delay(100);
    } else if (distance6 < 5){
      
    }


      
  } else if (distance2 > distance3) {
    backRight();
    delay(1000);
    if(distance6 < 5){
      
    } else if (distance6 > 5){
    backRight();
    delay(100);
    } else if (distance6 < 5){
      
    } else if (distance6 > 5){
    backRight();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backRight();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backRight();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backRight();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backRight();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backRight();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backRight();
    delay(100);
    } else if (distance6 < 5){
      
    }else if (distance6 > 5){
    backRight();
    delay(100);
    } else if (distance6 < 5){
      
    }
  } else
  {
    
  }

  //  back();
  //  if (distance6 <= 50){
  //    delay(2000);
  //  }else if (distance6 <= 40){
  //    delay(1500);
  //  }else if (distance6 <= 10){
  //    delay(1000);
  //  }else{
  //    delay(2000);
  //  }
}

