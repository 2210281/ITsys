#include <IRremote.h>

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  20      /* Time ESP32 will go to sleep (in seconds) */
int flag = 0; //フラグ関数
unsigned long startTime;  //最初の時間記録
unsigned long currentTime; //今の時間記録
const unsigned long period = 10000; //キープ時間

int receiverPin = 14;
RTC_DATA_ATTR int bootCount = 0;

void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}

void setup() {
  Serial.begin(115200);

  IrReceiver.begin(receiverPin, true);
  pinMode(ledPin, OUTPUT);
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  print_wakeup_reason();
  startTime = millis(); //最初の時間記録


  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush();
  Serial.println("This will never be printed");
}

void loop() {
  currentTime = millis(); //今の時間を記録
  digitalWrite(ledPin, HIGH);
  delay(1000);
  if (IrReceiver.decode() == true) {

    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();
  } else {
    if (flag == 0) {
      Serial.println("満杯");
      flag = 1;
    } else {
      flag = 0;
    }
  }
  if (currentTime - startTime >= period) {
    startTime = currentTime;
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                   " Seconds");

    Serial.println("おやすみなさい");
    esp_deep_sleep_start();
  }
}
