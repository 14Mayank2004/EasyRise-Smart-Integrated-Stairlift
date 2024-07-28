// Define the pins for the joystick
const int X_PIN = A0; // Analog pin for X-axis
const int Y_PIN = A1; // Analog pin for Y-axis

// Define the pin for the motor driver
const int MOTOR_SPEED_PIN = 9; // PWM pin for motor speed control
const int MOTOR_DIRECTION_PIN = 8; // Direction pin for motor

// Define the pins for the ultrasonic sensors
const int TRIGGER_PIN1 = 2; // Trigger pin for ultrasonic sensor 1
const int ECHO_PIN1 = 3; // Echo pin for ultrasonic sensor 1
const int TRIGGER_PIN2 = 4; // Trigger pin for ultrasonic sensor 2
const int ECHO_PIN2 = 5; // Echo pin for ultrasonic sensor 2

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);

  // Set motor pins as outputs
  pinMode(MOTOR_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_DIRECTION_PIN, OUTPUT);

  // Set ultrasonic sensor pins as output/input
  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
}

void loop() {
  // Read joystick values
  int yValue = analogRead(Y_PIN);

  // Determine motor direction and initial speed based on joystick
  int motorSpeed;
  int motorDirection;
  if (yValue > 550) { // Joystick moved up
    motorSpeed = map(yValue, 550, 1023, 0, 255);
    motorDirection = HIGH; // Forward
  } else if (yValue < 470) { // Joystick moved down
    motorSpeed = map(yValue, 470, 0, 0, 255);
    motorDirection = LOW; // Reverse
  } else { // Joystick at center
    motorSpeed = 0;
  }

  // Measure distance from ultrasonic sensor 1
  digitalWrite(TRIGGER_PIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN1, LOW);
  long duration1 = pulseIn(ECHO_PIN1, HIGH);
  long distance1 = (duration1 / 2) / 29.1;

  // Measure distance from ultrasonic sensor 2
  digitalWrite(TRIGGER_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN2, LOW);
  long duration2 = pulseIn(ECHO_PIN2, HIGH);
  long distance2 = (duration2 / 2) / 29.1;

  // Adjust motor speed based on distance from objects
  if (distance1 < 20 || distance2 < 20) { // Object detected within 20 cm
    int obstacleSpeed = map(min(distance1, distance2), 5, 20, 0, 255);
    motorSpeed = min(motorSpeed, obstacleSpeed);
  }

  // Set the motor speed and direction
  analogWrite(MOTOR_SPEED_PIN, motorSpeed);
  digitalWrite(MOTOR_DIRECTION_PIN, motorDirection);

  // Print the joystick values, motor speed, and distances to the serial monitor
  Serial.print("Y = ");
  Serial.print(yValue);
  Serial.print(", Motor speed = ");
  Serial.print(motorSpeed);
  Serial.print(", Distance1 = ");
  Serial.print(distance1);
  Serial.print(", Distance2 = ");
  Serial.println(distance2);

  // Wait a bit before the next reading
  delay(100);
}
