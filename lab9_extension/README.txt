Lab 9 extension — setup and verification

1. Replace your hosted index.html with the included index.html. Open the updated HTTPS page in Bluefy and reload it.
2. Open test2_bt_module/test2_bt_module.ino in Arduino IDE; select your Pro Mini variant and port, then upload.
3. Retain the working breadboard wiring: HM-10 TX to Arduino 6, common ground, and suitable module power. HM-10 RX is optional for this receive-only test. Do not use pins 0/1 for SoftwareSerial.
4. Open Serial Monitor at 9600 baud. Connect from the webpage.

Expected centered-joystick tests:
- Both switches off: decimal 0, LED off.
- Headlights on only: decimal 16, LED steadily on.
- Horn on only: decimal 32, LED blinks 10 complete cycles per second.
- Both on: decimal 48, LED blinks. Turn horn off: LED returns to steady on.
- Forward with both on: decimal 52.
- STOP now clears all bits and both switches.
- Releasing the joystick clears movement only, retaining switch settings.
- Disconnect or hide the page: all switches clear; receiver turns LED off after 500 ms without valid commands.

The horn is simulated using the built-in LED, as required by the assignment; no buzzer is needed. The blink uses millis(), not delay(): 50 ms on plus 50 ms off makes one 100 ms cycle (10 Hz). Repeated command bytes do not restart the blink timer.

Validation completed: JavaScript encoding and control-event checks; C++ host simulation of LED priority, 50 ms transitions, repeated commands, and timeout. Actual Arduino compilation, iPhone BLE behavior, and physical LED timing still require your hardware test.

Report: use your own setup photos and actual observed results. Required sections in the lab are title/name, summary, given examples, extension, conclusion, and work-distribution/AI-use table. Disclose that AI generated the extension code; describe your own wiring, testing, and troubleshooting accurately. This package contains the programming portion, not a completed experimental report.
