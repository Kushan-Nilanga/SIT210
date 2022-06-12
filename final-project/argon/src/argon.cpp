/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/donkushanathalage/Desktop/SIT210/final-project/argon/src/argon.ino"
// DHT library by AdaFruit
#include "ada_dht.h"

void setup();
void loop();
#line 4 "/Users/donkushanathalage/Desktop/SIT210/final-project/argon/src/argon.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(AUTOMATIC);

// pin that DHT11 is connected to
#define DHTPIN D4 

// our dht sensor is DHT22
#define DHTTYPE DHT22 

// ultrasonic sensor pins
#define HCSR04_PIN_TRIG	D2
#define HCSR04_PIN_ECHO	D3

// defining our DHT sensor using the AdaFruit library
// the library will handle I2C communication between the
// sensor and particle argon
DHT dht(DHTPIN, DHTTYPE); 

// main BLE Service to advertise
const BleUuid serviceUuid("19b10000-e8f2-537e-4f6c-d104768a1214");

// setup BLE Services
// const BleUuid temService("19b10001-e8f2-537e-4f6c-d104768a1214");
// const BleUuid humService("19b10002-e8f2-537e-4f6c-d104768a1214");
// const BleUuid dptService("19b10003-e8f2-537e-4f6c-d104768a1214");

// Setup BLE Characteristics 
BleCharacteristic tem("tem", BleCharacteristicProperty::READ, 
  BleUuid("19b10001-e8f2-537e-4f6c-d104768a1214"), serviceUuid);
BleCharacteristic hum("hum", BleCharacteristicProperty::READ, 
  BleUuid("19b10002-e8f2-537e-4f6c-d104768a1214"), serviceUuid);
BleCharacteristic dpt("dpt", BleCharacteristicProperty::READ, 
  BleUuid("19b10003-e8f2-537e-4f6c-d104768a1214"), serviceUuid);

float humVal = 0;
float temVal = 0;
float dptVal = 0;

void setup() {
  // Serial
  Serial.begin(9600);
  while(!Serial);

  // Setting device name
  BLE.setDeviceName("Container");
  Serial.println(BLE.address().toString());

  // Adding characteristics to BLE package
  BLE.addCharacteristic(tem);
  BLE.addCharacteristic(hum);
  BLE.addCharacteristic(dpt);

  // Advertising
  BleAdvertisingData advData;
  advData.appendServiceUUID(serviceUuid);
  BLE.advertise(&advData);

  // starting I2C connection between the DHT11 and argon
  dht.begin();

  // usltrasonic pins
  pinMode(HCSR04_PIN_TRIG, OUTPUT);
  pinMode(HCSR04_PIN_ECHO, INPUT);

  hum.setValue(humVal);
  tem.setValue(temVal);
  dpt.setValue(dptVal);

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}

void loop() {
  digitalWrite(A2, HIGH);
  digitalWrite(A1, LOW);

  // when a device is connected to the device
  while(!BLE.connected()){
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);

    // distance
    float timeTaken;
    digitalWrite(HCSR04_PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(HCSR04_PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(HCSR04_PIN_TRIG, LOW);
    timeTaken = pulseIn(HCSR04_PIN_ECHO, HIGH);//determine distance of wave
    dptVal = (timeTaken/2)/29.1;//using timeTaken calc distance of object

    // accessing temperature in celcius format
    temVal = dht.getTempCelcius();

    // accessing humidity in percentage
    humVal = dht.getHumidity();

    // Setting values
    hum.setValue(humVal);
    tem.setValue(temVal);
    dpt.setValue(dptVal);

    // printing output
    Serial.printf("temp: %f, hum: %f, dpt: %f\n", temVal, humVal, dptVal);

    delay(10);

  }
  delay(1s);
}