#include <SoftwareSerial.h>

// HM-10 TX -> Arduino 6; common GND; power for your breakout.
// HM-10 RX may be left disconnected for this receive-only test.
// If connected to Arduino 7, use suitable level shifting for 5 V logic.
SoftwareSerial bt_SW_serial(6, 7); // RX, TX
const byte HEADLIGHTS = 0x10; // bit 4
const byte HORN = 0x20;       // bit 5
const unsigned long HALF_PERIOD_MS = 50; // 50 ms ON + 50 ms OFF = 10 Hz
const unsigned long TIMEOUT_MS = 500;
byte command = 0;
bool hornWasOn = false;
bool ledOn = false;
unsigned long lastReceived = 0;
unsigned long lastToggle = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  bt_SW_serial.begin(9600);
  Serial.begin(9600);
  Serial.println("Waiting for Bluetooth commands...");
}

void loop() {
  while (bt_SW_serial.available() > 0) {
    byte received = bt_SW_serial.read();
    // Upper two bits are unused; ignore invalid commands.
    if (received & 0xC0) continue;
    command = received;
    lastReceived = millis();
    Serial.print("Decimal: ");
    Serial.print(command);
    Serial.print("  Binary: ");
    Serial.println(command, BIN);
  }

  unsigned long now = millis();
  if (now - lastReceived >= TIMEOUT_MS) command = 0;
  bool hornOn = (command & HORN) != 0;
  if (hornOn) {
    // Horn takes priority over headlights; do not restart on repeated bytes.
    if (!hornWasOn) {
      ledOn = true;
      lastToggle = now;
    } else if (now - lastToggle >= HALF_PERIOD_MS) {
      unsigned long intervals = (now - lastToggle) / HALF_PERIOD_MS;
      if (intervals & 1UL) ledOn = !ledOn;
      lastToggle += intervals * HALF_PERIOD_MS;
    }
  } else {
    ledOn = (command & HEADLIGHTS) != 0;
  }
  hornWasOn = hornOn;
  digitalWrite(LED_BUILTIN, ledOn ? HIGH : LOW);
}
