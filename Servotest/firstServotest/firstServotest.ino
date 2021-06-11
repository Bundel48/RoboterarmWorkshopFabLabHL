/// Einbinden der Servo Bibliothek
#include <Servo.h>

/// Erzeugung von Servo-Objekten zur Ansteuerung
Servo myServo;

/// min/max Werte der Servomotoren, um Getriebe zu schonen
#define SERVOMIN 10
#define SERVOMAX 170

/// GPIOs zum Anschließen der Servomotoren.
static const int servoPin = 16; ///< D0


void setup() {
  // put your setup code here, to run once:
  /// Initialisierung der seriellen Ausgabe 
  Serial.begin(115200);

  myServo.attach(servoPin);
  /// Bewege Servo auf die Min-Position
  myServo.write(SERVOMIN);
  /// Ausgabe der Operation auf seriellem Monitor
  Serial.println("Servo auf Wert" + String(SERVOMIN) + "gesetzt!");
}

void loop() {
  // put your main code here, to run repeatedly:
  

}
