#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <util/atomic.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define ENCODER1 A2
#define ENCODER2 A3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define DEBOUNCING_PERIOD 100
#define BUTTON_DEBOUNCING_PERIOD 10

LiquidCrystal_I2C lcd(0x27, 16, 2);

int menuItem = 0;
String menuOptions[] = {"RED", "GREEN", "BLUE"};
String charPriorToColor = ">";

int currentRGB[3] = {0, 0, 0};

bool menuActivated = false;

void initMenu() {
  lcd.setCursor(0, 0);

  lcd.print("STEROWANIE RGB");
  lcd.setCursor(0, 1);

  lcd.print(">RED 0");
}

void printMenu()
{
    lcd.setCursor(0, 1);

    int goodMenuItem = abs(menuItem);
    if(menuActivated) charPriorToColor = "*";
    else charPriorToColor = ">";

    lcd.print(charPriorToColor + menuOptions[goodMenuItem % 3] + " " + currentRGB[goodMenuItem % 3] + "     ");
}

void initSerial() {
    Serial.begin(9600);
    while (!Serial) {}
}

void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);

    pinMode(ENCODER1, INPUT_PULLUP);
    pinMode(ENCODER2, INPUT_PULLUP);

    lcd.init();
    lcd.backlight();
    initMenu();

    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT10);

    initSerial();
}

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
            if (!menuActivated)
            {
              menuItem++;
            } 
            else {
              int goodMenuItem = abs(menuItem);
              encoderValue = currentRGB[goodMenuItem % 3];
              if (encoderValue < 100)
              encoderValue += 1;
              currentRGB[goodMenuItem % 3] = encoderValue;
            }
        }
        else
        {
            if (!menuActivated)
            {
              menuItem--;
            }
            else {
              int goodMenuItem = abs(menuItem);
              encoderValue = currentRGB[goodMenuItem % 3];
              if (encoderValue > 0) encoderValue -= 1;
              currentRGB[goodMenuItem % 3] = encoderValue;
            }
        }
        lastChangeTimestamp = timestamp;

        lastChangeTimestamp = timestamp;
    }
    lastEn1 = en1;

    if (wasGreenButtonClicked())
    {
        menuActivated = true;
    }

    if(wasRedButtonClicked()) {
      menuActivated = false;
    }

    printMenu();
    Serial.println(String(currentRGB[0]) + " " + String(currentRGB[1]) + " " + String(currentRGB[2]));
    changeRGB();
}

bool wasRedButtonClicked(){
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(RED_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > BUTTON_DEBOUNCING_PERIOD)
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

bool wasGreenButtonClicked(){
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(GREEN_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > BUTTON_DEBOUNCING_PERIOD)
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
    int red = map(currentRGB[0], 0, 100, 0, 255);
    int green = map(currentRGB[1], 0, 100, 0, 255);
    int blue = map(currentRGB[2], 0, 100, 0, 255);

    digitalWrite(LED_RED, red);
    digitalWrite(LED_GREEN, green);
    digitalWrite(LED_BLUE, blue);
}
