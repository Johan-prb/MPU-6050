#include<Wire.h>
#include<LoRa.h>

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;
int i;
int j = 1;
double x;
double y;
double z;



double offx;
double offy;
double offz;

double fx;
double fy;
double fz;


double last_fx;
double last_fy;
double last_fz;

int pintombol = 2;
int pinled = 13;
int th = 10;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(pintombol, INPUT);
  pinMode(pinled, OUTPUT);

  if (!LoRa.begin(923E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
void loop() {
  if (digitalRead(pintombol))
  {
    setoffset();
    delay(1000);
    Serial.println("SET_OKE!!!!!!!!!");
  }

  //Serial.println(i);
  i++;
  ambil();
  fx += (x - offx);
  fy += (y - offy);
  fz += (z - offz);
  if (i >= 9)
  {
    fx = fx / 10;
    fy = fy / 10;
    fz = fz / 10;
    Serial.print("AngleX= ");
    Serial.println(fx);

    Serial.print("AngleY= ");
    Serial.println(fy);

    Serial.print("AngleZ= ");
    Serial.println(fz);
    Serial.println("-----------------------------------------");

    /*if (fx > 1 || fy > 1 || fz > 1)
    {
       LoRa.beginPacket();
       LoRa.print("1");
       LoRa.endPacket();
    }
    else {
       
       LoRa.beginPacket();
       LoRa.print("0");
       LoRa.endPacket();
    }*/

    


   
    delay(500);
   /* if (last_fx - fx > th || last_fy - fy > th || last_fz - fz > th)
    {
       LoRa.beginPacket();
       LoRa.print("1");
       LoRa.endPacket();
    }
    else {
       j = 0;
       LoRa.beginPacket();
       LoRa.print("0");
       LoRa.endPacket();
    }  
    */
  }




}


void setoffset()
{
  digitalWrite(pinled, 0);

  ambil();
  offx = x;
  offy = y;
  offz = z;
}
void ambil()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);


  delay(10);
}
