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
        peripheral = Peripheral(device, "random")
        dataService = peripheral.getServiceByUUID(dataServiceUUID)
        data = {}
        data["time"] = str(datetime.now())
        for characteristic in dataService.getCharacteristics():
            data[str(characteristic.uuid)] = unpack(
                'f', characteristic.read())[0]
        peripheral.disconnect()
        return data
    except:
        print(str(datetime.now()), "BLE connection err")
        return None

def get_device_uuids(url):
    try:
        return get(url).json()
    except:
        print(str(datetime.now()), "UUID fetch failed")
        return []


def post_device_data(url, device, data):
    if data is None:
        return

    try:
        post(url, {"uuid": device, "data": dumps(data)})
        print(str(datetime.now()), "data posted")
    except:
        print(str(datetime.now()), "data post to failed")


def loop():
    devices = get_device_uuids("http://<IP Address>:3000/api/container/uuids")
    for device in devices:
        data = get_device_data(device)
        if data is not None:    
            post_device_data(
            "http://<IP Address>:3000/api/container/log",
            device,
            data)

    sleep(60)


if __name__ == "__main__":
    while(True):
        loop()
