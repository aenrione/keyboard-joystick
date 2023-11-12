#include <Keyboard.h>

// Input Pins
const uint8_t Pin_Joystick_X = A0;         // Turn left/right
const uint8_t Pin_Joystick_Y = A1;         // Turn up/down
const uint8_t Pin_Button_Switch = 8;       // Button of the MX Switch
const uint8_t Pin_Button_Joystick = 9;     // Button of the joystick

// Keyboard KEYS
const char up_key    = 'k';
const char left_key  = 'h';
const char down_key  = 'j';
const char right_key = 'l';

const char joysick_key = 'o';
const char switch_key = 177; //ESC key

// CONSTANTS
const uint8_t joystick_high_threshold = 700; // After this is high
const uint8_t joystick_low_threshold = 300; // Below this is low
const uint8_t polling_delay = 300; // Push/Release delay for keys

// Key states
bool keyW = false;
bool keyA = false;
bool keyS = false;
bool keyD = false;

void setup() {
  // Initialize the keyboard
  Keyboard.begin();

  // Set pin modes for the buttons
  pinMode(Pin_Button_Switch, INPUT_PULLUP);
  pinMode(Pin_Button_Joystick, INPUT_PULLUP);
}

void loop() {
  // Read the joystick X-axis and map it
  int joystickX = analogRead(Pin_Joystick_X);
  if (joystickX < joystick_low_threshold && !keyA) {
    Keyboard.press(right_key);
    keyA = true;
  } else if (joystickX > joystick_high_threshold && !keyD) { 
    Keyboard.press(left_key);
    keyD = true;
  } else if (joystickX >= joystick_low_threshold && joystickX <= joystick_high_threshold && (keyA || keyD)) { // Deathzone
    Keyboard.release(right_key);
    Keyboard.release(left_key);
    keyA = false;
    keyD = false;
  }

  // Read the joystick Y-axis and map it
  int joystickY = analogRead(Pin_Joystick_Y);
  if (joystickY < joystick_low_threshold && !keyW) {
    Keyboard.press(up_key);
    keyW = true;
  } else if (joystickY > joystick_high_threshold && !keyS) {
    Keyboard.press(down_key);
    keyS = true;
  } else if (joystickY >= joystick_low_threshold && joystickY <= joystick_high_threshold && (keyW || keyS)) {
    Keyboard.release(up_key);
    Keyboard.release(down_key);
    keyW = false;
    keyS = false;
  }

  // Check if the MX Switch button is pressed and map it to the space bar
  if (digitalRead(Pin_Button_Switch) == LOW) {
    Keyboard.press(switch_key);
    delay(polling_delay);
    Keyboard.release(switch_key);
  }

  // Check if the joystick button is pressed and map it to the 'X' key
  if (digitalRead(Pin_Button_Joystick) == LOW) {
    Keyboard.press(joysick_key);
    delay(polling_delay);
    Keyboard.release(joysick_key);
  }
}
