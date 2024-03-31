// first encoder pins
const int FIRST_ENCODER_PIN_A = 2;
const int FIRST_ENCODER_PIN_B = 3;

// second encoder pins
const int SECOND_ENCODER_PIN_C = 5;
const int SECOND_ENCODER_PIN_D = 6;



const int MOTION_PIN = 4; //from loadcell microcontroller

volatile int FIRST_ENCODER_POSITION = 0;  // Current position of the first encoder
volatile int FIRST_ENCODER_FORMAL_POSITION = 0;  
volatile unsigned long FIRST_ENCODER_LAST_TIME = 0;
volatile float FIRST_ENCODER_SPEED = 0.0;

volatile int SECOND_ENCODER_POSITION = 0;  // Current position of the second encoder
volatile int SECOND_ENCODER_FORMAL_POSITION = 0;  
volatile unsigned long SECOND_ENCODER_LAST_TIME = 0;
volatile float SECOND_ENCODER_SPEED = 0.0;


//Declare encoder position in degrees
float FIRST_ENCODER_DEGREE = 0.0;
float SECOND_ENCODER_DEGREE = 0.0;


//CONSTANTS TO BE DETERMINED
const int FIRST_MAX_DEGREE = 90;
const int FIRST_MIN_DEGREE = 0;//almost equal to FIRST_ENCODER_DEGREE_CONSTANT
const int SECOND_MAX_DEGREE = 90;
const int SECOND_MIN_DEGREE = 0; //almost equal to SECOND_ENCODER_DEGREE_CONSTANT
float FIRST_ENCODER_DEGREE_CONSTANT = 0.0;//Declare encoder constant initial position in degrees
float SECOND_ENCODER_DEGREE_CONSTANT = 0.0;//Declare encoder constant initial position in degrees
// Define constants for distance per pulse and pulses per meter
const int PPR = 2000; // Pulses per revolution
const float HOUSING_DIAMETER_MM = 40.0; // Diameter of the encoder housing in millimeters
const float HOUSING_RADIUS_MM = HOUSING_DIAMETER_MM / 2.0; // Radius of the encoder housing in millimeters

// Calculate the circumference in millimeters
const float CIRCUMFERENCE_MM = 2.0 * PI * HOUSING_RADIUS_MM;

// Convert the circumference to meters
const float CIRCUMFERENCE_M = CIRCUMFERENCE_MM / 1000.0; 
// Calculate distance traveled per pulse in meters
float distancePerPulse_M = CIRCUMFERENCE_M / PPR;



void setup() {
  Serial.begin(9600);
  pinMode(MOTION_PIN, INPUT);
  pinMode(FIRST_ENCODER_PIN_A, INPUT);
  pinMode(FIRST_ENCODER_PIN_B, INPUT);
  pinMode(SECOND_ENCODER_PIN_C, INPUT);
  pinMode(SECOND_ENCODER_PIN_D, INPUT);


  // Enabling interrupts for the first encoder pins
  attachInterrupt(digitalPinToInterrupt(FIRST_ENCODER_PIN_A), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FIRST_ENCODER_PIN_B), updateEncoder, CHANGE);

  // Enabling interrupts for the second encoder pins
  attachInterrupt(digitalPinToInterrupt(SECOND_ENCODER_PIN_C), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SECOND_ENCODER_PIN_D), updateEncoder, CHANGE);


  // Read and store initial positions
  FIRST_ENCODER_POSITION = readEncoderPosition(digitalRead(FIRST_ENCODER_PIN_A), digitalRead(FIRST_ENCODER_PIN_B));
  SECOND_ENCODER_POSITION = readEncoderPosition(digitalRead(SECOND_ENCODER_PIN_C), digitalRead(SECOND_ENCODER_PIN_D));

  // Set initial formal positions
  FIRST_ENCODER_FORMAL_POSITION = FIRST_ENCODER_POSITION;
  SECOND_ENCODER_FORMAL_POSITION = SECOND_ENCODER_POSITION;


  // Calculate relative positions in degrees
  FIRST_ENCODER_DEGREE = ((float)FIRST_ENCODER_POSITION - FIRST_ENCODER_DEGREE_CONSTANT) / PPR * 360.0;
  SECOND_ENCODER_DEGREE = ((float)SECOND_ENCODER_POSITION - SECOND_ENCODER_DEGREE_CONSTANT) / PPR * 360.0;

  //system is not in motion 
  Serial.println("Listening for force input...");

}


