#include <SPI.h>
int nss=8;

void setup()
{

Serial.begin(9600);
while(!Serial);
pinMode(nss,OUTPUT);
SPI.begin();

}

void loop()
{
readRegister(0x06);
readRegister(0x07);
readRegister(0x08);
delay(2000);
writeRegister(0x06,0xB9);
readRegister(0x06);

}

void readRegister(uint8_t address)
{
 
  uint8_t response;
  digitalWrite(nss, LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(address & 0x7f);
  response = SPI.transfer(0x00);
  SPI.endTransaction();
  digitalWrite(nss, HIGH);
  //return response;
  Serial.println(response,HEX);


}

void writeRegister(uint8_t address, uint8_t value)
{
  uint8_t response;
  digitalWrite(nss, LOW);
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(address | 0x80);
  response = SPI.transfer(value);
  SPI.endTransaction();
  digitalWrite(nss, HIGH);
  //return response;
  //Serial1.println(response);
}
