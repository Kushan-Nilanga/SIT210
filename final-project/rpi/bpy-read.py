from bluepy.btle import UUID, Peripheral
import struct

p = Peripheral("3C:61:05:3F:CA:6A", "public")

dataService = p.getServiceByUUID("19b10000-e8f2-537e-4f6c-d104768a1214")

for ch in dataService.getCharacteristics():
    print(struct.unpack('f', ch.read()))
