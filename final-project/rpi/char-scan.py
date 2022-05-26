from bluepy.btle import UUID, Peripheral

p = Peripheral("E5:D0:E2:D6:80:E1", "random")

print("Handle   UUID                                Properties")
print("-------------------------------------------------------")
for ch in p.getCharacteristics():
    print("  0x" + format(ch.getHandle(), '02X') + "   " +
          str(ch.uuid) + " " + ch.propertiesToString())
