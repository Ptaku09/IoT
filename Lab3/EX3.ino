#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RED_BUTTON 2
#define GREEN_BUTTON 4

bool working = false;
bool display = true;
int seconds = 0;

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void displayTime()
{
  lcd.setCursor(9, 0);
  lcd.print(seconds);
}

void measureTime() {
  const unsigned long timeInterval = 1000UL;
    static unsigned long lastTime = 0UL;

    if (millis() - lastTime >= timeInterval){
      if(working){
        seconds++;
      }
    
      lastTime += timeInterval;
    }
}

#define DEBOUNCE_PERIOD 10UL

bool isRedButtonPressed(){
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(RED_BUTTON);

    if (previous_reading != current_reading){
      last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD){
      if (current_reading != debounced_button_state){
        if (debounced_button_state == HIGH && current_reading == LOW) {
          isPressed = true;
        }
        debounced_button_state = current_reading;
      }
    }

    previous_reading = current_reading;

    return isPressed;
}

bool isGreenButtonPressed(){
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(GREEN_BUTTON);

    if (previous_reading != current_reading){
      last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD){
      if (current_reading != debounced_button_state){
        if (debounced_button_state == HIGH && current_reading == LOW) {
          isPressed = true;
        }
        debounced_button_state = current_reading;
      }
    }

    previous_reading = current_reading;

    return isPressed;
}


void resetTimer()
{
  seconds = 0;
  working = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Seconds: 0");
}

void setup()
{
    initButtons();

    lcd.init();
    lcd.backlight();

    lcd.print("Seconds: 0");
    lcd.setCursor(9, 0);
}

void loop(){
  measureTime();
  
  if (display) displayTime();

  if(isGreenButtonPressed()) {
     if (!working && display) working = !working;
     else if(working && display) display = !display;
     else if (working && !display) display = !display;
  }

  if(isRedButtonPressed()) {
    resetTimer();
    working = false;
    display = true;
  }
}
