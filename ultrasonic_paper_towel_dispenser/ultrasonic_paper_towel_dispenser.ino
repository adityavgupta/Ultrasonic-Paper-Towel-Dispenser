/*
 HC-SR04 Ping distance sensor:*/
#define echoPin1 13 // Echo Pin
#define trigPin1 12 // Trigger Pin
#define motorPin1 8 // Pin to control motor

#define echoPin2 4 // Echo Pin
#define trigPin2 2 // Trigger Pin
#define motorPin2 7 // Pin to control motor

int maximumRange = 15; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration1, distance1; // Duration used to calculate distance
long duration2, distance2; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(motorPin1, OUTPUT);
 
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 pinMode(motorPin2, OUTPUT);
}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the 
distance of the nearest object by bouncing soundwaves off of it. */
 digitalWrite(trigPin1, LOW);
 delayMicroseconds(2);
 
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10);
 
 digitalWrite(trigPin1, LOW);
 duration1 = pulseIn(echoPin1, HIGH);
 
 digitalWrite(trigPin2, LOW);
 delayMicroseconds(2);
 
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 
 digitalWrite(trigPin2, LOW);
 duration2 = pulseIn(echoPin2, HIGH);
 
//Calculate the distance (in cm) based on the speed of sound. 
 distance1 = duration1/58.2;
 distance2 = duration2/58.2;
 
 if (distance1 >= maximumRange || distance1 <= minimumRange){
  /* Send a negative number to computer and Turn LED ON
  to indicate "out of range" */
     
     if (distance2 >= maximumRange || distance2 <= minimumRange){ 
        /* Send a negative number to computer and Turn LED ON
        to indicate "out of range" */
        Serial.println("No signal");
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
      }
      else if(distance2 <= maximumRange && distance2 >= minimumRange){ 
        /* Send the distance to the computer using Serial protocol, and 
        turn LED OFF to indicate successful reading. */
        Serial.print("0  ");
        Serial.print(distance2);
        Serial.print("\n");
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
      } 
  }
  
  else if(distance1 <= maximumRange && distance1 >= minimumRange){ 
    /* Send the distance to the computer using Serial protocol, and 
    turn LED OFF to indicate successful reading. */ 
    Serial.print(distance1);
    Serial.print("  0\n");
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  }
  
  //Delay 50ms before next reading.
  delay(50); 
}
