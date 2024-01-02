#include <SPI.h>
#include <LoRa.h>
#include "DHT.h"
#include <Servo.h>

#define DHTPIN A0     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int hum;
float temp; //Stores temperature value
int counter = 0;

int led = 13;                // the pin that the LED is atteched to
int sensor = 3;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

// defines pins numbers
const int trigPin = 8;
const int echoPin = 7;

// defines variables
long duration;
int distance;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo positiond

void setup() {    
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  myservo.attach(4);  // attaches the servo on pin 4 to the servo object
  Serial.begin(9600);
  dht.begin();

  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  Serial.print("\nSending Packet for DHT11 Sensor: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("Humidity: "); Serial.print("Current humidity = ");
  LoRa.print(hum); Serial.print(hum);
  LoRa.print("%"); Serial.print("%  ");

  LoRa.print("Temperature:"); Serial.print("temperature = ");
  LoRa.print(temp); Serial.print(temp);
  LoRa.print("c"); Serial.println("C  ");

  LoRa.endPacket();
  counter++;
  delay(1000);

  val = digitalRead(sensor);   // read sensor value
  
  Serial.print("\nSending Packet for PIR Motion Sensor: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();

  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!");
      LoRa.print("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        LoRa.print("Motion stopped!"); 
        state = LOW;       // update variable state to LOW
    }
  }

  LoRa.endPacket();
  counter++;
  delay(1000);

  Serial.print("\nSending Packet for Ultrasonic Sensor: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();

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
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: "); LoRa.print("Distance: ");
  Serial.println(distance); LoRa.print(distance);

  LoRa.endPacket();
  counter++;
  delay(1000);

  Serial.print("\nSending Packet for Servo Motor: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.print("Degree(s): "); LoRa.print("Degree(s): ");
    Serial.println(pos); LoRa.print(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.print("Degree(s): "); LoRa.print("Degree(s): ");
    Serial.println(pos); LoRa.print(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  LoRa.endPacket();
  counter++;
  delay(3000);
}
