from bluepy.btle import UUID, Peripheral
import struct

p = Peripheral("E5:D0:E2:D6:80:E1", "random")

dataService = p.getServiceByUUID("19b10000-e8f2-537e-4f6c-d104768a1214")

for ch in dataService.getCharacteristics():
    print(ch.uuid, struct.unpack('f', ch.read())[0])
