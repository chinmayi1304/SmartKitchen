const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int BUZZER_PIN = 4;   // 4

int led = 10;                // the pin that the led sensor is attached to
int sensor = 2 ;               // the pin that the sensor PIR is attached to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

int LED = 13;              // the pin that the LED fire sensor is attached to
int RELAY = 12;  
int Flame_sensor = 3;  
int Flame_detected; 


void setup() {
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);      // initialize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  pinMode(LED, OUTPUT);  
  pinMode(RELAY, OUTPUT);  
  digitalWrite(RELAY, HIGH);  
  pinMode(Flame_sensor, INPUT); 
  pinMode(BUZZER_PIN, OUTPUT); // set arduino pin to output mode
}

void loop() {
  long duration, inches, cm;
  float distance;
  
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  // measure duration of pulse from ECHO pin
  duration = pulseIn(echoPin, HIGH);
  // calculate the distance
  distance = 0.01750 * duration;

  if(distance < 1){
    digitalWrite(BUZZER_PIN, HIGH);
    } // turn on Piezo Buzzer
  else{
      digitalWrite(BUZZER_PIN, LOW);
      }  // turn off Piezo Buzzer
  
  Serial.print("Ultrasonic sensor: ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println(distance);

  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
   // delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
      //delay(100);
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }

  Flame_detected = digitalRead(Flame_sensor);  
  Serial.print("Flame sensor: ");  
  Serial.println(Flame_detected);   
  
  if (Flame_detected == 0) {  
   Serial.println("Flame detected! Take action immediately.");  
   digitalWrite(LED, HIGH);  
   digitalWrite(RELAY, LOW);  
   delay(500);  
  }   
  else {  
   Serial.println("No flame detected. Stay cool.");  
   digitalWrite(LED, LOW);  
   digitalWrite(RELAY, HIGH);  
  }  
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;


}


