#include "DiodeHandler.h"

void copyArray(int tabAim[], int tabFrom[], int len) {
    for(int i = 0; i < len; i++) {
        tabAim[i] = tabFrom[i];
    }
}

MyColor::MyColor(String name) {
    switch(name) {
        case "RED":
            copyArray(rgb, RED, rgbLen);
            break;
        case "GREEN":
            copyArray(rgb, GREEN, rgbLen);
            break;
        case "BLUE":
            copyArray(rgb, BLUE, rgbLen);
            break;
        case "YELLOW":
            copyArray(rgb, YELLOW, rgbLen);
            break;
        case "CYAN":
            copyArray(rgb, CYAN, rgbLen);
            break;
        case "MAGENTA":
            copyArray(rgb, MAGENTA, rgbLen);
            break;
        case "WHITE":
            copyArray(rgb, WHITE, rgbLen);
            break;
        case "BLACK":
            copyArray(rgb, BLACK, rgbLen);
            break;
    }
};

MyColor::MyColor(int r, int g, int b) {
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
};

int MyColor::red() {
    return rgb[0];
}

int MyColor::green() {
    return rgb[1];
}

int MyColor::blue() {
    return rgb[2];
}

DiodeHandler::DiodeHandler(int pinR, int pinG, int pinB) {
    r = pinR;
    g = pinG;
    b = pinB;
};

void DiodeHandler::init() {
    pinMode(r, OUTPUT);
    digitalWrite(r, LOW);

    pinMode(g, OUTPUT);
    digitalWrite(g, LOW);

    pinMode(b, OUTPUT);
    digitalWrite(b, LOW);
}

void DiodeHandler::writeRed(int val) {
    analogWrite(r, val);
}

void DiodeHandler::writeGreen(int val) {
    analogWrite(g, val);
}

void DiodeHandler::writeBlue(int val) {
    analogWrite(b, val);
}

void DiodeHandler::writeAll(int valR, int valG, int valB) {
    analogWrite(r, valR);
    analogWrite(g, valG);
    analogWrite(b, valB);
}

void DiodeHandler::showColor(String color) {
    MyColor myColor(color);

    analogWrite(r, myColor.red());
    analogWrite(g, myColor.green());
    analogWrite(b, myColor.blue());
}