#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

void initRGB() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(LED_RED, OUTPUT);
  analogWrite(LED_RED, 255);

  pinMode(LED_GREEN, OUTPUT);
  analogWrite(LED_GREEN, 0);

  pinMode(LED_BLUE, OUTPUT);
  analogWrite(LED_BLUE, 0);
}

void setup() {
  initRGB();
}

void increase(int led) {
  for (int i = 1; i <= 255; i++) {
    analogWrite(led, i);
    delay(5);
  }
}

void decrease(int led) {
  for (int i = 254; i >= 0; i--) {
    analogWrite(led, i);
    delay(5);
  }
}

void loop() {
  increase(LED_GREEN);
  decrease(LED_RED);
  increase(LED_BLUE);
  decrease(LED_GREEN);
  increase(LED_RED);
  decrease(LED_BLUE);
}

