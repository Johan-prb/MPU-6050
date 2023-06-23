#include <SPI.h>
#include <LoRa.h>

int pinled=3;


//inisialisasi lora
void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  pinMode(pinled, OUTPUT); 
  Serial.println("LoRa Receiver");

  //frekuensi lora
  if (!LoRa.begin(923E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // menerima paket dari transmitter
      String message = ""; 
      while (LoRa.available()){
        message += (char)LoRa.read();
        }
         
    // set digital pin state
    
//kode untuk aktuator
    if ( message == "0"){
      digitalWrite(pinled, LOW);
      }
    else{
      digitalWrite(pinled, HIGH);
      Serial.print("LONGSORRRR! \n");
      }

   

  }
 
}