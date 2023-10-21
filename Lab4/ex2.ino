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

      analogWrite(LED_RED, red);
      analogWrite(LED_GREEN, 0);
      analogWrite(LED_BLUE, 0);
    } else if (command.startsWith("green")) {
      command.replace("green-", "");
      green = command.toInt();

      analogWrite(LED_RED, 0);
      analogWrite(LED_GREEN, green);
      analogWrite(LED_BLUE, 0);
    } else if (command.startsWith("blue")) {
      command.replace("blue-", "");
      blue = command.toInt();

      analogWrite(LED_RED, 0);
      analogWrite(LED_GREEN, 0);
      analogWrite(LED_BLUE, blue);
    } else {
      Serial.println(String("Unknown command '") + command + "'");
    }
  }
}

