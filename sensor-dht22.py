# dht22 and am2302 for Raspberry Pi by Guy Francoeur 2023
#
# apt install libgpiod2
# pip3 install adafruit-dht
#
# Two sensors on GPIO 4 and 20

import Adafruit_DHT
import time

DHT_SENSOR = Adafruit_DHT.DHT22
GPIO_ID = 4

while True:
    humidity, temp_c = Adafruit_DHT.read_retry(DHT_SENSOR, GPIO_ID)

    if humidity is not None and temp_c is not None:
        temp_f = temp_c * (9 / 5) + 32
        print("Sensor PIN  4: {:0.1f}C / {:0.1f}F -- Humidity={:0.1f}%".format(temp_c, temp_f, humidity))
    #else:
    #    print("Failed to retrieve data from humidity sensor")

    h, t = Adafruit_DHT.read_retry(DHT_SENSOR, 20)
    if h is not None and t is not None:
        f = t * (9 / 5) + 32
        print("Sensor PIN 20: {:0.1f}C / {:0.1f}F -- Humidity={:0.1f}%\n\n".format(t, f, h))

    time.sleep(5.0)
