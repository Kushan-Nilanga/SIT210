import time
import requests

from gattlib import GATTRequester

server = "http://192.168.0.104:3000/api"


def get_devices():
    req = requests.get(server+"/container/uuids")
    return req.json()


def get_data(device):
    print("getting data from", device)
    try:
        req = GATTRequester(device)
        temp = req.read_by_uuid("2e0d3c00-0001-11ec-9d64-0242ac120002")
        hum = req.read_by_uuid("2e0d3c00-0002-11ec-9d64-0242ac120002")
        dpt = req.read_by_uuid("2e0d3c00-0003-11ec-9d64-0242ac120002")
        return temp, hum, dpt

    except:
        print("Error getting device data")
        return None


if __name__ == "__main__":

    while(True):
        devices = get_devices()
        print("Searching for devices", devices)

        for device in devices:
            data = get_data(device)
            if data is not None:
                print(data)

        time.sleep(10)
