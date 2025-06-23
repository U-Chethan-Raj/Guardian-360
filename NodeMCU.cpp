// ===============================
// NodeMCU Code (Wi-Fi / Blynk)
// ===============================
// Responsibilities:
// - Motion detection via PIR
// - Take snapshot with ESP32-CAM (or host IP)
// - Upload snapshot to imgbb
// - Send Blynk notification with image link

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <base64.h>

#define PIR_PIN D1
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
const String blynk_token = "YOUR_BLYNK_TOKEN";
const String imgbb_key = "YOUR_IMGBB_API_KEY";

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("WiFi connected");
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    Serial.println("Motion Detected!");
    String imageURL = captureSnapshot();
    if (imageURL != "") {
      sendBlynkAlert(imageURL);
    }
    delay(10000); // prevent flooding
  }
  delay(500);
}

String captureSnapshot() {
  // Replace with actual ESP32-CAM image capture or link snapshot
  String image = "dummy_base64_data_here";
  HTTPClient http;
  http.begin("https://api.imgbb.com/1/upload?key=" + imgbb_key);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int code = http.POST("image=" + image);
  String res = http.getString();
  http.end();

  if (code == 200 && res.indexOf("url") > 0) {
    int start = res.indexOf("\"url\":\"") + 7;
    int end = res.indexOf("\"", start);
    return res.substring(start, end).replace("\\/", "/");
  }
  return "";
}

void sendBlynkAlert(String imageURL) {
  HTTPClient http;
  http.begin("https://blynk.cloud/external/api/update?token=" + blynk_token + "&V1=" + imageURL);
  http.GET();
  http.end();

  http.begin("https://blynk.cloud/external/api/notify?token=" + blynk_token + "&message=Motion+detected+with+snapshot");
  http.GET();
  http.end();
}