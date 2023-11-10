#include "DiodeHandler.h"

DiodeHandler diodeHandler(6, 5, 3);

void setup() {
    diodeHandler.init();
}

void loop() {
    diodeHandler.showColor("RED");
    delay(1000);

    diodeHandler.showColor("GREEN");
    delay(1000);

    diodeHandler.showColor("BLUE");
    delay(1000);

    diodeHandler.showColor("YELLOW");
    delay(1000);

    diodeHandler.showColor("CYAN");
    delay(1000);

    diodeHandler.showColor("MAGENTA");
    delay(1000);

    diodeHandler.showColor("WHITE");
    delay(1000);

    diodeHandler.showColor("BLACK");
    delay(1000);

    diodeHandler.writeAll(20, 40, 60);
    delay(1000);
}