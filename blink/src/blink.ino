// setting output pin
const pin_t MY_LED = D8;
SYSTEM_THREAD(ENABLED);

// Defining name in morse code
char *name_in_morse[] = {
    "-", ".", "-", "*",      // K
    ".", ".", "-", "*",      // U
    ".", ".", ".", "*",      // S
    ".", ".", ".", ".", "*", // H
    ".", "-", "*",           // A
    "-", ".", "*"            // N
};

void setup()
{
    // setting the pin to be output
    pinMode(MY_LED, OUTPUT);
}

void loop()
{
    // iterating throught the morsecode
    for (uint i = 0; i < sizeof(name_in_morse) / sizeof(char); i++)
    {
        // display dot
        if (name_in_morse[i] == ".")
        {
            digitalWrite(MY_LED, HIGH);
            delay(1s);
            digitalWrite(MY_LED, LOW);
        }

        // display dah
        if (name_in_morse[i] == "-")
        {
            digitalWrite(MY_LED, HIGH);
            delay(3s);
            digitalWrite(MY_LED, LOW);
        }

        // end of letter
        if (name_in_morse[i] == "*")
        {
            digitalWrite(MY_LED, LOW);
            delay(3s);
        }

        digitalWrite(MY_LED, LOW);
        delay(3s);
    }
}