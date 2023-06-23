#include <SPI.h>
#include <LoRa.h>

int pinled=3;
int th=100;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  pinMode(pinled, OUTPUT); 
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(923E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
      String message = ""; 
      while (LoRa.available()){
        message += (char)LoRa.read();
        }
         
    // set digital pin state
    

    if ( message == "0"){
      digitalWrite(pinled, LOW);
      }
    else{
      digitalWrite(pinled, HIGH);
      Serial.print("LONGSORRRR! \n");
      }

   
    // print RSSI of packet
    //Serial.print("' with RSSI ");
    //Serial.println(LoRa.packetRssi());
  }
 
}