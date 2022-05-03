/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/donkushanathalage/Desktop/SIT210/ifttt/src/ifttt.ino"
void setup();
void loop();
#line 1 "/Users/donkushanathalage/Desktop/SIT210/ifttt/src/ifttt.ino"
const int thresh = 2500;
int lightIntensity = 0;
int photoResistorPin = A0;
bool isSunUp = false;


// setup() runs once, when the device is first turned on.
void setup() {
    
    Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    lightIntensity = analogRead(photoResistorPin);

    Serial.println(lightIntensity);

    if (lightIntensity <= thresh && isSunUp) {
        isSunUp =! isSunUp;
        Particle.publish("sun", "down");
        Serial.println("Sun down event triggered");
    }

    if (lightIntensity > thresh && !isSunUp) {
        isSunUp =! isSunUp;
        Particle.publish("sun", "up");
        Serial.println("Sun up event triggered");
    }

    delay(10s);
}