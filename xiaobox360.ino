/*
 * Xbox 360 Wireless Controller Adapter for Xiao RP2040
 * This code has been updated to merge logic from the XboxSlimRfReceiver source.
 * It interfaces with the RF module from an Xbox 360 wireless
 * controller receiver.
 *
 * Connection Guide:
 * - DATA_PIN (GPIO 6) to RF module's data line
 * - CLOCK_PIN (GPIO 7) to RF module's clock line
 * - 3.3V from Xiao to VCC on RF module
 * - GND from Xiao to GND on RF module
 * - BUTTON_PIN (GPIO 2) to button for sync trigger
 */

// Pin definitions from mycode.txt
#define DATA_PIN 6
#define CLOCK_PIN 7
#define BUTTON_PIN 2

// Commands from XboxSlimRfReceiver.txt
int start_cmd[10] = {0,0,0,0,0,1,0,0,1,0}; // Start Module command
int power_cmd[10] = {0,0,1,0,0,0,0,1,0,1}; // Ring of light startup animation command
int sync_cmd[11] = {0,0,0,0,0,0,0,1,0,0,1}; // Sync initiation command

// Data sending function for 11-bit commands from XboxSlimRfReceiver.txt
void sendData11(int cmd_do[]) {
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, LOW); // Start sending data
  int prev = 1;
  for(int i = 0; i < 11; i++){
    while (prev == digitalRead(CLOCK_PIN)){} // Wait for a change on the clock pin
    prev = digitalRead(CLOCK_PIN);
    delayMicroseconds(1000); // Delay after the downward edge of the clock
    digitalWrite(DATA_PIN, cmd_do[i]);
    while (prev == digitalRead(CLOCK_PIN)){} // Wait for the upward edge of the clock
    prev = digitalRead(CLOCK_PIN);
  }
  digitalWrite(DATA_PIN, HIGH);
  pinMode(DATA_PIN, INPUT); // Set data pin back to input
}

// Data sending function for 10-bit commands from XboxSlimRfReceiver.txt
void sendData10(int cmd_do[]) {
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, LOW); // Start sending data
  int prev = 1;
  for(int i = 0; i < 10; i++){ // Loop for 10 bits
    while (prev == digitalRead(CLOCK_PIN)){} // Wait for a change on the clock pin
    prev = digitalRead(CLOCK_PIN);
    delayMicroseconds(1000); // Delay after the downward edge of the clock
    digitalWrite(DATA_PIN, cmd_do[i]);
    while (prev == digitalRead(CLOCK_PIN)){} // Wait for the upward edge of the clock
    prev = digitalRead(CLOCK_PIN);
  }
  digitalWrite(DATA_PIN, HIGH);
  pinMode(DATA_PIN, INPUT); // Set data pin back to input
}

// LED initialization routine from XboxSlimRfReceiver.txt
void initLEDs(){
  sendData10(start_cmd);
  delay(50);
  sendData10(power_cmd);
  delay(50);
}

void setup() {
  Serial.begin(9600); 
  Serial.print("Initializing...");

  // Initialize pins, keeping the pullup for the button from mycode.txt
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, INPUT);

  delay(1000);
  initLEDs(); // Run the LED startup sequence
  Serial.println("OK");
}

void loop() {
  // Check if the sync button is pressed (active low due to INPUT_PULLUP)
  if(digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Synchronizing...");
    sendData11(sync_cmd); // Send the 11-bit sync command
    delay(3000); // Wait for sync process
  }
  delay(100);
}