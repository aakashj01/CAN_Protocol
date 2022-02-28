#include <mcp2515.h>          //Library for using CAN Communication 
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
struct can_frame canMsg3;
int potval,switchval; 
MCP2515 mcp2515(10); 

void setup() {
Serial.begin(9600);   // put your setup code here, to run once:

lcd.init();       //initialize i2c LCD
  lcd.backlight();
  delay(1000);
  
mcp2515.reset();      
mcp2515.setBitrate(CAN_125KBPS);  
mcp2515.setNormalMode();  

}

void loop() {
  if (mcp2515.readMessage(&canMsg3) == MCP2515::ERROR_OK) // To receive data (Poll Read)
     {
      
      if (canMsg3.can_id==0xCC)
      {
        
      potval = canMsg3.data[0];
      switchval = canMsg3.data[1];
    Serial.print("pot value: ");
    Serial.print(potval);

    Serial.print("  switch value: ");
    Serial.println(switchval);
      
    } 
     }
     lcd.setCursor(1,0);
     lcd.print("potval:");
     lcd.setCursor(1,1);
     lcd.print("switchval:");

lcd.setCursor(9,0);
  lcd.print("   ");
  lcd.setCursor(9,0);
  lcd.print(potval);
  lcd.setCursor(12,1);
  lcd.print(switchval);
  
}
