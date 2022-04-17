/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/donkushanathalage/Desktop/SIT210/calling-function/particle/src/particle.ino"

void setup();
void loop();
int change_light(String data);
#line 2 "/Users/donkushanathalage/Desktop/SIT210/calling-function/particle/src/particle.ino"
const pin_t RED = D3;
const pin_t AMBER = D4;
const pin_t GREEN = D5;

void setup()
{
    Serial.begin(9600);
    Particle.function("change-light", change_light);
    pinMode(RED, OUTPUT);
    pinMode(AMBER, OUTPUT);
    pinMode(GREEN, OUTPUT);
}

void loop() {}

int change_light(String data)
{
    digitalWrite(RED, LOW);
    digitalWrite(AMBER, LOW);
    digitalWrite(GREEN, LOW);

    Serial.println(data);
    if (data == "red")
        digitalWrite(RED, HIGH);

    if (data == "amb")
        digitalWrite(AMBER, HIGH);

    if (data == "grn")
        digitalWrite(GREEN, HIGH);

    return 0;
}