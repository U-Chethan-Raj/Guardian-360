// ===============================
// Arduino UNO Code (Main Control)
// ===============================
// Responsibilities:
// - Gas & flame detection
// - Location via GPS
// - SMS alert via SIM800L
// - Local voice alert via DFPlayer Mini

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial sim800(7, 8);       // SIM800L
SoftwareSerial gpsSerial(4, 3);    // GPS
SoftwareSerial dfSerial(10, 11);   // DFPlayer Mini

TinyGPSPlus gps;
DFRobotDFPlayerMini dfplayer;

#define GAS_SENSOR A0
#define FLAME_SENSOR A1
#define RED_LED 2
#define BUZZER 5

bool sosSent = false;

void setup() {
  Serial.begin(9600);
  sim800.begin(9600);
  gpsSerial.begin(9600);
  dfSerial.begin(9600);

  pinMode(GAS_SENSOR, INPUT);
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  sendATCommand("AT");
  sendATCommand("AT+CMGF=1");

  if (!dfplayer.begin(dfSerial)) {
    Serial.println("DFPlayer Mini not found!");
  } else {
    dfplayer.volume(20);
  }
}

void loop() {
  int gasVal = analogRead(GAS_SENSOR);
  int flameVal = analogRead(FLAME_SENSOR);

  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if ((gasVal > 300 || flameVal < 500) && gps.location.isUpdated() && !sosSent) {
    digitalWrite(RED_LED, HIGH);
    playSirenTone();  // Play emergency wailing tone

    String loc = "https://maps.google.com/?q=" + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
    String msg = "\n\n\t\uD83D\uDEA8 EMERGENCY DETECTED \uD83D\uDEA8\n";
    if (gasVal > 300) {
      msg += "Gas Leakage Detected\n";
      dfplayer.play(1); // 001.mp3
    }
    if (flameVal < 500) {
      msg += "Fire Detected\n";
      dfplayer.play(2); // 002.mp3
    }
    if (gasVal > 300 && flameVal < 500) {
      dfplayer.play(3); // 003.mp3
    }
    msg += "Location: " + loc + "\n";
    msg += "Automated voice alert activated.";

    sendSMS("+911122334455", msg);
    sendSMS("+911000000000", msg);
    sendSMS("+91xxxxxxxxxx", msg);

    sosSent = true;
  }
  delay(1000);
}

void sendATCommand(String cmd) {
  sim800.println(cmd);
  delay(1000);
}

void sendSMS(String number, String text) {
  sim800.println("AT+CMGS=\"" + number + "\"");
  delay(1000);
  sim800.println(text);
  sim800.write(26);
  delay(5000);
}

void playSirenTone() {
  for (int i = 500; i <= 1000; i += 10) {
    tone(BUZZER, i);
    delay(5);
  }
  for (int i = 1000; i >= 500; i -= 10) {
    tone(BUZZER, i);
    delay(5);
  }
}
 
