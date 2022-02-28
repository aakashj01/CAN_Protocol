#include <mcp2515.h>          //Library for using CAN Communication 
#include <SPI.h>
#include <LiquidCrystal_I2C.h>



LiquidCrystal_I2C lcd(0x27,16,2); 

struct can_frame canMsg1;
MCP2515 mcp2515(10); 

int distance,ldrValue; 
const int ledPin=6;
const int buzzpin=8;

void setup() {
pinMode(ledPin,OUTPUT);
pinMode(buzzpin,OUTPUT);
 
 Serial.begin(9600);   // put your setup code here, to run once:

lcd.init();       //initialize i2c LCD
  lcd.backlight();
  delay(1000);
  
mcp2515.reset();      
mcp2515.setBitrate(CAN_125KBPS);  
mcp2515.setNormalMode();  


}

void loop() {
 

   if (mcp2515.readMessage(&canMsg1) == MCP2515::ERROR_OK) // To receive data (Poll Read)
     {
      if (canMsg1.can_id==0xCC)
      {
        ldrValue=canMsg1.data[0];
        distance=canMsg1.data[1];
        Serial.print("LDR value:");
        Serial.print(ldrValue);
        Serial.print(" , ");
        Serial.print("obstacle distance:");
        Serial.println(distance);
        delay(100);
      }
lcd.setCursor(10,0);
lcd.print("   ");
if(ldrValue>=0&&ldrValue<=50){
  ldrValue=200;
  lcd.setCursor(12,1);
lcd.print("H");
  }
 else if(ldrValue>50&&ldrValue<=150){
  ldrValue=50;
  lcd.setCursor(12,1);
lcd.print("M");
  }
  else if(ldrValue>150&&ldrValue<=256){
  ldrValue=0;
  lcd.setCursor(12,1);
lcd.print("L");
  }
  if(distance<5){
    tone(buzzpin,450);
    }
    else if(distance>=5&&distance<10){
      tone(buzzpin,250);
      }
      else if(distance>=10&&distance<=15){
      tone(buzzpin,150);
      }
      else if(distance>=15){
      noTone(buzzpin);
      }
analogWrite(ledPin,ldrValue);
lcd.setCursor(0,0);
lcd.print("distance:");
lcd.setCursor(0,1);
lcd.print("headlights:");
lcd.setCursor(10,0);
lcd.print(distance);
}

  delay(100);
  
  }
  
