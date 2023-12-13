#!/usr/bin/env python3

# pylint: disable=no-member

import time
import RPi.GPIO as GPIO
from config import *  # pylint: disable=unused-wildcard-import
from mfrc522 import MFRC522

import datetime

import board
import neopixel

registered_cards = []

pixels = neopixel.NeoPixel(
        board.D18, 8, brightness=1.0/32, auto_write=False)

def buzzer(state):
    GPIO.output(buzzerPin, not state)

def rfidRead():
    global pixels
    MIFAREReader = MFRC522()
    
    while True:
        (status, TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)
        if status == MIFAREReader.MI_OK:
            (status, uid) = MIFAREReader.MFRC522_Anticoll()
            if status == MIFAREReader.MI_OK:
                if uid not in registered_cards:
                    registered_cards.append((uid, datetime.datetime.now()))
                    print("New card detected and registered. UID: " + str(uid) + " Time: " + str(datetime.datetime.now()))
                    buzzer(True)
                    pixels.fill((0, 255, 0))
                    time.sleep(0.5)
                    pixels.fill((0, 0, 0))
                    buzzer(False)
                    
                
                time.sleep(0.5)

if __name__ == "__main__":
    rfidRead()
    GPIO.cleanup()  # pylint: disable=no-member
