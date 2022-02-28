#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

const int ldrPin=A0;

struct can_frame canMsg1;
MCP2515 mcp2515(10);

void setup() {
  
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
 pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
 
 Serial.begin(9600);
 SPI.begin();   

pinMode(ldrPin, INPUT);

   mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS); //Sets CAN at speed 125KBPS
  mcp2515.setNormalMode();

  canMsg1.can_id  = 0xCC;           
  canMsg1.can_dlc = 2;     
}

void loop() {

int ldrValue = analogRead(ldrPin);

// Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  
canMsg1.data[0] = ldrValue; 
canMsg1.data[1] = distance;
   mcp2515.sendMessage(&canMsg1);
   delay(100);
}
