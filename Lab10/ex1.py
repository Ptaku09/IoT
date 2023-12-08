#!/usr/bin/env python3

import time
from PIL import Image, ImageDraw, ImageFont
import lib.oled.SSD1331 as SSD1331

import board
import busio
import adafruit_bme280.advanced as adafruit_bme280

def oled_config():
    disp = SSD1331.SSD1331()

    # Initialize library.
    disp.Init()
    # Clear display.
    disp.clear()

    # Create blank image for drawing.
    image1 = Image.new("RGB", (disp.width, disp.height), "WHITE")
    draw = ImageDraw.Draw(image1)
    fontLarge = ImageFont.truetype('./lib/oled/Font.ttf', 20)
    fontSmall = ImageFont.truetype('./lib/oled/Font.ttf', 13)

    # print("- draw line")
    # draw.line([(0, 0), (0, 63)], fill="BLUE", width=5)
    # draw.line([(0, 0), (95, 0)], fill="BLUE", width=5)
    # draw.line([(0, 63), (95, 63)], fill="BLUE", width=5)
    # draw.line([(95, 0), (95, 63)], fill="BLUE", width=5)

    # print("- draw rectangle")
    # draw.rectangle([(5, 5), (90, 30)], fill="BLUE")

    # print("- draw text")
    # draw.text((8, 0), u'Hello', font=fontLarge, fill="WHITE")
    # draw.text((12, 40), 'World !!!', font=fontSmall, fill="BLUE")

    # # image1 = image1.rotate(45)
    # disp.ShowImage(image1, 0, 0)
    # time.sleep(2)

    # print("- draw image")
    # image = Image.open('./lib/oled/pic.jpg')
    # disp.ShowImage(image, 0, 0)
    # time.sleep(2)

    # disp.clear()
    # disp.reset()

    return disp, image1, draw, fontSmall, fontLarge

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

def show_params():
    disp, image1, draw, fontSmall, fontLarge = oled_config()
    bme280 = bme280_config()

    while True:
        draw.rectangle([(0, 0), (95, 63)], fill="WHITE")
        temp = bme280.temperature
        humidity = bme280.humidity
        pressure = bme280.pressure
        
        draw.text((0, 0), f' 🌡 Temp: {temp:.2f} ℃', font=fontLarge, fill="BLUE")
        draw.text((0, 20), f' 💧 Humidity: {humidity:.2f} %', font=fontLarge, fill="BLUE")
        draw.text((0, 40), f' 📈 Pressure: {pressure:.2f} hPa', font=fontLarge, fill="BLUE")
        
        disp.ShowImage(image1, 0, 0)
        time.sleep(1)


if __name__ == "__main__":
    show_temp()
