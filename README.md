# PULSR: Stroke Survivor Arm Rehabilitation Project

## Overview

PULSR (Personalized Upper Limb Stroke Rehabilitation) is a project aimed at rehabilitating the arms of stroke survivors. It utilizes rotary encoders to monitor arm movement and load cells to measure force, coupled with motor control to provide resistance and assistance during rehabilitation exercises.

## Components

The project consists of the following components:

1. **Rotary Encoder Code**: Monitors the motion of the arm using rotary encoders and outputs direction and speed information over serial communication.

2. **Load Cell Code**: Interfaces with load cells to measure force exerted during arm movements and adjusts motor control accordingly.

3. **Motor Control Code**: Controls the motors to provide resistance and assistance based on the feedback received from the rotary encoders and load cells.

## Setup

### Hardware Requirements

- Rotary encoders for monitoring arm motion.
- Load cells to measure force exerted by the arm.
- Motors for providing resistance and assistance.
- Microcontroller (e.g., Arduino) to run the code.
- Connection wires and power supply.

### Software Requirements

- Arduino IDE or compatible software for programming the microcontroller.
- Necessary libraries for interfacing with rotary encoders, load cells, and serial communication.

## Installation

1. Connect the rotary encoders, load cells, and motors to the microcontroller as per the pin assignments specified in the code.
2. Upload the provided Arduino sketches (`Rotary_Encoder_Code`, `Load_Cell_Code`, `Motor_Control_Code`) to the microcontroller.
3. Ensure consistent baud rates for serial communication between the codes.
4. Power up the system and calibrate the load cells if necessary.

## Usage

1. Turn on the system and ensure all connections are secure.
2. Follow the instructions for positioning the arms and starting the rehabilitation exercises.
3. Monitor the feedback provided by the system through the serial monitor or any other visualization tool.
4. Adjust parameters as necessary to customize the rehabilitation program for individual users.
5. Ensure proper safety measures are in place during rehabilitation sessions.
