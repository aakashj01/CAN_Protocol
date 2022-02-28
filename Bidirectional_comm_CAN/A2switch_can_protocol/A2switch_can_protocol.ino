
#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication 

#define doorsw 6              //set digital pin 6 for the door switch

MCP2515 mcp2515(10);          // SPI CS Pin 10

struct can_frame canMsg2;
struct can_frame canMsg3;
                
 
void setup() {
                       
  Serial.begin(115200);                //Begins Serial Communication at 115200 baudrate 
  pinMode(7, OUTPUT);                 //set pin 7 as output i.e. led
  pinMode(doorsw,INPUT);
  digitalWrite(doorsw,HIGH); //enabling internal pullup for the switch
  
  mcp2515.reset();    
  mcp2515.setBitrate(CAN_125KBPS);          //Sets CAN at speed 125KBPS 
  mcp2515.setNormalMode();                  //Sets CAN at normal mode

  canMsg2.can_id = 0xCC;                   //can ID of sent/received data
  canMsg2.can_dlc = 1;
}

void loop() {
   
   if (mcp2515.readMessage(&canMsg3) == MCP2515::ERROR_OK){ // To receive data (Poll Read)
      if (canMsg3.can_id==0xCC){              //check receiving can data ID
      
        int z = canMsg3.data[0];       //assign variable z as the recieved data
        Serial.print("Received:");
        Serial.print(z);
        if (z==1){
           digitalWrite(7,LOW);       //turn on/off led according to recieved data
        }
        if(z==0){
           digitalWrite(7,HIGH);
        }
      
      }  
   }
     

  int sw = digitalRead(doorsw);   //reading switch sensor
  Serial.print(" sent:");
  Serial.println(sw);
  
  canMsg2.data[0]=sw;            
       
  mcp2515.sendMessage(&canMsg2);   //sending switch data on the can bus
   
  delay(100);  
   
}                    
