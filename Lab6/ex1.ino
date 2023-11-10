#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27,16,2);

OneWire oneWire(A1);
DallasTemperature tempSensors(&oneWire);

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

float tempIn = NULL;
float tempOut = NULL;
float maxTempOut = tempOut;
float minTempOut = tempOut;

void initLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void initRGB() {
    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, LOW);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}


void initTempSensors() {
  tempSensors.begin();
}

void updateMaxMinTemp() {
  tempSensors.requestTemperatures();
  tempIn = tempSensors.getTempCByIndex(1);
  tempOut = tempSensors.getTempCByIndex(0);
  
  if (maxTempOut == NULL || tempOut > maxTempOut) {
      maxTempOut = tempOut;
  }

  if (minTempOut == NULL || tempOut < minTempOut) {
      minTempOut = tempOut;
  }
}

void displayTemperatures() {
  char buffer[40];
  sprintf(buffer, "Temp  IN%8s", String(tempIn, 4).c_str());
  lcd.setCursor(0, 0);
  lcd.print(buffer);

  sprintf(buffer, "Temp OUT%8s", String(tempOut, 4).c_str());
  lcd.setCursor(0, 1);
  lcd.print(buffer);
}

bool isTooCold(float tempOut) {
  return tempOut < 21.0;
}

bool isTooHot(float tempOut) {
  return tempOut > 25.0;
}

void alertComfortZone() {
  if (isTooCold(tempOut)) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
  } else if (isTooHot(tempOut)) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
  } else {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }
}

void setup() {
  initLCD();
  initRGB();
  initTempSensors();
}

void loop() {
  updateMaxMinTemp();
  displayTemperatures();
  alertComfortZone();
}

