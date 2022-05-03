const int thresh = 2500;   // Threshold to trigger the event
int lightIntensity = 0;    // Light intensity variable 
int photoResistorPin = A0; // Analog pin that the sensor is connected to
bool isSunUp = false;      // Stores previous event


// setup() runs once, when the device is first turned on.
void setup() {
    Serial.begin(9600); // Serial for debugging
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    lightIntensity = analogRead(photoResistorPin); // Reading sensor value

    Serial.println(lightIntensity); // printing for debugging

    if (lightIntensity <= thresh && isSunUp) { 
        // if intensity is below the threshold and current event is not already triggered
        isSunUp =! isSunUp;
        Particle.publish("sun", "down"); // publish event
        Serial.println("Sun down event triggered");
    }

    if (lightIntensity > thresh && !isSunUp) {
        // if intensity is above the threshold and current event is not already triggered        
        isSunUp =! isSunUp;
        Particle.publish("sun", "up"); // publish event
        Serial.println("Sun up event triggered");
    }

    delay(10s);
}