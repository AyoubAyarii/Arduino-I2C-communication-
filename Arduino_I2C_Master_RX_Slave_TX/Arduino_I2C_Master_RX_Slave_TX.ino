#include <Wire.h>
 
#define LED_BLEU 4
#define LED_JAUNE 5
#define LED_ROUGE 6
#define LED_VERT 7
 
byte RxByte;
 
void setup() {
  Wire.begin(); // Initialize I2C 
  pinMode(LED_BLEU, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_VERT, OUTPUT);
}
 
void loop() {
  Wire.requestFrom(0x55, 1); // Request From Slave @ 0x55, Data Length = 1Byte
  while(Wire.available()) { 
    RxByte = Wire.read(); // Read Received Data From Slave Device
  }
  digitalWrite(LED_BLEU, (RxByte&0x01));// Turns on LED_BLEU if the least significant bit of RxByte is 1, otherwise turns it off.
  digitalWrite(LED_JAUNE, (RxByte&0x02));// Turns on LED_JAUNE if the second bit of RxByte is 1, otherwise turns it off.
  digitalWrite(LED_ROUGE, (RxByte&0x04));// Turns on LED_ROUGE if the third bit of RxByte is 1, otherwise turns it off.
  digitalWrite(LED_VERT, (RxByte&0x08));// Turns on LED_VERT if the fourth bit of RxByte is 1, otherwise turns it off.
  delay(100);
}


#include <Wire.h>

#define buttB 4
#define buttJ 5
#define buttR 6
#define buttG 7

byte TxByte = 0;

void I2C_TxHandler(void) {
  Wire.write(TxByte); // Sends the byte stored in TxByte to the I²C master device
}

void setup() {
  
  pinMode(buttB, INPUT);
  pinMode(buttJ, INPUT);
  pinMode(buttR, INPUT);
  pinMode(buttG, INPUT);// Set pins as INPUT without pull-downs

  
  Wire.begin(0x55);// Initialize I2C in Slave Mode with address 0x55
  Wire.onRequest(I2C_TxHandler);// Register the I2C_TxHandler function to handle I²C requests from the master
}

void loop() {
  byte BtnsData = 0;
  BtnsData |= digitalRead(buttB) << 0;
  BtnsData |= digitalRead(buttJ) << 1;
  BtnsData |= digitalRead(buttR) << 2;
  BtnsData |= digitalRead(buttG) << 3;

  TxByte = BtnsData;
  delay(10);
}

