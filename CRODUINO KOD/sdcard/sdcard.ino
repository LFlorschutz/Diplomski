#include <SD.h>
#include <SPI.h>
#include "DHT.h"
#include <SoftwareSerial.h>
int pinDHT = A0;
int tipDHT = DHT22;
int chipSelect = 4;
DHT dht(pinDHT, tipDHT);
File myFile;
SoftwareSerial bt(2,3);
char c =' ';

void setup()
{
  Serial.begin(9600);
  bt.begin(9600);
  dht.begin();
  Serial.println("DHT test");
  Serial.print("Initializing SD card...\n");
  pinMode(10, OUTPUT);
  SD.begin(4);
}
void loop()
{

  if (bt.available()){
    c = bt.read();
    if (c == 'r'){
      bt.println((String) readSensor(c));
    }
  }}
  
  float readSensor(char _c){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float i = dht.computeHeatIndex(t, h, false);
  delay (2000);

    if (isnan(h) || isnan(t)){
    Serial.println("Neuspjesno citanje s DHT22");
    return;
  }
  if (_c == 'r'){
    Serial.print("\n");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Heat index: ");
    Serial.print(i);
    Serial.print(" *C ");
    Serial.print("\n");

    bt.print("Temperature: ");
    bt.print(t);
    bt.print(" *C ");
    bt.print("\n");
    bt.print("Humidity: ");
    bt.print(h);
    bt.print(" %\t");
    bt.print("\n");
    bt.print("Heat index: ");
    bt.print(i);
    bt.print(" *C ");
    bt.print("\n");

  myFile = SD.open("dhtData.txt", FILE_WRITE);
  if(myFile) {
    delay(2000);
    myFile.print("Temperature: ");
    myFile.print(t);
    myFile.print("*C");
    myFile.print(" Humidity: ");
    myFile.print(h);
    myFile.print("%");
    myFile.print(" Heat index (Real feel): ");
    myFile.print(i);
    myFile.print(" *C ");
    myFile.println("\n");
    myFile.close();
  }}
  }
