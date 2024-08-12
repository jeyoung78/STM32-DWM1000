// Motor control pins
const int motorPin1_motor1 = 2;  // Input 1 on the L293B
const int motorPin2_motor1 = 4;  // Input 2 on the L293B
const int enablePin_motor1 = 3;  // Enable Pin on L293B to control speed

const int motorPin1_motor2 = 7;  // Input 1 on the L293B
const int motorPin2_motor2 = 8;  // Input 2 on the L293B
const int enablePin_motor2 = 6;  // Enable Pin on L293B to control speed

const int motorPin1_motor3 = 12;  // Input 1 on the L293B
const int motorPin2_motor3 = 13;  // Input 2 on the L293B
const int enablePin_motor3 = 11;  // Enable Pin on L293B to control speed

const int motorPin1_motor4 = 9;  // Input 1 on the L293B
const int motorPin2_motor4 = 10;  // Input 2 on the L293B
const int enablePin_motor4 = 5;  // Enable Pin on L293B to control speed

const int MAX_SIZE = 3;

int arr[MAX_SIZE];
int currentSize = 0;

void setup() {
  // Set motor pins as output
  pinMode(motorPin1_motor1, OUTPUT);
  pinMode(motorPin2_motor1, OUTPUT);
  pinMode(enablePin_motor1, OUTPUT);

  pinMode(motorPin1_motor2, OUTPUT);
  pinMode(motorPin2_motor2, OUTPUT);
  pinMode(enablePin_motor2, OUTPUT);

  pinMode(motorPin1_motor3, OUTPUT);
  pinMode(motorPin2_motor3, OUTPUT);
  pinMode(enablePin_motor3, OUTPUT);

  pinMode(motorPin1_motor4, OUTPUT);
  pinMode(motorPin2_motor4, OUTPUT);
  pinMode(enablePin_motor4, OUTPUT);

  // Start the serial communication with the ESP32
  Serial.begin(9600);
  // Start the serial communication with the computer (optional, for debugging)
  Serial.begin(9600);
}

void move_forward(int speed, bool direction) {
  if (direction == true) {
    // Set motor speed and direction
    digitalWrite(motorPin1_motor1, HIGH); // Forward
    digitalWrite(motorPin2_motor1, LOW); 
    analogWrite(enablePin_motor1, speed);

    digitalWrite(motorPin1_motor3, LOW); // Forward
    digitalWrite(motorPin2_motor3, HIGH); 
    analogWrite(enablePin_motor3, speed);
  }
  else {
    // Set motor speed and direction
    digitalWrite(motorPin1_motor1, LOW); // Forward
    digitalWrite(motorPin2_motor1, HIGH); 
    analogWrite(enablePin_motor1, speed);

    digitalWrite(motorPin1_motor3, HIGH); // Forward
    digitalWrite(motorPin2_motor3, LOW); 
    analogWrite(enablePin_motor3, speed);
  }
}

void move_sideway(int speed, bool direction) {
  if (direction == true) {
    // Set motor speed and direction
    digitalWrite(motorPin1_motor2, HIGH); // Forward
    digitalWrite(motorPin2_motor2, LOW); 
    analogWrite(enablePin_motor2, speed);

    digitalWrite(motorPin1_motor4, LOW); // Forward
    digitalWrite(motorPin2_motor4, HIGH); 
    analogWrite(enablePin_motor4, speed);
  }
  else {
    // Set motor speed and direction
    digitalWrite(motorPin1_motor2, LOW); // Forward
    digitalWrite(motorPin2_motor2, HIGH); 
    analogWrite(enablePin_motor2, speed);

    digitalWrite(motorPin1_motor4, HIGH); // Forward
    digitalWrite(motorPin2_motor4, LOW); 
    analogWrite(enablePin_motor4, speed);
  }
}

void stop() {
  digitalWrite(motorPin1_motor1, LOW); // Forward
  digitalWrite(motorPin2_motor1, LOW); 
  analogWrite(enablePin_motor1, 0);

  digitalWrite(motorPin1_motor3, LOW); // Forward
  digitalWrite(motorPin2_motor3, LOW); 
  analogWrite(enablePin_motor3, 0);

  // Set motor speed and direction
  digitalWrite(motorPin1_motor2, LOW); // Forward
  digitalWrite(motorPin2_motor2, LOW); 
  analogWrite(enablePin_motor2, 0);

  digitalWrite(motorPin1_motor4, LOW); // Forward
  digitalWrite(motorPin2_motor4, LOW); 
  analogWrite(enablePin_motor4, 0);
}

void loop() {
  // Check if data is available to read
  if (Serial.available()) {
    // Read the incoming data
    String data = Serial.readStringUntil('\n');
    // Print the data to the serial monitor
    Serial.println("Received: " + data);

    // Split the data by commas
    int index1 = data.indexOf(',');
    int index2 = data.indexOf(',', index1 + 1);

    int functionId = data.substring(0, index1).toInt();
    int param1 = data.substring(index1 + 1, index2).toInt();
    int param2 = data.substring(index2 + 1).toInt();

    // Call the appropriate function based on functionId
    if (functionId == 1) {
      stop();
      move_forward(param1, param2);
    } else if (functionId == 2) {
      stop();
      move_sideway(param1, param2);
    } else {
      stop();
    }
  }
}
