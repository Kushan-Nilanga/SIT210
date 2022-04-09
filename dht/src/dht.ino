
#include "ada_dht.h" // DHT library by AdaFruit

#define DHTPIN 5 // pin that DHT11 is connected to
#define DHTTYPE DHT11 // our sensor is DHT11

int temperature; // int variable to hold temperature
int humidity; // int variable to hold humidity


// defining our DHT sensor using the AdaFruit library
// the library will handle I2C communication between the
// sensor and particle argon
DHT dht(DHTPIN, DHTTYPE); 

void setup()
{
    // starting I2C connection between the DHT11 and argon
    dht.begin();

    // Serial communication for debugging purposes
    Serial.begin(9600);
}

void loop()
{
    // accessing temperature in celcius format
    temperature = dht.getTempCelcius();

    // accessing humidity in percentage
    humidity = dht.getHumidity();

    // printing the read values to serial monitor for debugging
    Serial.printlnf("Temp: %d, Hum: %d", temperature, humidity);

    // publishing the temperature to 'temp' webhook in particle console
    Particle.publish("temp", String(temperature), PRIVATE);

    // pblishing the humidity to 'hum' webhook in particle console
    Particle.publish("hum", String(humidity), PRIVATE);

    // repeating the loop after 2000 miliseconds
    delay(2000);
}


