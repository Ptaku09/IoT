#define LED_RED 6

#define RED_BUTTON 2
#define GREEN_BUTTON 4

int brighteness = 126;

void initRGB() {
  pinMode(LED_RED, OUTPUT);
  analogWrite(LED_RED, brighteness);
}

void initButtons() {
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void setup() {
  initRGB();
  initButtons();
}

void loop() {
  if (digitalRead(RED_BUTTON) == LOW && brighteness > 0) {
    brighteness--;
    analogWrite(LED_RED, brighteness);
    delay(10);
  }

  if (digitalRead(GREEN_BUTTON) == LOW && brighteness < 255) {
    brighteness++;
    analogWrite(LED_RED, brighteness);
    delay(10);
  }
}

