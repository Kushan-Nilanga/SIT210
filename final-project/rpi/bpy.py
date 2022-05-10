from bluepy.btle import UUID, Peripheral

p = Peripheral("3C:61:05:3F:CA:6A", "public")

print(p.getCharacteristics())
