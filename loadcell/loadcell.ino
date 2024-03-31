#include "HX711.h"
// Define the HX711 circuit and calibration factor
HX711 scale;

// Pin configuration
const int DOUT_PIN = 2;
const int SCK_PIN = 3;
const int MOTION_PIN = 4; //
int FORCE_THRESHOLD = 2; // ADJUSTABLE

// Calibration factor, adjust this based on your load cell and known weight
const float calibration_factor = 34000;

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale(calibration_factor);
  pinMode(MOTION_PIN, OUTPUT);
  digitalWrite(MOTION_PIN, LOW);
}
 
void loop() {
  //READING WEIGHT 
  float force = scale.get_units(10)*2;//two load cells

  if(force >= FORCE_THRESHOLD && digitalRead(MOTION_PIN) == LOW){
    // START MOTION
    digitalWrite(MOTION_PIN, HIGH); 
  }

  Serial.print("Force: ");
  Serial.print(force);
  Serial.println(" N");
if(force > FORCE_THRESHOLD){
    Serial.println("Force is above threshold, system has began motion");
  }else{
    Serial.println("Force is below threshold, system is static");
  }
}