void updateEncoder() {
  
  // Check if system in motion
  if(digitalRead(MOTION_PIN) == HIGH){
  


  
    // Read and store positions of encoder pins
    FIRST_ENCODER_POSITION = readEncoderPosition(digitalRea(FIRST_ENCODER_PIN_A, digitalRead(FIRST_ENCODER_PIN_B));
    SECOND_ENCODER_POSITION = readEncoderPosition(digitalRead(SECOND_ENCODER_PIN_C), digitalRead(SECOND_ENCODER_PIN_D));

    int sum = (FIRST_ENCODER_FORMAL_POSITION << 2) | FIRST_ENCODER_POSITION;
    int sum2 = (SECOND_ENCODER_FORMAL_POSITION << 2) | SECOND_ENCODER_POSITION;


    
    // Update the first encoder position based on the direction
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
      FIRST_ENCODER_POSITION++;
    } else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
      FIRST_ENCODER_POSITION--;
    }

    // Update the second encoder position based on the direction
    if (sum2 == 0b1101 || sum2 == 0b0100 || sum2 == 0b0010 || sum2 == 0b1011) {
      SECOND_ENCODER_POSITION++;
    } else if (sum2 == 0b1110 || sum2 == 0b0111 || sum2 == 0b0001 || sum2 == 0b1000) {
      SECOND_ENCODER_POSITION--;
    }


    // Calculate relative positions in degrees
    FIRST_ENCODER_DEGREE = ((float)FIRST_ENCODER_POSITION - FIRST_ENCODER_DEGREE_CONSTANT) / PPR * 360.0;
    SECOND_ENCODER_DEGREE = ((float)SECOND_ENCODER_POSITION - SECOND_ENCODER_DEGREE_CONSTANT) / PPR * 360.0;


    //CLOCKWISE
    if(FIRST_ENCODER_DEGREE >= FIRST_MAX_DEGREE){
      Serial.println("DIRECTION_TYPE:BACKWARD");
      delay(500);
    }else if(FIRST_ENCODER_DEGREE <= FIRST_MIN_DEGREE){
      Serial.println("DIRECTION_TYPE:FORWARD");
      delay(500);
    }


    //ANTI-CLOCKWISE
    if(SECOND_ENCODER_DEGREE >= SECOND_MAX_DEGREE){
      Serial.println("DIRECTION_TYPE:FORWARD");
      delay(500);
    }else if(SECOND_ENCODER_DEGREE <= SECOND_MIN_DEGREE){
      Serial.println("DIRECTION_TYPE:BACKWARD");
      delay(500);
    }




    //To USB-TTL
    unsigned long currentTime = millis();

    // First encoder speed
    unsigned long elapsedTime1 = currentTime - FIRST_ENCODER_LAST_TIME;
    FIRST_ENCODER_SPEED = (FIRST_ENCODER_POSITION - FIRST_ENCODER_FORMAL_POSITION) / (float)elapsedTime1*1000;

    // Second encoder speed
    unsigned long elapsedTime2 = currentTime - SECOND_ENCODER_LAST_TIME;
    SECOND_ENCODER_SPEED = (SECOND_ENCODER_POSITION - SECOND_ENCODER_FORMAL_POSITION) / (float)elapsedTime2*1000;

    // Convert encoder speeds to meters per second
    float FIRST_ENCODER_SPEED_MS = (SECOND_ENCODER_SPEED * distancePerPulse_M);
    float SECOND_ENCODER_SPEED_MS = (SECOND_ENCODER_SPEED * distancePerPulse_M);


    //set old values
    FIRST_ENCODER_FORMAL_POSITION = FIRST_ENCODER_POSITION;
    SECOND_ENCODER_FORMAL_POSITION = SECOND_ENCODER_POSITION;
    FIRST_ENCODER_LAST_TIME=currentTime;
    SECOND_ENCODER_LAST_TIME=currentTime;
    
    Serial.println("");
    Serial.print("First encoder position (degree): ");
    Serial.println(FIRST_ENCODER_DEGREE);
    Serial.print("First encoder speed (m/s): ");
    Serial.println(FIRST_ENCODER_SPEED_MS);

    Serial.println("");
    Serial.print("Second encoder position (degree): ");
    Serial.println(SECOND_ENCODER_DEGREE);
    Serial.print("Second encoder speed (m/s): ");
    Serial.println(SECOND_ENCODER_SPEED_MS);

  }
}



int readEncoderPosition(int AS, int BS) {
  int encoded = (AS << 1) | BS;
  return encoded;
}


void loop() {
 if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    // Serial.println("Received message: " + message);
  }
}
