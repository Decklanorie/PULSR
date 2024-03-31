#include <SoftwareSerial.h>  // Include for serial communication

// Define pin assignments
const int SW1_FR = 10;
const int SW2_FR = 9;
const int SW1_ENB = 2;
const int SW2_ENB = 8;
const int MotionPin = 4;

// Software serial for rxd (replace RX_PIN with your actual rxd pin)
const int RX_PIN = 10;  // Replace with your rxd pin
SoftwareSerial mySerial(RX_PIN, 11); // TX pin not used

// Variables for received message
String rxMessage = "";
String motion = "FORWARD";

void setup() {
  // Set brake pins as outputs and connect to COM (ground)

  // Set remaining pins as inputs
  pinMode(SW1_FR, INPUT);
  pinMode(SW2_FR, INPUT);
  pinMode(SW1_ENB, INPUT);
  pinMode(SW2_ENB, INPUT);
  pinMode(MotionPin, INPUT);

  mySerial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Check for incoming serial messages
  while (mySerial.available()) {
    char ch = mySerial.read();
    rxMessage += ch;
    if (ch == '\n') {
      processReceivedMessage();
    }
  }

  // Check motion pin and switch states
  if (digitalRead(MotionPin) == HIGH) {
    controlMotors();
  } else {
    // Stop motors if motion pin is low
    digitalWrite(SW1_ENB, LOW);
    digitalWrite(SW2_ENB, LOW);
  }
}

void controlMotors() {
  if(motion == 'FORWARD'){
    digitalWrite(SW1_ENB, HIGH);
    digitalWrite(SW2_ENB, HIGH);
    digitalWrite(SW1_FR, LOW);
    digitalWrite(SW2_FR, HIGH);
  }else if(motion == 'BACKWARD'){
    digitalWrite(SW1_ENB, HIGH);
    digitalWrite(SW2_ENB, HIGH);
    digitalWrite(SW1_FR, HIGH);
    digitalWrite(SW2_FR, LOW);
  }else{
    digitalWrite(SW1_ENB, LOW);
    digitalWrite(SW2_ENB, LOW);
  }
}

void processReceivedMessage() {
  if (rxMessage.startsWith("DIRECTION_TYPE:BACKWARD")) {
    motion = 'BACKWARD';
  } else if (rxMessage.startsWith("DIRECTION_TYPE:FORWARD")) {
    motion = 'FORWARD';
  }
  rxMessage = "";
  Serial.println("");
    Serial.print("System is moving: ");
    Serial.println(motion);
}
