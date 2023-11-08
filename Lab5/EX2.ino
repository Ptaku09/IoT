#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <util/atomic.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define ENCODER1 A2
#define ENCODER2 A3

#define RED_BUTTON 2

#define DEBOUNCING_PERIOD 100
#define RED_BUTTON_DEBOUNCING_PERIOD 10

LiquidCrystal_I2C lcd(0x27, 16, 2);

int menuItem = 0;
String menuOptions[] = {"RED", "GREEN", "BLUE", "WHITE"};

int currentRGB[3] = {0, 0, 0};

void printOuterMenu(int menuItem)
{
    lcd.clear();
    lcd.setCursor(0, 0);

    if (menuItem == 3)
    {
        lcd.print("WHITE");
    }
    else
    {
        lcd.print(menuOptions[menuItem]);
        lcd.setCursor(0, 1);
        lcd.print(menuOptions[(menuItem + 1) % 4]);
    }
}

void printInnerMenu()
{
    lcd.clear();
    lcd.setCursor(0, 0);

    for (size_t i = 0; i < currentRGB[menuItem % 3] / 17; i++)
    {
        lcd.print("#");
    }

    lcd.setCursor(0, 1);
    lcd.print(currentRGB[0]);
    lcd.print(" ");
    lcd.print(currentRGB[1]);
    lcd.print(" ");
    lcd.print(currentRGB[2]);
}

void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    pinMode(RED_BUTTON, INPUT_PULLUP);

    pinMode(ENCODER1, INPUT_PULLUP);
    pinMode(ENCODER2, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();
    printOuterMenu(menuItem);

    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT10);
}

bool currentlyOuterMenu = true;

volatile int encoder1 = HIGH;
volatile int encoder2 = HIGH;
volatile unsigned long encoderTimestamp = 0UL;

ISR(PCINT1_vect)
{
    encoder1 = digitalRead(ENCODER1);
    encoder2 = digitalRead(ENCODER2);
    encoderTimestamp = millis();
}

int encoderValue = 0;
int lastEn1 = LOW;
unsigned long lastChangeTimestamp = 0UL;
void loop()
{
    int en1;
    int en2;
    unsigned long timestamp;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        en1 = encoder1;
        en2 = encoder2;
        timestamp = encoderTimestamp;
    }

    if (en1 == LOW && timestamp > lastChangeTimestamp + DEBOUNCING_PERIOD)
    {
        if (en2 == HIGH)
        {
            if (currentlyOuterMenu)
            {
                if (menuItem < 3) menuItem++;
            } 
            else {
                encoderValue = currentRGB[menuItem % 3];
                if (encoderValue < 255)
                encoderValue += 15;
            }
        }
        else
        {
            if (currentlyOuterMenu)
            {
                if (menuItem > 0) menuItem--;
            }
            else {
                encoderValue = currentRGB[menuItem % 3];
                if (encoderValue > 0)
                encoderValue -= 15;
            }
        }
        lastChangeTimestamp = timestamp;

        navigateOuterMenu();
        lastChangeTimestamp = timestamp;
    }
    lastEn1 = en1;

    if (wasRedButtonClicked())
    {
        currentlyOuterMenu = !currentlyOuterMenu;
        if (currentlyOuterMenu)
        {
            printOuterMenu(menuItem);
        }
        else
        {
            printInnerMenu();
        }
    }
}

void navigateOuterMenu()
{
    if (currentlyOuterMenu)
    {
        printOuterMenu(menuItem);
    }
    else
    {
        navigateInnerMenu();
    }
}

void navigateInnerMenu()
{
    if (menuItem == 3)
    {
        currentRGB[0] = encoderValue;
        currentRGB[1] = encoderValue;
        currentRGB[2] = encoderValue;
    }
    else currentRGB[menuItem] = encoderValue;

    printInnerMenu();
    changeRGB();
}

bool wasRedButtonClicked()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(RED_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > RED_BUTTON_DEBOUNCING_PERIOD)
    {
        if (current_reading != debounced_button_state)
        {
            if (debounced_button_state == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debounced_button_state = current_reading;
        }
    }

    previous_reading = current_reading;

    return isPressed;
}

void changeRGB() {
    digitalWrite(LED_RED, currentRGB[0]);
    digitalWrite(LED_GREEN, currentRGB[1]);
    digitalWrite(LED_BLUE, currentRGB[2]);
}

void minOfThree(int a, int b, int c) {
    if (a < b && a < c) return a;
    if (b < a && b < c) return b;
    return c;
}