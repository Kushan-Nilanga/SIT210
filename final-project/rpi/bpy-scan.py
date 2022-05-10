from bluepy.btle import UUID, Peripheral

p = Peripheral("3C:61:05:3F:CA:6A", "public")

print("Handle   UUID                                Properties")
print("-------------------------------------------------------")
for ch in p.getCharacteristics():
    print("  0x" + format(ch.getHandle(), '02X') + "   " +
          str(ch.uuid) + " " + ch.propertiesToString())
