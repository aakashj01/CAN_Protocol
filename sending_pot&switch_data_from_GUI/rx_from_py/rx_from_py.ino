
int incomingByte1;  // for incoming serial data
int incomingByte2;
#include <SPI.h>
#include <mcp2515.h> 
struct can_frame canMsg3; 
MCP2515 mcp2515(10);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

 mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS); 
  mcp2515.setNormalMode();

  canMsg3.can_id  = 0xCC;           
  canMsg3.can_dlc = 2;  
  
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte1 = Serial.parseInt();
    Serial.print("pot value: ");
    Serial.print(incomingByte1);

    incomingByte2 = Serial.parseInt();
    Serial.print("  switch value: ");
    Serial.println(incomingByte2);

canMsg3.data[0]=incomingByte1;
canMsg3.data[1]=incomingByte2;

mcp2515.sendMessage(&canMsg3); 
delay(100);

}

}
