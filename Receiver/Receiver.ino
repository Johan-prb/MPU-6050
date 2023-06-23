#include <SPI.h>
#include <LoRa.h>

int pinled=13;
int th=100;

void setup() {
  Serial.begin(9600);
  while (!Serial);

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
       // read digital signal
    int j = LoRa.read();
    Serial.print(j);

    // set digital pin state
    digitalWrite(pinled, j);


   
    // print RSSI of packet
    //Serial.print("' with RSSI ");
    //Serial.println(LoRa.packetRssi());
  }
 
}
