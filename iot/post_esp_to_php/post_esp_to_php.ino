// ---------------------------------------------------------------
/*
  http_post.ino

          Jul/25/2023
*/
// ---------------------------------------------------------------
#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

WiFiServer server(80);
HTTPClient http;

const char *ssid = "CampusIoT-WiFi";
const char *password = "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";

int count = 0;

// ---------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  Serial.println("*** setup start ***");
  Serial.print("Connecting...");
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println("connected");
  Serial.println(WiFi.localIP());
  server.begin();
  delay(3000);
  Serial.println("*** setup *** aaa ***");
  delay(1000);

  Serial.println("*** setup ***");
}

// ---------------------------------------------------------------
void loop()
{
  Serial.println("*** loop *** " + String(count));
  delay(2000);
  String url_target = "http://127.0.0.1/backet/receive.php";
  http_post_proc(url_target);
  delay(3000);
  count++;
}

// ---------------------------------------------------------------
void http_post_proc(String url_target)
{
  DynamicJsonDocument doc(128);
  char data_json[128];

  doc["id"] = "1";
  doc["situ"] = "このごみ箱は満杯です。";
  serializeJson(doc, data_json);

  if((WiFi.status() == WL_CONNECTED)) {
    Serial.print("[HTTP] begin...\n");
    http.begin(url_target);
    Serial.print("[HTTP] POST...\n");
    int httpCode = http.POST((uint8_t*)data_json, strlen(data_json));
    if(httpCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        }
      }else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
    http.end();
  }
  else
    {
    Serial.print("connect failed");
    }
}

// ---------------------------------------------------------------
