#include <WiFi.h>
#include <HTTPClient.h>
const char* situ = "ごみ箱が満杯です";
int id = 1;

const char* ssid = "CampusIoT-WiFi";
const char* password =  "0b8b413f2c0fa6aa90e085e9431abbf1fa1b2bd2db0ecf4ae9ce4b2e87da770c";
const char* url =  "http://localhost/backet/receive.php";
String payload_pattern = "{\"id\":\""+String(id)+"\",\"situ\":\""+situ+"\"}";


void setup() {
 
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
   
  //float temperature = 23.456;
  //float humidity = 80.21;
  String payload = payload_pattern;
  //payload.replace("$temperature$",String(temperature));
  //payload.replace("$humidity$",String(humidity));
  //payload.replace("$counter$",String(counter));
 
  if(WiFi.status()== WL_CONNECTED){ 
 
    HTTPClient http;   
 
    http.begin(url);  
    int httpResponseCode = http.POST(payload); 
 
    if(httpResponseCode>0){
      String response = http.getString(); 
      Serial.println(httpResponseCode);
      Serial.println(response);
    }else{
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }
    http.end();
 
  }else{
 
    Serial.println("Error in WiFi connection");   
 
  }
 
  delay(1000);  //Send a request every second
 
}

void loop() {
}
