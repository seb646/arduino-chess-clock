// Define dependencies
#include <ezButton.h>  // Ref: https://arduinogetstarted.com/tutorials/arduino-button-library

// Define button variables; Ref: https://arduinogetstarted.com/faq/arduino-how-to-detect-button-press-event
ezButton BUTTON1(4);           // Player 1; Pin 4
ezButton BUTTON2(11);          // Player 2; Pin 11
bool BUTTON1_PRESSED = false;  // Player 1 button state
bool BUTTON2_PRESSED = false;  // Player 2 button state

// Define LED variables
int LED1 = 2;   // Player 1; Pin 2; Green LED
int LED2 = 13;  // Player 2; Pin 13; Blue LED

// Define time variables
unsigned long START_TIME = 600;       // 10 Mins = 600 Seconds; Unit: Seconds
unsigned long TIME1 = START_TIME;     // Player 1 time
unsigned long TIME2 = START_TIME;     // Player 2 time
unsigned long GAME_TIME = 0;          // Set current game time; Unit: Seconds
unsigned long PREVIOUS_TIME = 0;      // Define previous run time
unsigned long COUNT_INTERVAL = 1000;  // Set count interval; Unit: Milliseconds

// Setup code, runs once on program start
void setup() {
  // Init pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Init serial communication
  Serial.begin(9600);

  // Debounce the buttons
  BUTTON1.setDebounceTime(50);
  BUTTON2.setDebounceTime(50);

  // Communicate instructions to users
  delay(1000);
  Serial.println("Welcome, players!");
  Serial.println("Player 1 is GREEN.");
  Serial.println("Player 2 is BLUE.");
  Serial.println("Each player has 10 minutes each to complete their turns.");
  Serial.println("Press any button to begin. The player who has a light on goes first!");
  delay(100);
}

// Loop code, runs continuously
void loop() {
  // Find current button state
  findButtonStates();

  // --------------------------------------------
  // PLAYER 1 LOGIC
  // --------------------------------------------
  if (TIME1 > 0) {
    while (BUTTON1_PRESSED) {
      // Set LED states
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);

      // Get current run time; Counter Ref: https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay
      unsigned long CURRENT_TIME = millis();

      if (CURRENT_TIME - PREVIOUS_TIME >= COUNT_INTERVAL) {
        // Save current run time to counter
        PREVIOUS_TIME = CURRENT_TIME;

        // Lower Player 1 time by 1 second
        TIME1 = TIME1 - 1;

        // Add 1 second to current time
        GAME_TIME = GAME_TIME + 1;

        // Print current times to serial
        Serial.println("----------------------");
        Serial.println("Overall Game Time: ");
        Serial.println(GAME_TIME);
        Serial.println("seconds");
        Serial.println("------");
        Serial.println("Player 1 (Green) Time: ");
        Serial.println(TIME1);
        Serial.println("seconds");
        Serial.println("------");
        Serial.println("Player 2 (Blue) Time: ");
        Serial.println(TIME2);
        Serial.println("seconds");
        Serial.println("----------------------");
      }

      // Check button states before next iteration
      findButtonStates();
    }
  } else if (BUTTON1_PRESSED) {
    Serial.println("Player 1 (Green) has run out of time! :(");
  }

  // --------------------------------------------
  // PLAYER 2 LOGIC
  // --------------------------------------------
  if (TIME2 > 0) {
    while (BUTTON2_PRESSED) {
      // Set LED states
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, LOW);

      // Get current time
      unsigned long CURRENT_TIME = millis();

      if (CURRENT_TIME - PREVIOUS_TIME >= COUNT_INTERVAL) {
        // Save current time to counter
        PREVIOUS_TIME = CURRENT_TIME;

        // Lower Player 2 time by 1 second
        TIME2 = TIME2 - 1;

        // Add 1 second to current time
        GAME_TIME = GAME_TIME + 1;

        // Print current times to serial
        Serial.println("----------------------");
        Serial.println("Overall Game Time: ");
        Serial.println(GAME_TIME);
        Serial.println("seconds");
        Serial.println("------");
        Serial.println("Player 1 (Green) Time: ");
        Serial.println(TIME1);
        Serial.println("seconds");
        Serial.println("------");
        Serial.println("Player 2 (Blue) Time: ");
        Serial.println(TIME2);
        Serial.println("seconds");
        Serial.println("----------------------");
      }

      // Check button states before next iteration
      findButtonStates();
    }
  } else if (BUTTON2_PRESSED) {
    Serial.println("Player 2 (Blue) has run out of time! :(");
  }
}

// Function: find current state of buttons 1 and 2
void findButtonStates() {
  // Must init buttons by calling loop function; Ref: https://arduinogetstarted.com/library/button/example/arduino-multiple-button-all
  BUTTON1.loop();
  BUTTON2.loop();

  // Check button press states
  if (BUTTON1.isPressed()) {
    BUTTON1_PRESSED = true;
    BUTTON2_PRESSED = false;
  } else if (BUTTON2.isPressed()) {
    BUTTON1_PRESSED = false;
    BUTTON2_PRESSED = true;
  }
}