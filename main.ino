#include "esp_camera.h"
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include "FS.h"
#include "SD_MMC.h"

// Pin Definitions
#define GPS_RX 16
#define GPS_TX 17
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  // Initialize Camera (Model AI_THINKER)
  camera_config_t config;
  // ... (insert standard camera_config settings here)
  esp_err_t err = esp_camera_init(&config);
  
  if (err != ESP_OK) {
    Serial.println("CAMERA STATUS: [FAIL]");
    return;
  }
  Serial.println("CAMERA STATUS: [OK]");

  // Initialize SD Card
  if(!SD_MMC.begin()){
    Serial.println("STORAGE STATUS: [ERROR: NO SD CARD]");
  } else {
    Serial.println("STORAGE STATUS: [SD CARD DETECTED]");
  }
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isUpdated()) {
        Serial.print("GPS DATA: ");
        Serial.print(gps.location.lat(), 6);
        Serial.print(",");
        Serial.println(gps.location.lng(), 6);
        
        // Trigger capture function here
      }
    }
  }
}
