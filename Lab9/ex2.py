#!/usr/bin/env python3

from config import *
import w1thermsensor
import os
import neopixel
import board
import busio
import adafruit_bme280.advanced as adafruit_bme280


index = 0
options = ["Temperature", "Humidity", "Pressure"]

temperature = [18, 19, 20, 21, 22, 23, 24, 25]
humidity = [40, 41, 42, 43, 44, 45, 46, 47]
pressure = [1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007]


def ds18b20_config():
    sensor = w1thermsensor.W1ThermSensor()
    return sensor


def bme280_config():
    i2c = busio.I2C(board.SCL, board.SDA)
    bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c, 0x76)

    bme280.sea_level_pressure = 1013.25
    bme280.standby_period = adafruit_bme280.STANDBY_TC_500
    bme280.iir_filter = adafruit_bme280.IIR_FILTER_X16
    bme280.overscan_pressure = adafruit_bme280.OVERSCAN_X16
    bme280.overscan_humidity = adafruit_bme280.OVERSCAN_X1
    bme280.overscan_temperature = adafruit_bme280.OVERSCAN_X2

    return bme280


def pixels_config():
    pixels = neopixel.NeoPixel(board.D18, 8, brightness=1.0 / 32, auto_write=False)

    return pixels


def buttonCallback():
    global index
    index = (index + 1) % len(options)


def show_data():
    ds18b20 = ds18b20_config()
    bme280 = bme280_config()
    pixels = pixels_config()

    GPIO.add_event_detect(
        buttonRed, GPIO.FALLING, callback=buttonCallback, bouncetime=200
    )

    while True:
        pixels.fill((0, 0, 0))

        if options[index] == "Temperature":
            temp = ds18b20.get_temperature()

            for i in range(0, 8):
                if temp >= temperature[i]:
                    pixels[i] = (255, 0, 0)

        elif options[index] == "Humidity":
            hum = bme280.humidity

            for i in range(0, 8):
                if hum >= humidity[i]:
                    pixels[i] = (0, 255, 0)

        elif options[index] == "Pressure":
            pres = bme280.pressure

            for i in range(0, 8):
                if pres >= pressure[i]:
                    pixels[i] = (0, 0, 255)

        pixels.show()


if __name__ == "__main__":
    show_data()
