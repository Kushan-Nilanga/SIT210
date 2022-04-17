// led output pins
const pin_t RED = D3;
const pin_t AMBER = D4;
const pin_t GREEN = D5;

void setup()
{
    Serial.begin(9600); // serial port to debug code

    Particle.function("change-light", change_light); // exposing functions to post requests

    // setting pin modes
    pinMode(RED, OUTPUT);
    pinMode(AMBER, OUTPUT);
    pinMode(GREEN, OUTPUT);
}

void loop() {} // we wont be using loop functionality in this

// change light callback function
int change_light(String data)
{
    // printing out data recieved
    Serial.println(data);

    // turning off all the lights
    digitalWrite(RED, LOW);
    digitalWrite(AMBER, LOW);
    digitalWrite(GREEN, LOW);

    // turning on RED if the data is red
    if (data == "red")
        digitalWrite(RED, HIGH);

    // turning on AMBER if the data is amb
    if (data == "amb")
        digitalWrite(AMBER, HIGH);

    // turning on GREEN if the data is grn
    if (data == "grn")
        digitalWrite(GREEN, HIGH);

    return 0; // returning 0 on success operation
}