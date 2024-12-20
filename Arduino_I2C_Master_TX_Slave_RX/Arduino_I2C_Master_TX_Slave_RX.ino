
#include <Wire.h>
 
int Pot;
 
void setup() {
  Wire.begin(); // Initialize I2C
}
 
void loop() {
  Pot = analogRead(A0);
  Wire.beginTransmission(0x55); //  Transmit to device with address 85 (0x55)
  Wire.write((Pot>>2));      // Sends Potentiometer Reading (8Bit)
  Wire.endTransmission();       // Stop transmitting
  delay(100);
}



#include <Wire.h>
 
#define LED_PIN 9
 
byte RxByte;
 
void I2C_RxHandler(int numBytes)
{
  while(Wire.available()) {  //  Read Any Received Data
    RxByte = Wire.read(); // Data received by Wire.read() will be stored in RxByte
  }
}
 
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Wire.begin(0x55); // Initialize I2C (Slave Mode: address=0x55 )
  Wire.onReceive(I2C_RxHandler); // Register an "event handler" (a function) // the function that will handle the incoming data
}
 
void loop() {
  analogWrite(LED_PIN, RxByte);
  delay(100);
}




