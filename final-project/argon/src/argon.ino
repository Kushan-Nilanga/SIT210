/*
 * Project argon
 * Description:
 * Author:
 * Date:
 */

// maximum number of expected bluetooth devices 
const size_t SCAN_RESULT_MAX = 30;

// our peripheral device
String Uuid = "2932878e-0000-11ec-9d64-0242ac120002"; 
BleUuid serviceUuid(Uuid);

// characteristic to get data
BleCharacteristic temCharacteristic;
BleCharacteristic humCharacteristic;
BleCharacteristic dptCharacteristic;

// peer
BlePeerDevice peer;

// characteristic data handler
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context);

// setup() runs once, when the device is first turned on.
void setup(){
    Serial.begin(9600);
    Serial.println("Serial Began");
    BLE.on();

    // attaching handler to callback on data in characteristic
    temCharacteristic.onDataReceived(onDataReceived, NULL);
    humCharacteristic.onDataReceived(onDataReceived, NULL);
    dptCharacteristic.onDataReceived(onDataReceived, NULL);
}

// loop() runs over and over again, as quickly as it can execute.
void loop(){
    // scanning for devices
    BleScanResult scanResults[SCAN_RESULT_MAX];
    int count = BLE.scan(scanResults, SCAN_RESULT_MAX);


    Serial.printlnf("devices %d", count);

    // going through each of the device
    for(int i = 0; i < count; i++){
        const size_t a = 8;
        BleUuid *foundUUID = (BleUuid*) malloc(a * sizeof(BleUuid));

        // getting Uuids of advertised services
        size_t len = scanResults[i].advertisingData.serviceUUID(foundUUID, (size_t)sizeof(*foundUUID));

        // going through each of the services
        for(size_t j = 0; j < len; j++){

            // if the advertised service is our data service collect data
            if(*(foundUUID+j) == serviceUuid){

                // address of the device
                BleAddress peerAddress = scanResults[i].address; 

                // connecting to the device
                peer = BLE.connect(peerAddress);

                // sendind data to API if the device is connected
                if(BLE.connected()){
                    bool tem = peer.getCharacteristicByUUID(temCharacteristic, BleUuid("2e0d3c00-0001-11ec-9d64-0242ac120002"));

                    bool hum = peer.getCharacteristicByUUID(humCharacteristic, BleUuid("2e0d3c00-0002-11ec-9d64-0242ac120002"));

                    bool dpt = peer.getCharacteristicByUUID(dptCharacteristic, BleUuid("2e0d3c00-0003-11ec-9d64-0242ac120002"));

                    Serial.printlnf("Temp %d", tem);
                    Serial.printlnf("Humi %d", hum);
                    Serial.printlnf("Dept %d", dpt);

                    BLE.disconnect(peer);
                    // disconnecting the connected device
                }
            }
        }

        free(foundUUID);
    }

    Serial.println();
}


void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context) {
    Serial.println("data received");
}
