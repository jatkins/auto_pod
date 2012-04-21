#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

const byte ROWS = 4;
const byte COLS = 3;

char nav_keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'} 
};

LiquidCrystal lcd(12, 11, 10, 9, 13, 14);

byte row_pins[ROWS] = {5, 4, 3, 2};
byte col_pins[COLS] = {8, 7, 6};

Keypad keypad = Keypad( makeKeymap(nav_keys), row_pins, col_pins, ROWS, COLS );

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, world"); 
}

void loop() {
  lcd.setCursor(0,1);
  lcd.print(millis()/1000); 
}
