/*
 Terminal input, serial output
 To determine the long Push and short Push
 */

#include <InputTerminal.h>

// Instantiate a InputTerminal object with BUTTON_0 to BUTTON_2
// the number of the pushbutton pin
#define BUTTON_0 6
#define BUTTON_1 5
#define BUTTON_2 2
unsigned char sw_list[] = { BUTTON_0, BUTTON_1, BUTTON_2 };
InputTerminal tm(sw_list, sizeof(sw_list));

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // Serial port connection waiting
  }
}

void loop() {
  unsigned int shortonw;
  unsigned int longonw;

  tm.scan();                  // Update the terminaldata
  shortonw = tm.read_s();     // Read the short key input data
  longonw = tm.read_l();      // Read the long key input data

  if (shortonw != 0) {
    switch (shortonw) {
      case 0x01:
        Serial.println("Short ON : BUTTON_0\n");
        break;
      case 0x02:
        Serial.println("Short ON : BUTTON_1\n");
        break;
      case 0x03:
        Serial.println("Short ON : BUTTON_0 & BUTTON_1\n");
        break;
      case 0x04:
        Serial.println("Short ON : BUTTON_2\n");
        break;
      case 0x05:
        Serial.println("Short ON : BUTTON_0 & BUTTON_2\n");
        break;
      case 0x06:
        Serial.println("Short ON : BUTTON_1 & BUTTON_2\n");
        break;
      case 0x07:
        Serial.println("Short ON : BUTTON_0 & BUTTON_1 & BUTTON_2\n");
        break;
      default:
        Serial.println("Short Other Key.\n");
        break;
    }
  }
  else if (longonw != 0) {
    switch (longonw) {
      case 0x01:
        Serial.println("Long ON : BUTTON_0\n");
        break;
      case 0x02:
        Serial.println("Long ON : BUTTON_1\n");
        break;
      case 0x03:
        Serial.println("Long ON : BUTTON_0 & BUTTON_1\n");
        break;
      case 0x04:
        Serial.println("Long ON : BUTTON_2\n");
        break;
      case 0x05:
        Serial.println("Long ON : BUTTON_0 & BUTTON_2\n");
        break;
      case 0x06:
        Serial.println("Long ON : BUTTON_1 & BUTTON_2\n");
        break;
      case 0x07:
        Serial.println("Long ON : BUTTON_0 & BUTTON_1 & BUTTON_2\n");
        break;
     default:
        Serial.println("Long Other Key.\n");
        break;
    }
  }
  else {}

}




