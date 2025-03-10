#define IR_SENSOR_RIGHT 3
#define IR_SENSOR_LEFT 2

// #define MOTOR_SPEED 120 // Default speed
// #define TURN_SPEED 150 // Speed during turns
// #define PIVOT_SPEED 80 // Speed for the opposite motor during turns

#define MOTOR_SPEED 200 // Default speed
#define TURN_SPEED 255 // Max speed for turns
#define PIVOT_SPEED 150 // Higher pivot speed for better turning


// Right motor
int enableRightMotor = 9;
int rightMotorPin1 = 4;
int rightMotorPin2 = 5;

// Left motor
int enableLeftMotor = 10;
int leftMotorPin1 = 6;
int leftMotorPin2 = 7;

void setup()
{
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  Serial.begin(9600);

  rotateMotor(MOTOR_SPEED, MOTOR_SPEED); // Start moving forward immediately
}

void loop()
{
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  Serial.print("Right: ");
  Serial.print(rightIRSensorValue);
  Serial.print(" | Left: ");
  Serial.println(leftIRSensorValue);

  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
  {
    // Move forward
    Serial.println("Moving Forward");
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW)
  {
    // Turn left - Increase left motor speed while moving the right motor backward at a lower speed
    Serial.println("Turning Left");
    rotateMotor(-PIVOT_SPEED, TURN_SPEED);
  }
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH)
  {
    // Turn right - Increase right motor speed while moving the left motor backward at a lower speed
    Serial.println("Turning Right");
    rotateMotor(TURN_SPEED, -PIVOT_SPEED);
  }
  else 
  {
    // If sensors detect nothing (both HIGH), keep moving forward
    Serial.println("No Detection, Keep Moving Forward");
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  // Right motor control
  digitalWrite(rightMotorPin1, rightMotorSpeed > 0 ? HIGH : LOW);
  digitalWrite(rightMotorPin2, rightMotorSpeed < 0 ? HIGH : LOW);
  
  // Left motor control
  digitalWrite(leftMotorPin1, leftMotorSpeed > 0 ? HIGH : LOW);
  digitalWrite(leftMotorPin2, leftMotorSpeed < 0 ? HIGH : LOW);
  
  // Set motor speeds
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}
