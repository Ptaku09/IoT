#!/usr/bin/env python3

from config import *
import RPi.GPIO as GPIO


dutyCycle = 0
diode = GPIO.PWM(led1, 50)
previousLeft = GPIO.input(encoderLeft)
previousRight = GPIO.input(encoderRight)


def encoderCallback(_):
    global dutyCycle
    global previousLeft
    global previousRight

    currentLeft = GPIO.input(encoderLeft)
    currentRight = GPIO.input(encoderRight)

    if previousLeft == 1 and currentLeft == 0 and dutyCycle < 100:
        dutyCycle += 5
        diode.ChangeDutyCycle(dutyCycle)

    if previousRight == 1 and currentRight == 0 and dutyCycle > 0:
        dutyCycle -= 5
        diode.ChangeDutyCycle(dutyCycle)


def diodeBrightness():
    diode.start(dutyCycle)

    GPIO.add_event_detect(
        encoderLeft, GPIO.FALLING, callback=encoderCallback, bouncetime=200
    )
    GPIO.add_event_detect(
        encoderRight, GPIO.FALLING, callback=encoderCallback, bouncetime=200
    )

    while True:
        pass


if __name__ == "__main__":
    diodeBrightness()
