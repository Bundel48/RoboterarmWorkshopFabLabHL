#include <ESP8266WebServer.h>
#include <Servo.h>
#include "WLANDaten.h" ///< Deine Netzwerk Zugangsdaten
#include "index.h" ///< Code deiner Weboberflaeche

/// ********************************DEFINITION DER SERVOS*******************************************************
/// Erzeugung von Servo-Objekten zur Ansteuerung der unterschiedlichen Teile des Roboterarmes.
Servo baseServo;  ///< Servo der unteren Basisplatte.
Servo lowerArmServo; ///< Servo des unteren Armes.
Servo middleArmServo; ///< Servo des mittleren Armes.
Servo upperArmServo; ///< Servo des Endeffektors.

/// min/max Werte der Servomotoren, um Getriebe zu schonen
#define SERVOMIN 10
#define SERVOMAX 170

/// GPIOs zum Anschließen der Servomotoren.
static const int baseServoPin = 16; ///< D0
static const int lowerArmServoPin = 5; ///< D1
static const int middleArmServoPin = 4; ///< D2
static const int upperArmServoPin = 0; ///< D3

/// Strings, um HTTP-GET Werte der unterschiedlichen Servos zu speichern.
String baseValueString = String(90);
String lowerArmValueString = String(90);
String middleArmValueString = String(90);
String upperArmValueString = String(90);

/// ********************************************WEBSERVER***************************************
/// Webserver lauscht auf Port 80.
ESP8266WebServer server(80);

/// Definition einer festen IP-Adresse deiner Weboberflaeche (Optional)
IPAddress local_IP(192, 168, 188, 94);
IPAddress gateway(192, 168, 188, 1);
IPAddress subnet(255, 255, 0, 0);

/**
 * Verarbeitung der gesetzten Sensorwerte der Weboberflaeche. 
 */
void handleValue(){
  String newBaseServoValue = server.arg("baseServoPos");
  String newLowerArmServoValue = server.arg("lowerArmServoPos");
  String newMiddleArmServoValue = server.arg("middleArmServoPos");
  String newUpperArmServoValue = server.arg("upperArmServoPos");
  if ((newBaseServoValue != "") && (newBaseServoValue != baseValueString)){
    smoothServoMovement(newBaseServoValue.toInt(), baseValueString.toInt(), baseServo);
    baseValueString = newBaseServoValue;
  }

  if ((newLowerArmServoValue != "") && (newLowerArmServoValue != lowerArmValueString)){
    smoothServoMovement(newLowerArmServoValue.toInt(), lowerArmValueString.toInt(), lowerArmServo);
    lowerArmValueString = newLowerArmServoValue;
  }

  if ((newMiddleArmServoValue != "") && (newMiddleArmServoValue != middleArmValueString)){
    smoothServoMovement(newMiddleArmServoValue.toInt(), middleArmValueString.toInt(), middleArmServo);
    middleArmValueString = newMiddleArmServoValue;
  }

  if ((newUpperArmServoValue != "") && (newUpperArmServoValue != upperArmValueString)){
    smoothServoMovement(newUpperArmServoValue.toInt(), upperArmValueString.toInt(), upperArmServo);
    upperArmValueString = newUpperArmServoValue;
  }
  server.send(200, "text/plane", "OK");
}

/**
 * Weiche, schrittweise Bewegung des Servomotors.
 * 
 * @param newServoValue Ziel der Bewegung. Neuer Servowert.
 * @param currentServoValue Startpunkt der Bewegung. Aktueller Servowert.
 * @param currentServo Referenz auf Servo welcher bewegt werden soll. 
 */
void smoothServoMovement(int newServoValue, int currentServoValue, Servo currentServo){
  if( newServoValue <= SERVOMAX && newServoValue >= SERVOMIN){
    if( newServoValue <=  currentServoValue ){
      for( int servoPos = currentServoValue; servoPos >= newServoValue; servoPos--){
        currentServo.write(servoPos);
        delay(10);     
      }
    }else{
      for ( int servoPos = currentServoValue; servoPos <= newServoValue; servoPos++){
        currentServo.write(servoPos);
        delay(10);
      }
    }
    Serial.println(newServoValue);
  }else{
    Serial.println("Servo value out of range!");
  }
}
/**
 * Initialisierung der Servos,
 * Konfiguration und Starten des Webservers
 */
void setup() {
  /// Definition der Baudrate für Seriellen Monitor.
  Serial.begin(115200);
  
  /// Einbinden der Servomotoren an definierte PINs.
  baseServo.attach(baseServoPin);  
  lowerArmServo.attach(lowerArmServoPin); 
  middleArmServo.attach(middleArmServoPin); 
  upperArmServo.attach(upperArmServoPin); 

  smoothServoMovement(baseValueString.toInt(), baseServo.read(), baseServo);
  smoothServoMovement(lowerArmValueString.toInt(), lowerArmServo.read(), lowerArmServo);
  smoothServoMovement(middleArmValueString.toInt(), middleArmServo.read(), middleArmServo);
  smoothServoMovement(upperArmValueString.toInt(), upperArmServo.read(), upperArmServo);
  
/// ******************************WEBSERVER************************************************
  /// Setzen der festen IP-Adresse (Optional)
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  /** 
   *  Herstellung der WiFi Verbindung mit deinem privaten Heimnetzwerk (SSID = Netzwerkname).
   *  Muss zuvor in der Datei WLANDaten.h eingetragen werden.
   */
  Serial.print("Verbinde zu: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.print("Warte auf Verbindung. ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  /// Ausgabe der IP-Adresse im seriellen Monitor, unter der du deine Website erreichen kannst. 
  Serial.println("");
  Serial.println("WiFi verbunden!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  /// Einbinden der Weboberflaeche.
  server.on("/", [](){
    server.send(200, "text/html", webpage);
  });
  /// Handling der gesetzten Servowerte der Weboberflaeche.
  server.on("/setValue", handleValue);
  /// Starten des Webservers.
  server.begin();
}

/**
 * Kontinuierlich wiederholende Schleife des ESPs.
 */
void loop(){
  server.handleClient();
}
