/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/donkushanathalage/Desktop/SIT210/buddy/src/buddy.ino"
void setup();
void loop();
void handler(const char *event, const char *data);
#line 1 "/Users/donkushanathalage/Desktop/SIT210/buddy/src/buddy.ino"
const pin_t LED = D8; // setting led pin

void setup()
{
    Particle.subscribe("buddy", handler); // subscribing to buddy event
    pinMode(LED, OUTPUT);                 // setting led pin mode output
    Serial.begin(9600);                   // setting up serial monitor
}

void loop() {} // we wont be using the loop function

void handler(const char *event, const char *data)
{
    Serial.println(data); // printing the data

    if (strcmp(data, "wave") == 0) // on a wave event show 3 long blinks
    {
        for (int i = 0; i < 3; i++)
        {
            digitalWrite(LED, HIGH);
            delay(500ms);
            digitalWrite(LED, LOW);
            delay(500ms);
        }
    }

    if (strcmp(data, "pat") == 0) // on a pat event show 10 rapid blinks
    {
        for (int i = 0; i < 10; i++)
        {
            digitalWrite(LED, HIGH);
            delay(50ms);
            digitalWrite(LED, LOW);
            delay(50ms);
        }
    }
}