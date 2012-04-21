#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

char nav_keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'} 
};

byte row_pins[rows] = {5, 4, 3, 2};
byte col_pins[cols] = {8, 7, 6};

Keypad keypad = Keypad( makeKeymap(keys), row_pins, col_pins, rows, cols );
