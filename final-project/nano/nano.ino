/*
 * Project argon
 * Description:
 * Author:
 * Date:
 */

// BLE package for Arduino
#include <ArduinoBLE.h>

// setup BLE
BLEService dataService("19b10000-e8f2-537e-4f6c-d104768a1214");

// BLE characteristics
BLEFloatCharacteristic tem("19b10001-e8f2-537e-4f6c-d104768a1214", BLERead); // Temperature
BLEFloatCharacteristic hum("19b10002-e8f2-537e-4f6c-d104768a1214", BLERead); // Humidity
BLEFloatCharacteristic dpt("19b10003-e8f2-537e-4f6c-d104768a1214", BLERead); // Depths

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
    BLE.setLocalName("Container");

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

    // delay till the central device connects
    delay(500);

    // while central is connected
    while (central.connected())
    {
        digitalWrite(LED_BUILTIN, HIGH);

        // updating values
        hum.writeValue(random(100));
        tem.writeValue(random(100));
        dpt.writeValue(random(100));

        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
    }
}