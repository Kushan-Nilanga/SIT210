/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/donkushanathalage/Desktop/particle/dht/src/dht.ino"

#include "ada_dht.h"

void setup();
void loop();
#line 4 "/Users/donkushanathalage/Desktop/particle/dht/src/dht.ino"
#define DHTPIN 5
#define DHTTYPE DHT11

int temperature;
int humidity;

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    dht.begin();
    Serial.begin(9600);
}

void loop()
{
    temperature = dht.getTempCelcius();
    humidity = dht.getHumidity();

    Serial.printlnf("Temp: %d, Hum: %d", temperature, humidity);
    Particle.publish("temp", String(temperature), PRIVATE);
    Particle.publish("hum", String(humidity), PRIVATE);
    delay(2000);
}
