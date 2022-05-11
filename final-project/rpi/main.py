from bluepy.btle import UUID, Peripheral
from time import sleep
from requests import get, post
from struct import unpack
from json import dumps
from datetime import datetime


devices = []
dataServiceUUID = "19b10000-e8f2-537e-4f6c-d104768a1214"


def get_device_data(device):
    try:
        peripheral = Peripheral(device)
        dataService = peripheral.getServiceByUUID(dataServiceUUID)
        data = {}
        data["time"] = str(datetime.now())
        for characteristic in dataService.getCharacteristics():
            data[str(characteristic.uuid)] = unpack(
                'f', characteristic.read())[0]
        peripheral.disconnect()
        return data
    except:
        print("Error fetching data via BLE")
        return None


def get_device_uuids(url):
    try:
        return get(url).json()
    except:
        print("UUID fetch failed")
        return []


def post_device_data(url, device, data):
    if data is None:
        return

    try:
        post(url, {"uuid": device, "data": dumps(data)})
        print("data posted")
    except:
        print("data post to failed")


def loop():
    devices = get_device_uuids("http://192.168.0.104:3000/api/container/uuids")
    for device in devices:
        data = get_device_data(device)
        post_device_data(
            "http://192.168.0.104:3000/api/container/log",
            device,
            data)

    sleep(10)


if __name__ == "__main__":
    while(True):
        loop()
