#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

bool blink = true;

void blinkRedLed()
{
    const unsigned long redLedBlinkInterval = 500UL;
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

        if (!blink) {
          digitalWrite(LED_RED, LOW);
        } 
        else {
          digitalWrite(LED_RED, redLedState);
        }
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
        
        if (!blink) {
          digitalWrite(LED_GREEN, LOW);
        } 
        else {
          digitalWrite(LED_GREEN, greenLedState);
        }
    }
}

void blinkBlueLed()
{
    const unsigned long blueLedBlinkInterval = 1500UL;
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
        
        if (!blink) {
          digitalWrite(LED_BLUE, LOW);
        } 
        else {
          digitalWrite(LED_BLUE, blueLedState);
        }
    }
}

void stopBlinking() {
    const unsigned long noBlinkInterval = 9000UL;
    const unsigned long noBlinkDuration = 2000UL;

    static unsigned long lastNoBlinkTime = 0UL;
    static unsigned long noBlinkDurationStart = 9000UL;

    if (millis() - lastNoBlinkTime >= noBlinkInterval)
    {
        if (millis() - noBlinkDurationStart < noBlinkDuration) {
          blink = false;
        }
        else {
          blink = true;
          noBlinkDurationStart += noBlinkInterval + noBlinkDuration;
          lastNoBlinkTime += noBlinkInterval + noBlinkDuration;
        }
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
    stopBlinking();
    blinkRedLed();
    blinkGreenLed();
    blinkBlueLed();
}
