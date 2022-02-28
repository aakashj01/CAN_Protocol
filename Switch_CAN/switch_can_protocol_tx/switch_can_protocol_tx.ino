#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication

#define doorsw 6
   
struct can_frame canMsg3;  // door sw message
MCP2515 mcp2515(10); // chip select pin 10


void setup() 
{
 
  Serial.begin(115200);
  pinMode(doorsw,INPUT);
  digitalWrite(doorsw,HIGH); //enabling internal pullup for the switch
  //SPI.begin();               //Begins SPI communication
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

  canMsg3.can_id  = 0xCC;           //for door switch
  canMsg3.can_dlc = 1;  
  
}

void loop() 
{ 
  int sw = digitalRead(doorsw);
  Serial.print("door :");
  Serial.println(sw);
  
  canMsg3.data[0]=sw;            
       
  mcp2515.sendMessage(&canMsg3);    
  delay(100);
}
