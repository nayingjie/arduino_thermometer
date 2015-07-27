#define THERMISTORPIN A0
#define THERMISTORNOMINAL 10000
#define TEMPERATURENOMINAL 25
#define NUMSAMPLES 25
#define BCOEFFICIENT 4050
#define SERIESRESISTOR 10000
#define THERMISTORPIN2 A3
#define THERMISTORPIN3 A2
#define DHTPIN 2
#define DHTTYPE DHT11
int samples[NUMSAMPLES];
int samples_two[NUMSAMPLES];
int samples_three[NUMSAMPLES];
#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"

byte mac[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xEE
};
IPAddress ip(192, 168, 1, 3);
EthernetServer server(80);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  dht.begin();
  analogReference(EXTERNAL);
}

void loop() {
  uint8_t i;
          float average;
          float average_two;
          float average_three;
          for (i = 0; i < NUMSAMPLES; i++) {
            samples[i] = analogRead(THERMISTORPIN);
            samples_two[i] = analogRead(THERMISTORPIN2);
            samples_three[i] = analogRead(THERMISTORPIN3);
            Serial.println(samples_two[i]);
            Serial.println("#####");
            Serial.println(samples_three[i]);
            delay(10);
          }
          average = 0;
          for (i = 0; i < NUMSAMPLES; i++) {
            average += samples[i];
            average_two += samples_two[i];
            average_three += samples_three[i];
          }
          average /= NUMSAMPLES;
          average = 1023 / average - 1;
          average = SERIESRESISTOR / average;
          float tempreading;
          tempreading = average / THERMISTORNOMINAL;
          tempreading = log(tempreading);
          tempreading /= BCOEFFICIENT;
          tempreading += 1.0 / (TEMPERATURENOMINAL + 273.15);
          tempreading = 1.0 / tempreading;
          tempreading -= 273.15;
          tempreading = tempreading * 9 / 5 + 32;
          average_two /= NUMSAMPLES;
          average_two = 1023 / average_two - 1;
          average_two = SERIESRESISTOR / average_two;
          average_two = average_two;
          float tempreadtwo;
          tempreadtwo = average_two / THERMISTORNOMINAL;
          tempreadtwo = log(tempreadtwo);
          tempreadtwo /= BCOEFFICIENT;
          tempreadtwo += 1.0 / (TEMPERATURENOMINAL + 273.15);
          tempreadtwo = 1.0 / tempreadtwo;
          tempreadtwo -= 273.15;
          tempreadtwo = tempreadtwo * 9 / 5 + 32;  
          average_three /= NUMSAMPLES;
          average_three = 1023 / average_three - 1;
          average_three = SERIESRESISTOR / average_three;
          float tempreadthree;
          tempreadthree = average_three / THERMISTORNOMINAL;
          tempreadthree = log(tempreadthree);
          tempreadthree /= BCOEFFICIENT;
          tempreadthree += 1.0 / (TEMPERATURENOMINAL + 273.15);
          tempreadthree = 1.0 / tempreadthree;
          tempreadthree -= 273.15;
          tempreadthree = tempreadthree * 9 / 5 + 32;
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          float f = dht.readTemperature(true);
          float hif = dht.computeHeatIndex(f, h);
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 0");
          client.println();
          client.println(average);
          client.println(tempreading);
          client.println(average_two);
          client.println(tempreadtwo);
          client.println(average_three);
          client.println(tempreadthree);
          client.println(h);
          client.println(f);
          client.println(hif);
          
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
  }
}
