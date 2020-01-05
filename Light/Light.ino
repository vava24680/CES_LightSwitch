#include <Bridge.h>
#define OUTPUT_PIN 7
#define LED_OUTPUT_PIN 13

char pin13_value_str[2];
char output_pin_value_str[2];
int value_int;

int switch_state = 0;

void setup() {
    pinMode(OUTPUT_PIN, OUTPUT);
    pinMode(LED_OUTPUT_PIN, OUTPUT);
    // Disable the relay first
    digitalWrite(OUTPUT_PIN, HIGH);
    Serial.begin(9600);
    Bridge.begin();   // Pins 0 and 1 should be avoided as they are used by the Bridge library.
}

void loop() {
    Bridge.get("Reg_done",  pin13_value_str, 2);
    if ( strcmp(pin13_value_str, "") != 0 ) {
      digitalWrite(LED_OUTPUT_PIN, HIGH);
    }

    Bridge.get("Open",  output_pin_value_str, 2);
    if ( strcmp(output_pin_value_str, "") != 0 ) {
        output_pin_value_str[1] = '\0';
        // Flip the signal since the target rely is triggered by low-voltage
        value_int = atoi(output_pin_value_str) >= 1 ? 0 : 1;
        digitalWrite(OUTPUT_PIN, value_int);
        Bridge.put("Open", "");
    }
}
