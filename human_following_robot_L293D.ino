// Human Following Robot with L293D Motor Driver
// Make A Creativity - Rushanthan

#include <NewPing.h>
#include <Servo.h>

// Pin definitions
#define CENTER_IR A2           // Center IR sensor
#define TRIGGER_PIN A1         // Ultrasonic trigger
#define ECHO_PIN A0            // Ultrasonic echo
#define MAX_DISTANCE 200       // Max distance for ultrasonic

// L293D Motor Driver Pins
#define MOTOR1_PIN1 2          // Motor 1 direction pin 1
#define MOTOR1_PIN2 3          // Motor 1 direction pin 2
#define MOTOR1_ENABLE 5        // Motor 1 speed control (PWM)

#define MOTOR2_PIN1 4          // Motor 2 direction pin 1
#define MOTOR2_PIN2 7          // Motor 2 direction pin 2
#define MOTOR2_ENABLE 6        // Motor 2 speed control (PWM)

#define MOTOR3_PIN1 8          // Motor 3 direction pin 1
#define MOTOR3_PIN2 9          // Motor 3 direction pin 2
#define MOTOR3_ENABLE 10       // Motor 3 speed control (PWM)

#define MOTOR4_PIN1 11         // Motor 4 direction pin 1
#define MOTOR4_PIN2 12         // Motor 4 direction pin 2
#define MOTOR4_ENABLE 13       // Motor 4 speed control (PWM)

// Sensor variables
unsigned int distance = 0;
unsigned int Center_Value = 0;

// Initialize ultrasonic sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Servo setup for robot hands
Servo leftHandServo;
Servo rightHandServo;

int leftHandPos = 90;
int rightHandPos = 90;
bool swingDirection = true;  // true = up, false = down

void setup() {
  Serial.begin(9600);

  // Initialize motor pins
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR1_ENABLE, OUTPUT);
  
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  pinMode(MOTOR2_ENABLE, OUTPUT);
  
  pinMode(MOTOR3_PIN1, OUTPUT);
  pinMode(MOTOR3_PIN2, OUTPUT);
  pinMode(MOTOR3_ENABLE, OUTPUT);
  
  pinMode(MOTOR4_PIN1, OUTPUT);
  pinMode(MOTOR4_PIN2, OUTPUT);
  pinMode(MOTOR4_ENABLE, OUTPUT);

  // Attach servo motors (using different pins since motor driver uses many pins)
  leftHandServo.attach(A3);   // Connect left hand servo to pin A3
  rightHandServo.attach(A4);  // Connect right hand servo to pin A4

  // Set initial hand positions
  leftHandServo.write(leftHandPos);
  rightHandServo.write(rightHandPos);

  pinMode(CENTER_IR, INPUT); // Set IR pin as input
  
  // Stop all motors initially
  stopMotors();
}

void loop() {
  delay(50);  // Delay between readings
  distance = sonar.ping_cm();
  Center_Value = digitalRead(CENTER_IR);

  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("IR Center: ");
  Serial.println(Center_Value);

  if ((distance > 1) && (distance < 15) && (Center_Value == 1)) {
    // Move Forward
    moveForward(130);

    // Swing hands while walking
    if (swingDirection) {
      leftHandPos = 60;
      rightHandPos = 120;
    } else {
      leftHandPos = 120;
      rightHandPos = 60;
    }
    leftHandServo.write(leftHandPos);
    rightHandServo.write(rightHandPos);
    swingDirection = !swingDirection;
    delay(300);  // Delay to simulate walking motion

  } else if (distance > 15 || Center_Value == 0) {
    // Stop
    stopMotors();

    // Reset hand position
    leftHandServo.write(90);
    rightHandServo.write(90);
  }
}

// Function to move forward
void moveForward(int speed) {
  // Motor 1 - Forward
  digitalWrite(MOTOR1_PIN1, HIGH);
  digitalWrite(MOTOR1_PIN2, LOW);
  analogWrite(MOTOR1_ENABLE, speed);
  
  // Motor 2 - Forward
  digitalWrite(MOTOR2_PIN1, HIGH);
  digitalWrite(MOTOR2_PIN2, LOW);
  analogWrite(MOTOR2_ENABLE, speed);
  
  // Motor 3 - Forward
  digitalWrite(MOTOR3_PIN1, HIGH);
  digitalWrite(MOTOR3_PIN2, LOW);
  analogWrite(MOTOR3_ENABLE, speed);
  
  // Motor 4 - Forward
  digitalWrite(MOTOR4_PIN1, HIGH);
  digitalWrite(MOTOR4_PIN2, LOW);
  analogWrite(MOTOR4_ENABLE, speed);
}

// Function to stop all motors
void stopMotors() {
  // Stop Motor 1
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, LOW);
  analogWrite(MOTOR1_ENABLE, 0);
  
  // Stop Motor 2
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, LOW);
  analogWrite(MOTOR2_ENABLE, 0);
  
  // Stop Motor 3
  digitalWrite(MOTOR3_PIN1, LOW);
  digitalWrite(MOTOR3_PIN2, LOW);
  analogWrite(MOTOR3_ENABLE, 0);
  
  // Stop Motor 4
  digitalWrite(MOTOR4_PIN1, LOW);
  digitalWrite(MOTOR4_PIN2, LOW);
  analogWrite(MOTOR4_ENABLE, 0);
}