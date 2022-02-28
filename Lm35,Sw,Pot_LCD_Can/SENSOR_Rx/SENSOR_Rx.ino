
#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

struct can_frame canMsg1; 
struct can_frame canMsg2;
struct can_frame canMsg3;
 
MCP2515 mcp2515(10);                 // SPI CS Pin 10 
int x,z;
 
void setup() {
  pinMode(7,OUTPUT);
  lcd.init();       //initialize i2c LCD
  lcd.backlight();
  delay(1000);
    
  SPI.begin();                       //Begins SPI communication
  
  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate 
  
  mcp2515.reset();      

  mcp2515.setBitrate(CAN_125KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz 
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
}

void loop() 
{
  if (mcp2515.readMessage(&canMsg2) == MCP2515::ERROR_OK) // To receive data (Poll Read)
   {
if (canMsg2.can_id==0xBB)
      {
     int y = canMsg2.data[0];         
     Serial.print("lm35_T:");
     Serial.print(y);
     Serial.print(", ");
     lcd.setCursor(0,1);     
      lcd.print("lm35_T:");
      lcd.print(y);
      delay(100);
      }
   }
if (mcp2515.readMessage(&canMsg1) == MCP2515::ERROR_OK) // To receive data (Poll Read)
    {
      if(canMsg1.can_id==0xAA)
    {
     x = canMsg1.data[0];         
     Serial.print("pot value:");
     Serial.println(x);
     Serial.print(", ");
     lcd.setCursor(12,0);
      lcd.print("   ");
     lcd.setCursor(1,0);     
     lcd.print("pot value: ");
      lcd.print(x);
    
      z = canMsg1.data[1];
     Serial.print("Door:");         
     Serial.println(z);
     
     if (z==1){
      digitalWrite(7,LOW);
     }
     
     if(z==0){
      digitalWrite(7,HIGH);
      }
      
     lcd.setCursor(12,1);     
     lcd.print("D:");
     lcd.print(z);
    
     Serial.print("PotVal:");
     Serial.println(x);
     Serial.print("SwitchVal:");
     Serial.println(z);
     delay(100); 
    }
    }
}
    
    
     if (mcp2515.readMessage(&canMsg3) == MCP2515::ERROR_OK) // To receive data (Poll Read)
     {
      if (canMsg3.can_id==0xCC)
      {
     int z = canMsg3.data[0];
     Serial.print("Door:");         
     Serial.println(z);
     
     if (z==1){
      digitalWrite(7,LOW);
     }
     
     if(z==0){
      digitalWrite(7,HIGH);
      }
      
     lcd.setCursor(12,1);     
     lcd.print("D:");
     lcd.print(z);
     delay(110);
    } 
     }
    delay(100);
   lcd.clear();
                   
