
#include <Wire.h>
 
#define LED_BLEU 4
#define LED_JAUNE 5
#define LED_ROUGE 6
#define LED_VERT 7
 
int Pot;
byte RxByte;
 
void setup() {
  Wire.begin(); // Initialize I2C
  pinMode(LED_BLEU, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_VERT, OUTPUT);
}
 
void loop() {
  // I2C TX
  Pot = analogRead(A0);
  Wire.beginTransmission(0x55); // Transmit to device with address 85 (0x55)
  Wire.write((Pot>>2));      // Sends Potentiometer Reading (8Bit)
  Wire.endTransmission();       // Stop transmitting
  // I2C RX
  Wire.requestFrom(0x55, 1); // Request From Slave @ 0x55, Data Length = 1Byte
  while(Wire.available()) {  // Read Received Datat From Slave Device
    RxByte = Wire.read();
  }
   digitalWrite(LED_BLEU, (RxByte&0x01));// Turns on LED_BLEU if the least significant bit of RxByte is 1, otherwise turns it off.
  digitalWrite(LED_JAUNE, (RxByte&0x02));// Turns on LED_JAUNE if the second bit of RxByte is 1, otherwise turns it off.
  digitalWrite(LED_ROUGE, (RxByte&0x04));// Turns on LED_ROUGE if the third bit of RxByte is 1, otherwise turns it off.
  digitalWrite(LED_VERT, (RxByte&0x08));// Turns on LED_VERT if the fourth bit of RxByte is 1, otherwise turns it off.
  delay(100);
}


#include <Wire.h>
 
#define LED_PIN 9
#define LED_BLEU 4
#define LED_JAUNE 5
#define LED_ROUGE 6
#define LED_VERT 7
 
byte RxByte;
byte TxByte = 0;
 
void I2C_RxHandler(int numBytes)
{
  while(Wire.available()) {  // Read Any Received Data
    RxByte = Wire.read(); // Data received by Wire.read() will be stored in RxByte
  }
}
 
void I2C_TxHandler(void)
{
  Wire.write(TxByte);// Sends the byte stored in TxByte to the I²C master device
}
 
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BLEU, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_VERT, OUTPUT);
  Wire.begin(0x55); // Initialize I2C (Slave Mode: address=0x55 )
  Wire.onReceive(I2C_RxHandler); // Register an "event handler" (a function) // the function that will handle the incoming data
  Wire.onRequest(I2C_TxHandler); // Register the I2C_TxHandler function to handle I²C requests from the master
}
 
void loop() {
  byte BtnsData = 0;
  BtnsData |= digitalRead(LED_BLEU) << 0;
  BtnsData |= digitalRead(LED_JAUNE) << 1;
  BtnsData |= digitalRead(LED_ROUGE) << 2;
  BtnsData |= digitalRead(LED_VERT) << 3;
  TxByte = BtnsData;
  analogWrite(LED_PIN, RxByte);
  delay(10);
}

