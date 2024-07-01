// 赤外線リモコンのデータ受信
 
// IRRemoteライブラリのインクルード
#include <IRremote.h>
 
// 受信PIN設定
int ReceivePin = 14; 
 
// オブジェクト生成
IRrecv irrecv(ReceivePin);   // IRrecv
decode_results results;     // decode_results
 
void setup() {
  // put your setup code here, to run once:
  // シリアルポート設定
  Serial.begin(115200); 
  // 赤外線受信機モジュール起動
  irrecv.enableIRIn();
  // 起動待機
  delay(500);   // 500ms停止
}
 
void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)){   //　受信情報あり
    // シリアルモニタへ受信情報表示
    Serial.print("Code: "); 
    Serial.print(results.value, HEX); // 受信値を16進数で値を出力
    Serial.print(",  bits: ");
    Serial.println(results.bits);     // 受信値長をビット数を出力
  // 指定キーの判定
    if( results.value == 0xB8B4F137 ){  // 上キー(FF18E7)
      Serial.println("上キー");
    }
    
    // モジュールの復帰    
    irrecv.resume();
  }  
  delay(1000); // 1000ミリ秒停止
}
