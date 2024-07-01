/*IRremoteESP8266:demonstrates sending IR codes with IRsend.*/
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
const uint16_t kIrLed = 27;  //GPIO pin. Recommended: 4 (D2).
IRsend irsend=IRsend(kIrLed);  // Set the GPIO to be used.
uint16_t rawData[35] = {  7000,4760,280,560,280,1400,280,560,280,1400,280,560,280,1400,280,560,280,1400,280,560,280,1400,280,560,280,560,280,1400,280,1400,280,1400,280,1400,280
};

void setup() {
  irsend.begin();
  Serial.begin(115200);
}

void loop() {
  Serial.println("Sending a rawData.");
  irsend.sendRaw(rawData, 35, 38);  //Send a raw data at 38kHz.
  delay(5000);
}
