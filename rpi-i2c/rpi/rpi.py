from smbus import SMBus

addr = 0x08  # bus address
bus = SMBus(1)  # indicates /dev/ic2-1

while True:

    r = int(input("r > "))
    g = int(input("g > "))
    b = int(input("b > "))
    print("sending RGB values")
    bus.write_i2c_block_data(addr, 1, [r, g, b])
