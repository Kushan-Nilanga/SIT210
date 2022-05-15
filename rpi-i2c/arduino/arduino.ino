#include <Wire.h>

#define slave 0x08

#define R A0
#define B A1
#define G A2

void setup()
{
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  Wire.begin(slave);
  Wire.onReceive(recieved);

  Serial.begin(9600);
  Serial.println("started");
}

void recieved(int count)
{
  Serial.println("data recieved");
  int data[4];

  int x = 0;
  while (Wire.available())
  {
    data[x] = Wire.read();
    x++;
  }

  Serial.println(data[1]);
  Serial.println(data[2]);
  Serial.println(data[3]);

  analogWrite(R, data[1]);
  analogWrite(G, data[2]);
  analogWrite(B, data[3]);
}

void loop()
{
  delay(100);
}
