/*
 * Project argon
 * Description:
 * Author:
 * Date:
 */

// BLE package for Arduino
#include <ArduinoBLE.h>

// setup BLE
BLEService dataService("2932878e-0000-11ec-9d64-0242ac120002");

// BLE characteristics
BLEFloatCharacteristic tem("2e0d3c00-0001-11ec-9d64-0242ac120002", BLERead); // Temperature
BLEFloatCharacteristic hum("2e0d3c00-0002-11ec-9d64-0242ac120002", BLERead); // Humidity
BLEFloatCharacteristic dpt("2e0d3c00-0003-11ec-9d64-0242ac120002", BLERead); // Depths

// setup() runs once, when the device is first turned on.
void setup()
{
    // status symbol
    pinMode(LED_BUILTIN, OUTPUT);

    // Initialize BLE
    if (!BLE.begin())
    {
        // Failed to initialize BLE, blink the internal LED
        Serial.println("Failed initializing BLE");
        while (1)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
        }
    }

    // Set advertised local name and services UUID
    BLE.setDeviceName("Arduino Nano 33 IoT");
    BLE.setLocalName("Arduino Container");

    // advertised service
    BLE.setAdvertisedService(dataService);

    // adding characteristics to service
    dataService.addCharacteristic(tem);
    dataService.addCharacteristic(hum);
    dataService.addCharacteristic(dpt);

    // BLE service
    BLE.addService(dataService);

    // writing initial values
    tem.writeValue((float)0.0);
    hum.writeValue((float)0.0);
    dpt.writeValue((float)0.0);

    // advertise data
    BLE.advertise();
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
    // Listen to central
    BLEDevice central = BLE.central();

    // while central is connected
    while (central.connected())
    {
        // updating values
        hum.writeValue(random(100));
        tem.writeValue(random(100));
        dpt.writeValue(random(100));

        delay(500);
    }
}