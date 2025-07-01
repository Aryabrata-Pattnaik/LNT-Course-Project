#include <Servo.h>

// Servo objects
Servo servoX;  // Horizontal
Servo servoY;  // Vertical

// LDR pins
int ldrTopLeft = A0;
int ldrTopRight = A1;
int ldrBottomLeft = A2;
int ldrBottomRight = A3;

// Servo positions
int posX = 90;  // Initial positions
int posY = 90;

void setup() {
  servoX.attach(9);  // Horizontal servo on pin 9
  servoY.attach(10); // Vertical servo on pin 10

  servoX.write(posX);
  servoY.write(posY);

  // Serial for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Read LDR values
  int tl = analogRead(ldrTopLeft);
  int tr = analogRead(ldrTopRight);
  int bl = analogRead(ldrBottomLeft);
  int br = analogRead(ldrBottomRight);

  // Averages
  int topAvg = (tl + tr) / 2;
  int bottomAvg = (bl + br) / 2;
  int leftAvg = (tl + bl) / 2;
  int rightAvg = (tr + br) / 2;

  int threshold = 50;  // Sensitivity threshold

  // Vertical movement
  if (abs(topAvg - bottomAvg) > threshold) {
    if (topAvg > bottomAvg && posY < 180) {
      posY++;
    } else if (bottomAvg > topAvg && posY > 0) {
      posY--;
    }
    servoY.write(posY);
  }

  // Horizontal movement
  if (abs(leftAvg - rightAvg) > threshold) {
    if (leftAvg > rightAvg && posX > 0) {
      posX--;
    } else if (rightAvg > leftAvg && posX < 180) {
      posX++;
    }
    servoX.write(posX);
  }

  delay(100);  // Stabilize readings
}
