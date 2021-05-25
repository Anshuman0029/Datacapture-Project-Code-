#define echoPin 2             // the echo pin of HC-SR04 is connected with pin 2 of Arduino
#define trigPin 3             // the trig pin of HC-SR04 is connected with pin 3 of Arduino
#define buzzer 8              // the buzzer is connected with pin 8 of Arduino
#define ledPin 9              // the led is connected with pin 9 of arduino
#define inputPin 5            // The Dout pin of PIR sensor is connected with pin 5 of Arduino
long duration;                // variable to store the value of time duration
int distance;                 // variable to store the value of distance 
  
int val = 0;                 // vatiable to store the state of PIR sensor pin as 1 or 0


void setup() {
  pinMode(trigPin, OUTPUT);        // pin 3 of Arduino set as output 
  pinMode(echoPin, INPUT);         // pin 2 of Arduino set as input
  pinMode(ledPin, OUTPUT);         // pin 9 of Arduino set as output
  pinMode(inputPin, INPUT);        // pin 5 of Arduino set as input
  Serial.begin(9600); 
  Serial.println("LABEL,Date, Time,Distance(in cm),No. of times Soc. Distancing Violated, State, No. of Times Motion detected");    // Column name for PLX-DAQ
}

void loop() {

    
    Serial.print("DATA, DATE,TIME,");
    distance = Ultrasonic_sensor();              // call to Ultrasonic_sensor() function
    Serial.print(distance);
    Serial.print(",");
    if(distance <100)
    {
      digitalWrite(buzzer, HIGH);              // buzzer will produce alarm
      Serial.print(1);                         // printing 1 in the PLQ- DAQ record
      
    }
    else
    {
      digitalWrite(buzzer,LOW);
      Serial.print(0);                        // printing 0 in PLX-DAQ record 
    } 
    Serial.print(","); 
    delay(100);
    Motion();                                // call to Motion() function
    delay(100);
    
}

/*
 * THe function Ultrasonic_sensor() return the distance between the system and object by transmitting a 
 * sound wave
 */
int Ultrasonic_sensor()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; 

  
 
}
/*
 *  The Motion() procedure is used to detect motion near the system using the "if" statement.
 */
void Motion()
{
   val = digitalRead(inputPin);  
   if (val == HIGH) 
   { 
     Serial.print("Motion detected,");
     Serial.println(1);
     
     digitalWrite(13,HIGH);
     digitalWrite(13,LOW);          
     digitalWrite(ledPin, HIGH); 
     //digitalWrite(ledPin, LOW);
     delay(10000);
     
     
   } 
  else
  {   
      Serial.print("Motion not detected,");
      Serial.println(0);
      digitalWrite(ledPin, LOW); 
      digitalWrite(13,LOW); 
  }
}
