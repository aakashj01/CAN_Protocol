
#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication 

struct can_frame canMsg3;
 
MCP2515 mcp2515(10);                 // SPI CS Pin 10 
 
void setup() {
  //SPI.begin();                       //Begins SPI communication
  
  Serial.begin(115200);                //Begins Serial Communication at 9600 baudrate 
  pinMode(7, OUTPUT);
  mcp2515.reset();      

  mcp2515.setBitrate(CAN_125KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz 
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
}

void loop() 
{
   if (mcp2515.readMessage(&canMsg3) == MCP2515::ERROR_OK) // To receive data (Poll Read)
     {
      if (canMsg3.can_id==0xCC)
      {
        
     int z = canMsg3.data[0];
     Serial.print("Received:");
     Serial.println(z);
     if (z==1){
      digitalWrite(7,LOW);
     }
     
     if(z==0){
      digitalWrite(7,HIGH);
      }
      
    } 
     }
    
   
}                    
