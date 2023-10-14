#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

void blinkRedLed()
{
    const unsigned long redLedBlinkInterval = 900UL;
    static int redLedState = LOW;
    static unsigned long lastRedLedBlinkTime = 0UL;

    if (millis() - lastRedLedBlinkTime >= redLedBlinkInterval)
    {
        if (redLedState == HIGH)
        {
            redLedState = LOW;
        }
        else
        {
            redLedState = HIGH;
        }

        lastRedLedBlinkTime += redLedBlinkInterval;
        digitalWrite(LED_RED, redLedState);
    }
}

void blinkGreenLed()
{
    const unsigned long greenLedBlinkInterval = 1000UL;
    static int greenLedState = LOW;
    static unsigned long lastGreenLedBlinkTime = 0UL;

    if (millis() - lastGreenLedBlinkTime >= greenLedBlinkInterval)
    {
        if (greenLedState == HIGH)
        {
            greenLedState = LOW;
        }
        else
        {
            greenLedState = HIGH;
        }

        lastGreenLedBlinkTime += greenLedBlinkInterval;
        digitalWrite(LED_GREEN, greenLedState);
    }
}

void blinkBlueLed()
{
    const unsigned long blueLedBlinkInterval = 1100UL;
    static int blueLedState = LOW;
    static unsigned long lastBlueLedBlinkTime = 0UL;

    if (millis() - lastBlueLedBlinkTime >= blueLedBlinkInterval)
    {
        if (blueLedState == HIGH)
        {
            blueLedState = LOW;
        }
        else
        {
            blueLedState = HIGH;
        }

        lastBlueLedBlinkTime += blueLedBlinkInterval;
        digitalWrite(LED_BLUE, blueLedState);
    }
}

void setup()
{
    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, LOW);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

void loop()
{
    blinkRedLed();
    blinkGreenLed();
    blinkBlueLed();
}