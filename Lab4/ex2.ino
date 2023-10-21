#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

void initRGB()
{
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_GREEN, LOW);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_BLUE, LOW);
}

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}

  initRGB();
}

int red = 0;
int green = 0;
int blue = 0;

void loop()
{
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil("\n");
    command.trim();
    command.toLowerCase();

    if (command.startsWith("red")) {
      command.replace("red-", "");
      red = command.toInt();

      if (command == "0") {
        analogWrite(LED_RED, 0);
      }

      if (red != 0) {
        analogWrite(LED_RED, red);
      }
    } else if (command.startsWith("green")) {
      command.replace("green-", "");

      if (command == "0") {
        analogWrite(LED_GREEN, 0);
      }

      green = command.toInt();

      if (green != 0) {
        analogWrite(LED_GREEN, green);
      }
    } else if (command.startsWith("blue")) {
      command.replace("blue-", "");
      blue = command.toInt();

      if (command == "0") {
        analogWrite(LED_BLUE, 0);
      }

      if (blue != 0) {
        analogWrite(LED_BLUE, blue);
      }
    } else {
      Serial.println(String("Unknown command '") + command + "'");
    }
  }
}

