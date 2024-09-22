#include <Arduino.h>
#include <gf2x.h>

void setup() {
    Serial.begin(115200);
    delay(2000);
    Serial.println("Running on GF2X v" + String(GF2X_VERSION_MAJOR) + "." + String(GF2X_VERSION_MINOR) + "." + String(GF2X_VERSION_PATCHLEVEL));
}

void loop() {
    unsigned long a[4] = {0x01ABCDEF, 0xFFFFFFFF, 0x00000000};
    unsigned long b[4] = {0x01ABCDEF, 0xFFFFFFFF, 0x00000000};
    unsigned long c[4+4] = {};
    gf2x_mul(c, a, 4, b, 4);
    Serial.println("Result C:");
    for(int i=0; i < sizeof(c) / sizeof(*c); i++) {
        Serial.print(c[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
    delay(1000);
}