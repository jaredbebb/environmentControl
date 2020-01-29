
/*
 * From https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-temperature-and-humidity-dht-sensors-9e5975
*/
#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);
int relay = 8;

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  // Pin for relay module set as output
  pinMode(relay, OUTPUT);

  dht.begin();
}

void loop() {
  
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  
  Serial.println(" *F");

//  if (h <= 4.0){
//    digitalWrite(pinOut, HIGH);
//  }
//  else {
//    digitalWrite(pinOut, LOW);

  Serial.println("HIGH signal to socket ");
  digitalWrite(relay, HIGH);
  delay(5000);
  
  Serial.println("LOW signal to socket ");
  digitalWrite(relay, LOW);
  delay(5000);
  
}
