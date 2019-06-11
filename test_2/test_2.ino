#include <Encoder.h>
// ロータリーエンコーダ用ライブラリ導入

// ライブラリのリファレンスページ https://www.pjrc.com/teensy/td_libs_Encoder.html
// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

// エンコーダ接続ピン指定:2=緑, 3=茶, GND=黄
Encoder knobMain(2, 3);
//   avoid using pins with LEDs attached

//各種ピン番号を定数に.
#define cautionLED 4
#define LeftLED 5
#define RightLED 6
#define sw 7

void setup() {
  Serial.begin(9600);
//  Serial.println("TwoKnobs Encoder Test:");
  pinMode(LeftLED, OUTPUT); //左LED
  pinMode(RightLED, OUTPUT); //右LED
  pinMode(cautionLED, OUTPUT); //警告用LED
  pinMode(sw, INPUT); //エンコーダ値リセットスイッチ
}
// 古い値の定義？
long positionMain  = -999;
//新しいエンコーダ値のもとの変数定義
long newMain;

void loop() {
  //新しいエンコーダの値を代入
  newMain = knobMain.read();
  //前の値と変わったら処理
  if (newMain != positionMain) {
    rotation();
    // エンコーダ値をモニタに映す←はblender対応のためコメント化
//    Serial.print("Now Encoder = ");
//    Serial.print(newMain);
//    Serial.println();
    positionMain = newMain;

  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  // シリアルモニタから何らかの文字列を受け取ったら今までの値をリセットする
  if (digitalRead(sw) == HIGH) {
    Serial.read();
    Serial.println("Reset encoder by switch");
    // 以下でロータリーエンコーダ値を上書き(ただしエンコーダライブラリを入れていないとこの機能は使用不可)
    knobMain.write(0);
    digitalWrite(cautionLED, LOW);
  }
  //エンコーダ値警告
   int danger = 100;
  //正負問わず、上で定義した数値を超えたら赤LEDで警告する
   if(newMain >= danger && newMain > 0){
    digitalWrite(cautionLED, HIGH);
    }else if(newMain <= -(danger) && newMain < 0){
    digitalWrite(cautionLED, HIGH);
   }else{
    digitalWrite(cautionLED, LOW);
   }
}

// エンコーダ左右振り分け
void rotation(){
  //点灯&消灯時間
  int SetTime = 10;
  // 左回りの処理
  // newMainが前回の値より小さかったら
  if(newMain < positionMain){
    //LEDとBlenderへ渡す値を出す
        digitalWrite(LeftLED, HIGH);
        digitalWrite(RightLED, LOW);
        Serial.println("-0.5");
        delay(SetTime);
    //LEDを光らせすぎないように消している
        digitalWrite(LeftLED, LOW);
        digitalWrite(RightLED, LOW);
        delay(SetTime);
  // 右回りの処理
  }else if(newMain > positionMain){
  //左回りと同様に
        digitalWrite(LeftLED, LOW);
        digitalWrite(RightLED, HIGH);
        delay(SetTime);
        digitalWrite(LeftLED, LOW);
        digitalWrite(RightLED, LOW);
        delay(SetTime);
        Serial.println("+0.5");
      }
  }
