// Define the pins for the joystick
const int X_PIN = A0; // Analog pin for X-axis
const int Y_PIN = A1; // Analog pin for Y-axis

// Define the pin for the motor driver
const int MOTOR_SPEED_PIN = 6; // PWM pin for motor speed control
const int MOTOR_DIRECTION_PIN = 7; // Direction pin for motor

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);

  // Set motor pins as outputs
  pinMode(MOTOR_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_DIRECTION_PIN, OUTPUT);
}

void loop() {
  // Read joystick values
  int yValue = analogRead(Y_PIN);

  // Map the Y value to a motor speed and direction
  int motorSpeed;
  int motorDirection;

  if (yValue > 550) { // Joystick moved up
    motorSpeed = map(yValue, 550, 1023, 0, 255);
    motorDirection = LOW; // Forward
  } else if (yValue < 470) { // Joystick moved down
    motorSpeed = map(yValue, 470, 0, 0, 255);
    motorDirection = HIGH; // Reverse
  } else { // Joystick at center
    motorSpeed = 0;
  }

  // Set the motor speed and direction
  analogWrite(MOTOR_SPEED_PIN, motorSpeed);
  digitalWrite(MOTOR_DIRECTION_PIN, motorDirection);

  // Print the joystick values and motor speed to the serial monitor
  Serial.print("Y = ");
  Serial.print(yValue);
  Serial.print(", Motor speed = ");
  Serial.println(motorSpeed);

  // Wait a bit before the next reading
  delay(100);
}
