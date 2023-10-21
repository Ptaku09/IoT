#define POTENTIOMETER A0

void initSerial() {
    Serial.begin(9600);
    while (!Serial) {}
}

void setup() {
    initSerial();
}

void loop()
{
    int value = analogRead(POTENTIOMETER);
    String str = String(value);
    Serial.println(str);
}
