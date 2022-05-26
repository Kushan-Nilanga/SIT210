
#include "ada_dht.h" // DHT library by AdaFruit

#define DHTPIN D4 // pin that DHT11 is connected to
#define DHTTYPE DHT22 // our sensor is DHT11
#define HCSR04_PIN_TRIG	D2
#define HCSR04_PIN_ECHO	D3

int temperature; // int variable to hold temperature
int humidity; // int variable to hold humidity


int sound = 0;


// defining our DHT sensor using the AdaFruit library
// the library will handle I2C communication between the
// sensor and particle argon
DHT dht(DHTPIN, DHTTYPE); 

void setup()
{
    // starting I2C connection between the DHT11 and argon
    dht.begin();

    // usltrasonic pins
    pinMode(HCSR04_PIN_TRIG, OUTPUT);
    pinMode(HCSR04_PIN_ECHO, INPUT);

    // Serial communication for debugging purposes
    Serial.begin(9600);
}

void loop()
{
    // distance
    float timeTaken, distance;
    digitalWrite(HCSR04_PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(HCSR04_PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(HCSR04_PIN_TRIG, LOW);
    timeTaken = pulseIn(HCSR04_PIN_ECHO, HIGH);//determine distance of wave
    distance = (timeTaken/2)/29.1;//using timeTaken calc distance of object

    // accessing temperature in celcius format
    temperature = dht.getTempCelcius();

    // accessing humidity in percentage
    humidity = dht.getHumidity();

    // printing the read values to serial monitor for debugging
    Serial.printlnf("Depth: %f, Temp: %d, Hum: %d", distance, temperature, humidity);

    // // publishing the temperature to 'temp' webhook in particle console
    // Particle.publish("temp", String(temperature), PRIVATE);

    // // pblishing the humidity to 'hum' webhook in particle console
    // Particle.publish("hum", String(humidity), PRIVATE);

    // repeating the loop after 2000 miliseconds
    delay(1000);
}
        
        


