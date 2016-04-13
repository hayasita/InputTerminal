/*
 Terminal input, serial output
 
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
  unsigned int onw;

  tm.scan();           // Update the terminaldata
  onw = tm.read();     // Read the key input data

  if (onw != 0) {
    switch (onw) {
      case 0x01:
        Serial.println("ON : BUTTON_0\n");
        break;
      case 0x02:
        Serial.println("ON : BUTTON_1\n");
        break;
      case 0x03:
        Serial.println("ON : BUTTON_0 & BUTTON_1\n");
        break;
      case 0x04:
        Serial.println("ON : BUTTON_2\n");
        break;
      case 0x05:
        Serial.println("ON : BUTTON_0 & BUTTON_2\n");
        break;
      case 0x06:
        Serial.println("ON : BUTTON_1 & BUTTON_2\n");
        break;
      case 0x07:
        Serial.println("ON : BUTTON_0 & BUTTON_1 & BUTTON_2\n");
        break;
      default:
        Serial.println("Other Key.\n");
        break;
    }
  }
  else {}

}




