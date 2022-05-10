

TCPClient client;
const byte server[] = {192, 168, 0, 104};
const int port = 3000;

byte uuids[32*4];

void setup()
{
    Serial.begin(9600);

    if (client.connect(server, port))
    {
        client.println("GET /api/container/uuids HTTP/1.1");
        client.println("Host: requestb.in");
        client.println("Content-Length: 0");
        client.println();
        client.flush();
    }
}


void loop()
{
    if (client.available())
    {
        char c = client.read();
        // Serial.println(i);
        Serial.print(c);
        // for(int ptr = 0; uuids[ptr] != 0x00; ptr++)
        // {
        //     Serial.print(char(uuids[ptr]));
        // }
        // Serial.println();
    }

    if (!client.connected())
    {
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();
        for (;;)
            ;
    }
}